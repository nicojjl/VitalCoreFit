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
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout;
    QFrame *tarjetaCalorias;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QProgressBar *barProteinas;
    QLabel *label_4;
    QProgressBar *barCarbos;
    QLabel *label_5;
    QProgressBar *progressBar_3;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *buscadorAlimentos;
    QListWidget *listaComidasHoy;
    QWidget *page;
    QGridLayout *gridLayout;
    QTabWidget *TABLA;
    QWidget *Pesas;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QWidget *Cardio;
    QComboBox *comboDiasRutina;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_2;
    QLabel *Peso_2;
    QLineEdit *inputPeso;
    QLabel *Peso;
    QLabel *label_6;
    QLabel *label_8;
    QComboBox *comboBox;
    QLabel *nombre;
    QLineEdit *inputEdad;
    QLabel *label_7;
    QLabel *Edad;
    QLineEdit *lineEdit_3;
    QLineEdit *inputNombre;
    QComboBox *comboGenero;
    QComboBox *comboObjetivo;
    QPushButton *btnGuardarPerfil;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(655, 440);
        MainWindow->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        MainWindow->setStyleSheet(QString::fromUtf8("/* Color de fondo de toda la ventana principal */\n"
"QMainWindow {\n"
"    background-color: #0F1722;\n"
"}\n"
"\n"
"/* LA BARRA LATERAL (List Widget) */\n"
"QListWidget {\n"
"    background-color: #1E2736;\n"
"    border: none;\n"
"    outline: none; /* Quita el borde punteado feo al hacer clic */\n"
"    padding-top: 20px;\n"
"}\n"
"\n"
"/* LOS BOTONES DE LA BARRA LATERAL */\n"
"QListWidget::item {\n"
"    color: #A0AAB5;\n"
"    min-height: 40px;\n"
"    padding-left: 15px;\n"
"    border-radius: 8px;\n"
"    margin: 5px 10px 5px 10px; /* Margen para que no toque los bordes */\n"
"    font-family: \"Segoe UI\", Arial;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QListWidget::item:hover {\n"
"    background-color: #2A3648;\n"
"    color: white;\n"
"}\n"
"\n"
"/* EL BOT\303\223N SELECCIONADO (Efecto Cian) */\n"
"QListWidget::item:selected {\n"
"    background-color: #00E5FF;\n"
"    color: #000000;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* FONDO DEL \303\201REA DE CONTENIDO (Stacked Widget) */\n"
"QStackedWidg"
                        "et {\n"
"    background-color: #0F1722;\n"
"}\n"
"\n"
"/* NUEVO: ESTILO PARA LAS TARJETAS (CARDS) */\n"
"\n"
"QFrame#tarjetaCalorias {\n"
"    background-color: #1E2736;\n"
"    border-radius: 12px;\n"
"}\n"
"/* El fondo de la nueva tarjeta */\n"
"QFrame#tarjetaMacros {\n"
"    background-color: #1E2736;\n"
"    border-radius: 12px;\n"
"}\n"
"\n"
"/* ESTILO GENERAL DE LAS BARRAS DE PROGRESO */\n"
"QProgressBar {\n"
"    background-color: #2A3648; /* El color del \"camino\" vac\303\255o (Gris oscuro) */\n"
"    border: none;\n"
"    border-radius: 5px; /* Bordes redondeados */\n"
"    height: 8px; /* Hace la barra bien delgada y moderna */\n"
"    color: transparent; /* Oculta el porcentaje num\303\251rico del centro */\n"
"}\n"
"\n"
"/* EL RELLENO DE LAS BARRAS */\n"
"QProgressBar::chunk {\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"/* COLORES ESPEC\303\215FICOS SEG\303\232N EL MACRONUTRIENTE */\n"
"QProgressBar#barProteinas::chunk {\n"
"    background-color: #00E676; /* Verde ne\303\263n */\n"
"}\n"
"\n"
"QPro"
                        "gressBar#barCarbos::chunk {\n"
"    background-color: #FF9100; /* Naranja */\n"
"}\n"
"\n"
"QProgressBar#barGrasas::chunk {\n"
"    background-color: #FF1744; /* Rojo */\n"
"}\n"
"\n"
"/* Color para los textos de los labels de esta tarjeta */\n"
"QFrame#tarjetaMacros QLabel {\n"
"    color: #FFFFFF;\n"
"    font-size: 11px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"/* M\303\223DULO DE NUTRICI\303\223N */\n"
"\n"
"/* ESTILO DEL BUSCADOR DE ALIMENTOS */\n"
"QLineEdit#buscadorAlimentos {\n"
"    background-color: #1E2736;\n"
"    color: #FFFFFF;\n"
"    border: 2px solid #2A3648; /* Borde gris oscuro por defecto */\n"
"    border-radius: 8px;\n"
"    padding: 10px;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"}\n"
"\n"
"/* EFECTO CUANDO EL USUARIO HACE CLIC PARA ESCRIBIR */\n"
"QLineEdit#buscadorAlimentos:focus {\n"
"    border: 2px solid #00E5FF; /* El borde se ilumina en Cian */\n"
"    background-color: #151D29; /* Se oscurece un poco el fondo */\n"
"}\n"
"\n"
"/* ESTILO DE LA LISTA D"
                        "E COMIDAS DEL D\303\215A */\n"
"QListWidget#listaComidasHoy {\n"
"    background-color: #1E2736;\n"
"    border-radius: 12px;\n"
"    border: 1px solid #2A3648;\n"
"    padding: 10px;\n"
"    outline: none;\n"
"}\n"
"\n"
"/* Elementos dentro de la lista de comidas */\n"
"QListWidget#listaComidasHoy::item {\n"
"    background-color: #0F1722; /* Fondo m\303\241s oscuro para cada comida */\n"
"    border-radius: 6px;\n"
"    border-left: 4px solid #00E676; /* Una rayita verde a la izquierda como tu prototipo */\n"
"    color: white;\n"
"    padding: 10px;\n"
"    margin-bottom: 5px;\n"
"}\n"
"\n"
"/*M\303\223DULO DE ENTRENAMIENTO */\n"
"\n"
"/* PESTA\303\221AS INTERNAS (Pesas / Cardio) */\n"
"QTabWidget::pane {\n"
"    border: none;\n"
"    background-color: #0F1722;\n"
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
""
                        "    background-color: #2A3648;\n"
"    color: #00E5FF;\n"
"    font-weight: bold;\n"
"    border-bottom: 2px solid #00E5FF;\n"
"}\n"
"\n"
"/* COMBO BOX (Selector de d\303\255as) */\n"
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
"/* LA TABLA DE RUTINAS */\n"
"QTableWidget#tablaRutina {\n"
"    background-color: #1E2736;\n"
"    color: #FFFFFF;\n"
"    border: 1px solid #2A3648;\n"
"    border-radius: 8px;\n"
"    gridline-color: #2A3648; /* Color de las l\303\255neas de la cuadr\303\255cula */\n"
"    selection-background-color: #00E5FF; /* Celda seleccionada en cian */\n"
"    selection-color: #000000;\n"
"    font-size: 13px;\n"
"    outline: none;\n"
"}\n"
"\n"
"/* ENCABEZADOS DE LA TABLA */\n"
"QHeaderView::section {\n"
"    background-color: "
                        "#0F1722;\n"
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
"/*M\303\223DULO DE PERFIL Y BOTONES */\n"
"\n"
"\n"
"/* ESTILO DEL BOT\303\223N PRINCIPAL */\n"
"QPushButton#btnGuardarPerfil {\n"
"    background-color: #00E5FF; /* El cian caracter\303\255stico de la app */\n"
"    color: #000000; /* Texto negro para contraste */\n"
"    border: none;\n"
"    border-radius: 8px;\n"
"    padding: 12px;\n"
"    font-weight: bold;\n"
"    font-size: 14px;\n"
"    font-family: \"Segoe UI\", Arial;\n"
"}\n"
"\n"
"/* EFECTO HOVER (Al pasar el mouse) */\n"
"QPushButton#btnGuardarPerfil:hover {\n"
"    background-color: #33EEFF; /* Un cian un poco m\303\241s claro */\n"
"}\n"
"\n"
"/* EFECTO PRESSED (Al hacer clic) */\n"
"QPushButton#btnGuardarPerfil:pressed {\n"
"    background-color: #00B8CC;"
                        " /* Un cian m\303\241s oscuro */\n"
"}\n"
"\n"
"/* Ajuste de color para las etiquetas del formulario */\n"
"QStackedWidget QLabel {\n"
"    color: #A0AAB5;\n"
"    font-weight: bold;\n"
"}"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        listWidget = new QListWidget(centralwidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setMaximumSize(QSize(200, 16777215));

        horizontalLayout->addWidget(listWidget);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        verticalLayout = new QVBoxLayout(page_3);
        verticalLayout->setObjectName("verticalLayout");
        tarjetaCalorias = new QFrame(page_3);
        tarjetaCalorias->setObjectName("tarjetaCalorias");
        tarjetaCalorias->setFrameShape(QFrame::Shape::StyledPanel);
        tarjetaCalorias->setFrameShadow(QFrame::Shadow::Raised);
        label = new QLabel(tarjetaCalorias);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 20, 101, 16));
        label_2 = new QLabel(tarjetaCalorias);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 35, 21, 21));

        verticalLayout->addWidget(tarjetaCalorias);

        frame = new QFrame(page_3);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        verticalLayout_2->addWidget(label_3);

        barProteinas = new QProgressBar(frame);
        barProteinas->setObjectName("barProteinas");
        barProteinas->setValue(24);

        verticalLayout_2->addWidget(barProteinas);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        barCarbos = new QProgressBar(frame);
        barCarbos->setObjectName("barCarbos");
        barCarbos->setValue(24);

        verticalLayout_2->addWidget(barCarbos);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");

        verticalLayout_2->addWidget(label_5);

        progressBar_3 = new QProgressBar(frame);
        progressBar_3->setObjectName("progressBar_3");
        progressBar_3->setValue(24);

        verticalLayout_2->addWidget(progressBar_3);


        verticalLayout->addWidget(frame);

        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        verticalLayout_3 = new QVBoxLayout(page_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        buscadorAlimentos = new QLineEdit(page_4);
        buscadorAlimentos->setObjectName("buscadorAlimentos");

        verticalLayout_3->addWidget(buscadorAlimentos);

        listaComidasHoy = new QListWidget(page_4);
        listaComidasHoy->setObjectName("listaComidasHoy");

        verticalLayout_3->addWidget(listaComidasHoy);

        stackedWidget->addWidget(page_4);
        page = new QWidget();
        page->setObjectName("page");
        gridLayout = new QGridLayout(page);
        gridLayout->setObjectName("gridLayout");
        TABLA = new QTabWidget(page);
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

        comboDiasRutina = new QComboBox(page);
        comboDiasRutina->addItem(QString());
        comboDiasRutina->addItem(QString());
        comboDiasRutina->addItem(QString());
        comboDiasRutina->addItem(QString());
        comboDiasRutina->setObjectName("comboDiasRutina");

        gridLayout->addWidget(comboDiasRutina, 0, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_5 = new QVBoxLayout(page_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        Peso_2 = new QLabel(page_2);
        Peso_2->setObjectName("Peso_2");

        gridLayout_2->addWidget(Peso_2, 6, 1, 1, 1);

        inputPeso = new QLineEdit(page_2);
        inputPeso->setObjectName("inputPeso");

        gridLayout_2->addWidget(inputPeso, 3, 1, 1, 1);

        Peso = new QLabel(page_2);
        Peso->setObjectName("Peso");

        gridLayout_2->addWidget(Peso, 2, 1, 1, 1);

        label_6 = new QLabel(page_2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 2, 0, 1, 1);

        label_8 = new QLabel(page_2);
        label_8->setObjectName("label_8");

        gridLayout_2->addWidget(label_8, 0, 2, 1, 1);

        comboBox = new QComboBox(page_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        gridLayout_2->addWidget(comboBox, 1, 2, 1, 1);

        nombre = new QLabel(page_2);
        nombre->setObjectName("nombre");

        gridLayout_2->addWidget(nombre, 0, 0, 1, 1);

        inputEdad = new QLineEdit(page_2);
        inputEdad->setObjectName("inputEdad");

        gridLayout_2->addWidget(inputEdad, 1, 1, 1, 1);

        label_7 = new QLabel(page_2);
        label_7->setObjectName("label_7");

        gridLayout_2->addWidget(label_7, 2, 2, 1, 1);

        Edad = new QLabel(page_2);
        Edad->setObjectName("Edad");

        gridLayout_2->addWidget(Edad, 0, 1, 1, 1);

        lineEdit_3 = new QLineEdit(page_2);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout_2->addWidget(lineEdit_3, 3, 0, 1, 1);

        inputNombre = new QLineEdit(page_2);
        inputNombre->setObjectName("inputNombre");

        gridLayout_2->addWidget(inputNombre, 1, 0, 1, 1);

        comboGenero = new QComboBox(page_2);
        comboGenero->addItem(QString());
        comboGenero->addItem(QString());
        comboGenero->setObjectName("comboGenero");

        gridLayout_2->addWidget(comboGenero, 3, 2, 1, 1);

        comboObjetivo = new QComboBox(page_2);
        comboObjetivo->addItem(QString());
        comboObjetivo->addItem(QString());
        comboObjetivo->addItem(QString());
        comboObjetivo->setObjectName("comboObjetivo");

        gridLayout_2->addWidget(comboObjetivo, 7, 1, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        btnGuardarPerfil = new QPushButton(page_2);
        btnGuardarPerfil->setObjectName("btnGuardarPerfil");

        verticalLayout_5->addWidget(btnGuardarPerfil);

        stackedWidget->addWidget(page_2);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 655, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(listWidget, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

        stackedWidget->setCurrentIndex(3);
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

        label->setText(QCoreApplication::translate("MainWindow", "Calorias Consumidas", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "kcal", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Prote\303\255nas", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Carbohidratos", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Grasas", nullptr));
        buscadorAlimentos->setPlaceholderText(QCoreApplication::translate("MainWindow", "Buscar alimento en cat\303\241logo...", nullptr));
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
        comboDiasRutina->setItemText(0, QCoreApplication::translate("MainWindow", "2 D\303\255as", nullptr));
        comboDiasRutina->setItemText(1, QCoreApplication::translate("MainWindow", "3 D\303\255as", nullptr));
        comboDiasRutina->setItemText(2, QCoreApplication::translate("MainWindow", "4 D\303\255as", nullptr));
        comboDiasRutina->setItemText(3, QCoreApplication::translate("MainWindow", "5 D\303\255as", nullptr));

        Peso_2->setText(QCoreApplication::translate("MainWindow", "Objetivo:", nullptr));
        Peso->setText(QCoreApplication::translate("MainWindow", "Peso (kg):", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Altura (cm):", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Nivel de Actividad:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Sedentario", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Ligero", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Moderado", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Activo", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Muy Activo", nullptr));

        nombre->setText(QCoreApplication::translate("MainWindow", "Nombre:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "G\303\251nero:", nullptr));
        Edad->setText(QCoreApplication::translate("MainWindow", "Edad:", nullptr));
        comboGenero->setItemText(0, QCoreApplication::translate("MainWindow", "Masculino", nullptr));
        comboGenero->setItemText(1, QCoreApplication::translate("MainWindow", "Femenino", nullptr));

        comboObjetivo->setItemText(0, QCoreApplication::translate("MainWindow", "Bajar", nullptr));
        comboObjetivo->setItemText(1, QCoreApplication::translate("MainWindow", "Mantener", nullptr));
        comboObjetivo->setItemText(2, QCoreApplication::translate("MainWindow", "Subir", nullptr));

        btnGuardarPerfil->setText(QCoreApplication::translate("MainWindow", "Guardar Perfil", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
