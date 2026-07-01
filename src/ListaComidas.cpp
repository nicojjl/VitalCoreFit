#include "../../include/models/ListaComidas.h"
#include <iostream>
using namespace std;
// Asigna memoria dinámica e inserta un nuevo alimento con su respectiva porción al final de la lista enlazada de comidas consumidas en el día.

// Busca y remueve un nodo específico de la lista de comidas basándose en su índice, reconectando los punteros y liberando la memoria asociada.

// Itera sobre todos los alimentos consumidos, ajustando las calorías según la porción ingerida (en gramos) para obtener el total calórico diario.

// Elimina secuencialmente todos los nodos de la lista de comidas para limpiar la memoria dinámica asignada durante la sesión actual y evitar fugas.
void agregarComida(ListaComidas& lista, Alimento alimento, double cantidad){
    NodoComida* nuevo = new NodoComida();
    nuevo->alimento = alimento;
    nuevo->cantidad = cantidad;
    nuevo->siguiente = nullptr;
    if(lista.cabeza == nullptr){
        lista.cabeza= nuevo;
    } else{
        NodoComida* actual = lista.cabeza;
        while(actual->siguiente != nullptr){
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
    lista.cantidad++;
}
void eliminarComida(ListaComidas& lista, int posicion) {
    if (lista.cabeza == nullptr){
        return;
    } 
    if(posicion == 0){
        NodoComida* aEliminar = lista.cabeza;
        lista.cabeza = lista.cabeza->siguiente;
        delete aEliminar;
    } else {
        NodoComida* anterior = lista.cabeza;
        for(int i = 0; i < posicion - 1; i++){
            if(anterior->siguiente == nullptr){
                return;
            } 
            anterior = anterior->siguiente;
        }
        NodoComida* aEliminar = anterior->siguiente;
        if (aEliminar == nullptr){
            return;
        } 
        anterior->siguiente = aEliminar->siguiente;
        delete aEliminar;
    }
    lista.cantidad--; 
}
double calcularCaloriasDelDia(const ListaComidas& lista) {
    double total = 0.0;
    NodoComida* actual = lista.cabeza;
    while (actual != nullptr){
        total +=(actual->alimento.calorias * actual->cantidad)/100.0;
        actual = actual->siguiente;
    }
    return total;
}
void liberarLista(ListaComidas& lista) {
    NodoComida* actual = lista.cabeza;
    while(actual != nullptr){
        NodoComida* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    lista.cabeza = nullptr;
    lista.cantidad = 0;
}