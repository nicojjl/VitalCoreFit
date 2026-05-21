#include "../../include/models/ListaComidas.h"
#include <iostream>
using namespace std;

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