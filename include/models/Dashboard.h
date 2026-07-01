#pragma once
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
// se define la estructura y funciones del panel principal. Calcula y agrupa el balance neto, las calorías consumidas y las quemadas para evaluar el estado diario del usuario.