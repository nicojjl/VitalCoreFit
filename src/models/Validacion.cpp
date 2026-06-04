#include "../../include/models/Validacion.h"

bool validarUsuario(const Usuario& u, std::string& mensajeError) {
    if (u.nombre.empty()) {
        mensajeError = "El nombre no puede estar vacio";
        return false;
    }
    if (u.edad < 10 || u.edad > 100) {
        mensajeError = "La edad debe estar entre 10 y 100 anos";
        return false;
    }
    if (u.peso < 20.0 || u.peso > 300.0) {
        mensajeError = "El peso debe estar entre 20 y 300 kg";
        return false;
    }
    if (u.altura < 100.0 || u.altura > 250.0) {
        mensajeError = "La altura debe estar entre 100 y 250 cm";
        return false;
    }
    return true;
}

bool validarBrzycki(double peso, int repeticiones, std::string& mensajeError) {
    if (peso <= 0.0) {
        mensajeError = "El peso debe ser mayor a 0";
        return false;
    }
    if (repeticiones < 1 || repeticiones > 36) {
        mensajeError = "Las repeticiones deben estar entre 1 y 36";
        return false;
    }
    return true;
}

bool validarCardio(double bpm, double minutos, std::string& mensajeError) {
    if (bpm < 30.0 || bpm > 250.0) {
        mensajeError = "Las pulsaciones deben estar entre 30 y 250 bpm";
        return false;
    }
    if (minutos < 1.0 || minutos > 600.0) {
        mensajeError = "Los minutos deben estar entre 1 y 600";
        return false;
    }
    return true;
}

bool validarMET(double met, std::string& mensajeError) {
    if (met < 0.1 || met > 20.0) {
        mensajeError = "El factor MET debe estar entre 0.1 y 20";
        return false;
    }
    return true;
}