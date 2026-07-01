#include "mainwindow.h"

#include <QApplication>
// Punto de entrada principal de la aplicación. Inicializa el entorno gráfico de Qt, instancia la ventana principal (MainWindow) y arranca el ciclo de eventos del programa.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
