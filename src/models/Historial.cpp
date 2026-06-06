#include "../../include/models/Historial.h"
#include "../../include/json.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

std::string obtenerFechaHoy() {
    time_t ahora = time(nullptr);
    tm* fecha = localtime(&ahora);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", fecha);
    return std::string(buffer);
}

void guardarDiaEnHistorial(const ListaComidas& listaDia, const ListaEjercicio& listaEjercicios, double caloriasConsumidas, double caloriasQuemadas, double balanceNeto) {
    nlohmann::json historial;
    
    std::ifstream entrada("data/historial.json");
    if (entrada.is_open()) {
        entrada >> historial;
        entrada.close();
    } else {
        historial["registros"] = nlohmann::json::array();
    }

    nlohmann::json registroHoy;
    registroHoy["fecha"] = obtenerFechaHoy();
    registroHoy["caloriasConsumidas"] = caloriasConsumidas;
    registroHoy["caloriasQuemadas"] = caloriasQuemadas;
    registroHoy["balanceNeto"] = balanceNeto;

    nlohmann::json arregloComidas = nlohmann::json::array();
    NodoComida* actualComida = listaDia.cabeza;
    while (actualComida != nullptr) {
        nlohmann::json comida;
        comida["nombre"]   = actualComida->alimento.nombre;
        comida["cantidad"] = actualComida->cantidad;
        comida["calorias"] = (actualComida->alimento.calorias * actualComida->cantidad) / 100.0;
        arregloComidas.push_back(comida);
        actualComida = actualComida->siguiente;
    }
    registroHoy["comidas"] = arregloComidas;

    nlohmann::json arregloEjercicios = nlohmann::json::array();
    NodoEjercicio* actualEjercicio = listaEjercicios.cabeza;
    while (actualEjercicio != nullptr) {
        nlohmann::json ejercicio;
        ejercicio["nombre"] = actualEjercicio->ejercicio.nombre;
        ejercicio["series"] = actualEjercicio->ejercicio.series;
        ejercicio["repeticiones"] = actualEjercicio->ejercicio.repeticiones;
        ejercicio["peso"] = actualEjercicio->ejercicio.peso;
        ejercicio["volumen"] = actualEjercicio->ejercicio.volumen;
        arregloEjercicios.push_back(ejercicio);
        actualEjercicio = actualEjercicio->siguiente;
    }
    registroHoy["ejercicios"] = arregloEjercicios;

    historial["registros"].push_back(registroHoy);

    std::ofstream salida("data/historial.json");
    salida << historial.dump(4);
    salida.close();
}

void mostrarHistorial() {
    std::ifstream archivo("data/historial.json");
    if (!archivo.is_open()) {
        std::cout << "\nNo hay historial guardado en dias anteriores." << std::endl;
        return;
    }
    nlohmann::json historial;
    archivo >> historial;
    archivo.close();
    
    std::cout << "\n=== HISTORIAL DE DIAS ANTERIORES ===" << std::endl;
    for (const auto& registro : historial["registros"]) {
        std::cout << "Fecha: " << registro["fecha"] << std::endl;
        std::cout << "  Consumido: " << registro["caloriasConsumidas"] << " kcal" << std::endl;
        std::cout << "  Quemado:   " << registro["caloriasQuemadas"]   << " kcal" << std::endl;
        std::cout << "  Balance:   " << registro["balanceNeto"]        << " kcal" << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}