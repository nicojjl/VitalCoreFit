#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <vector>
#include <QListWidgetItem>
#include "Usuario.h"
#include "PersistenciaUsuario.h"
#include "Nutricion.h"
#include "ListaComidas.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QTimer>
#include <QScrollArea>
#include <QGroupBox>
#include <QCheckBox>
#include <QFrame>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnGuardarPerfil_clicked();
    void on_buscadorAlimentos_textChanged(const QString &arg1);
    void on_listaResultadosBusqueda_itemDoubleClicked(QListWidgetItem *item);
    void on_btnAgregarComida_clicked();
    void on_btnVolverNutricion_clicked();
    void on_comboDiasRutina_currentTextChanged(const QString &arg1);
    void on_btnFinalizarRutina_clicked();
    void on_btnRegistrarCardio_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void calcularVolumenEnVivo();
    void on_btnResetDia_clicked();
    void on_btnExportarReporte_clicked();
    void on_btnDescanso_clicked();
    void actualizarCronometro();
    void cargarRutinaEstiloHevy(const QString &diaRutina);

private:
    Ui::MainWindow *ui;
    Usuario perfilUsuario;
    std::vector<Alimento> catalogoAlimentos;
    ListaComidas listaDelDia;
    QTimer *timerDescanso;
    int tiempoRestante;

    void actualizarDashboardVisual();
    void cargarDatosUI();
    void dibujarGrafico();
    void guardarDiarioAlimentosJson();
    void cargarDiarioAlimentosJson();
    void agregarComidaInterfazVisual(const Alimento& alimento);
};

#endif // MAINWINDOW_H