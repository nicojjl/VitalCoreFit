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
#include <QToolTip>
#include <QCursor>
#include <QIntValidator>
#include <QDoubleValidator>

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

    timerDescanso = new QTimer(this);
    connect(timerDescanso, &QTimer::timeout, this, &MainWindow::actualizarCronometro);

    catalogoAlimentos = cargarAlimentos("data/foods.json");
    listaDelDia.cabeza = nullptr;
    listaDelDia.cantidad = 0;

    if (cargarPerfil(perfilUsuario)) {
        cargarDatosUI();
        actualizarDashboardVisual();
    }

    if (ui->listaComidasHoy) {
        ui->listaComidasHoy->setStyleSheet(
            "QListWidget { background-color: #1E2736; border-radius: 12px; border: 1px solid #2A3648; outline: none; }"
            "QListWidget::item { background-color: #0F1722; border-radius: 6px; border-left: 4px solid #00E676; margin-bottom: 5px; }"
            "QListWidget::item:hover { background-color: #2A3648; }"
            );
    }

    if (ui->comboDiasRutina) {
        ui->comboDiasRutina->clear();
        ui->comboDiasRutina->addItems({"Lunes (Push)", "Martes (Pull)", "Miércoles (Legs)", "Jueves (Push)", "Viernes (Pull)", "Sábado (Legs)"});
    }

    if (ui->listaGuia) {
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
    }

    if (ui->stackedWidget) {
        ui->stackedWidget->setCurrentWidget(ui->dashboard);
    }
    if (ui->listWidget) {
        ui->listWidget->setCurrentRow(0);
    }

    QSettings settings("VitalCoreFit", "App");
    if (ui->lblCaloriasQuemadas) {
        QString qm = settings.value("quemadasHoy", "0").toString();
        qm.replace("🔥 Quemadas: ", "").replace(" kcal", "");
        ui->lblCaloriasQuemadas->setText("🔥 Quemadas: " + qm + " kcal");
    }
    if (ui->comboDiasRutina) {
        ui->comboDiasRutina->setCurrentText(settings.value("ultimaRutina", "Lunes (Push)").toString());
    }

    cargarDiarioAlimentosJson();
    actualizarDashboardVisual();

    if (ui->btnDescanso) {
        ui->btnDescanso->setStyleSheet(
            "QPushButton { "
            "background-color: #121A25; "
            "color: #00E5FF; "
            "border: 2px solid #00E5FF; "
            "border-radius: 10px; "
            "font-size: 16px; "
            "font-weight: bold; "
            "padding: 8px; "
            "} "
            "QPushButton:hover { "
            "background-color: #00E5FF; "
            "color: #121A25; "
            "}"
            );
        ui->btnDescanso->setCursor(Qt::PointingHandCursor);
    }

    if (ui->lblCronometro) {
        ui->lblCronometro->setStyleSheet(
            "QLabel { "
            "color: #00E676; "
            "font-size: 42px; "
            "font-weight: bold; "
            "font-family: 'Segoe UI', monospace; "
            "background-color: transparent; "
            "}"
            );
        ui->lblCronometro->setAlignment(Qt::AlignCenter);
    }

    // ========================================================
    // MAGIA C++: REDISEÑO AUTOMÁTICO (DASHBOARD Y PERFIL)
    // ========================================================
    QString estiloTarjeta = "QFrame { background-color: #121A25; border-radius: 12px; border: 1px solid #2A3648; }";
    if (ui->tarjetaBalance) ui->tarjetaBalance->setStyleSheet(estiloTarjeta);
    if (ui->tarjetaConsumidas) ui->tarjetaConsumidas->setStyleSheet(estiloTarjeta);
    if (ui->tarjetaMacros) ui->tarjetaMacros->setStyleSheet(estiloTarjeta);

    QString estiloTitulo = "QLabel { color: #8E9BAE; font-size: 14px; font-weight: bold; background: transparent; border: none; }";
    // Tamaño de letra ajustado a 20px para que el texto descriptivo quepa bien en pantalla
    QString estiloNumero = "QLabel { color: #FFFFFF; font-size: 20px; font-weight: bold; background: transparent; border: none; }";

    if (ui->dashboard) {
        QList<QLabel*> etiquetasDash = ui->dashboard->findChildren<QLabel*>();
        for (QLabel* lbl : etiquetasDash) {
            if (lbl->objectName().contains("lblCalorias") || lbl->objectName().contains("lblBalance") || lbl->objectName().contains("lblMeta")) {
                lbl->setStyleSheet(estiloNumero);
                lbl->setAlignment(Qt::AlignCenter);
            } else {
                lbl->setStyleSheet(estiloTitulo);
            }
        }
    }

    // Estilo para que el buscador de alimentos se vea con texto blanco
    if (ui->buscadorAlimentos) {
        ui->buscadorAlimentos->setStyleSheet("QLineEdit { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 8px; font-size: 16px; } QLineEdit:focus { border: 2px solid #00E5FF; }");
    }

    QString estiloBarra = "QProgressBar { border: none; background-color: #1E2736; border-radius: 8px; text-align: center; color: white; font-weight: bold; } QProgressBar::chunk { border-radius: 8px; }";
    if (ui->barProteinas) ui->barProteinas->setStyleSheet(estiloBarra + "QProgressBar::chunk { background-color: #00E676; }");
    if (ui->barCarbos) ui->barCarbos->setStyleSheet(estiloBarra + "QProgressBar::chunk { background-color: #FF9100; }");
    if (ui->barGrasas) ui->barGrasas->setStyleSheet(estiloBarra + "QProgressBar::chunk { background-color: #FF1744; }");

    if (ui->btnResetDia) {
        ui->btnResetDia->setStyleSheet("QPushButton { background-color: #FF1744; color: white; border-radius: 8px; padding: 10px; font-weight: bold; font-size: 14px; } QPushButton:hover { background-color: #D50000; }");
        ui->btnResetDia->setCursor(Qt::PointingHandCursor);
    }

    QString estiloInputs = "QLineEdit, QComboBox { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 8px; font-size: 14px; } QLineEdit:focus, QComboBox:focus { border: 2px solid #00E5FF; background-color: #121A25; }";
    if (ui->perfil) {
        QList<QWidget*> inputsPerfil = ui->perfil->findChildren<QWidget*>();
        for (QWidget* w : inputsPerfil) {
            if (qobject_cast<QLineEdit*>(w) || qobject_cast<QComboBox*>(w)) {
                w->setStyleSheet(estiloInputs);
            } else if (qobject_cast<QLabel*>(w)) {
                w->setStyleSheet(estiloTitulo);
            }
        }
    }

    if (ui->btnGuardarPerfil) {
        ui->btnGuardarPerfil->setStyleSheet("QPushButton { background-color: #00E5FF; color: #121A25; border-radius: 10px; padding: 12px; font-size: 16px; font-weight: bold; } QPushButton:hover { background-color: #00B8D4; }");
        ui->btnGuardarPerfil->setCursor(Qt::PointingHandCursor);
    }
}

