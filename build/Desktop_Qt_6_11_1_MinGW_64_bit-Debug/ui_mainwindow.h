/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *dashboard;
    QVBoxLayout *verticalLayout;
    QFrame *tarjetaConsumidas;
    QVBoxLayout *verticalLayout_7;
    QFrame *tarjetaQuemadas;
    QLabel *label_9;
    QLabel *lblCaloriasQuemadas;
    QFrame *tarjetaConsumidas_2;
    QFrame *tarjetaBalance;
    QVBoxLayout *verticalLayout_8;
    QFrame *tarjetaConsumidas_3;
    QLabel *label_10;
    QLabel *lblBalanceNeto;
    QLabel *lblCaloriasConsumidas;
    QLabel *lblMetaCalorica;
    QFrame *tarjetaBalance_2;
    QLabel *label;
    QFrame *tarjetaMacros;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QFrame *tarjetaMacros_2;
    QProgressBar *barProteinas;
    QLabel *label_4;
    QProgressBar *barCarbos;
    QLabel *label_5;
    QProgressBar *progressBar_3;
    QWidget *alimentos;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnHistorialComidas;
    QPushButton *btnAgregarComida;
    QLabel *lblCaloriasNutricion;
    QListWidget *listaComidasHoy;
    QWidget *rutinas;
    QGridLayout *gridLayout;
    QComboBox *comboDiasRutina;
    QTabWidget *TABLA;
    QWidget *Pesas;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QWidget *Cardio;
    QPushButton *btnFinalizarRutina;
    QWidget *perfil;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *Peso_2;
    QLineEdit *inputPeso;
    QLabel *Peso;
    QLabel *label_6;
    QLabel *label_8;
    QComboBox *comboActividad;
    QLabel *nombre;
    QLineEdit *inputEdad;
    QLabel *label_7;
    QLabel *Edad;
    QLineEdit *inputAltura;
    QLineEdit *inputNombre;
    QComboBox *comboGenero;
    QComboBox *comboObjetivo;
    QPushButton *btnGuardarPerfil;
    QWidget *page_buscador;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *buscadorAlimentos;
    QListWidget *listaResultadosBusqueda;
    QPushButton *btnVolverNutricion;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(655, 487);
        MainWindow->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"/* 1FONDOS GENERALES  */\n"
"\n"
"QMainWindow {\n"
"    background-color: #0F1722;\n"
"}\n"
"\n"
"/* Forzar el fondo oscuro en las p\303\241ginas internas */\n"
"QStackedWidget, QStackedWidget > QWidget {\n"
"    background-color: #0F1722;\n"
"}\n"
"\n"
"\n"
"/* BARRA DE NAVEGACI\303\223N LATERAL */\n"
"\n"
"QListWidget {\n"
"    background-color: #1E2736;\n"
"    border: none;\n"
"    outline: none;\n"
"    padding-top: 20px;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    color: #A0AAB5;\n"
"    min-height: 40px;\n"
"    padding-left: 15px;\n"
"    border-radius: 8px;\n"
"    margin: 5px 10px 5px 10px;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #2A3648;\n"
"    color: white;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #00E5FF;\n"
"    color: #000000;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* DASHBOARD (TARJETAS Y MACROS)*/\n"
"\n"
"QFrame#tarjetaConsumidas, \n"
"QFrame#tarjetaQuemadas, \n"
""
                        "QFrame#tarjetaBalance, \n"
"QFrame#tarjetaMacros {\n"
"    background-color: #1E2736;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"/* Letras blancas para los t\303\255tulos de las tarjetas */\n"
"QFrame#tarjetaConsumidas QLabel, \n"
"QFrame#tarjetaQuemadas QLabel, \n"
"QFrame#tarjetaBalance QLabel,\n"
"QFrame#tarjetaMacros QLabel {\n"
"    color: #FFFFFF;\n"
"    font-weight: bold;\n"
"    font-size: 12px;\n"
"}\n"
"\n"
"/* Destacar los n\303\272meros grandes de las tarjetas en Cian */\n"
"QLabel#lblCaloriasConsumidas, \n"
"QLabel#lblCaloriasQuemadas, \n"
"QLabel#lblBalanceNeto {\n"
"    color: #00E5FF;\n"
"    font-size: 18px;\n"
"}\n"
"\n"
"/* Barras de Progreso */\n"
"QProgressBar {\n"
"    background-color: #2A3648;\n"
"    border: none;\n"
"    border-radius: 5px;\n"
"    height: 8px;\n"
"    color: transparent;\n"
"}\n"
"QProgressBar::chunk {\n"
"    border-radius: 5px;\n"
"}\n"
"QProgressBar#barProteinas::chunk { background-color: #00E676; }\n"
"QProgressBar#barCarbos::chunk { background-color: #FF9100; "
                        "}\n"
