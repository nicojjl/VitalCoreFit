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
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(665, 440);
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

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 665, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(listWidget, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

        stackedWidget->setCurrentIndex(2);
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

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
