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
#include <QMovie>
#include <QComboBox>
#include <QGroupBox>
#include <QScrollArea>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

const QString ESTILO_BG = "background-color: transparent;";
const QString ESTILO_TITULO = "QLabel { color: #8E9BAE; font-size: 14px; font-weight: bold; background: transparent; border: none; }";
const QString ESTILO_NUMERO = "QLabel { color: #FFFFFF; font-size: 20px; font-weight: bold; background: transparent; border: none; }";
const QString ESTILO_INPUT = "QLineEdit, QComboBox { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 8px; font-size: 14px; } QLineEdit:focus, QComboBox:focus { border: 2px solid #00E5FF; background-color: #121A25; } QComboBox QAbstractItemView { background-color: #1E2736; color: white; selection-background-color: #2A3648; }";
const QString ESTILO_BTN_BASE = "QPushButton { border-radius: 8px; font-weight: bold; }";

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

    configurarEstilosBasicos();
    crearPaginaCardioNativa();
    crearPaginaInfoNativa();
    inyectarSelectorDisponibilidad();

    if (cargarPerfil(perfilUsuario)) {
        cargarDatosUI();
        actualizarDashboardVisual();
    }

    QSettings settings("VitalCoreFit", "App");

    if (ui->lblCaloriasQuemadas) {
        QString qm = settings.value("quemadasHoy", "0").toString();
        qm.replace("🔥 Quemadas: ", "").replace(" kcal", "");
        ui->lblCaloriasQuemadas->setText("🔥 Quemadas: " + qm + " kcal");
    }

    cargarDiarioAlimentosJson();
    actualizarEstadoVacioNutricion();
    actualizarDashboardVisual();
    aplicarEstilosCyberpunk();
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

void MainWindow::configurarEstilosBasicos()
{
    if (ui->listWidget) {
        ui->listWidget->clear();
        ui->listWidget->addItems(QStringList({
            "Dashboard",
            "Estadísticas",
            "Nutricion",
            "Rutinas",
            "Cardio",
            "Guia",
            "Perfil",
            "¿Cómo Funciona?"
        }));
        ui->listWidget->setCurrentRow(0);
    }

    if (ui->btnHistorialComidas) {
        ui->btnHistorialComidas->hide();
    }

    if (ui->listaComidasHoy) {
        ui->listaComidasHoy->setStyleSheet(
            "QListWidget { background-color: #1E2736; border-radius: 12px; border: 1px solid #2A3648; outline: none; }\n"
            "QListWidget::item { background-color: #0F1722; border-radius: 6px; border-left: 4px solid #00E676; margin-bottom: 5px; }\n"
            "QListWidget::item:hover { background-color: #2A3648; }"
            );
    }

    if (ui->stackedWidget) {
        ui->stackedWidget->setCurrentWidget(ui->dashboard);
    }

    if (ui->page_guia) {
        if (ui->page_guia->layout()) {
            QLayoutItem *item;
            while ((item = ui->page_guia->layout()->takeAt(0)) != nullptr) {
                delete item->widget();
                delete item;
            }
            delete ui->page_guia->layout();
        }

        QHBoxLayout *layGuia = new QHBoxLayout(ui->page_guia);
        layGuia->setSpacing(20);

        QListWidget *listaEjercicios = new QListWidget();
        listaEjercicios->setStyleSheet(
            "QListWidget { background-color: #1E2736; border-radius: 12px; border: 1px solid #2A3648; color: white; font-size: 16px; outline: none; }\n"
            "QListWidget::item { padding: 15px; border-bottom: 1px solid #2A3648; }\n"
            "QListWidget::item:selected { background-color: #00E5FF; color: #121A25; font-weight: bold; border-radius: 8px; }"
            );

        QStringList ejerciciosNombres = {
            "Bench Press (Mancuernas)", "Overhead Press (Hombros)", "Elevaciones Laterales",
            "Tricep V-Grip", "Pull Ups (Dominadas)", "Remo con Mancuerna", "Face Pulls",
            "Barbell Curl (Bíceps)", "Hammer Curl", "Sentadilla Libre", "Peso Muerto Rumano (RDL)",
            "Zancadas (Lunges)", "Elevación de Talones", "Press Inclinado (Mancuernas)", "Pec Fly (Aperturas)"
        };
        listaEjercicios->addItems(ejerciciosNombres);

        QWidget *panelDer = new QWidget();
        QVBoxLayout *layDer = new QVBoxLayout(panelDer);
        layDer->setContentsMargins(0, 0, 0, 0);

        QLabel *lblImagen = new QLabel();
        lblImagen->setAlignment(Qt::AlignCenter);
        lblImagen->setScaledContents(true);
        lblImagen->setMaximumHeight(350);
        lblImagen->setStyleSheet("QLabel { background-color: #0F1722; border: 2px dashed #2A3648; border-radius: 12px; }");

        QLabel *lblTecnica = new QLabel("");
        lblTecnica->setWordWrap(true);
        lblTecnica->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        lblTecnica->setStyleSheet("QLabel { color: #FFFFFF; font-size: 16px; margin-top: 20px; line-height: 1.5; }");

        layDer->addWidget(lblImagen);
        layDer->addWidget(lblTecnica);
        layDer->addStretch();

        layGuia->addWidget(listaEjercicios, 1);
        layGuia->addWidget(panelDer, 2);

        connect(listaEjercicios, &QListWidget::currentTextChanged, [lblImagen, lblTecnica](const QString &ejercicio) {

            if (lblImagen->movie()) {
                lblImagen->movie()->stop();
                delete lblImagen->movie();
                lblImagen->setMovie(nullptr);
            }

            QString rutaGif = "data/default.gif";
            QString txt = "";

            if (ejercicio == "Bench Press (Mancuernas)") { rutaGif = "data/bench_press.gif"; txt = "Técnica: Acuéstate manteniendo 5 puntos de apoyo en la banca. Retrae las escápulas y empuja el peso sobre el pecho."; }
            else if (ejercicio == "Overhead Press (Hombros)") { rutaGif = "data/ohp.gif"; txt = "Técnica: Core firme, no arquees la espalda baja. Empuja las mancuernas sobre la cabeza hasta bloquear codos."; }
            else if (ejercicio == "Elevaciones Laterales") { rutaGif = "data/laterales.gif"; txt = "Técnica: Inclinación ligera hacia adelante. Sube los brazos guiando el movimiento con los codos."; }
            else if (ejercicio == "Tricep V-Grip") { rutaGif = "data/pushdown.gif"; txt = "Técnica: Codos pegados al cuerpo en todo momento. Empuja hacia abajo bloqueando los tríceps al final."; }
            else if (ejercicio == "Pull Ups (Dominadas)") { rutaGif = "data/pull_ups.gif"; txt = "Técnica: Agarre un poco más ancho que los hombros. Sube hasta pasar la barbilla y baja controlado."; }
            else if (ejercicio == "Remo con Mancuerna") { rutaGif = "data/remo.gif"; txt = "Técnica: Apoya rodilla y mano en la banca. Jala la mancuerna hacia tu cadera apretando la espalda."; }
            else if (ejercicio == "Face Pulls") { rutaGif = "data/facepull.gif"; txt = "Técnica: Jala la polea hacia tu frente, separando las manos y contrayendo los deltoides posteriores."; }
            else if (ejercicio == "Barbell Curl (Bíceps)") { rutaGif = "data/curl_biceps.gif"; txt = "Técnica: Mantén los codos fijos a tus costados, no te balancees. Aprieta el bíceps arriba."; }
            else if (ejercicio == "Hammer Curl") { rutaGif = "data/hammer.gif"; txt = "Técnica: Agarre neutro (palmas enfrentadas). Sube controladamente para trabajar el braquiorradial."; }
            else if (ejercicio == "Sentadilla Libre") { rutaGif = "data/sentadilla.gif"; txt = "Técnica: Pecho arriba, espalda recta. Rompe el paralelo (baja de 90 grados) si tu movilidad lo permite."; }
            else if (ejercicio == "Peso Muerto Rumano (RDL)") { rutaGif = "data/rdl.gif"; txt = "Técnica: Empuja la cadera hacia atrás con rodillas semi-flexionadas hasta sentir estiramiento en isquiotibiales."; }
            else if (ejercicio == "Zancadas (Lunges)") { rutaGif = "data/lunges.gif"; txt = "Técnica: Da un paso firme y baja hasta que la rodilla trasera casi toque el piso. Mantén el torso recto."; }
            else if (ejercicio == "Elevación de Talones") { rutaGif = "data/calf.gif"; txt = "Técnica: Sube explosivamente sobre las puntas de los pies y baja lento sintiendo el estiramiento."; }
            else if (ejercicio == "Press Inclinado (Mancuernas)") { rutaGif = "data/incline_press.gif"; txt = "Técnica: Banca a 30-45 grados. Empuja enfocándote en la parte superior del pecho."; }
            else if (ejercicio == "Pec Fly (Aperturas)") { rutaGif = "data/pec_fly.gif"; txt = "Técnica: Codos ligeramente flexionados, abre los brazos sintiendo el estiramiento en el pectoral."; }

            QMovie *gif = new QMovie(rutaGif);
            lblImagen->setMovie(gif);
            gif->start();
            lblTecnica->setText("🔥 " + ejercicio + "\n\n" + txt);
        });

        listaEjercicios->setCurrentRow(0);
    }
}

