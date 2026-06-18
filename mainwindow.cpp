#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (cargarPerfil(perfilUsuario)) {
        actualizarDashboardVisual();
    }
    catalogoAlimentos = cargarAlimentos("data/foods.json");
    listaDelDia.cabeza = nullptr;
    listaDelDia.cantidad = 0;

    ui->listaComidasHoy->setStyleSheet(
        "QListWidget { background-color: #1E2736; border-radius: 12px; border: 1px solid #2A3648; outline: none; }"
        "QListWidget::item { background-color: #0F1722; border-radius: 6px; border-left: 4px solid #00E676; margin-bottom: 5px; }"
        "QListWidget::item:hover { background-color: #2A3648; }"
        );
    ui->comboDiasRutina->clear();
    ui->comboDiasRutina->addItems({"Lunes (Push)", "Martes (Pull)", "Miércoles (Legs)", "Jueves (Push)", "Viernes (Pull)", "Sábado (Legs)"});

    configurarTablaRutinas();
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
            "QPushButton {"
            "   background-color: #FF1744;"
            "   color: white;"
            "   border-radius: 13px;"
            "   font-size: 12px;"
            "   border: none;"
            "   padding-bottom: 1px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #D50000;"
            "}"
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

    auto crearInputRecomendado = [](QString recomendacion) {
        QLineEdit *input = new QLineEdit();
        input->setPlaceholderText(recomendacion);
        input->setAlignment(Qt::AlignCenter);

        input->setStyleSheet("QLineEdit { background: transparent; color: #000000; border: 1px solid #CCC; border-radius: 4px; font-size: 13px; }"
                             "QLineEdit:focus { border: 2px solid #00E5FF; background: #FFFFFF; color: #000000; }");
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

    qDebug() << "Entrenamiento finalizado. Volumen total:" << volumenTotalLibras << "lb";
    qDebug() << "Calorías quemadas estimadas:" << caloriasQuemadas << "kcal";

    actualizarDashboardVisual();
}

