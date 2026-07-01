#pragma once
#include <string>
#include "ListaComidas.h"
#include "Entrenamiento.h"

std::string obtenerFechaHoy();
void guardarDiaEnHistorial(const ListaComidas& listaDia, const ListaEjercicio& listaEjercicios, double caloriasConsumidas, double caloriasQuemadas, double balanceNeto);
void mostrarHistorial();
// Módulo de registro temporal. Permite capturar la fecha actual y guardar el resumen del día (comidas, rutinas y balances calóricos) para alimentar los gráficos y el análisis estadístico.