void MainWindow::crearPaginaInfoNativa()
{
    page_info = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(page_info);
    mainLayout->setContentsMargins(20, 20, 20, 20);


    QScrollArea *scrollInfo = new QScrollArea();
    scrollInfo->setWidgetResizable(true);
    scrollInfo->setStyleSheet(
        "QScrollArea { border: none; background: transparent; }\n"
        "QWidget#qt_scrollarea_viewport { background: transparent; }"
        );


    QFrame *tarjetaInfo = new QFrame();
    tarjetaInfo->setStyleSheet("QFrame { background-color: #121A25; border: 1px solid #2A3648; border-radius: 12px; }");
    QVBoxLayout *layout = new QVBoxLayout(tarjetaInfo);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel *lblTitulo = new QLabel("VitalCoreFit - Plataforma Integral");
    lblTitulo->setStyleSheet("color: #00E5FF; font-size: 28px; font-weight: bold; border: none; background: transparent;");
    lblTitulo->setAlignment(Qt::AlignCenter);

    QLabel *lblDesc = new QLabel(
        "<div style='font-size: 14px; color: #FFFFFF; line-height: 1.5;'>"
        "<b style='color: #00E676; font-size: 16px;'>1. Diagnóstico e Identificación del Problema:</b><br>"
        "Según la Encuesta Nacional de Salud de Chile (2025), el 42% de los adultos chilenos poseen obesidad. "
        "El problema actual se divide en tres partes: primero, el tener que usar múltiples apps desconectadas entre sí para comer y entrenar; "
        "segundo, la dificultad de realizar cálculos matemáticos de nutrientes o rutinas a mano sin conocimientos previos; y tercero, "
        "la falta de gráficos que muestren de forma clara el progreso a través del tiempo.<br><br>"

        "<b style='color: #00E676; font-size: 16px;'>2. La Solución y Base Matemática (VitalCoreFit):</b><br>"
        "VitalCoreFit es un programa de escritorio hecho en C++ usando Qt que soluciona los tres problemas anteriores centralizando todo en "
        "un perfil personal. Para que los cálculos sean exactos, el programa automatiza fórmulas matemáticas de salud clínica: "
        "calcula las calorías base con la <b>ecuación de Mifflin-St Jeor</b>, y usa la <b>fórmula de Brzycki</b> para medir la fuerza máxima.<br><br>"

        "<b style='color: #00E676; font-size: 16px;'>3. ¿Cómo usar la aplicación? (Módulos):</b><br>"
        "<ul>"
        "<li><b style='color: #00E5FF;'>Perfil:</b> Aquí ingresas tus datos físicos y tu objetivo. El sistema calcula automáticamente tu Meta Diaria (TDEE).</li>"
        "<li><b style='color: #00E5FF;'>Dashboard:</b> Es tu pantalla principal. Muestra tu balance neto en tiempo real (consumidas vs quemadas) y las barras de progreso exactas en gramos para Proteínas, Carbohidratos y Grasas.</li>"
        "<li><b style='color: #00E5FF;'>Nutrición:</b> Buscador interactivo donde registras lo que comes. Al hacer doble clic en un alimento de la base de datos, sus calorías se suman automáticamente a tu día.</li>"
        "<li><b style='color: #00E5FF;'>Rutinas:</b> Eliges tu disponibilidad (2 a 6 días) y el sistema te asigna una estructura de entrenamiento (Ej: PPL). Registras tus sets, repeticiones y peso (LBS) para que el sistema calcule el volumen movido. Posee un cronómetro de descanso integrado.</li>"
        "<li><b style='color: #00E5FF;'>Cardio:</b> Módulo para registrar minutos e intensidad de actividad. Las calorías quemadas se restan instantáneamente de tu balance diario.</li>"
        "<li><b style='color: #00E5FF;'>Guía:</b> Un diccionario visual integrado. Seleccionas un ejercicio y verás una animación mostrando la técnica correcta y los músculos implicados.</li>"
        "<li><b style='color: #00E5FF;'>Estadísticas:</b> Panel visual donde el programa gráfica en barras tu balance diario y dibuja una línea de progreso histórico para asegurar que exista 'Sobrecarga Progresiva'.</li>"
        "</ul><br>"

        "<b style='color: #00E676; font-size: 16px;'>4. Resultado Final Esperado:</b><br>"
        "Entregar un software funcional, estable y eficiente que permita a cualquier usuario registrar sus alimentos y actividades físicas, "
        "automatizando cálculos y proporcionando visualizaciones gráficas claras para ayudarle a cumplir su meta física y de salud."
        "</div>"
        );
    lblDesc->setWordWrap(true);
    lblDesc->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    lblDesc->setStyleSheet("border: none; background: transparent;");

    layout->addWidget(lblTitulo);
    layout->addSpacing(30);
    layout->addWidget(lblDesc);
    layout->addStretch();

    scrollInfo->setWidget(tarjetaInfo);
    mainLayout->addWidget(scrollInfo);

    ui->stackedWidget->addWidget(page_info);
}
void MainWindow::crearPaginaCardioNativa()
{
    page_cardio = new QWidget();
    QVBoxLayout *layCardio = new QVBoxLayout(page_cardio);
    layCardio->setContentsMargins(60, 40, 60, 40);

    QLabel *lblTitulo = new QLabel("Quema Calórica de Cardio");
    lblTitulo->setStyleSheet("color: #00E5FF; font-size: 28px; font-weight: bold;");
    lblTitulo->setAlignment(Qt::AlignCenter);

    inputMinutosCardio = new QLineEdit();
    inputMinutosCardio->setPlaceholderText("Minutos de entrenamiento (Ej: 30)");
    inputMinutosCardio->setValidator(new QIntValidator(1, 300, this));
    inputMinutosCardio->setAlignment(Qt::AlignCenter);
    inputMinutosCardio->setStyleSheet(
        "QLineEdit { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 12px; font-size: 16px; }\n"
        "QLineEdit:focus { border: 2px solid #00E5FF; background-color: #121A25; }"
        );

    comboIntensidadCardio = new QComboBox();
    comboIntensidadCardio->addItems(QStringList({"Ligero (Caminata)", "Moderado (Trote/Bici)", "Intenso (Sprint/HIIT)"}));
    comboIntensidadCardio->setStyleSheet(
        "QComboBox { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 12px; font-size: 16px; }\n"
        "QComboBox:focus { border: 2px solid #00E5FF; background-color: #121A25; }\n"
        "QComboBox QAbstractItemView { background-color: #1E2736; color: white; selection-background-color: #2A3648; }"
        );

    QPushButton *btnGuardarCardio = new QPushButton("🔥 Registrar Sesión de Cardio");
    btnGuardarCardio->setCursor(Qt::PointingHandCursor);
    btnGuardarCardio->setStyleSheet(
        "QPushButton { background-color: #FF1744; color: white; font-weight: bold; font-size: 18px; padding: 15px; border-radius: 10px; margin-top: 20px; }\n"
        "QPushButton:hover { background-color: #D50000; }"
        );

    layCardio->addStretch();
    layCardio->addWidget(lblTitulo);
    layCardio->addSpacing(30);
    layCardio->addWidget(inputMinutosCardio);
    layCardio->addSpacing(10);
    layCardio->addWidget(comboIntensidadCardio);
    layCardio->addSpacing(10);
    layCardio->addWidget(btnGuardarCardio);
    layCardio->addStretch();

    ui->stackedWidget->addWidget(page_cardio);

    connect(btnGuardarCardio, &QPushButton::clicked, this, &MainWindow::on_btnRegistrarCardio_clicked);
}

