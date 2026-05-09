#include "../../include/models/Nutricion.h"
#include "../../include/json.hpp"
#include <fstream>
#include <iostream>
using namespace std;

vector<Alimento> cargarAlimentos(const string& rutaArchivo) {
    vector<Alimento> lista;
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo de alimentos." << endl;
        return lista;
    }
    nlohmann::json datosJson;
    archivo >> datosJson;
    for (const auto& item : datosJson["alimentos"]) {
        Alimento nuevoAlimento;
        nuevoAlimento.nombre = item["nombre"].get<string>();
        nuevoAlimento.calorias = item["calorias"].get<double>();
        nuevoAlimento.proteina = item["proteina"].get<double>();
        nuevoAlimento.carbohidratos = item["carbohidratos"].get<double>();
        nuevoAlimento.grasa = item["grasa"].get<double>();
        lista.push_back(nuevoAlimento);
    }
    return lista;
}