MainWindow::~MainWindow()
{
    QSettings settings("VitalCoreFit", "App");
    if (ui->lblCaloriasQuemadas) {
        QString qm = ui->lblCaloriasQuemadas->text();
        qm.replace("🔥 Quemadas: ", "").replace(" kcal", "");
        settings.setValue("quemadasHoy", qm);
    }
    if (ui->comboDiasRutina) {
        settings.setValue("ultimaRutina", ui->comboDiasRutina->currentText());
    }

    guardarDiarioAlimentosJson();
    delete ui;
}

void MainWindow::actualizarDashboardVisual()
{
    if (ui->lblMetaCalorica) {
        ui->lblMetaCalorica->setText("🎯 Meta Diaria: " + QString::number(perfilUsuario.metaCalorica) + " kcal");
    }

    double consumidas = calcularCaloriasDelDia(listaDelDia);
    if (ui->lblCaloriasConsumidas) {
        ui->lblCaloriasConsumidas->setText("🍔 Consumidas: " + QString::number(consumidas, 'f', 0) + " kcal");
    }

    double quemadas = 0;
    if (ui->lblCaloriasQuemadas) {
        QString txtQuemadas = ui->lblCaloriasQuemadas->text();
        txtQuemadas.replace("🔥 Quemadas: ", "").replace(" kcal", "");
        quemadas = txtQuemadas.toDouble();
    }

    double balance = consumidas - quemadas;
    if (ui->lblBalanceNeto) {
        ui->lblBalanceNeto->setText("⚖️ Balance Neto: " + QString::number(balance, 'f', 0) + " kcal");
    }

    int metaProtes = (perfilUsuario.tdee * 0.30) / 4;
    int metaCarbos = (perfilUsuario.tdee * 0.40) / 4;
    int metaGrasas = (perfilUsuario.tdee * 0.30) / 9;

    if (ui->barProteinas) {
        ui->barProteinas->setMaximum(metaProtes);
        ui->barProteinas->setValue(metaProtes * 0.5);
    }
    if (ui->barCarbos) {
        ui->barCarbos->setMaximum(metaCarbos);
        ui->barCarbos->setValue(metaCarbos * 0.8);
    }
    if (ui->barGrasas) {
        ui->barGrasas->setMaximum(metaGrasas);
        ui->barGrasas->setValue(metaGrasas * 0.3);
    }
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

void MainWindow::agregarComidaInterfazVisual(const Alimento& alimento)
{
    if (!ui->listaComidasHoy) return;

    QString textoDiario = QString::fromStdString(alimento.nombre) + " 100g  +" + QString::number(alimento.calorias) + " kcal";

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
        if (ui->lblCaloriasNutricion) {
            ui->lblCaloriasNutricion->setText("Calorías consumidas hoy: " + QString::number(caloriasActualizadas) + " kcal");
        }
        actualizarDashboardVisual();
    });
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
        agregarComidaInterfazVisual(alimentoEncontrado);

        double caloriasTotalesHoy = calcularCaloriasDelDia(listaDelDia);
        if (ui->lblCaloriasNutricion) {
            ui->lblCaloriasNutricion->setText("Calorías consumidas hoy: " + QString::number(caloriasTotalesHoy) + " kcal");
        }

        // --- UX: VOLVER AUTOMÁTICAMENTE A LA PANTALLA ANTERIOR ---
        if (ui->stackedWidget && ui->alimentos) {
            ui->stackedWidget->setCurrentWidget(ui->alimentos);
        }
    }
    actualizarDashboardVisual();
}