void MainWindow::inyectarSelectorDisponibilidad()
{
    if (ui->comboDiasRutina && ui->comboDiasRutina->parentWidget() && ui->comboDiasRutina->parentWidget()->layout()) {
        QBoxLayout* layoutRutinas = qobject_cast<QBoxLayout*>(ui->comboDiasRutina->parentWidget()->layout());

        if (layoutRutinas) {
            QComboBox* comboDisponibilidad = new QComboBox();
            comboDisponibilidad->addItems(QStringList({"6 Días (PPL)", "5 Días (Bro Split)", "4 Días (Upper/Lower)", "3 Días (Full Body)", "2 Días (Full Body)"}));
            comboDisponibilidad->setStyleSheet(
                "QComboBox { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 8px; font-size: 14px; }\n"
                "QComboBox:focus { border: 2px solid #00E5FF; background-color: #121A25; }\n"
                "QComboBox QAbstractItemView { background-color: #1E2736; color: white; selection-background-color: #2A3648; }"
                );

            QLabel *lblDisp = new QLabel("Disponibilidad de Entrenamiento:");
            lblDisp->setStyleSheet("QLabel { color: #8E9BAE; font-size: 14px; font-weight: bold; background: transparent; border: none; }");

            layoutRutinas->insertWidget(0, comboDisponibilidad);
            layoutRutinas->insertWidget(0, lblDisp);

            connect(comboDisponibilidad, &QComboBox::currentTextChanged, [this](const QString& disp) {
                ui->comboDiasRutina->clear();
                if (disp.contains("6 Días")) {
                    ui->comboDiasRutina->addItems(QStringList({"Lunes (Push)", "Martes (Pull)", "Miércoles (Legs)", "Jueves (Push)", "Viernes (Pull)", "Sábado (Legs)"}));
                }
                else if (disp.contains("5 Días")) {
                    ui->comboDiasRutina->addItems(QStringList({"Lunes (Pecho)", "Martes (Espalda)", "Miércoles (Piernas)", "Jueves (Hombros)", "Viernes (Brazos)"}));
                }
                else if (disp.contains("4 Días")) {
                    ui->comboDiasRutina->addItems(QStringList({"Lunes (Upper)", "Martes (Lower)", "Jueves (Upper)", "Viernes (Lower)"}));
                }
                else if (disp.contains("3 Días")) {
                    ui->comboDiasRutina->addItems(QStringList({"Lunes (Full Body)", "Miércoles (Full Body)", "Viernes (Full Body)"}));
                }
                else if (disp.contains("2 Días")) {
                    ui->comboDiasRutina->addItems(QStringList({"Día 1 (Full Body A)", "Día 2 (Full Body B)"}));
                }
            });

            ui->comboDiasRutina->clear();
            ui->comboDiasRutina->addItems(QStringList({"Lunes (Push)", "Martes (Pull)", "Miércoles (Legs)", "Jueves (Push)", "Viernes (Pull)", "Sábado (Legs)"}));
        }
    }
}

