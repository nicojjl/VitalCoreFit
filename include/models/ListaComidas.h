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

// Gestiona el consumo diario mediante una lista enlazada dinámica. Administra la memoria para agregar o eliminar porciones, y sumariza eficientemente las calorías totales ingeridas en el día.
// Por temas de tiempo no se podra cambiar todo el sistema a POO ni con map, pero si algun futuro se considera mejorar o comercializar el programa se considerara eso y mucho mas cambios.