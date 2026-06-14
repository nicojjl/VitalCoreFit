#pragma once
#include <vector>
#include <string>
#include "Alimento.h"

struct NodoComida{
    Alimento alimento;
    double cantidad;
    NodoComida* siguiente;
};

struct ListaComidas {
    NodoComida* cabeza;  
    int cantidad;        
};

void agregarComida(ListaComidas& lista, Alimento alimento, double cantidad);
void eliminarComida(ListaComidas& lista, int posicion);
double calcularCaloriasDelDia(const ListaComidas& lista);
void liberarLista(ListaComidas& lista);