void MainWindow::aplicarEstilosCyberpunk()
{
    if (ui->btnDescanso) {
        ui->btnDescanso->setStyleSheet(
            "QPushButton { background-color: #121A25; color: #00E5FF; border: 2px solid #00E5FF; border-radius: 8px; font-size: 16px; font-weight: bold; padding: 8px; }\n"
            "QPushButton:hover { background-color: #00E5FF; color: #121A25; }"
            );
        ui->btnDescanso->setCursor(Qt::PointingHandCursor);
    }

    if (ui->lblCronometro) {
        ui->lblCronometro->setStyleSheet("QLabel { color: #00E676; font-size: 42px; font-weight: bold; font-family: 'Segoe UI', monospace; background-color: transparent; }");
        ui->lblCronometro->setAlignment(Qt::AlignCenter);
    }

    QString estiloTarjeta = "QFrame { background-color: #121A25; border-radius: 12px; border: 1px solid #2A3648; }";
    if (ui->tarjetaBalance) ui->tarjetaBalance->setStyleSheet(estiloTarjeta);
    if (ui->tarjetaConsumidas) ui->tarjetaConsumidas->setStyleSheet(estiloTarjeta);
    if (ui->tarjetaMacros) ui->tarjetaMacros->setStyleSheet(estiloTarjeta);

    if (ui->dashboard) {
        for (QLabel* lbl : ui->dashboard->findChildren<QLabel*>()) {
            if (lbl->objectName().contains("lblCalorias") || lbl->objectName().contains("lblBalance") || lbl->objectName().contains("lblMeta")) {
                lbl->setStyleSheet("QLabel { color: #FFFFFF; font-size: 20px; font-weight: bold; background: transparent; border: none; }");
                lbl->setAlignment(Qt::AlignCenter);
            } else {
                lbl->setStyleSheet("QLabel { color: #8E9BAE; font-size: 14px; font-weight: bold; background: transparent; border: none; }");
            }
        }
    }

    if (ui->buscadorAlimentos) {
        ui->buscadorAlimentos->setStyleSheet(
            "QLineEdit { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 8px; font-size: 16px; }\n"
            "QLineEdit:focus { border: 2px solid #00E5FF; }"
            );
    }

    if (ui->btnResetDia) {
        ui->btnResetDia->setStyleSheet(
            "QPushButton { background-color: #FF1744; color: white; border-radius: 8px; padding: 10px; font-weight: bold; font-size: 14px; }\n"
            "QPushButton:hover { background-color: #D50000; }"
            );
        ui->btnResetDia->setCursor(Qt::PointingHandCursor);
    }

    if (ui->lblCaloriasNutricion) {
        ui->lblCaloriasNutricion->setStyleSheet("QLabel#lblCaloriasNutricion { color: #FFFFFF; font-size: 16px; font-weight: bold; background: transparent; border: none; }");
        ui->lblCaloriasNutricion->setAlignment(Qt::AlignCenter);
    }

    if (ui->perfil) {
        QString estiloInputs =
            "QLineEdit, QComboBox { background-color: #1E2736; color: white; border: 2px solid #2A3648; border-radius: 8px; padding: 8px; font-size: 14px; }\n"
            "QLineEdit:focus, QComboBox:focus { border: 2px solid #00E5FF; background-color: #121A25; }\n"
            "QComboBox QAbstractItemView { background-color: #1E2736; color: white; selection-background-color: #2A3648; }";

        for (QWidget* w : ui->perfil->findChildren<QWidget*>()) {
            if (qobject_cast<QLineEdit*>(w) || qobject_cast<QComboBox*>(w)) {
                w->setStyleSheet(estiloInputs);
            } else if (qobject_cast<QLabel*>(w)) {
                w->setStyleSheet("QLabel { color: #8E9BAE; font-size: 14px; font-weight: bold; background: transparent; border: none; }");
            }
        }
    }

    if (ui->btnGuardarPerfil) {
        ui->btnGuardarPerfil->setStyleSheet(
            "QPushButton { background-color: #00E5FF; color: #121A25; border-radius: 10px; padding: 12px; font-size: 16px; font-weight: bold; }\n"
            "QPushButton:hover { background-color: #00B8D4; }"
            );
        ui->btnGuardarPerfil->setCursor(Qt::PointingHandCursor);
    }
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

    double quemadas = 0.0;
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

    int protesConsumidas = (consumidas * 0.30) / 4;
    int carbosConsumidos = (consumidas * 0.40) / 4;
    int grasasConsumidas = (consumidas * 0.30) / 9;

    QString baseBar = "QProgressBar { border: none; background-color: #1E2736; border-radius: 8px; text-align: center; color: white; font-weight: bold; }\nQProgressBar::chunk { border-radius: 8px; ";

    if (ui->barProteinas) {
        ui->barProteinas->setMaximum(metaProtes);
        ui->barProteinas->setValue(protesConsumidas);
        ui->barProteinas->setFormat(QString::number(protesConsumidas) + "g / " + QString::number(metaProtes) + "g");
        ui->barProteinas->setStyleSheet(baseBar + "background-color: #00E676; }");
    }

    if (ui->barCarbos) {
        ui->barCarbos->setMaximum(metaCarbos);
        ui->barCarbos->setValue(carbosConsumidos);
        ui->barCarbos->setFormat(QString::number(carbosConsumidos) + "g / " + QString::number(metaCarbos) + "g");
        ui->barCarbos->setStyleSheet(baseBar + "background-color: #FF9100; }");
    }

    if (ui->barGrasas) {
        ui->barGrasas->setMaximum(metaGrasas);
        ui->barGrasas->setValue(grasasConsumidas);
        ui->barGrasas->setFormat(QString::number(grasasConsumidas) + "g / " + QString::number(metaGrasas) + "g");
        ui->barGrasas->setStyleSheet(baseBar + "background-color: #FF1744; }");
    }
}

