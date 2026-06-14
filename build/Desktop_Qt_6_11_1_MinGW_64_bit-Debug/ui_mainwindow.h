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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
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
    QWidget *page_4;
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
"/* ------------------------------------------- */\n"
"/* NUEVO: ESTILO PARA LAS TARJETAS (CARDS) */\n"
"/* ------------------------------------------- */\n"
"QFrame#tarjetaCalorias {\n"
"    background-color: #1E2736;\n"
"    border-radius: 12px;\n"
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
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        stackedWidget->addWidget(page_4);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 665, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);
        QObject::connect(listWidget, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

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

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
