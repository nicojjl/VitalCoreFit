#include <iostream>
#include "include/models/Usuario.h"

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
    return 0;
}