void MainWindow::on_btnGuardarPerfil_clicked()
{
    if (ui->inputNombre->text().isEmpty() || ui->inputEdad->text().isEmpty() || ui->inputPeso->text().isEmpty() || ui->inputAltura->text().isEmpty()) {
        QMessageBox::warning(this, "Campos Incompletos", "Por favor, completa todos tus datos.");
        return;
    }

    perfilUsuario.nombre = ui->inputNombre->text().toStdString();
    perfilUsuario.edad = ui->inputEdad->text().toInt();
    perfilUsuario.peso = ui->inputPeso->text().toDouble();
    perfilUsuario.altura = ui->inputAltura->text().toDouble();
    perfilUsuario.GeneroUsuario = (ui->comboGenero->currentText() == "Masculino") ? Genero::Masculino : Genero::Femenino;

    QString obj = ui->comboObjetivo->currentText();
    perfilUsuario.ObjetivoUsuario = (obj == "Bajar") ? Objetivo::Bajar : (obj == "Mantener" ? Objetivo::Mantener : Objetivo::Subir);

    QString act = ui->comboActividad->currentText();
    perfilUsuario.NivelActividadUsuario = (act == "Sedentario") ? NivelActividad::Sedentario : (act == "Ligero" ? NivelActividad::Ligero : (act == "Activo" ? NivelActividad::Activo : NivelActividad::MuyActivo));

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

void MainWindow::on_btnHistorialComidas_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->alimentos);
}

void MainWindow::actualizarEstadoVacioNutricion()
{
    if (listaDelDia.cantidad == 0) {
        ui->listaComidasHoy->clear();
        QListWidgetItem *itemVacio = new QListWidgetItem("(AÚN NO HAS COMENZADO A COMER)");
        itemVacio->setTextAlignment(Qt::AlignCenter);
        itemVacio->setForeground(QColor("#8E9BAE"));
        itemVacio->setFlags(Qt::NoItemFlags);
        ui->listaComidasHoy->addItem(itemVacio);
    }
}

