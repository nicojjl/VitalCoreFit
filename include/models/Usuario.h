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
    double tdee;
    double metaCalorica;
    double macroProteinas;
    double macroCarbos;
    double macroGrasas;
    Genero generoUsuario;
    Objetivo objetivoUsuario;
    NivelActividad nivelActividadUsuario;
};