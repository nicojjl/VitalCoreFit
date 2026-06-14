#pragma once
#include <iostream>
#include "Entrenamiento.h"

struct ResultadoDash {
    double caloriasConsumidas;
    double caloriasQuemadas;
    double balanceNeto;
    double metaCalorica;
    double diferenciaMeta;
    int estado;
};

double calcularTotalQuemado(const ListaEjercicio& listaEjercicios);
ResultadoDash calcularDashboard(double caloriasConsumidas, double caloriasQuemadas, double metaCalorica);
void imprimirEstadoDash(const ResultadoDash& dash);