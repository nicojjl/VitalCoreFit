#pragma once
#include <vector>
#include <string>
#include "Alimento.h"

std::vector<Alimento> cargarAlimentos(const std::string& rutaArchivo);
std::vector<Alimento> buscarAlimento(const std::vector<Alimento>& catalogo, const std::string& textoBusqueda);
// Motor de gestión del catálogo. Se encarga de leer y cargar la base de datos de alimentos desde el almacenamiento, proporcionando herramientas de filtrado y búsqueda en tiempo real.