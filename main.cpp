#include <iostream>
#include <vector>
#include "include/models/Usuario.h"
#include "include/models/Nutricion.h"
#include "include/models/Alimento.h"
#include "include/models/ListaComidas.h"
#include "include/models/Entrenamiento.h"
#include "include/models/Dashboard.h"
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
    vector<Alimento> encontrados = buscarAlimento(lista, "ar");
    for (int i = 0; i < encontrados.size(); i++) {
        cout << encontrados[i].nombre << endl;
    }
    
    ListaComidas diaDeHoy;
    diaDeHoy.cabeza = nullptr;
    diaDeHoy.cantidad = 0;

    agregarComida(diaDeHoy, lista[0], 200.0); // 200g de Arroz
    agregarComida(diaDeHoy, lista[1], 100.0); // 100g de Palta

    double caloriasHoy = calcularCaloriasDelDia(diaDeHoy);
    cout << "Calorias del dia: " << caloriasHoy << " kcal" << endl;

    liberarLista(diaDeHoy);
    ListaEjercicio EjercicioDeHoy;
    EjercicioDeHoy.cabeza = nullptr;
    EjercicioDeHoy.cantidad = 0;

    Ejercicio pressBanca;
    pressBanca.nombre = "Press de banca";
    pressBanca.series = 3;
    pressBanca.repeticiones = 10;
    pressBanca.peso = 60.0;
    pressBanca.volumen = calcularVolumen(3, 10, 60.0);
    pressBanca.caloriasQuemadas = calcularCaloriasQuemadas(3.5, 70.0, 45.0);
    agregarEjercicio(EjercicioDeHoy, pressBanca);

    double volumen = calcularVolumen(3, 10, 60.0);
    double CaloriasQuemadas = calcularCaloriasQuemadas(3.5,70,45);
    double FCMax = calcularFCMax(19);
    int ZonaCardiaca = calcularZonaCardiaca(150, FCMax);

    cout << "Volumen: " << volumen << endl;
    cout << "Calorias Quemadas: " << CaloriasQuemadas << endl;
    cout << "FCMax: " << FCMax << endl;
    cout << "ZonaCardiaca: " << ZonaCardiaca << endl;
   
    double totalQuemado = calcularTotalQuemado(EjercicioDeHoy);
    ResultadoDash dash  = calcularDashboard(caloriasHoy, totalQuemado, prueba.metaCalorica);
    imprimirEstadoDash(dash);

    liberarListaEjercicios(EjercicioDeHoy);
    return 0;
}