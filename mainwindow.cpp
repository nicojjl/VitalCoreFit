#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTabWidget>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    if (cargarPerfil(perfilUsuario)) {
        actualizarDashboardVisual();
    }

    catalogoAlimentos = cargarAlimentos("data/foods.json");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::actualizarDashboardVisual()
{
    ui->lblMetaCalorica->setText(QString::number(perfilUsuario.metaCalorica) + " kcal");
    ui->lblCaloriasConsumidas->setText("0 kcal");
    ui->lblCaloriasQuemadas->setText("0 kcal");
    ui->lblBalanceNeto->setText("0 kcal");
}

void MainWindow::on_btnGuardarPerfil_clicked()
{
    perfilUsuario.nombre = ui->inputNombre->text().toStdString();
    perfilUsuario.edad = ui->inputEdad->text().toInt();
    perfilUsuario.peso = ui->inputPeso->text().toDouble();
    perfilUsuario.altura = ui->inputAltura->text().toDouble();

    if (ui->comboGenero->currentText() == "Masculino") {
        perfilUsuario.GeneroUsuario = Genero::Masculino;
    } else {
        perfilUsuario.GeneroUsuario = Genero::Femenino;
    }

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


    qDebug() << "Perfil guardado con éxito.";
    qDebug() << "TDEE Calculado:" << perfilUsuario.tdee << "kcal";
    qDebug() << "Meta Calorica:" << perfilUsuario.metaCalorica << "kcal";


    actualizarDashboardVisual();
}

void MainWindow::on_buscadorAlimentos_textChanged(const QString &arg1)
{
    ui->listaComidasHoy->clear();

    if (arg1.isEmpty()) {
        return;
    }

    std::string textoBusqueda = arg1.toStdString();
    std::vector<Alimento> resultados = buscarAlimento(catalogoAlimentos, textoBusqueda);

    for (size_t i = 0; i < resultados.size(); i++) {
        QString nombreItem = QString::fromStdString(resultados[i].nombre);
        QString kcalItem = QString::number(resultados[i].calorias);

        QString textoMostrar = nombreItem + " (" + kcalItem + " kcal)";

        ui->listaComidasHoy->addItem(textoMostrar);
    }
}