void MainWindow::on_comboDiasRutina_currentTextChanged(const QString &arg1)
{
    cargarRutinaEstiloHevy(arg1);
}

void MainWindow::cargarRutinaEstiloHevy(const QString &diaRutina)
{
    if (!ui->scrollArea) return;

    QWidget *contenedorPrincipal = new QWidget();
    contenedorPrincipal->setStyleSheet("background-color: transparent;");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(contenedorPrincipal);
    layoutPrincipal->setSpacing(15);

    struct EjercicioSetup { QString nombre; int series; QString reps; QString pesoBase; };
    std::vector<EjercicioSetup> ejerciciosHoy;

    if (diaRutina.contains("Push")) {
        ejerciciosHoy = { {"Bench Press", 4, "8", "135"}, {"Tríceps V-Grip Pushdown", 3, "12", "40"} };
    } else if (diaRutina.contains("Pull")) {
        ejerciciosHoy = { {"Pull-ups (Dominadas)", 3, "Fallo", "0"}, {"Barbell Curl", 3, "10", "60"} };
    } else if (diaRutina.contains("Legs")) {
        ejerciciosHoy = { {"Sentadilla Libre (Squat)", 4, "8", "185"} };
    }

    QSettings memoriaMuscular("VitalCoreFit", "Pesos");

    for (const auto& ej : ejerciciosHoy) {
        QGroupBox *tarjetaEjercicio = new QGroupBox(ej.nombre);
        tarjetaEjercicio->setStyleSheet(
            "QGroupBox { font-size: 16px; font-weight: bold; color: #00E5FF; border: 1px solid #2A3648; border-radius: 8px; margin-top: 15px; background-color: #121A25; }"
            "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px 0 5px; }"
            );

        QVBoxLayout *layoutTarjeta = new QVBoxLayout(tarjetaEjercicio);

        QWidget *filaHeader = new QWidget();
        QHBoxLayout *layoutHeader = new QHBoxLayout(filaHeader);
        layoutHeader->setContentsMargins(0, 5, 0, 0);

        QLabel *lblSetH = new QLabel("SET");
        QLabel *lblRepsH = new QLabel("REPS");
        QLabel *lblPesoH = new QLabel("LBS");

        lblSetH->setStyleSheet("color: #8E9BAE; font-weight: bold; font-size: 12px;");
        lblRepsH->setStyleSheet("color: #8E9BAE; font-weight: bold; font-size: 12px;");
        lblPesoH->setStyleSheet("color: #8E9BAE; font-weight: bold; font-size: 12px;");

        layoutHeader->addWidget(lblSetH, 1, Qt::AlignCenter);
        layoutHeader->addWidget(lblRepsH, 2, Qt::AlignCenter);
        layoutHeader->addWidget(lblPesoH, 2, Qt::AlignCenter);
        layoutHeader->addSpacing(40);

        layoutTarjeta->addWidget(filaHeader);

        QString repsGuardadas = memoriaMuscular.value(ej.nombre + "_reps", ej.reps).toString();
        QString pesoGuardado = memoriaMuscular.value(ej.nombre + "_peso", ej.pesoBase).toString();

        for (int i = 1; i <= ej.series; ++i) {
            QWidget *filaSerie = new QWidget();
            QHBoxLayout *layoutSerie = new QHBoxLayout(filaSerie);
            layoutSerie->setContentsMargins(0, 5, 0, 5);

            QLabel *lblNumSerie = new QLabel(QString::number(i));
            lblNumSerie->setStyleSheet("color: white; font-weight: bold; font-size: 14px;");

            QLineEdit *inputReps = new QLineEdit();
            inputReps->setPlaceholderText(repsGuardadas);
            inputReps->setAlignment(Qt::AlignCenter);
            inputReps->setStyleSheet("QLineEdit { background: #1E2736; color: white; border: none; border-radius: 4px; font-size: 14px; padding: 5px; } QLineEdit:focus { border: 1px solid #00E5FF; }");
            inputReps->setValidator(new QIntValidator(0, 999, this));

            QLineEdit *inputPeso = new QLineEdit();
            inputPeso->setPlaceholderText(pesoGuardado);
            inputPeso->setAlignment(Qt::AlignCenter);
            inputPeso->setStyleSheet(inputReps->styleSheet());
            QDoubleValidator *pesoValidator = new QDoubleValidator(0.0, 2000.0, 2, this);
            pesoValidator->setNotation(QDoubleValidator::StandardNotation);
            inputPeso->setValidator(pesoValidator);

            QPushButton *btnCheck = new QPushButton(QString::fromUtf8("\u2713"));
            btnCheck->setFixedSize(32, 32);
            btnCheck->setCursor(Qt::PointingHandCursor);
            btnCheck->setStyleSheet(
                "QPushButton { background-color: #2A3648; color: #8E9BAE; border-radius: 8px; font-size: 18px; font-weight: bold; border: none; }"
                "QPushButton:checked { background-color: #00E676; color: black; }"
                );
            btnCheck->setCheckable(true);

            connect(btnCheck, &QPushButton::toggled, [this, filaSerie, btnCheck](bool checked) {
                if (checked) {
                    filaSerie->setStyleSheet("background-color: rgba(0, 230, 118, 0.15); border-radius: 6px;");
                    on_btnDescanso_clicked();
                } else {
                    filaSerie->setStyleSheet("background-color: transparent;");
                }
                calcularVolumenEnVivo();
            });

            connect(inputReps, &QLineEdit::textChanged, this, &MainWindow::calcularVolumenEnVivo);
            connect(inputPeso, &QLineEdit::textChanged, this, &MainWindow::calcularVolumenEnVivo);

            layoutSerie->addWidget(lblNumSerie, 1, Qt::AlignCenter);
            layoutSerie->addWidget(inputReps, 2);
            layoutSerie->addWidget(inputPeso, 2);
            layoutSerie->addWidget(btnCheck, 0, Qt::AlignRight);

            layoutTarjeta->addWidget(filaSerie);
        }
        layoutPrincipal->addWidget(tarjetaEjercicio);
    }

    QPushButton *btnFinalizar = new QPushButton("Finalizar Entrenamiento");
    btnFinalizar->setCursor(Qt::PointingHandCursor);
    btnFinalizar->setStyleSheet(
        "QPushButton { background-color: #00E676; color: #121A25; font-size: 18px; font-weight: bold; border-radius: 10px; padding: 15px; margin-top: 20px; }"
        "QPushButton:hover { background-color: #00C853; }"
        );
    connect(btnFinalizar, &QPushButton::clicked, this, &MainWindow::on_btnFinalizarRutina_clicked);
    layoutPrincipal->addWidget(btnFinalizar);

    layoutPrincipal->addStretch();

    ui->scrollArea->setWidget(contenedorPrincipal);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; } QWidget#qt_scrollarea_viewport { background: transparent; }");
}

