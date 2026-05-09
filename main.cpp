#include <iostream>
#include <vector>
#include "include/models/Usuario.h"
#include "include/models/Nutricion.h"
#include "include/models/Alimento.h"
using namespace std;

int main(){
    Usuario prueba;
    prueba.nombre = "Nicoals";
    prueba.peso = 70.0;
    prueba.edad = 19;
    prueba.altura = 175.0;
    prueba.GeneroUsuario = Genero::Masculino;
    prueba.NivelActividadUsuario = NivelActividad::Moderado;
    prueba.ObjetivoUsuario = Objetivo::Mantener;

    double tmbusuario = calcularTMB(prueba);
    double tdeeusuario = calcularTDEE(prueba,tmbusuario);
    calcularMetas(prueba,tdeeusuario);

    cout << "TMB: " << tmbusuario << endl;
    cout << "TDEE: " << tdeeusuario << endl;
    cout << "Carbo: " << prueba.macroCarbos << endl;
    cout << "Grasas: " << prueba.macroGrasas << endl;
    cout << "Proteina: " << prueba.macroProteinas << endl;
    vector<Alimento> lista = cargarAlimentos("data/foods.json");
    for (const auto& alimento : lista) {
        cout << alimento.nombre << " - " << alimento.calorias << " kcal " << " - " << alimento.carbohidratos << " gramos " << " - " << alimento.proteina << " gramos " << " - " << alimento.grasa << " gramos" << endl;
    }
    return 0;
}