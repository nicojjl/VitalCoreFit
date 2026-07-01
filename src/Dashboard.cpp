#include "../../include/models/Dashboard.h"
#include "../../include/models/Entrenamiento.h"
#include <iostream>
using namespace std;
// Recorre la lista enlazada de ejercicios para sumar y retornar el total exacto de calorías quemadas durante la sesión de entrenamiento actual.

// Evalúa las calorías consumidas y quemadas frente a la meta diaria, determinando matemáticamente si el usuario está en déficit, superávit o balance ideal.

// Muestra por consola un resumen detallado de las métricas diarias y el estado calórico actual del usuario para fines de depuración e información.
double calcularTotalQuemado(const ListaEjercicio& listaEjercicios) {
    double total = 0.0;
    NodoEjercicio* actual = listaEjercicios.cabeza;
    while (actual != nullptr) {
        total += actual->ejercicio.caloriasQuemadas;
        actual = actual->siguiente;
    }
    return total;
}

ResultadoDash calcularDashboard(double caloriasConsumidas, double caloriasQuemadas, double metaCalorica) {
    ResultadoDash resultado;
    resultado.caloriasConsumidas = caloriasConsumidas;
    resultado.caloriasQuemadas   = caloriasQuemadas;
    resultado.balanceNeto        = caloriasConsumidas - caloriasQuemadas;
    resultado.metaCalorica       = metaCalorica;
    resultado.diferenciaMeta     = resultado.balanceNeto - metaCalorica;

    if (resultado.diferenciaMeta <= -100.0) {
        resultado.estado = -1;
    } else if (resultado.diferenciaMeta >= 100.0) {
        resultado.estado = 1;
    } else {
        resultado.estado = 0;
    }
    return resultado;
}

void imprimirEstadoDash(const ResultadoDash& dash) {
    cout << "===================" << endl;
    cout << "   DASHBOARD DE PRUEBA      " << endl;
    cout << "===================" << endl;
    cout << "Calorias consumidas: " << dash.caloriasConsumidas << " kcal" << endl;
    cout << "Calorias quemadas:   " << dash.caloriasQuemadas   << " kcal" << endl;
    cout << "Balance neto:        " << dash.balanceNeto        << " kcal" << endl;
    cout << "Meta calorica:       " << dash.metaCalorica       << " kcal" << endl;
    cout << "Diferencia con meta: " << dash.diferenciaMeta     << " kcal" << endl;

    if (dash.estado == -1) {
        cout << "Estado: EN DEFICIT CALORICO" << endl;
    } else if (dash.estado == 0) {
        cout << "Estado: BALANCE IDEAL"       << endl;
    } else {
        cout << "Estado: SUPERAVIT CALORICO"  << endl;
    }
    cout << "===================" << endl;
}
