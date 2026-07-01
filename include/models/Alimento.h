#pragma once
#include <string>

struct Alimento{
    std::string nombre;
    double calorias;
    double proteina;
    double carbohidratos;
    double grasa;
};
// Estructura base para los alimentos. Almacena el nombre y los macronutrientes esenciales (proteínas, carbohidratos, grasas) junto con las calorías totales para utilizarlos en los cálculos de la dieta.