void MainWindow::on_buscadorAlimentos_textChanged(const QString &arg1)
{
    ui->listaResultadosBusqueda->clear();

    if (arg1.isEmpty()) {
        return;
    }

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

    if (ui->listaComidasHoy->count() == 1 && ui->listaComidasHoy->item(0)->text() == "(AÚN NO HAS COMENZADO A COMER)") {
        ui->listaComidasHoy->clear();
    }

    QListWidgetItem *itemVisual = new QListWidgetItem(ui->listaComidasHoy);
    itemVisual->setSizeHint(QSize(0, 45));

    QWidget *filaWidget = new QWidget();
    filaWidget->setStyleSheet("background-color: transparent;");

    QHBoxLayout *layoutFila = new QHBoxLayout(filaWidget);
    layoutFila->setContentsMargins(10, 0, 10, 0);

    QLabel *lblComida = new QLabel(QString::fromStdString(alimento.nombre) + " 100g  +" + QString::number(alimento.calorias) + " kcal");
    lblComida->setStyleSheet("color: white; font-family: 'Segoe UI'; font-size: 14px; font-weight: bold; background: transparent; border: none;");

    QPushButton *btnBorrar = new QPushButton(QString::fromUtf8("\u2716"));
    btnBorrar->setFixedSize(26, 26);
    btnBorrar->setCursor(Qt::PointingHandCursor);
    btnBorrar->setStyleSheet(
        "QPushButton { background-color: #FF1744; color: white; border-radius: 13px; font-size: 12px; padding-bottom: 1px; border: none; }\n"
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
        actualizarEstadoVacioNutricion();
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

        if (ui->stackedWidget && ui->alimentos) {
            ui->stackedWidget->setCurrentWidget(ui->alimentos);
        }
    }

    actualizarDashboardVisual();
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
    if (!archivo.open(QIODevice::ReadOnly)) {
        return;
    }

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

    if (diaRutina.contains("Push") || diaRutina.contains("Pecho")) {
        ejerciciosHoy = {
            {"Bench Press (Mancuernas)", 4, "8", "100"},
            {"Overhead Press (Hombros)", 3, "10", "60"},
            {"Press Inclinado (Mancuernas)", 3, "10", "80"},
            {"Elevaciones Laterales", 3, "15", "20"},
            {"Tricep V-Grip", 3, "12", "40"}
        };
    }
    else if (diaRutina.contains("Pull") || diaRutina.contains("Espalda")) {
        ejerciciosHoy = {
            {"Pull Ups (Dominadas)", 4, "Fallo", "0"},
            {"Remo con Mancuerna", 3, "10", "50"},
            {"Face Pulls", 3, "15", "30"},
            {"Barbell Curl (Bíceps)", 3, "10", "60"},
            {"Hammer Curl", 3, "12", "30"}
        };
    }
    else if (diaRutina.contains("Legs") || diaRutina.contains("Piernas") || diaRutina.contains("Lower")) {
        ejerciciosHoy = {
            {"Sentadilla Libre", 4, "8", "185"},
            {"Peso Muerto Rumano (RDL)", 3, "10", "135"},
            {"Zancadas (Lunges)", 3, "12", "40"},
            {"Elevación de Talones", 4, "15", "100"}
        };
    }
    else if (diaRutina.contains("Upper")) {
        ejerciciosHoy = {
            {"Bench Press (Mancuernas)", 3, "8", "100"},
            {"Pull Ups (Dominadas)", 3, "Fallo", "0"},
            {"Overhead Press (Hombros)", 3, "10", "60"},
            {"Barbell Curl (Bíceps)", 3, "10", "60"}
        };
    }
    else if (diaRutina.contains("Hombros")) {
        ejerciciosHoy = {
            {"Overhead Press (Hombros)", 4, "8", "60"},
            {"Elevaciones Laterales", 4, "15", "20"},
            {"Face Pulls", 3, "15", "30"}
        };
    }
    else if (diaRutina.contains("Brazos")) {
        ejerciciosHoy = {
            {"Barbell Curl (Bíceps)", 3, "10", "60"},
            {"Tricep V-Grip", 3, "12", "40"},
            {"Hammer Curl", 3, "12", "30"}
        };
    }
    else {
        ejerciciosHoy = {
            {"Sentadilla Libre", 3, "8", "185"},
            {"Bench Press (Mancuernas)", 3, "8", "100"},
            {"Pull Ups (Dominadas)", 3, "Fallo", "0"},
            {"Overhead Press (Hombros)", 3, "10", "60"},
            {"Barbell Curl (Bíceps)", 2, "12", "60"},
            {"Tricep V-Grip", 2, "12", "40"}
        };
    }

    QSettings memoriaMuscular("VitalCoreFit", "Pesos");

    for (const auto& ej : ejerciciosHoy) {
        QGroupBox *tarjetaEjercicio = new QGroupBox(ej.nombre);
        tarjetaEjercicio->setStyleSheet(
            "QGroupBox { font-size: 16px; font-weight: bold; color: #00E5FF; border: 1px solid #2A3648; border-radius: 8px; margin-top: 15px; background-color: #121A25; }\n"
            "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }"
            );

        QVBoxLayout *layoutTarjeta = new QVBoxLayout(tarjetaEjercicio);

        QWidget *filaHeader = new QWidget();
        QHBoxLayout *layoutHeader = new QHBoxLayout(filaHeader);
        layoutHeader->setContentsMargins(0, 5, 0, 0);

        QLabel *lblSetH = new QLabel("SET");
        QLabel *lblRepsH = new QLabel("REPS");
        QLabel *lblPesoH = new QLabel("LBS");

        QString estH = "color: #8E9BAE; font-weight: bold; font-size: 12px;";
        lblSetH->setStyleSheet(estH);
        lblRepsH->setStyleSheet(estH);
        lblPesoH->setStyleSheet(estH);

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
            inputReps->setStyleSheet(
                "QLineEdit { background: #1E2736; color: white; border: none; border-radius: 4px; font-size: 14px; padding: 5px; }\n"
                "QLineEdit:focus { border: 1px solid #00E5FF; }"
                );
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
            btnCheck->setCheckable(true);
            btnCheck->setStyleSheet(
                "QPushButton { background-color: #2A3648; color: #8E9BAE; border-radius: 8px; font-size: 18px; font-weight: bold; border: none; }\n"
                "QPushButton:checked { background-color: #00E676; color: black; }"
                );

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
        "QPushButton { background-color: #00E676; color: #121A25; font-size: 18px; font-weight: bold; border-radius: 10px; padding: 15px; margin-top: 20px; }\n"
        "QPushButton:hover { background-color: #00C853; }"
        );
    connect(btnFinalizar, &QPushButton::clicked, this, &MainWindow::on_btnFinalizarRutina_clicked);

    layoutPrincipal->addWidget(btnFinalizar);
    layoutPrincipal->addStretch();

    ui->scrollArea->setWidget(contenedorPrincipal);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setStyleSheet(
        "QScrollArea { border: none; background: transparent; }\n"
        "QWidget#qt_scrollarea_viewport { background: transparent; }"
        );
}

