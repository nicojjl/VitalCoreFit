#include "../../include/models/PersistenciaUsuario.h"
#include "../../include/models/Usuario.h"
#include "../../include/json.hpp" 
#include <fstream>
#include <iostream>
// Convierte las métricas y datos biológicos del perfil del usuario a formato JSON y los escribe de manera persistente en el almacenamiento local.

// Recupera y decodifica el archivo JSON local para poblar los atributos del perfil biológico al iniciar la aplicación. Retorna falso si el archivo no existe.
void guardarPerfil(const Usuario& u) {
    nlohmann::json json;
    json["nombre"]   = u.nombre;
    json["edad"]     = u.edad;
    json["peso"]     = u.peso;
    json["altura"]   = u.altura;
    json["genero"]   = static_cast<int>(u.GeneroUsuario);
    json["objetivo"] = static_cast<int>(u.ObjetivoUsuario);
    json["actividad"]= static_cast<int>(u.NivelActividadUsuario);
    json["tmb"]      = u.tmb;
    json["imc"]     = u.imc;
    json["tdee"]     = u.tdee;
    
    json["metaCalorica"]   = u.metaCalorica;
    json["macroProteinas"] = u.macroProteinas;
    json["macroCarbos"]    = u.macroCarbos;
    json["macroGrasas"]    = u.macroGrasas;

    std::ofstream archivo("data/perfil.json");
    if (archivo.is_open()) {
        archivo << json.dump(4);
        archivo.close();
    }
}

bool cargarPerfil(Usuario& u) {
    std::ifstream archivo("data/perfil.json");
    if (!archivo.is_open()) {
        return false;   
    }
    nlohmann::json json;
    archivo >> json;
    archivo.close();

    u.nombre  = json["nombre"].get<std::string>();
    u.edad = json["edad"].get<int>();
    u.peso = json["peso"].get<double>();
    u.altura = json["altura"].get<double>();
    u.GeneroUsuario = static_cast<Genero>(json["genero"].get<int>());

    u.ObjetivoUsuario  = static_cast<Objetivo>(json["objetivo"].get<int>());
    u.NivelActividadUsuario  = static_cast<NivelActividad>(json["actividad"].get<int>());
    u.tmb            = json["tmb"].get<double>();
    u.tdee           = json["tdee"].get<double>();
    u.imc           = json["imc"].get<double>();
    u.metaCalorica   = json["metaCalorica"].get<double>();
    u.macroProteinas = json["macroProteinas"].get<double>();
    u.macroCarbos    = json["macroCarbos"].get<double>();
    u.macroGrasas    = json["macroGrasas"].get<double>();

    return true;
}