void MainWindow::on_btnFinalizarRutina_clicked()
{
    calcularVolumenEnVivo();
    guardarHistorialRutina();

    QString txtQuemadas = ui->lblCaloriasQuemadas ? ui->lblCaloriasQuemadas->text() : "0";
    txtQuemadas.replace("🔥 Quemadas: ", ""); // Limpiamos el prefijo para el resumen

    QString nombreRutina = ui->comboDiasRutina ? ui->comboDiasRutina->currentText() : "Desconocida";

    QString resumen = "¡Entrenamiento Registrado con Éxito!\n\n"
                      "Rutina: " + nombreRutina + "\n"
                                       "Volumen total movido: " + QString::number(ultimoVolumenCalculado, 'f', 1) + " lbs\n"
                                                                          "Calorías quemadas: " + txtQuemadas + "\n\n"
                                      "Tus datos han sido guardados en tu historial.";

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
    // Función desactivada temporalmente porque el panel de Cardio fue eliminado en el diseñador
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
    QString txtQuemadas = ui->lblCaloriasQuemadas ? ui->lblCaloriasQuemadas->text() : "0";
    txtQuemadas.replace("🔥 Quemadas: ", "").replace(" kcal", "");
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

    QBarSeries *seriesBarras = new QBarSeries();
    seriesBarras->append(setConsumidas);
    seriesBarras->append(setQuemadas);
    seriesBarras->append(setMeta);

    QChart *chartBarras = new QChart();
    chartBarras->addSeries(seriesBarras);
    chartBarras->setTitle("Balance Energético del Día");
    chartBarras->setAnimationOptions(QChart::SeriesAnimations);

    connect(seriesBarras, &QBarSeries::hovered, this, [](bool status, int index, QBarSet *barset) {
        if (status) {
            double valor = barset->at(index);
            QString texto = barset->label() + ": " + QString::number(valor, 'f', 0) + " kcal";
            QToolTip::showText(QCursor::pos(), texto);
        } else {
            QToolTip::hideText();
        }
    });

    chartBarras->setBackgroundBrush(QBrush(QColor(0x1E2736)));
    chartBarras->setTitleBrush(QBrush(Qt::white));
    chartBarras->legend()->setLabelColor(Qt::white);

    QStringList categories;
    categories << "Hoy";
    QBarCategoryAxis *axisXB = new QBarCategoryAxis();
    axisXB->append(categories);
    axisXB->setLabelsColor(Qt::white);
    chartBarras->addAxis(axisXB, Qt::AlignBottom);
    seriesBarras->attachAxis(axisXB);

    QValueAxis *axisYB = new QValueAxis();
    axisYB->setLabelsColor(Qt::white);
    chartBarras->addAxis(axisYB, Qt::AlignLeft);
    seriesBarras->attachAxis(axisYB);

    QChartView *viewBarras = new QChartView(chartBarras);
    viewBarras->setRenderHint(QPainter::Antialiasing);
    viewBarras->setBackgroundBrush(QBrush(QColor(0x1E2736)));

    QLineSeries *serieVolumen = new QLineSeries();
    serieVolumen->setName("Volumen Total Movido (lbs)");
    serieVolumen->setColor(QColor(0x00E5FF));
    QPen pen = serieVolumen->pen();
    pen.setWidth(4);
    serieVolumen->setPen(pen);

    QStringList fechasHistorial;
    double maxVolumen = 1000;

    QFile archivoLectura("data/historial_rutinas.json");
    if (archivoLectura.open(QIODevice::ReadOnly)) {
        QJsonArray arrayHistorial = QJsonDocument::fromJson(archivoLectura.readAll()).array();
        for (int i = 0; i < arrayHistorial.size(); ++i) {
            QJsonObject rutina = arrayHistorial[i].toObject();
            double vol = rutina["volumen_lbs"].toDouble();
            QString fecha = rutina["fecha"].toString().section(" ", 0, 0);

            serieVolumen->append(i, vol);
            fechasHistorial << fecha;
            if (vol > maxVolumen) maxVolumen = vol;
        }
        archivoLectura.close();
    }

    if (fechasHistorial.isEmpty()) {
        serieVolumen->append(0, 0);
        fechasHistorial << "Sin datos";
    }

    connect(serieVolumen, &QLineSeries::hovered, this, [](const QPointF &point, bool state) {
        if (state) {
            QString texto = "Volumen: " + QString::number(point.y(), 'f', 1) + " lbs";
            QToolTip::showText(QCursor::pos(), texto);
        } else {
            QToolTip::hideText();
        }
    });

    QChart *chartLineas = new QChart();
    chartLineas->addSeries(serieVolumen);
    chartLineas->setTitle("Sobrecarga Progresiva (Progreso en el Tiempo)");
    chartLineas->setAnimationOptions(QChart::SeriesAnimations);
    chartLineas->setBackgroundBrush(QBrush(QColor(0x1E2736)));
    chartLineas->setTitleBrush(QBrush(Qt::white));
    chartLineas->legend()->setLabelColor(Qt::white);

    QBarCategoryAxis *axisXL = new QBarCategoryAxis();
    axisXL->append(fechasHistorial);
    axisXL->setLabelsColor(Qt::white);
    chartLineas->addAxis(axisXL, Qt::AlignBottom);
    serieVolumen->attachAxis(axisXL);

    QValueAxis *axisYL = new QValueAxis();
    axisYL->setRange(0, maxVolumen + 500);
    axisYL->setLabelsColor(Qt::white);
    chartLineas->addAxis(axisYL, Qt::AlignLeft);
    serieVolumen->attachAxis(axisYL);

    QChartView *viewLineas = new QChartView(chartLineas);
    viewLineas->setRenderHint(QPainter::Antialiasing);
    viewLineas->setBackgroundBrush(QBrush(QColor(0x1E2736)));

    QTabWidget *tabsGraficos = new QTabWidget();
    tabsGraficos->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #2A3648; background: #1E2736; border-radius: 8px; }"
        "QTabBar::tab { background: #121A25; color: #8E9BAE; padding: 10px 20px; border-top-left-radius: 6px; border-top-right-radius: 6px; margin-right: 2px; }"
        "QTabBar::tab:selected { background: #00E5FF; color: #121A25; font-weight: bold; }"
        );

    QWidget *tab1 = new QWidget();
    QVBoxLayout *lay1 = new QVBoxLayout(tab1);
    lay1->setContentsMargins(0,0,0,0);
    lay1->addWidget(viewBarras);

    QWidget *tab2 = new QWidget();
    QVBoxLayout *lay2 = new QVBoxLayout(tab2);
    lay2->setContentsMargins(0,0,0,0);
    lay2->addWidget(viewLineas);

    tabsGraficos->addTab(tab1, "Balance Diario");
    tabsGraficos->addTab(tab2, "Progreso Histórico");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(ui->lienzoGrafico);
    layoutPrincipal->setContentsMargins(0,0,0,0);
    layoutPrincipal->addWidget(tabsGraficos);
    ui->lienzoGrafico->setLayout(layoutPrincipal);
}

