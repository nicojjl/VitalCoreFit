#pragma once
#include <string>
#include "ListaComidas.h"
#include "Entrenamiento.h"

std::string obtenerFechaHoy();
void guardarDiaEnHistorial(const ListaComidas& listaDia, const ListaEjercicio& listaEjercicios, double caloriasConsumidas, double caloriasQuemadas, double balanceNeto);
void mostrarHistorial();