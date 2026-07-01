#include "../../include/models/Entrenamiento.h"
#include <iostream>
using namespace std;
// Aplica la fórmula de Brzycki para estimar el peso máximo que el usuario puede levantar a una sola repetición basándose en su rendimiento actual.

// Multiplica series, repeticiones y peso para cuantificar la carga total de trabajo (volumen) movida en un ejercicio específico durante la sesión.

// Utiliza el equivalente metabólico (MET), el peso corporal y la duración para estimar de forma precisa el gasto energético de una actividad física.

// Aplica la fórmula fisiológica estándar basada en la edad para determinar la frecuencia cardíaca máxima segura recomendada para el usuario.

// Compara las pulsaciones actuales con el máximo permitido para clasificar la intensidad del esfuerzo cardiovascular en una de cinco zonas de entrenamiento.

// Inserta de forma dinámica un nuevo registro de ejercicio al final de la lista enlazada que representa la rutina de la sesión actual.

// Recorre y elimina de la memoria cada nodo de la lista de ejercicios para prevenir fugas de memoria al finalizar la rutina.
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