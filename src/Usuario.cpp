#include "../../include/models/Usuario.h"

double calcularIMC(const Usuario& datousuario) {
    if (datousuario.altura <= 0) return 0.0;
    double alturaEnMetros = datousuario.altura / 100.0;
    return datousuario.peso / (alturaEnMetros * alturaEnMetros);
}
double calcularTMB(const Usuario& datousuario) {
    if (datousuario.GeneroUsuario == Genero::Masculino){
        double TMB = 10*(datousuario.peso) + 6.25*(datousuario.altura)-5*(datousuario.edad)+5;
        return TMB;
    } else if(datousuario.GeneroUsuario == Genero::Femenino){
        double TMB = 10*(datousuario.peso) + 6.25*(datousuario.altura)-5*(datousuario.edad)-161;
        return TMB;
    }
    return -1.0;
}

double calcularTDEE(const Usuario& datousuario, double tmb) {
    double TDEE = -1.0;
    switch(datousuario.NivelActividadUsuario){
        case NivelActividad::Sedentario:
            TDEE = tmb * 1.2;
            break;
        case NivelActividad::Ligero:
            TDEE = tmb * 1.375;
            break;
        case NivelActividad::Moderado:
            TDEE = tmb * 1.55;
            break;
        case NivelActividad::Activo:
            TDEE = tmb * 1.725;
            break;
        case NivelActividad::MuyActivo:
            TDEE = tmb * 1.9;
            break;
        default:
            return -1.0;
        }
     return TDEE; 
}

void calcularMetas(Usuario& datousuario, double tdee) {
    switch (datousuario.ObjetivoUsuario){
    case Objetivo::Bajar:
        datousuario.metaCalorica = tdee - 500;
        break;
    case Objetivo::Mantener:
        datousuario.metaCalorica = tdee;
        break;
    case Objetivo::Subir:
        datousuario.metaCalorica = tdee + 300;
        break;
    }   

    datousuario.macroProteinas = ((datousuario.metaCalorica)/4)*0.3;
    datousuario.macroCarbos = ((datousuario.metaCalorica)/4)*0.4;
    datousuario.macroGrasas = ((datousuario.metaCalorica)/9)*0.3;
}