void MainWindow::calcularVolumenEnVivo()
{
    double volumenTotalLibras = 0;

    if (!ui->scrollArea || !ui->scrollArea->widget()) return;

    QSettings memoriaMuscular("VitalCoreFit", "Pesos");

    QList<QGroupBox*> tarjetas = ui->scrollArea->widget()->findChildren<QGroupBox*>();
    for (QGroupBox* tarjeta : tarjetas) {
        QList<QLineEdit*> inputs = tarjeta->findChildren<QLineEdit*>();
        QList<QPushButton*> botones = tarjeta->findChildren<QPushButton*>();

        int indexBoton = 0;
        for (int i = 0; i < inputs.size(); i += 2) {
            if (i + 1 >= inputs.size() || indexBoton >= botones.size()) break;

            QPushButton* btnCheck = botones.at(indexBoton);
            indexBoton++;

            if (btnCheck && btnCheck->isChecked()) {
                QLineEdit* inputReps = inputs.at(i);
                QLineEdit* inputPeso = inputs.at(i+1);

                QString txtReps = inputReps->text().isEmpty() ? inputReps->placeholderText() : inputReps->text();
                QString txtPeso = inputPeso->text().isEmpty() ? inputPeso->placeholderText() : inputPeso->text();

                memoriaMuscular.setValue(tarjeta->title() + "_reps", txtReps);
                memoriaMuscular.setValue(tarjeta->title() + "_peso", txtPeso);

                int reps = txtReps.section("-", 0, 0).toInt();
                double peso = txtPeso.toDouble();

                if (reps <= 0 && txtReps.toLower() == "fallo") reps = 10;

                volumenTotalLibras += (reps * peso);
            }
        }
    }
    ultimoVolumenCalculado = volumenTotalLibras;

    double caloriasQuemadas = volumenTotalLibras * 0.005;
    if (ui->lblCaloriasQuemadas) {
        ui->lblCaloriasQuemadas->setText("🔥 Quemadas: " + QString::number(caloriasQuemadas, 'f', 0) + " kcal");
    }

    if (ui->lblCaloriasConsumidas) {
        QString txtConsumidas = ui->lblCaloriasConsumidas->text();
        txtConsumidas.replace("🍔 Consumidas: ", "").replace(" kcal", "");
        double consumidas = txtConsumidas.toDouble();
        double balance = consumidas - caloriasQuemadas;
        if (ui->lblBalanceNeto) {
            ui->lblBalanceNeto->setText("⚖️ Balance Neto: " + QString::number(balance, 'f', 0) + " kcal");
        }
    }

    if (ui->stackedWidget && ui->stackedWidget->currentWidget() == ui->page_graficos) {
        dibujarGrafico();
    }
}

