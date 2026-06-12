#include <iostream>
#include <vector>
#include <windows.h>
#include "include/models/Usuario.h"
#include "include/models/Nutricion.h"
#include "include/models/Alimento.h"
#include "include/models/ListaComidas.h"
#include "include/models/Entrenamiento.h"
#include "include/models/Dashboard.h"
#include "include/models/PersistenciaUsuario.h" 
#include "include/models/Validacion.h"
#include "include/models/Historial.h"

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);

    Usuario u; 
    string error;

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
        u.imc = calcularIMC(u);
        calcularMetas(u, u.tdee);

        if (!validarUsuario(u, error)) {
            cout << "Error en el perfil: " << error << endl;
            return 1;
        }
        guardarPerfil(u); 
    }

    mostrarHistorial();

    cout << "\n--- Tus Metas Nutricionales ---" << endl;
    cout << "TMB: " << u.tmb << " kcal" << endl;
    cout << "IMC: " << u.imc << " %" << endl;
    cout << "TDEE: " << u.tdee << " kcal" << endl;
    cout << "Carbo: " << u.macroCarbos << " g" << endl;
    cout << "Grasas: " << u.macroGrasas << " g" << endl;
    cout << "Proteina: " << u.macroProteinas << " g" << endl;

    vector<Alimento> lista = cargarAlimentos("data/foods.json");

    if (lista.empty()) {
        cout << "Saliendo del programa para evitar errores de memoria." << endl;
        return 1;
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
    
    if (!validarBrzycki(pressBanca.peso, pressBanca.repeticiones, error)) {
        cout << "Error al calcular 1RM: " << error << endl;
    }

    pressBanca.volumen = calcularVolumen(pressBanca.series, pressBanca.repeticiones, pressBanca.peso);
    
    double metActual = 3.5;
    double minutosActuales = 45.0;
    
    if (!validarMET(metActual, error)) {
        cout << "Error en MET: " << error << endl;
    } else {
        pressBanca.caloriasQuemadas = calcularCaloriasQuemadas(metActual, u.peso, minutosActuales); 
    }
    
    agregarEjercicio(EjercicioDeHoy, pressBanca);

    double totalQuemado = calcularTotalQuemado(EjercicioDeHoy);
    ResultadoDash dash = calcularDashboard(caloriasHoy, totalQuemado, u.metaCalorica);
    
    cout << "\n--- Dashboard ---" << endl;
    imprimirEstadoDash(dash);

    double balanceNeto = caloriasHoy - totalQuemado;

    guardarDiaEnHistorial(diaDeHoy, EjercicioDeHoy, caloriasHoy, totalQuemado, balanceNeto);

    liberarLista(diaDeHoy);
    liberarListaEjercicios(EjercicioDeHoy);
    
    if (!validarUsuario(u, error)) {
        cout << "No se pudo guardar el progreso por error en el perfil: " << error << endl;
    } else {
        guardarPerfil(u);
        cout << "\nProgreso guardado correctamente. ¡Hasta luego!" << endl;
    }

    return 0;
}