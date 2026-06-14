#pragma once
#include <vector>
#include <string>
#include "Alimento.h"

std::vector<Alimento> cargarAlimentos(const std::string& rutaArchivo);
std::vector<Alimento> buscarAlimento(const std::vector<Alimento>& catalogo, const std::string& textoBusqueda);