void MainWindow::on_btnResetDia_clicked()
{
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Finalizar Día",
                                      "¿Terminaste por hoy? Esto reiniciará todos tus contadores a cero para empezar un nuevo día de entrenamiento.",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (ui->listaComidasHoy) ui->listaComidasHoy->clear();
        if (ui->lblCaloriasQuemadas) ui->lblCaloriasQuemadas->setText("🔥 Quemadas: 0 kcal");

        NodoComida* actual = listaDelDia.cabeza;
        while (actual != nullptr) {
            NodoComida* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
        listaDelDia.cabeza = nullptr;
        listaDelDia.cantidad = 0;
        QFile::remove("data/diario.json");

        QSettings settings("VitalCoreFit", "App");
        settings.setValue("quemadasHoy", "0");

        actualizarDashboardVisual();
        if (ui->stackedWidget && ui->stackedWidget->currentWidget() == ui->page_graficos) {
            dibujarGrafico();
        }
    }
}

void MainWindow::guardarDiarioAlimentosJson()
{
    QJsonArray arrayComidas;
    NodoComida* actual = listaDelDia.cabeza;

    while (actual != nullptr) {
        QJsonObject objetoAlimento;
        objetoAlimento["nombre"] = QString::fromStdString(actual->alimento.nombre);
        objetoAlimento["calorias"] = actual->alimento.calorias;
        arrayComidas.append(objetoAlimento);
        actual = actual->siguiente;
    }

    QJsonDocument documento(arrayComidas);
    QFile archivo("data/diario.json");
    if (archivo.open(QIODevice::WriteOnly)) {
        archivo.write(documento.toJson());
        archivo.close();
    }
}