void MainWindow::calcularVolumenEnVivo()
{
    if (!ui->scrollArea || !ui->scrollArea->widget()) {
        return;
    }

    double volumenTotalLibras = 0;
    QSettings memoriaMuscular("VitalCoreFit", "Pesos");

    QList<QGroupBox*> tarjetas = ui->scrollArea->widget()->findChildren<QGroupBox*>();

    for (QGroupBox* tarjeta : tarjetas) {
        QList<QLineEdit*> inputs = tarjeta->findChildren<QLineEdit*>();
        QList<QPushButton*> botones = tarjeta->findChildren<QPushButton*>();

        int indexBoton = 0;
        for (int i = 0; i < inputs.size() - 1; i += 2) {
            if (indexBoton >= botones.size()) break;

            QPushButton* btnCheck = botones.at(indexBoton);
            indexBoton++;

            if (btnCheck && btnCheck->isChecked()) {
                QLineEdit* inputReps = inputs.at(i);
                QLineEdit* inputPeso = inputs.at(i+1);

                QString txtReps = inputReps->text().isEmpty() ? inputReps->placeholderText() : inputReps->text();
                QString txtPeso = inputPeso->text().isEmpty() ? inputPeso->placeholderText() : inputPeso->text();

                memoriaMuscular.setValue(tarjeta->title() + "_reps", txtReps);
                memoriaMuscular.setValue(tarjeta->title() + "_peso", txtPeso);

                int reps = 0;
                if (txtReps.toLower() == "fallo") {
                    reps = 10;
                } else {
                    reps = txtReps.section("-", 0, 0).toInt();
                }

                double peso = txtPeso.toDouble();
                if (reps > 0) {
                    volumenTotalLibras += (reps * peso);
                }
            }
        }
    }

    ultimoVolumenCalculado = volumenTotalLibras;
    double caloriasQuemadas = volumenTotalLibras * 0.005;

    if (ui->lblCaloriasQuemadas) {
        ui->lblCaloriasQuemadas->setText("🔥 Quemadas: " + QString::number(caloriasQuemadas, 'f', 0) + " kcal");
    }

    actualizarDashboardVisual();

    if (ui->stackedWidget && ui->stackedWidget->currentWidget() == ui->page_graficos) {
        dibujarGrafico();
    }
}

void MainWindow::on_btnFinalizarRutina_clicked()
{
    calcularVolumenEnVivo();
    guardarHistorialRutina();

    QString txtQuemadas = ui->lblCaloriasQuemadas ? ui->lblCaloriasQuemadas->text() : "0";
    txtQuemadas.replace("🔥 Quemadas: ", "");

    QString nombreRutina = ui->comboDiasRutina ? ui->comboDiasRutina->currentText() : "Desconocida";

    QString resumen = "¡Entrenamiento Registrado con Éxito!\n\n"
                      "Rutina: " + nombreRutina + "\n"
                                       "Volumen total movido: " + QString::number(ultimoVolumenCalculado, 'f', 1) + " lbs\n"
                                                                          "Calorías quemadas: " + txtQuemadas + "\n\n"
                                      "Tus datos han sido guardados en tu historial.";

    QMessageBox::information(this, "Éxito", resumen);
}

void MainWindow::guardarHistorialRutina()
{
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

void MainWindow::on_btnExportarReporte_clicked()
{

}

void MainWindow::on_btnDescanso_clicked()
{
    tiempoRestante = 90;

    if (ui->lblCronometro) {
        ui->lblCronometro->setText("01:30");
        ui->lblCronometro->setStyleSheet("QLabel { color: #00E676; font-size: 42px; font-weight: bold; background-color: transparent; }");
    }

    timerDescanso->start(1000);
}

void MainWindow::actualizarCronometro()
{
    tiempoRestante--;

    if (ui->lblCronometro) {
        int minutos = tiempoRestante / 60;
        int segundos = tiempoRestante % 60;

        QString textoReloj = QString("%1:%2")
                                 .arg(minutos, 2, 10, QChar('0'))
                                 .arg(segundos, 2, 10, QChar('0'));

        ui->lblCronometro->setText(textoReloj);
    }

    if (tiempoRestante <= 0) {
        timerDescanso->stop();
        if (ui->lblCronometro) {
            ui->lblCronometro->setStyleSheet("QLabel { color: #FF1744; font-size: 42px; font-weight: bold; background-color: transparent; }");
        }
        QMessageBox::information(this, "¡Tiempo!", "¡A darle a la siguiente serie!");
    }
}

void MainWindow::on_btnResetDia_clicked()
{
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Finalizar Día",
                                      "¿Terminaste por hoy? Esto reiniciará todos tus contadores a cero para empezar un nuevo día de entrenamiento.",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        if (ui->listaComidasHoy) {
            ui->listaComidasHoy->clear();
        }

        if (ui->lblCaloriasQuemadas) {
            ui->lblCaloriasQuemadas->setText("🔥 Quemadas: 0 kcal");
        }

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

        actualizarEstadoVacioNutricion();
        actualizarDashboardVisual();

        if (ui->stackedWidget && ui->stackedWidget->currentWidget() == ui->page_graficos) {
            dibujarGrafico();
        }
    }
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
    else if (menuSeleccionado == "Cardio") {
        ui->stackedWidget->setCurrentWidget(page_cardio);
    }
    else if (menuSeleccionado == "Guia" || menuSeleccionado == "Guía") {
        ui->stackedWidget->setCurrentWidget(ui->page_guia);
    }
    else if (menuSeleccionado == "Perfil") {
        ui->stackedWidget->setCurrentWidget(ui->perfil);
    }
    else if (menuSeleccionado == "Estadísticas" || menuSeleccionado == "Estadisticas") {
        dibujarGrafico();
        ui->stackedWidget->setCurrentWidget(ui->page_graficos);
    }
    else if (menuSeleccionado == "¿Cómo Funciona?" || menuSeleccionado == "Como Funciona") {
        ui->stackedWidget->setCurrentWidget(page_info);
    }
}