"QProgressBar#barGrasas::chunk { background-color: #FF1744; }\n"
"\n"
"\n"
"/* M\303\223DULO DE NUTRICI\303\223N*/\n"
"\n"
"QLineEdit#buscadorAlimentos {\n"
"    background-color: #1E2736;\n"
"    color: #FFFFFF;\n"
"    border: 2px solid #2A3648;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"}\n"
"QLineEdit#buscadorAlimentos:focus {\n"
"    border: 2px solid #00E5FF;\n"
"    background-color: #151D29;\n"
"}\n"
"\n"
"QListWidget#listaComidasHoy {\n"
"    background-color: #1E2736;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #2A3648;\n"
"    padding: 10px;\n"
"    outline: none;\n"
"}\n"
"QListWidget#listaComidasHoy::item {\n"
"    background-color: #0F1722;\n"
"    border-radius: 6px;\n"
"    border-left: 4px solid #00E676;\n"
"    color: white;\n"
"    padding: 10px;\n"
"    margin-bottom: 5px;\n"
"}\n"
"\n"
"/* M\303\223DULO DE ENTRENAMIENTO*/\n"
"\n"
"QTabWidget::pane {\n"
"    border: none;\n"
"    background-color:"
                        " #0F1722;\n"
"}\n"
"QTabBar::tab {\n"
"    background-color: #1E2736;\n"
"    color: #A0AAB5;\n"
"    padding: 8px 20px;\n"
"    margin-right: 2px;\n"
"    border-top-left-radius: 6px;\n"
"    border-top-right-radius: 6px;\n"
"}\n"
"QTabBar::tab:selected {\n"
"    background-color: #2A3648;\n"
"    color: #00E5FF;\n"
"    font-weight: bold;\n"
"    border-bottom: 2px solid #00E5FF;\n"
"}\n"
"\n"
"QComboBox#comboDiasRutina {\n"
"    background-color: #1E2736;\n"
"    color: white;\n"
"    border: 2px solid #2A3648;\n"
"    border-radius: 6px;\n"
"    padding: 5px 15px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"}\n"
"QComboBox#comboDiasRutina::drop-down {\n"
"    border: none;\n"
"}\n"
"\n"
"QTableWidget#tablaRutina {\n"
"    background-color: #1E2736;\n"
"    color: #FFFFFF;\n"
"    border: 1px solid #2A3648;\n"
"    border-radius: 8px;\n"
"    gridline-color: #2A3648;\n"
"    selection-background-color: #00E5FF;\n"
"    selection-color: #000000;\n"
"    font-size: 13px;\n"
"    outline: none;\n"
""
                        "}\n"
"QHeaderView::section {\n"
"    background-color: #0F1722;\n"
"    color: #A0AAB5;\n"
"    padding: 6px;\n"
"    border: none;\n"
"    font-weight: bold;\n"
"    border-bottom: 1px solid #2A3648;\n"
"    border-right: 1px solid #2A3648;\n"
"}\n"
"QTableCornerButton::section {\n"
"    background-color: #0F1722;\n"
"    border: none;\n"
"}\n"
"\n"
"/* M\303\223DULO DE PERFIL Y BOTONES  */\n"
"\n"
"QPushButton#btnGuardarPerfil {\n"
"    background-color: #00E5FF;\n"
"    color: #000000;\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"}\n"
"QPushButton#btnGuardarPerfil:hover {\n"
"    background-color: #33EEFF;\n"
"}\n"
"QPushButton#btnGuardarPerfil:pressed {\n"
"    background-color: #00B8CC;\n"
"}\n"
"\n"
"/* Ajuste sutil para las etiquetas del formulario de perfil */\n"
"QWidget#perfil QLabel {\n"
"    color: #A0AAB5;\n"
"    font-weight: bold;\n"
"}\n"
"/* Botones del m\303\263dulo de"
                        " nutrici\303\263n */\n"
