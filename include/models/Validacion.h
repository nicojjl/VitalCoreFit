#pragma once
#include "Usuario.h"
#include <string>

bool validarUsuario(const Usuario& u, std::string& mensajeError);
bool validarBrzycki(double peso, int repeticiones, std::string& mensajeError);
bool validarCardio(double bpm, double minutos, std::string& mensajeError);
bool validarMET(double met, std::string& mensajeError);
// Capa de seguridad y control de errores. Filtra la entrada del usuario asegurando que los datos de perfil, pesos, repeticiones y cardio tengan sentido lógico y viabilidad matemática.