void MainWindow::cargarDiarioAlimentosJson()
{
    QFile archivo("data/diario.json");
    if (!archivo.open(QIODevice::ReadOnly)) return;

    QByteArray datos = archivo.readAll();
    archivo.close();

    QJsonDocument documento = QJsonDocument::fromJson(datos);
    QJsonArray arrayComidas = documento.array();

    for (int i = 0; i < arrayComidas.size(); ++i) {
        QJsonObject objetoAlimento = arrayComidas[i].toObject();
        Alimento alimento;
        alimento.nombre = objetoAlimento["nombre"].toString().toStdString();
        alimento.calorias = objetoAlimento["calorias"].toDouble();

        agregarComida(listaDelDia, alimento, 100.0);
        agregarComidaInterfazVisual(alimento);
    }

    double caloriasTotalesHoy = calcularCaloriasDelDia(listaDelDia);
    if (ui->lblCaloriasNutricion) {
        ui->lblCaloriasNutricion->setText("Calorías consumidas hoy: " + QString::number(caloriasTotalesHoy) + " kcal");
    }
}

void MainWindow::on_btnExportarReporte_clicked()
{
    // Omitido
}

void MainWindow::on_btnDescanso_clicked()
{
    tiempoRestante = 90;
    if (ui->lblCronometro) {
        ui->lblCronometro->setText("01:30");
    }
    timerDescanso->start(1000);
    ui->lblCronometro->setStyleSheet("QLabel { color: #00E676; font-size: 42px; font-weight: bold; background-color: transparent; }");
}

