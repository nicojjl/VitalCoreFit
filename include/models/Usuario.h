#pragma once
#include <string>

enum class Genero {Masculino, Femenino};
enum class Objetivo {Bajar, Mantener, Subir};
enum class NivelActividad {Sedentario, Ligero, Moderado, Activo, MuyActivo};

struct Usuario {
    std::string nombre;
    int edad;
    double peso;
    double altura;
    double tmb;
    double imc;
    double tdee;
    double metaCalorica;
    double macroProteinas;
    double macroCarbos;
    double macroGrasas;
    Genero GeneroUsuario;
    Objetivo ObjetivoUsuario;
    NivelActividad NivelActividadUsuario;
};

double calcularIMC(const Usuario& datousuario);
double calcularTMB(const Usuario& datousuario);
double calcularTDEE(const Usuario& datousuario, double tmb);
void   calcularMetas(Usuario& datousuario, double tdee);
// Núcleo del programa. Define las características personales e integra los algoritmos fisiológicos (IMC, TMB, TDEE) necesarios para calcular automáticamente las metas calóricas y distribución de macros.