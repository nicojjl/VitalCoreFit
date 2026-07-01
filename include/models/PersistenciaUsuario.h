#pragma once
#include "Usuario.h"
#include <string>

void guardarPerfil(const Usuario& u);
bool cargarPerfil(Usuario& u);
// Maneja el flujo de guardado y carga del perfil. puente entre los datos en memoria de C++ y el almacenamiento físico local para conservar el progreso.