#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "Usuario.h"
#include "PersistenciaUsuario.h"
#include "Nutricion.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
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

private:
    Ui::MainWindow *ui;
    Usuario perfilUsuario;
    std::vector<Alimento> catalogoAlimentos;

    // Función de la Clase 8 para repintar el Dashboard
    void actualizarDashboardVisual();
};
#endif // MAINWINDOW_H