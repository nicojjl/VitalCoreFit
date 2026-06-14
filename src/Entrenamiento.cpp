#include "../../include/models/Entrenamiento.h"
#include <iostream>
using namespace std;

double calcular1RM(double peso, int repeticiones){
    return peso * (36.0 / (37.0 - repeticiones));
}
double calcularVolumen(int series, int repeticiones, double peso){
    return series*repeticiones*peso;
}
double calcularCaloriasQuemadas(double met, double pesoCorporal, double minutos){
    return met*pesoCorporal*(minutos/60);
}
double calcularFCMax(int edad){
    return 208-(0.7*edad);
}
int calcularZonaCardiaca(double bpmActual, double fcMax){
    double porcentaje = (bpmActual/fcMax)*100.0;
    if(porcentaje<60){
        return 1;
    }else if (porcentaje<70){
        return 2;
    }else if (porcentaje<80){
        return 3;
    }else if (porcentaje<90){
        return 4;
    }else{
        return 5;
    }
}
void agregarEjercicio(ListaEjercicio& lista, Ejercicio ejercicio){
    NodoEjercicio* nuevo = new NodoEjercicio();
    nuevo->ejercicio = ejercicio;
    nuevo->siguiente = nullptr;
    if(lista.cabeza == nullptr){
        lista.cabeza= nuevo;
    } else{
        NodoEjercicio* actual = lista.cabeza;
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    lista.cantidad++;
}
void liberarListaEjercicios(ListaEjercicio& lista) {
    NodoEjercicio* actual = lista.cabeza;
    while(actual != nullptr){
        NodoEjercicio* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
}