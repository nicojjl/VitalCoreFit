#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QMessageBox>
#include <QLineEdit>

// Librerías de Gráficos
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    catalogoAlimentos = cargarAlimentos("data/foods.json");
    listaDelDia.cabeza = nullptr;
    listaDelDia.cantidad = 0;


    if (cargarPerfil(perfilUsuario)) {
        cargarDatosUI();
        actualizarDashboardVisual();
    }

    ui->listaComidasHoy->setStyleSheet(
        "QListWidget { background-color: #1E2736; border-radius: 12px; border: 1px solid #2A3648; outline: none; }"
        "QListWidget::item { background-color: #0F1722; border-radius: 6px; border-left: 4px solid #00E676; margin-bottom: 5px; }"
        "QListWidget::item:hover { background-color: #2A3648; }"
        );

    ui->listaCardioHoy->setStyleSheet(ui->listaComidasHoy->styleSheet());

    ui->comboDiasRutina->clear();
    ui->comboDiasRutina->addItems({"Lunes (Push)", "Martes (Pull)", "Miércoles (Legs)", "Jueves (Push)", "Viernes (Pull)", "Sábado (Legs)"});

    configurarTablaRutinas();

    if (cargarPerfil(perfilUsuario)) {
        cargarDatosUI();
        actualizarDashboardVisual();
    }

    ui->inputTiempoCardio->setText("");
    ui->inputTiempoCardio->setPlaceholderText("Minutos de duración (ej. 30)");

    // Configuración del Manual
    ui->listaGuia->setStyleSheet(
        "QListWidget { background-color: transparent; border: none; outline: none; }"
        "QListWidget::item { padding: 10px; }"
        "QListWidget::item:selected { background-color: transparent; }"
        );
    ui->listaGuia->setWordWrap(true);
    ui->listaGuia->setSpacing(5);
    ui->listaGuia->setSelectionMode(QAbstractItemView::NoSelection);
    ui->listaGuia->setFocusPolicy(Qt::NoFocus);

    auto agregarTextoGuia = [this](QString texto, int tamanoLetra, QString colorHex, bool esBold) {
        QListWidgetItem *item = new QListWidgetItem(texto);
        QFont fuente("Segoe UI", tamanoLetra);
        fuente.setBold(esBold);
        item->setFont(fuente);
        item->setForeground(QColor(colorHex));
        ui->listaGuia->addItem(item);
    };

    agregarTextoGuia("Manual de VitalCoreFit", 24, "#00E5FF", true);
    agregarTextoGuia("1. Introducción", 18, "#00E676", true);
    agregarTextoGuia("Bienvenido a VitalCoreFit. Esta aplicación está diseñada para ayudarte a mantenerte fuerte, sano y con energía. No te preocupes por los números complejos, el sistema hará los cálculos por ti.\n", 14, "#FFFFFF", false);
    agregarTextoGuia("2. ¿Cómo funciona la Nutrición?", 18, "#00E676", true);
    agregarTextoGuia("Para mantener tu masa muscular y proteger tus huesos, necesitas comer suficientes Proteínas (carnes, huevos, legumbres). En la pestaña Nutrición, busca lo que comiste y hazle doble clic. El panel principal te mostrará una barra verde: esa es tu meta de proteínas del día. ¡Intenta llenarla!\n", 14, "#FFFFFF", false);
    agregarTextoGuia("3. Guía de Ejercicios Seguros", 18, "#00E676", true);
    agregarTextoGuia("El entrenamiento de fuerza previene caídas. Aquí tienes cómo hacer los movimientos principales:\n"
                     "• Caminata (Cardio): Mantén la espalda recta. 30 minutos al día mejoran tu corazón.\n"
                     "• Sentadilla Libre: Siéntate y párate de una silla lentamente. Usa los brazos para apoyarte.\n"
                     "• Pushdown: Si usas bandas elásticas, empuja hacia abajo suavemente para fortalecer los brazos.\n", 14, "#FFFFFF", false);
    agregarTextoGuia("* Recuerda: Consulta siempre con tu médico antes de realizar esfuerzos físicos.", 14, "#FF1744", true);

    // Forzar Inicio
    ui->stackedWidget->setCurrentWidget(ui->dashboard);
    ui->listWidget->setCurrentRow(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::actualizarDashboardVisual()
{
    ui->lblMetaCalorica->setText("Meta: " + QString::number(perfilUsuario.metaCalorica) + " kcal");

    double consumidas = calcularCaloriasDelDia(listaDelDia);
    ui->lblCaloriasConsumidas->setText(QString::number(consumidas, 'f', 0) + " kcal");

    QString txtQuemadas = ui->lblCaloriasQuemadas->text();
    txtQuemadas.replace(" kcal", "");
    double quemadas = txtQuemadas.toDouble();

    double balance = consumidas - quemadas;
    ui->lblBalanceNeto->setText(QString::number(balance, 'f', 0) + " kcal");

    int metaProtes = (perfilUsuario.tdee * 0.30) / 4;
    int metaCarbos = (perfilUsuario.tdee * 0.40) / 4;
    int metaGrasas = (perfilUsuario.tdee * 0.30) / 9;

    ui->barProteinas->setMaximum(metaProtes);
    ui->barCarbos->setMaximum(metaCarbos);
    ui->progressBar_3->setMaximum(metaGrasas);

    ui->barProteinas->setValue(metaProtes * 0.5);
    ui->barCarbos->setValue(metaCarbos * 0.8);
    ui->progressBar_3->setValue(metaGrasas * 0.3);
}

void MainWindow::on_btnGuardarPerfil_clicked()
{
    if (ui->inputNombre->text().isEmpty() || ui->inputEdad->text().isEmpty() ||
        ui->inputPeso->text().isEmpty() || ui->inputAltura->text().isEmpty()) {
        QMessageBox::warning(this, "Campos Incompletos", "Por favor, completa todos tus datos personales antes de guardar el perfil.");
        return;
    }

    perfilUsuario.nombre = ui->inputNombre->text().toStdString();
    perfilUsuario.edad = ui->inputEdad->text().toInt();
    perfilUsuario.peso = ui->inputPeso->text().toDouble();
    perfilUsuario.altura = ui->inputAltura->text().toDouble();

    if (ui->comboGenero->currentText() == "Masculino") perfilUsuario.GeneroUsuario = Genero::Masculino;
    else perfilUsuario.GeneroUsuario = Genero::Femenino;

    QString objTexto = ui->comboObjetivo->currentText();
    if (objTexto == "Bajar") perfilUsuario.ObjetivoUsuario = Objetivo::Bajar;
    else if (objTexto == "Mantener") perfilUsuario.ObjetivoUsuario = Objetivo::Mantener;
    else if (objTexto == "Subir") perfilUsuario.ObjetivoUsuario = Objetivo::Subir;

    QString actTexto = ui->comboActividad->currentText();
    if (actTexto == "Sedentario") perfilUsuario.NivelActividadUsuario = NivelActividad::Sedentario;
    else if (actTexto == "Ligero") perfilUsuario.NivelActividadUsuario = NivelActividad::Ligero;
    else if (actTexto == "Moderado") perfilUsuario.NivelActividadUsuario = NivelActividad::Moderado;
    else if (actTexto == "Activo") perfilUsuario.NivelActividadUsuario = NivelActividad::Activo;
    else if (actTexto == "Muy Activo") perfilUsuario.NivelActividadUsuario = NivelActividad::MuyActivo;

    perfilUsuario.tmb = calcularTMB(perfilUsuario);
    perfilUsuario.tdee = calcularTDEE(perfilUsuario, perfilUsuario.tmb);
    perfilUsuario.imc = calcularIMC(perfilUsuario);
    calcularMetas(perfilUsuario, perfilUsuario.tdee);

    guardarPerfil(perfilUsuario);
    actualizarDashboardVisual();

    QString mensajeExito = "Perfil guardado correctamente.\n\nTu nueva meta diaria es de " + QString::number(perfilUsuario.metaCalorica) + " kcal.";
    QMessageBox::information(this, "Perfil Actualizado", mensajeExito);
    ui->stackedWidget->setCurrentWidget(ui->dashboard);
}

void MainWindow::on_btnAgregarComida_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_buscador);
}