"QPushButton#btnAgregarComida, QPushButton#btnHistorialComidas, QPushButton#btnVolverNutricion {\n"
"    background-color: #1E2736;\n"
"    color: #FFFFFF;\n"
"    border: 1px solid #2A3648;\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnAgregarComida:hover, QPushButton#btnHistorialComidas:hover, QPushButton#btnVolverNutricion:hover {\n"
"    background-color: #2A3648;\n"
"    border: 1px solid #00E5FF;\n"
"    color: #00E5FF;\n"
"}\n"
"\n"
"/* Nuevo estilo de la lista de b\303\272squedas */\n"
"QListWidget#listaResultadosBusqueda {\n"
"    background-color: #1E2736;\n"
"    border-radius: 8px;\n"
"    border: none;\n"
"    color: white;\n"
"    padding: 5px;\n"
"}\n"
"QListWidget#listaResultadosBusqueda::item {\n"
"    padding: 10px;\n"
"    border-bottom: 1px solid #2A3648;\n"
"}\n"
"QListWidget#listaResultadosBusqueda::item:hover {\n"
"    background-color: #2A3648;\n"
"}\n"
"\n"
"/* DISE\303\221O DE LA "
                        "P\303\201GINA BUSCADOR (FOTO 2)     */\n"
"\n"
"\n"
"/* El Buscador de arriba */\n"
"QLineEdit#buscadorAlimentos {\n"
"    background-color: #1E2736;\n"
"    color: #FFFFFF;\n"
"    border: 1px solid #2A3648;\n"
"    border-radius: 6px;\n"
"    padding: 12px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"\n"
"/* El efecto Cian al pasar el mouse o seleccionar (Como en tu foto) */\n"
"QListWidget#listaResultadosBusqueda::item:hover, \n"
"QListWidget#listaResultadosBusqueda::item:selected {\n"
"    background-color: #00E5FF;\n"
"    color: #000000;\n"
"    border-radius: 6px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* El bot\303\263n Volver alargado de abajo */\n"
"QPushButton#btnVolverNutricion {\n"
"    background-color: #D3D3D3; \n"
"    color: #000000;\n"
"    border: none;\n"
"    border-radius: 6px;\n"
"    padding: 10px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton#btnVolverNutricion:hover {\n"
"    background-color: #B0B0B0;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        listWidget = new QListWidget(centralwidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_2->addWidget(listWidget);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        dashboard = new QWidget();
        dashboard->setObjectName("dashboard");
        verticalLayout = new QVBoxLayout(dashboard);
        verticalLayout->setObjectName("verticalLayout");
        tarjetaConsumidas = new QFrame(dashboard);
        tarjetaConsumidas->setObjectName("tarjetaConsumidas");
        tarjetaConsumidas->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaConsumidas->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_7 = new QVBoxLayout(tarjetaConsumidas);
        verticalLayout_7->setObjectName("verticalLayout_7");
        tarjetaQuemadas = new QFrame(tarjetaConsumidas);
        tarjetaQuemadas->setObjectName("tarjetaQuemadas");
        tarjetaQuemadas->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaQuemadas->setFrameShadow(QFrame::Shadow::Raised);
        label_9 = new QLabel(tarjetaQuemadas);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(10, 20, 251, 16));
        lblCaloriasQuemadas = new QLabel(tarjetaQuemadas);
        lblCaloriasQuemadas->setObjectName("lblCaloriasQuemadas");
        lblCaloriasQuemadas->setGeometry(QRect(80, 35, 21, 21));
        tarjetaConsumidas_2 = new QFrame(tarjetaQuemadas);
        tarjetaConsumidas_2->setObjectName("tarjetaConsumidas_2");
        tarjetaConsumidas_2->setGeometry(QRect(9, 9, 171, 21));
        tarjetaConsumidas_2->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaConsumidas_2->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_7->addWidget(tarjetaQuemadas);

        tarjetaBalance = new QFrame(tarjetaConsumidas);
        tarjetaBalance->setObjectName("tarjetaBalance");
        tarjetaBalance->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaBalance->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_8 = new QVBoxLayout(tarjetaBalance);
        verticalLayout_8->setObjectName("verticalLayout_8");
        tarjetaConsumidas_3 = new QFrame(tarjetaBalance);
        tarjetaConsumidas_3->setObjectName("tarjetaConsumidas_3");
        tarjetaConsumidas_3->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaConsumidas_3->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_8->addWidget(tarjetaConsumidas_3);

        label_10 = new QLabel(tarjetaBalance);
        label_10->setObjectName("label_10");

        verticalLayout_8->addWidget(label_10);

        lblBalanceNeto = new QLabel(tarjetaBalance);
        lblBalanceNeto->setObjectName("lblBalanceNeto");

        verticalLayout_8->addWidget(lblBalanceNeto);


        verticalLayout_7->addWidget(tarjetaBalance);

        lblCaloriasConsumidas = new QLabel(tarjetaConsumidas);
        lblCaloriasConsumidas->setObjectName("lblCaloriasConsumidas");

        verticalLayout_7->addWidget(lblCaloriasConsumidas);

        lblMetaCalorica = new QLabel(tarjetaConsumidas);
        lblMetaCalorica->setObjectName("lblMetaCalorica");

        verticalLayout_7->addWidget(lblMetaCalorica);

        tarjetaBalance_2 = new QFrame(tarjetaConsumidas);
        tarjetaBalance_2->setObjectName("tarjetaBalance_2");
        tarjetaBalance_2->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaBalance_2->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_7->addWidget(tarjetaBalance_2);

        label = new QLabel(tarjetaConsumidas);
        label->setObjectName("label");

        verticalLayout_7->addWidget(label);


        verticalLayout->addWidget(tarjetaConsumidas);

        tarjetaMacros = new QFrame(dashboard);
        tarjetaMacros->setObjectName("tarjetaMacros");
        tarjetaMacros->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaMacros->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(tarjetaMacros);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(tarjetaMacros);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        tarjetaMacros_2 = new QFrame(tarjetaMacros);
        tarjetaMacros_2->setObjectName("tarjetaMacros_2");
        tarjetaMacros_2->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaMacros_2->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout_2->addWidget(tarjetaMacros_2);

        barProteinas = new QProgressBar(tarjetaMacros);
        barProteinas->setObjectName("barProteinas");
        barProteinas->setValue(24);

        verticalLayout_2->addWidget(barProteinas);

        label_4 = new QLabel(tarjetaMacros);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        barCarbos = new QProgressBar(tarjetaMacros);
        barCarbos->setObjectName("barCarbos");
        barCarbos->setValue(24);

        verticalLayout_2->addWidget(barCarbos);

        label_5 = new QLabel(tarjetaMacros);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        progressBar_3 = new QProgressBar(tarjetaMacros);
        progressBar_3->setObjectName("progressBar_3");
        progressBar_3->setValue(24);

        verticalLayout_2->addWidget(progressBar_3);


        verticalLayout->addWidget(tarjetaMacros);

        stackedWidget->addWidget(dashboard);
        alimentos = new QWidget();
        alimentos->setObjectName("alimentos");
        verticalLayout_3 = new QVBoxLayout(alimentos);
        verticalLayout_3->setObjectName("verticalLayout_3");
        btnHistorialComidas = new QPushButton(alimentos);
        btnHistorialComidas->setObjectName("btnHistorialComidas");

        verticalLayout_3->addWidget(btnHistorialComidas);

        btnAgregarComida = new QPushButton(alimentos);
        btnAgregarComida->setObjectName("btnAgregarComida");

        verticalLayout_3->addWidget(btnAgregarComida);

        lblCaloriasNutricion = new QLabel(alimentos);
        lblCaloriasNutricion->setObjectName("lblCaloriasNutricion");

        verticalLayout_3->addWidget(lblCaloriasNutricion);

        listaComidasHoy = new QListWidget(alimentos);
        listaComidasHoy->setObjectName("listaComidasHoy");

        verticalLayout_3->addWidget(listaComidasHoy);

        stackedWidget->addWidget(alimentos);
        rutinas = new QWidget();
        rutinas->setObjectName("rutinas");
        gridLayout = new QGridLayout(rutinas);
        gridLayout->setObjectName("gridLayout");
        comboDiasRutina = new QComboBox(rutinas);
        comboDiasRutina->addItem(QString());
        comboDiasRutina->addItem(QString());
        comboDiasRutina->addItem(QString());
        comboDiasRutina->addItem(QString());
        comboDiasRutina->setObjectName("comboDiasRutina");

        gridLayout->addWidget(comboDiasRutina, 0, 0, 1, 1);

        TABLA = new QTabWidget(rutinas);
        TABLA->setObjectName("TABLA");
        Pesas = new QWidget();
        Pesas->setObjectName("Pesas");
        verticalLayout_4 = new QVBoxLayout(Pesas);
        verticalLayout_4->setObjectName("verticalLayout_4");
        tableWidget = new QTableWidget(Pesas);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName("tableWidget");

        verticalLayout_4->addWidget(tableWidget);

        TABLA->addTab(Pesas, QString());
        Cardio = new QWidget();
        Cardio->setObjectName("Cardio");
        TABLA->addTab(Cardio, QString());

        gridLayout->addWidget(TABLA, 1, 0, 1, 1);

        btnFinalizarRutina = new QPushButton(rutinas);
        btnFinalizarRutina->setObjectName("btnFinalizarRutina");

        gridLayout->addWidget(btnFinalizarRutina, 2, 0, 1, 1);

        stackedWidget->addWidget(rutinas);
        perfil = new QWidget();
        perfil->setObjectName("perfil");
        verticalLayout_5 = new QVBoxLayout(perfil);
        verticalLayout_5->setObjectName("verticalLayout_5");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        Peso_2 = new QLabel(perfil);
        Peso_2->setObjectName("Peso_2");

        gridLayout_2->addWidget(Peso_2, 6, 1, 1, 1);

        inputPeso = new QLineEdit(perfil);
        inputPeso->setObjectName("inputPeso");

        gridLayout_2->addWidget(inputPeso, 3, 1, 1, 1);

        Peso = new QLabel(perfil);
        Peso->setObjectName("Peso");

        gridLayout_2->addWidget(Peso, 2, 1, 1, 1);

        label_6 = new QLabel(perfil);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_8 = new QLabel(perfil);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        comboActividad = new QComboBox(perfil);
        comboActividad->addItem(QString());
        comboActividad->addItem(QString());
        comboActividad->addItem(QString());
        comboActividad->addItem(QString());
        comboActividad->addItem(QString());
        comboActividad->setObjectName("comboActividad");

        gridLayout_2->addWidget(comboActividad, 1, 2, 1, 1);

        nombre = new QLabel(perfil);
        nombre->setObjectName("nombre");

        gridLayout_2->addWidget(nombre, 0, 0, 1, 1);

        inputEdad = new QLineEdit(perfil);
        inputEdad->setObjectName("inputEdad");

        gridLayout_2->addWidget(inputEdad, 1, 1, 1, 1);

        label_7 = new QLabel(perfil);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 2, 2, 1, 1);

        Edad = new QLabel(perfil);
        Edad->setObjectName("Edad");

        gridLayout_2->addWidget(Edad, 0, 1, 1, 1);

        inputAltura = new QLineEdit(perfil);
        inputAltura->setObjectName("inputAltura");

        gridLayout_2->addWidget(inputAltura, 3, 0, 1, 1);

        inputNombre = new QLineEdit(perfil);
        inputNombre->setObjectName("inputNombre");

        gridLayout_2->addWidget(inputNombre, 1, 0, 1, 1);

        comboGenero = new QComboBox(perfil);
        comboGenero->addItem(QString());
        comboGenero->addItem(QString());
        comboGenero->setObjectName("comboGenero");

        gridLayout_2->addWidget(comboGenero, 3, 2, 1, 1);

        comboObjetivo = new QComboBox(perfil);
        comboObjetivo->addItem(QString());
        comboObjetivo->addItem(QString());
        comboObjetivo->addItem(QString());
        comboObjetivo->setObjectName("comboObjetivo");

        gridLayout_2->addWidget(comboObjetivo, 7, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        btnGuardarPerfil = new QPushButton(perfil);
        btnGuardarPerfil->setObjectName("btnGuardarPerfil");

        verticalLayout_5->addWidget(btnGuardarPerfil);

        stackedWidget->addWidget(perfil);
        page_buscador = new QWidget();
        page_buscador->setObjectName("page_buscador");
        verticalLayout_6 = new QVBoxLayout(page_buscador);
        verticalLayout_6->setObjectName("verticalLayout_6");
        buscadorAlimentos = new QLineEdit(page_buscador);
        buscadorAlimentos->setObjectName("buscadorAlimentos");

        verticalLayout_6->addWidget(buscadorAlimentos);

        listaResultadosBusqueda = new QListWidget(page_buscador);
        listaResultadosBusqueda->setObjectName("listaResultadosBusqueda");

        verticalLayout_6->addWidget(listaResultadosBusqueda);

        btnVolverNutricion = new QPushButton(page_buscador);
        btnVolverNutricion->setObjectName("btnVolverNutricion");

        verticalLayout_6->addWidget(btnVolverNutricion);

        stackedWidget->addWidget(page_buscador);

        horizontalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 655, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(listWidget, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

        stackedWidget->setCurrentIndex(0);
        TABLA->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MainWindow", "Nutricion", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MainWindow", "Rutinas", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MainWindow", "Perfil", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        label_9->setText(QCoreApplication::translate("MainWindow", "Calor\303\255as Quemadas", nullptr));
        lblCaloriasQuemadas->setText(QCoreApplication::translate("MainWindow", "kcal", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Calor\303\255as Quemadas", nullptr));
        lblBalanceNeto->setText(QCoreApplication::translate("MainWindow", "kcal", nullptr));
        lblCaloriasConsumidas->setText(QCoreApplication::translate("MainWindow", "kcal", nullptr));
        lblMetaCalorica->setText(QCoreApplication::translate("MainWindow", "Meta: 0 kcal", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Calorias Consumidas", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Prote\303\255nas", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Carbohidratos", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Grasas", nullptr));
        btnHistorialComidas->setText(QCoreApplication::translate("MainWindow", "Historial de comidas", nullptr));
        btnAgregarComida->setText(QCoreApplication::translate("MainWindow", "Agregar comida", nullptr));
        lblCaloriasNutricion->setText(QCoreApplication::translate("MainWindow", "Calor\303\255as consumidas hoy: 0 kcal", nullptr));
        comboDiasRutina->setItemText(0, QCoreApplication::translate("MainWindow", "2 D\303\255as", nullptr));
        comboDiasRutina->setItemText(1, QCoreApplication::translate("MainWindow", "3 D\303\255as", nullptr));
        comboDiasRutina->setItemText(2, QCoreApplication::translate("MainWindow", "4 D\303\255as", nullptr));
        comboDiasRutina->setItemText(3, QCoreApplication::translate("MainWindow", "5 D\303\255as", nullptr));

        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Ejercicio", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "M\303\272sculo", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Series x Reps", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Peso", nullptr));
        TABLA->setTabText(TABLA->indexOf(Pesas), QCoreApplication::translate("MainWindow", "Pesas", nullptr));
        TABLA->setTabText(TABLA->indexOf(Cardio), QCoreApplication::translate("MainWindow", "Cardio", nullptr));
        btnFinalizarRutina->setText(QCoreApplication::translate("MainWindow", "Finalizar Entrenamiento", nullptr));
        Peso_2->setText(QCoreApplication::translate("MainWindow", "Objetivo:", nullptr));
        Peso->setText(QCoreApplication::translate("MainWindow", "Peso (kg):", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Altura (cm):", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Nivel de Actividad:", nullptr));
        comboActividad->setItemText(0, QCoreApplication::translate("MainWindow", "Sedentario", nullptr));
        comboActividad->setItemText(1, QCoreApplication::translate("MainWindow", "Ligero", nullptr));
        comboActividad->setItemText(2, QCoreApplication::translate("MainWindow", "Moderado", nullptr));
        comboActividad->setItemText(3, QCoreApplication::translate("MainWindow", "Activo", nullptr));
        comboActividad->setItemText(4, QCoreApplication::translate("MainWindow", "Muy Activo", nullptr));

        nombre->setText(QCoreApplication::translate("MainWindow", "Nombre:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "G\303\251nero:", nullptr));
        Edad->setText(QCoreApplication::translate("MainWindow", "Edad:", nullptr));
        comboGenero->setItemText(0, QCoreApplication::translate("MainWindow", "Masculino", nullptr));
        comboGenero->setItemText(1, QCoreApplication::translate("MainWindow", "Femenino", nullptr));

        comboObjetivo->setItemText(0, QCoreApplication::translate("MainWindow", "Bajar", nullptr));
        comboObjetivo->setItemText(1, QCoreApplication::translate("MainWindow", "Mantener", nullptr));
        comboObjetivo->setItemText(2, QCoreApplication::translate("MainWindow", "Subir", nullptr));

        btnGuardarPerfil->setText(QCoreApplication::translate("MainWindow", "Guardar Perfil", nullptr));
        buscadorAlimentos->setPlaceholderText(QCoreApplication::translate("MainWindow", "Buscar alimento en cat\303\241logo...", nullptr));
        btnVolverNutricion->setText(QCoreApplication::translate("MainWindow", "Volver", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
