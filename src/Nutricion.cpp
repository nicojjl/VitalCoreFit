#include "../../include/models/Nutricion.h"
#include "../../include/json.hpp"
#include <fstream>
#include <iostream>
using namespace std;
// Lee la base de datos JSON local de alimentos y reconstruye un catálogo completo de objetos de tipo Alimento en un vector para uso interno.

// Filtra el catálogo de alimentos comparando las cadenas de texto en minúsculas, retornando coincidencias parciales o exactas según los parámetros de búsqueda del usuario.
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
vector<Alimento> buscarAlimento(const vector<Alimento>& catalogo, const string& textoBusqueda) {
    vector<Alimento> resultados;
    string textoMinusculo = textoBusqueda;
    for (int i = 0; i < textoMinusculo.size(); i++){
        textoMinusculo[i] = tolower(textoMinusculo[i]);
    }
    for (int i = 0; i < catalogo.size(); i++){
        string nombreMin = catalogo[i].nombre;
        for (int z = 0; z<nombreMin.size(); z++){
            nombreMin[z]= tolower(nombreMin[z]);
        }
        if (nombreMin.find(textoMinusculo) != string::npos) {
            resultados.push_back(catalogo[i]); 
        }
    }
    return resultados;
}