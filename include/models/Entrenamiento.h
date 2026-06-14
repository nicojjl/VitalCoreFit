#pragma once
#include <string>

struct Ejercicio{
    double peso;
    double volumen;
    double caloriasQuemadas;
    int series;
    int repeticiones;
    std::string nombre;
};

struct SesionCardio{
    std::string tipo;
    double minutos;
    double distanciakm;
    double bpmPromedio;
    int zonaCardiaca;
    double caloriasQuemadas;
};

struct NodoEjercicio {
    Ejercicio ejercicio;
    NodoEjercicio* siguiente;
};

struct ListaEjercicio {
    NodoEjercicio* cabeza;
    int cantidad;
};

double calcular1RM(double peso, int repeticiones);
double calcularVolumen(int series, int repeticiones, double peso);
double calcularCaloriasQuemadas(double met, double pesoCorporal, double minutos);
double calcularFCMax(int edad);
int calcularZonaCardiaca(double bpmActual, double fcMax);
void agregarEjercicio(ListaEjercicio& lista, Ejercicio ejercicio);
void liberarListaEjercicios(ListaEjercicio& lista);