void MainWindow::actualizarCronometro()
{
    tiempoRestante--;

    int minutos = tiempoRestante / 60;
    int segundos = tiempoRestante % 60;

    QString textoReloj = QString("%1:%2")
                             .arg(minutos, 2, 10, QChar('0'))
                             .arg(segundos, 2, 10, QChar('0'));

    if (ui->lblCronometro) {
        ui->lblCronometro->setText(textoReloj);
    }

    if (tiempoRestante <= 0) {
        timerDescanso->stop();

        ui->lblCronometro->setStyleSheet("QLabel { color: #FF1744; font-size: 42px; font-weight: bold; background-color: transparent; }");
        QMessageBox::information(this, "¡Descanso Terminado!", "¡A darle a la siguiente serie con todo el peso!");
    }
}

void MainWindow::guardarHistorialRutina(){
    QString rutaArchivo = "data/historial_rutinas.json";
    QJsonArray arrayHistorial;

    QFile archivoLectura(rutaArchivo);
    if (archivoLectura.open(QIODevice::ReadOnly)) {
        QByteArray datos = archivoLectura.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(datos);
        arrayHistorial = doc.array();
        archivoLectura.close();
    }

    QJsonObject nuevaRutina;
    nuevaRutina["fecha"] = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm");

    if (ui->comboDiasRutina) {
        nuevaRutina["rutina"] = ui->comboDiasRutina->currentText();
    }

    nuevaRutina["volumen_lbs"] = ultimoVolumenCalculado;

    QString txtQuemadas = ui->lblCaloriasQuemadas ? ui->lblCaloriasQuemadas->text() : "0 kcal";
    txtQuemadas.replace("🔥 Quemadas: ", "").replace(" kcal", "");
    nuevaRutina["calorias"] = txtQuemadas.toDouble();

    arrayHistorial.append(nuevaRutina);

    QFile archivoEscritura(rutaArchivo);
    if (archivoEscritura.open(QIODevice::WriteOnly)) {
        QJsonDocument docGuardar(arrayHistorial);
        archivoEscritura.write(docGuardar.toJson());
        archivoEscritura.close();
    }
}

void MainWindow::on_btnHistorialComidas_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->alimentos);
}