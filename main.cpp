#include <iostream>
#include <vector>
#include "include/models/Usuario.h"
#include "include/models/Nutricion.h"
#include "include/models/Alimento.h"
#include "include/models/ListaComidas.h"
#include "include/models/Entrenamiento.h"
#include "include/models/Dashboard.h"
#include "include/models/PersistenciaUsuario.h" 

using namespace std;

int main(){
    Usuario u; 

    if (cargarPerfil(u)) {
        cout << "--- Perfil cargado exitosamente ---" << endl;
        cout << "Bienvenido de vuelta, " << u.nombre << "!" << endl;
    } else {
        cout << "--- No hay perfil guardado. Creando perfil de prueba... ---" << endl;
        
        u.nombre = "Nicolas"; 
        u.peso = 70.0;
        u.edad = 19;
        u.altura = 175.0;
        u.GeneroUsuario = Genero::Masculino;
        u.NivelActividadUsuario = NivelActividad::Moderado;
        u.ObjetivoUsuario = Objetivo::Mantener;

  
        u.tmb = calcularTMB(u);
        u.tdee = calcularTDEE(u, u.tmb);
        calcularMetas(u, u.tdee);

        guardarPerfil(u); 
    }


    cout << "\n--- Tus Metas Nutricionales ---" << endl;
    cout << "TMB: " << u.tmb << " kcal" << endl;
    cout << "TDEE: " << u.tdee << " kcal" << endl;
    cout << "Carbo: " << u.macroCarbos << " g" << endl;
    cout << "Grasas: " << u.macroGrasas << " g" << endl;
    cout << "Proteina: " << u.macroProteinas << " g" << endl;

    cout << "\n--- Base de Datos de Alimentos ---" << endl;
    vector<Alimento> lista = cargarAlimentos("data/foods.json");
    for (const auto& alimento : lista) {
        cout << alimento.nombre << " - " << alimento.calorias << " kcal " 
             << " - " << alimento.carbohidratos << " g - " 
             << alimento.proteina << " g - " << alimento.grasa << " g" << endl;
    }
    
    cout << "\nBuscando 'ar':" << endl;
    vector<Alimento> encontrados = buscarAlimento(lista, "ar");
    for (size_t i = 0; i < encontrados.size(); i++) {
        cout << encontrados[i].nombre << endl;
    }
    

    ListaComidas diaDeHoy;
    diaDeHoy.cabeza = nullptr;
    diaDeHoy.cantidad = 0;

    agregarComida(diaDeHoy, lista[0], 200.0); 
    agregarComida(diaDeHoy, lista[1], 100.0); 

    double caloriasHoy = calcularCaloriasDelDia(diaDeHoy);
    cout << "\nCalorias consumidas hoy: " << caloriasHoy << " kcal" << endl;
    
    ListaEjercicio EjercicioDeHoy;
    EjercicioDeHoy.cabeza = nullptr;
    EjercicioDeHoy.cantidad = 0;

    Ejercicio pressBanca;
    pressBanca.nombre = "Press de banca";
    pressBanca.series = 3;
    pressBanca.repeticiones = 10;
    pressBanca.peso = 60.0;
    pressBanca.volumen = calcularVolumen(3, 10, 60.0);
    pressBanca.caloriasQuemadas = calcularCaloriasQuemadas(3.5, u.peso, 45.0); 
    agregarEjercicio(EjercicioDeHoy, pressBanca);


    double volumen = calcularVolumen(3, 10, 60.0);
    double CaloriasQuemadas = calcularCaloriasQuemadas(3.5, u.peso, 45.0); 
    double FCMax = calcularFCMax(u.edad); 
    int ZonaCardiaca = calcularZonaCardiaca(150, FCMax);

    cout << "\n--- Resumen de Entrenamiento ---" << endl;
    cout << "Volumen: " << volumen << " kg" << endl;
    cout << "Calorias Quemadas: " << CaloriasQuemadas << " kcal" << endl;
    cout << "FCMax: " << FCMax << " bpm" << endl;
    cout << "Zona Cardiaca: " << ZonaCardiaca << endl;

    double totalQuemado = calcularTotalQuemado(EjercicioDeHoy);
    ResultadoDash dash = calcularDashboard(caloriasHoy, totalQuemado, u.metaCalorica);
    
    cout << "\n--- Dashboard ---" << endl;
    imprimirEstadoDash(dash);

    liberarLista(diaDeHoy);
    liberarListaEjercicios(EjercicioDeHoy);
    
    guardarPerfil(u);
    cout << "\nProgreso guardado correctamente. ¡Hasta luego!" << endl;

    return 0;
}