void MainWindow::on_btnVolverNutricion_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->alimentos);
}

void MainWindow::on_buscadorAlimentos_textChanged(const QString &arg1)
{
    ui->listaResultadosBusqueda->clear();
    if (arg1.isEmpty()) return;

    std::string textoBusqueda = arg1.toStdString();
    std::vector<Alimento> resultados = buscarAlimento(catalogoAlimentos, textoBusqueda);

    for (size_t i = 0; i < resultados.size(); i++) {
        QString nombreItem = QString::fromStdString(resultados[i].nombre);
        QString kcalItem = QString::number(resultados[i].calorias);
        ui->listaResultadosBusqueda->addItem(nombreItem + " (" + kcalItem + " kcal)");
    }
}

void MainWindow::on_listaResultadosBusqueda_itemDoubleClicked(QListWidgetItem *item)
{
    QString textoItem = item->text();
    QString nombreAlimento = textoItem.section(" (", 0, 0);

    Alimento alimentoEncontrado;
    bool encontrado = false;

    for (size_t i = 0; i < catalogoAlimentos.size(); i++) {
        if (QString::fromStdString(catalogoAlimentos[i].nombre) == nombreAlimento) {
            alimentoEncontrado = catalogoAlimentos[i];
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        agregarComida(listaDelDia, alimentoEncontrado, 100.0);
        QString textoDiario = QString::fromStdString(alimentoEncontrado.nombre) + " 100g  +" + QString::number(alimentoEncontrado.calorias) + " kcal";

        QListWidgetItem *itemVisual = new QListWidgetItem(ui->listaComidasHoy);
        itemVisual->setSizeHint(QSize(0, 45));

        QWidget *filaWidget = new QWidget();
        filaWidget->setStyleSheet("background-color: transparent;");

        QHBoxLayout *layoutFila = new QHBoxLayout(filaWidget);
        layoutFila->setContentsMargins(10, 0, 10, 0);

        QLabel *lblComida = new QLabel(textoDiario);
        lblComida->setStyleSheet("color: white; font-family: 'Segoe UI'; font-size: 14px; font-weight: bold; background: transparent; border: none;");

        QPushButton *btnBorrar = new QPushButton(QString::fromUtf8("\u2716"));
        btnBorrar->setFixedSize(26, 26);
        btnBorrar->setCursor(Qt::PointingHandCursor);
        btnBorrar->setStyleSheet(
            "QPushButton { background-color: #FF1744; color: white; border-radius: 13px; font-size: 12px; border: none; padding-bottom: 1px; }"
            "QPushButton:hover { background-color: #D50000; }"
            );

        layoutFila->addWidget(lblComida);
        layoutFila->addStretch();
        layoutFila->addWidget(btnBorrar);

        ui->listaComidasHoy->setItemWidget(itemVisual, filaWidget);

        connect(btnBorrar, &QPushButton::clicked, [this, itemVisual]() {
            int fila = ui->listaComidasHoy->row(itemVisual);
            delete ui->listaComidasHoy->takeItem(fila);
            double caloriasActualizadas = calcularCaloriasDelDia(listaDelDia);
            ui->lblCaloriasNutricion->setText("Calorías consumidas hoy: " + QString::number(caloriasActualizadas) + " kcal");
            actualizarDashboardVisual();
        });

        double caloriasTotalesHoy = calcularCaloriasDelDia(listaDelDia);
        ui->lblCaloriasNutricion->setText("Calorías consumidas hoy: " + QString::number(caloriasTotalesHoy) + " kcal");
    }
    actualizarDashboardVisual();
}

void MainWindow::configurarTablaRutinas()
{
    ui->tableWidget->setColumnCount(4);
    QStringList cabeceras = {"Ejercicio", "Series", "Repeticiones", "Peso (lb)"};
    ui->tableWidget->setHorizontalHeaderLabels(cabeceras);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
}

void MainWindow::on_comboDiasRutina_currentTextChanged(const QString &arg1)
{
    ui->tableWidget->setRowCount(0);

    auto crearInputRecomendado = [this](QString recomendacion) {
        QLineEdit *input = new QLineEdit();
        input->setPlaceholderText(recomendacion);
        input->setAlignment(Qt::AlignCenter);
        input->setStyleSheet("QLineEdit { background: transparent; color: #000000; border: 1px solid #CCC; border-radius: 4px; font-size: 13px; }"
                             "QLineEdit:focus { border: 2px solid #00E5FF; background: #FFFFFF; color: #000000; }");

        // CONEXIÓN EN TIEMPO REAL: Se enlaza cada caja al cálculo
        connect(input, &QLineEdit::textChanged, this, &MainWindow::calcularVolumenEnVivo);

        return input;
    };

    if (arg1.contains("Push")) {
        ui->tableWidget->setRowCount(2);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Bench Press"));
        ui->tableWidget->setCellWidget(0, 1, crearInputRecomendado("4"));
        ui->tableWidget->setCellWidget(0, 2, crearInputRecomendado("8-10"));
        ui->tableWidget->setCellWidget(0, 3, crearInputRecomendado("135"));
        ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Tríceps V-Grip Pushdown"));
        ui->tableWidget->setCellWidget(1, 1, crearInputRecomendado("3"));
        ui->tableWidget->setCellWidget(1, 2, crearInputRecomendado("12"));
        ui->tableWidget->setCellWidget(1, 3, crearInputRecomendado("40"));
    }
    else if (arg1.contains("Pull")) {
        ui->tableWidget->setRowCount(2);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Pull-ups (Dominadas)"));
        ui->tableWidget->setCellWidget(0, 1, crearInputRecomendado("3"));
        ui->tableWidget->setCellWidget(0, 2, crearInputRecomendado("Fallo"));
        ui->tableWidget->setCellWidget(0, 3, crearInputRecomendado("0"));
        ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Barbell Curl"));
        ui->tableWidget->setCellWidget(1, 1, crearInputRecomendado("3"));
        ui->tableWidget->setCellWidget(1, 2, crearInputRecomendado("10-12"));
        ui->tableWidget->setCellWidget(1, 3, crearInputRecomendado("60"));
    }
    else if (arg1.contains("Legs")) {
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Sentadilla Libre (Squat)"));
        ui->tableWidget->setCellWidget(0, 1, crearInputRecomendado("4"));
        ui->tableWidget->setCellWidget(0, 2, crearInputRecomendado("8"));
        ui->tableWidget->setCellWidget(0, 3, crearInputRecomendado("185"));
    }
}

void MainWindow::on_btnFinalizarRutina_clicked()
{
    // Ya no hacemos el cálculo desde cero porque 'calcularVolumenEnVivo' lo hace.
    // Solo forzamos un recálculo final por si acaso y mostramos el resumen.
    calcularVolumenEnVivo();

    QString txtQuemadas = ui->lblCaloriasQuemadas->text();
    txtQuemadas.replace(" kcal", "");

    QString resumen = "¡Excelente entrenamiento!\n\nCalorías estimadas quemadas en esta sesión: " + txtQuemadas + " kcal";
    QMessageBox::information(this, "Entrenamiento Finalizado", resumen);
}

void MainWindow::cargarDatosUI()
{
    if (!perfilUsuario.nombre.empty()) {
        ui->inputNombre->setText(QString::fromStdString(perfilUsuario.nombre));
        ui->inputEdad->setText(QString::number(perfilUsuario.edad));
        ui->inputPeso->setText(QString::number(perfilUsuario.peso));
        ui->inputAltura->setText(QString::number(perfilUsuario.altura));

        if (perfilUsuario.GeneroUsuario == Genero::Masculino) ui->comboGenero->setCurrentText("Masculino");
        else ui->comboGenero->setCurrentText("Femenino");

        if (perfilUsuario.ObjetivoUsuario == Objetivo::Bajar) ui->comboObjetivo->setCurrentText("Bajar");
        else if (perfilUsuario.ObjetivoUsuario == Objetivo::Mantener) ui->comboObjetivo->setCurrentText("Mantener");
        else if (perfilUsuario.ObjetivoUsuario == Objetivo::Subir) ui->comboObjetivo->setCurrentText("Subir");

        if (perfilUsuario.NivelActividadUsuario == NivelActividad::Sedentario) ui->comboActividad->setCurrentText("Sedentario");
        else if (perfilUsuario.NivelActividadUsuario == NivelActividad::Ligero) ui->comboActividad->setCurrentText("Ligero");
        else if (perfilUsuario.NivelActividadUsuario == NivelActividad::Moderado) ui->comboActividad->setCurrentText("Moderado");
        else if (perfilUsuario.NivelActividadUsuario == NivelActividad::Activo) ui->comboActividad->setCurrentText("Activo");
        else if (perfilUsuario.NivelActividadUsuario == NivelActividad::MuyActivo) ui->comboActividad->setCurrentText("Muy Activo");
    }
}

void MainWindow::on_btnRegistrarCardio_clicked()
{
    if (ui->inputTiempoCardio->text().isEmpty()) {
        QMessageBox::warning(this, "Datos Faltantes", "Por favor ingresa los minutos que duró tu sesión de cardio.");
        return;
    }

    bool esNumeroValido;
    int minutos = ui->inputTiempoCardio->text().toInt(&esNumeroValido);

    if (!esNumeroValido || minutos <= 0) {
        QMessageBox::critical(this, "Error de Formato", "Por favor ingresa un número válido.\nNo se aceptan letras ni números negativos.");
        ui->inputTiempoCardio->clear();
        return;
    }

    if (minutos > 240) {
        QMessageBox::warning(this, "Límite Excedido", "El tiempo máximo permitido es de 4 horas (240 min).");
        ui->inputTiempoCardio->clear();
        return;
    }

    double horas = minutos / 60.0;
    double pesoKg = perfilUsuario.peso > 0 ? perfilUsuario.peso : 70.0;
    QString tipoCardio = ui->comboCardio->currentText();
    double met = 5.0;

    if (tipoCardio == "Trotadora") met = 8.0;
    else if (tipoCardio == "Bicicleta Estática") met = 6.0;
    else if (tipoCardio == "Caminata") met = 3.5;
    else if (tipoCardio == "Escaladora") met = 7.0;

    double caloriasCardio = met * pesoKg * horas;

    QListWidgetItem *itemVisual = new QListWidgetItem(ui->listaCardioHoy);
    itemVisual->setSizeHint(QSize(0, 45));
    itemVisual->setData(Qt::UserRole, caloriasCardio);

    QWidget *filaWidget = new QWidget();
    filaWidget->setStyleSheet("background-color: transparent;");

    QHBoxLayout *layoutFila = new QHBoxLayout(filaWidget);
    layoutFila->setContentsMargins(10, 0, 10, 0);

    QString textoHistorial = QString::number(minutos) + " min de " + tipoCardio + "  +" + QString::number(caloriasCardio, 'f', 0) + " kcal";
    QLabel *lblCardio = new QLabel(textoHistorial);
    lblCardio->setStyleSheet("color: white; font-family: 'Segoe UI'; font-size: 14px; font-weight: bold; background: transparent; border: none;");

    QPushButton *btnBorrar = new QPushButton(QString::fromUtf8("\u2716"));
    btnBorrar->setFixedSize(26, 26);
    btnBorrar->setCursor(Qt::PointingHandCursor);
    btnBorrar->setStyleSheet(
        "QPushButton { background-color: #FF1744; color: white; border-radius: 13px; font-size: 12px; border: none; padding-bottom: 1px; }"
        "QPushButton:hover { background-color: #D50000; }"
        );

    layoutFila->addWidget(lblCardio);
    layoutFila->addStretch();
    layoutFila->addWidget(btnBorrar);
    ui->listaCardioHoy->setItemWidget(itemVisual, filaWidget);

    QString txtQuemadas = ui->lblCaloriasQuemadas->text();
    txtQuemadas.replace(" kcal", "");
    double quemadasActuales = txtQuemadas.toDouble();
    ui->lblCaloriasQuemadas->setText(QString::number(quemadasActuales + caloriasCardio, 'f', 0) + " kcal");

    connect(btnBorrar, &QPushButton::clicked, [this, itemVisual]() {
        double calsRestar = itemVisual->data(Qt::UserRole).toDouble();
        QString txtQuem = ui->lblCaloriasQuemadas->text();
        txtQuem.replace(" kcal", "");
        double qActual = txtQuem.toDouble();
        ui->lblCaloriasQuemadas->setText(QString::number(qActual - calsRestar, 'f', 0) + " kcal");

        int fila = ui->listaCardioHoy->row(itemVisual);
        delete ui->listaCardioHoy->takeItem(fila);
        actualizarDashboardVisual();
    });

    ui->inputTiempoCardio->clear();
    actualizarDashboardVisual();
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString menuSeleccionado = item->text();

    if (menuSeleccionado == "Dashboard") {
        ui->stackedWidget->setCurrentWidget(ui->dashboard);
    }
    else if (menuSeleccionado == "Nutricion" || menuSeleccionado == "Nutrición") {
        ui->stackedWidget->setCurrentWidget(ui->alimentos);
    }
    else if (menuSeleccionado == "Rutinas") {
        ui->stackedWidget->setCurrentWidget(ui->rutinas);
    }
    else if (menuSeleccionado == "Perfil") {
        ui->stackedWidget->setCurrentWidget(ui->perfil);
    }
    else if (menuSeleccionado == "Guía" || menuSeleccionado == "Guia" || menuSeleccionado == "listaGuia") {
        ui->stackedWidget->setCurrentWidget(ui->page_guia);
    }
    else if (menuSeleccionado == "Estadísticas" || menuSeleccionado == "Estadisticas") {
        dibujarGrafico();
        ui->stackedWidget->setCurrentWidget(ui->page_graficos);
    }
}

void MainWindow::dibujarGrafico()
{
    if (ui->lienzoGrafico->layout() != nullptr) {
        QLayoutItem *item;
        while ((item = ui->lienzoGrafico->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->lienzoGrafico->layout();
    }

    double consumidas = calcularCaloriasDelDia(listaDelDia);

    QString txtQuemadas = ui->lblCaloriasQuemadas->text();
    txtQuemadas.replace(" kcal", "");
    double quemadas = txtQuemadas.toDouble();

    double meta = perfilUsuario.metaCalorica > 0 ? perfilUsuario.metaCalorica : 2000;

    QBarSet *setConsumidas = new QBarSet("Consumidas");
    QBarSet *setQuemadas = new QBarSet("Quemadas");
    QBarSet *setMeta = new QBarSet("Meta Diaria");

    *setConsumidas << consumidas;
    *setQuemadas << quemadas;
    *setMeta << meta;

    setConsumidas->setColor(QColor(0x00E676));
    setQuemadas->setColor(QColor(0xFF1744));
    setMeta->setColor(QColor(0x00E5FF));

    QBarSeries *series = new QBarSeries();
    series->append(setConsumidas);
    series->append(setQuemadas);
    series->append(setMeta);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Balance Energético del Día");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->setBackgroundBrush(QBrush(QColor(0x1E2736)));
    chart->setTitleBrush(QBrush(Qt::white));
    chart->legend()->setLabelColor(Qt::white);

    QStringList categories;
    categories << "Hoy";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(Qt::white);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setBackgroundBrush(QBrush(QColor(0x1E2736)));

    QVBoxLayout *layout = new QVBoxLayout(ui->lienzoGrafico);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(chartView);
    ui->lienzoGrafico->setLayout(layout);
}

void MainWindow::calcularVolumenEnVivo()
{
    double volumenTotalLibras = 0;

    for (int fila = 0; fila < ui->tableWidget->rowCount(); ++fila) {

        QLineEdit *inputSeries = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(fila, 1));
        QLineEdit *inputReps = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(fila, 2));
        QLineEdit *inputPeso = qobject_cast<QLineEdit*>(ui->tableWidget->cellWidget(fila, 3));

        if (inputSeries && inputReps && inputPeso) {
            QString txtSeries = inputSeries->text().isEmpty() ? inputSeries->placeholderText() : inputSeries->text();
            QString txtReps = inputReps->text().isEmpty() ? inputReps->placeholderText() : inputReps->text();
            QString txtPeso = inputPeso->text().isEmpty() ? inputPeso->placeholderText() : inputPeso->text();

            int series = txtSeries.toInt();
            int reps = txtReps.section("-", 0, 0).toInt();
            double peso = txtPeso.toDouble();

            volumenTotalLibras += (series * reps * peso);
        }
    }

    double caloriasQuemadas = volumenTotalLibras * 0.005;
    ui->lblCaloriasQuemadas->setText(QString::number(caloriasQuemadas, 'f', 0) + " kcal");

    QString txtConsumidas = ui->lblCaloriasConsumidas->text();
    txtConsumidas.replace(" kcal", "");
    double consumidas = txtConsumidas.toDouble();

    double balance = consumidas - caloriasQuemadas;
    ui->lblBalanceNeto->setText(QString::number(balance, 'f', 0) + " kcal");

    if (ui->stackedWidget->currentWidget() == ui->page_graficos) {
        dibujarGrafico();
    }
}