#include "mainwindow.h"
#include "ui_mainwindow.h"

// ¡Súper importante! Tienes que incluir las librerías de los widgets que vas a usar
#include <QTabWidget>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}