void MainWindow::on_btnRegistrarCardio_clicked()
{
    if (inputMinutosCardio->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Ingresa los minutos entrenados.");
        return;
    }

    int min = inputMinutosCardio->text().toInt();
    int factor = 5;

    if (comboIntensidadCardio->currentIndex() == 1) {
        factor = 8;
    }
    else if (comboIntensidadCardio->currentIndex() == 2) {
        factor = 12;
    }

    int quemadasNuevas = min * factor;
    int quemadasActuales = 0;

    if (ui->lblCaloriasQuemadas) {
        QString txt = ui->lblCaloriasQuemadas->text();
        txt.replace("🔥 Quemadas: ", "").replace(" kcal", "");
        quemadasActuales = txt.toInt();
    }

    int totalQuemadas = quemadasActuales + quemadasNuevas;

    if (ui->lblCaloriasQuemadas) {
        ui->lblCaloriasQuemadas->setText("🔥 Quemadas: " + QString::number(totalQuemadas) + " kcal");
    }

    QSettings settings("VitalCoreFit", "App");
    settings.setValue("quemadasHoy", QString::number(totalQuemadas));

    actualizarDashboardVisual();
    inputMinutosCardio->clear();

    QMessageBox::information(this, "Cardio Registrado", "¡Excelente trabajo!\nQuemaste " + QString::number(quemadasNuevas) + " kcal extra.");

    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentWidget(ui->dashboard);
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
    chartBarras->setBackgroundBrush(QBrush(QColor(0x1E2736)));
    chartBarras->setTitleBrush(QBrush(Qt::white));
    chartBarras->legend()->setLabelColor(Qt::white);

    connect(seriesBarras, &QBarSeries::hovered, this, [](bool status, int index, QBarSet *barset) {
        if (status) {
            double valor = barset->at(index);
            QString texto = barset->label() + ": " + QString::number(valor, 'f', 0) + " kcal";
            QToolTip::showText(QCursor::pos(), texto);
        } else {
            QToolTip::hideText();
        }
    });

    QBarCategoryAxis *axisXB = new QBarCategoryAxis();
    axisXB->append(QStringList({"Hoy"}));
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

    QBarSet *setVolumen = new QBarSet("Volumen Total Movido (lbs)");
    setVolumen->setColor(QColor(0x00E5FF));

    QStringList fechasHistorial;
    double maxVolumen = 1000;

    QFile archivoLectura("data/historial_rutinas.json");
    if (archivoLectura.open(QIODevice::ReadOnly)) {
        QJsonArray arrayHistorial = QJsonDocument::fromJson(archivoLectura.readAll()).array();
        for (int i = 0; i < arrayHistorial.size(); ++i) {
            QJsonObject rutina = arrayHistorial[i].toObject();
            double vol = rutina["volumen_lbs"].toDouble();
            if (vol > 0) {
                QString fecha = rutina["fecha"].toString().section(" ", 0, 0);
                *setVolumen << vol;
                fechasHistorial << fecha;
                if (vol > maxVolumen) {
                    maxVolumen = vol;
                }
            }
        }
        archivoLectura.close();
    }

    if (fechasHistorial.isEmpty()) {
        *setVolumen << 0;
        fechasHistorial << "Sin datos";
    }

    QBarSeries *seriesVolumen = new QBarSeries();
    seriesVolumen->append(setVolumen);

    connect(seriesVolumen, &QBarSeries::hovered, this, [](bool status, int index, QBarSet *barset) {
        if (status) {
            double valor = barset->at(index);
            QString texto = "Volumen: " + QString::number(valor, 'f', 1) + " lbs";
            QToolTip::showText(QCursor::pos(), texto);
        } else {
            QToolTip::hideText();
        }
    });

    QChart *chartProgreso = new QChart();
    chartProgreso->addSeries(seriesVolumen);
    chartProgreso->setTitle("Sobrecarga Progresiva (Volumen por Sesión)");
    chartProgreso->setAnimationOptions(QChart::SeriesAnimations);
    chartProgreso->setBackgroundBrush(QBrush(QColor(0x1E2736)));
    chartProgreso->setTitleBrush(QBrush(Qt::white));
    chartProgreso->legend()->setLabelColor(Qt::white);

    QBarCategoryAxis *axisXP = new QBarCategoryAxis();
    axisXP->append(fechasHistorial);
    axisXP->setLabelsColor(Qt::white);
    chartProgreso->addAxis(axisXP, Qt::AlignBottom);
    seriesVolumen->attachAxis(axisXP);

    QValueAxis *axisYP = new QValueAxis();
    axisYP->setRange(0, maxVolumen + 500);
    axisYP->setLabelsColor(Qt::white);
    chartProgreso->addAxis(axisYP, Qt::AlignLeft);
    seriesVolumen->attachAxis(axisYP);

    QChartView *viewProgreso = new QChartView(chartProgreso);
    viewProgreso->setRenderHint(QPainter::Antialiasing);
    viewProgreso->setBackgroundBrush(QBrush(QColor(0x1E2736)));

    QTabWidget *tabsGraficos = new QTabWidget();
    tabsGraficos->setStyleSheet(
        "QTabWidget::pane { border: 1px solid #2A3648; background: #1E2736; border-radius: 8px; }\n"
        "QTabBar::tab { background: #121A25; color: #8E9BAE; padding: 10px 20px; border-top-left-radius: 6px; border-top-right-radius: 6px; margin-right: 2px; }\n"
        "QTabBar::tab:selected { background: #00E5FF; color: #121A25; font-weight: bold; }"
        );

    QWidget *tab1 = new QWidget();
    QVBoxLayout *lay1 = new QVBoxLayout(tab1);
    lay1->setContentsMargins(0,0,0,0);
    lay1->addWidget(viewBarras);

    QWidget *tab2 = new QWidget();
    QVBoxLayout *lay2 = new QVBoxLayout(tab2);
    lay2->setContentsMargins(0,0,0,0);
    lay2->addWidget(viewProgreso);

    tabsGraficos->addTab(tab1, "Balance Diario");
    tabsGraficos->addTab(tab2, "Progreso Histórico");

    QVBoxLayout *layoutPrincipal = new QVBoxLayout(ui->lienzoGrafico);
    layoutPrincipal->setContentsMargins(0,0,0,0);
    layoutPrincipal->addWidget(tabsGraficos);
    ui->lienzoGrafico->setLayout(layoutPrincipal);
}