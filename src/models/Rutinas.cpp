#include "../../include/models/Rutinas.h"
#include <iostream>

using namespace std;

double calcularPesoSugerido(double unRM, double porcentaje) {
    return unRM * porcentaje;
}

Rutina crearRutinaFullBody2() {
    Rutina r;
    r.nombre = "Full-Body 2 Dias";
    r.diasPorSemana = 2;

    DiaRutina lunes;
    lunes.nombreDia = "Lunes";
    lunes.enfoque = "Full-Body";
    lunes.cantidadEjercicios = 5;

    lunes.ejercicios[0] = {"Sentadilla", "Piernas", 3, 10, 0.70};
    lunes.ejercicios[1] = {"Press de Banca", "Pecho", 3, 10, 0.70};
    lunes.ejercicios[2] = {"Remo con Barra", "Espalda", 3, 10, 0.70};
    lunes.ejercicios[3] = {"Press Militar", "Hombros", 3, 10, 0.70};
    lunes.ejercicios[4] = {"Curl de Biceps", "Biceps", 3, 12, 0.60};

    r.dias[0] = lunes;

    DiaRutina jueves;
    jueves.nombreDia = "Jueves";
    jueves.enfoque = "Full-Body";
    jueves.cantidadEjercicios = 5;

    jueves.ejercicios[0] = {"Peso Muerto", "Piernas/Espalda baja", 3, 8, 0.75};
    jueves.ejercicios[1] = {"Press Inclinado", "Pecho", 3, 10, 0.65};
    jueves.ejercicios[2] = {"Jalones al Pecho", "Espalda", 3, 10, 0.65};
    jueves.ejercicios[3] = {"Elevaciones Laterales", "Hombros", 3, 12, 0.50};
    jueves.ejercicios[4] = {"Extensiones de Triceps", "Triceps", 3, 12, 0.60};

    r.dias[1] = jueves;

    return r;
}

Rutina crearRutinaFullBody3() {
    Rutina r;
    r.nombre = "Full-Body 3 Dias";
    r.diasPorSemana = 3;

    r.dias[0].nombreDia = "Lunes";
    r.dias[0].enfoque = "Full-Body A";
    r.dias[0].cantidadEjercicios = 5;
    r.dias[0].ejercicios[0] = {"Sentadilla Trasera", "Cuádriceps", 4, 6, 0.80};
    r.dias[0].ejercicios[1] = {"Press Banca", "Pecho", 4, 8, 0.75};
    r.dias[0].ejercicios[2] = {"Remo con Barra", "Espalda", 4, 8, 0.75};
    r.dias[0].ejercicios[3] = {"Elevaciones Laterales", "Hombros", 3, 12, 0.60};
    r.dias[0].ejercicios[4] = {"Curl de Bíceps con Barra", "Bíceps", 3, 10, 0.65};

    r.dias[1].nombreDia = "Miércoles";
    r.dias[1].enfoque = "Full-Body B";
    r.dias[1].cantidadEjercicios = 5;
    r.dias[1].ejercicios[0] = {"Peso Muerto Rumano", "Isquiotibiales/Glúteos", 4, 8, 0.75};
    r.dias[1].ejercicios[1] = {"Dominadas", "Espalda", 4, 8, 0.0};
    r.dias[1].ejercicios[2] = {"Press Militar", "Hombros", 3, 10, 0.70};
    r.dias[1].ejercicios[3] = {"Prensa de Piernas", "Cuádriceps", 3, 12, 0.70};
    r.dias[1].ejercicios[4] = {"Press Francés", "Tríceps", 3, 10, 0.65};

    r.dias[2].nombreDia = "Viernes";
    r.dias[2].enfoque = "Full-Body C";
    r.dias[2].cantidadEjercicios = 5;
    r.dias[2].ejercicios[0] = {"Hip Thrust", "Glúteos", 4, 10, 0.75};
    r.dias[2].ejercicios[1] = {"Press Inclinado con Mancuernas", "Pecho", 3, 10, 0.70};
    r.dias[2].ejercicios[2] = {"Jalones al Pecho", "Espalda", 3, 12, 0.65};
    r.dias[2].ejercicios[3] = {"Zancadas con Mancuerna", "Piernas", 3, 12, 0.65};
    r.dias[2].ejercicios[4] = {"Elevación de Talones", "Pantorrillas", 4, 15, 0.60};

    return r;
}

Rutina crearRutinaTorsoPierna() {
    Rutina r;
    r.nombre = "Torso/Pierna 4 Dias";
    r.diasPorSemana = 4;


    r.dias[0].nombreDia = "Lunes";
    r.dias[0].enfoque = "Torso";
    r.dias[0].cantidadEjercicios = 5;
    r.dias[0].ejercicios[0] = {"Press Banca", "Pecho", 4, 8, 0.75};
    r.dias[0].ejercicios[1] = {"Remo con Barra", "Espalda", 4, 8, 0.75};
    r.dias[0].ejercicios[2] = {"Press Militar", "Hombros", 3, 10, 0.70};
    r.dias[0].ejercicios[3] = {"Jalones al Pecho", "Espalda", 3, 12, 0.65};
    r.dias[0].ejercicios[4] = {"Fondos", "Pecho/Triceps", 3, 10, 0.0}; 

    r.dias[1].nombreDia = "Martes";
    r.dias[1].enfoque = "Pierna";
    r.dias[1].cantidadEjercicios = 5;
    r.dias[1].ejercicios[0] = {"Sentadilla", "Piernas", 4, 8, 0.75};
    r.dias[1].ejercicios[1] = {"Peso Muerto", "Piernas", 3, 8, 0.75};
    r.dias[1].ejercicios[2] = {"Prensa", "Piernas", 3, 10, 0.70};
    r.dias[1].ejercicios[3] = {"Extensiones", "Piernas", 3, 12, 0.60};
    r.dias[1].ejercicios[4] = {"Curl Femoral", "Piernas", 3, 12, 0.60};

    r.dias[2] = r.dias[0]; 
    r.dias[2].nombreDia = "Jueves";

    r.dias[3] = r.dias[1];
    r.dias[3].nombreDia = "Viernes";

    return r;
}

Rutina crearRutinaFrecuencia2() {
    Rutina r;
    r.nombre = "Push/Pull/Legs - Frecuencia 2";
    r.diasPorSemana = 5;

    r.dias[0].nombreDia = "Lunes";
    r.dias[0].enfoque = "Pecho";
    r.dias[0].cantidadEjercicios = 4;
    r.dias[0].ejercicios[0] = {"Press Banca", "Pecho", 4, 8, 0.75};
    r.dias[0].ejercicios[1] = {"Press Inclinado con Mancuernas", "Pecho", 4, 10, 0.70};
    r.dias[0].ejercicios[2] = {"Aperturas en Polea", "Pecho", 3, 12, 0.60};
    r.dias[0].ejercicios[3] = {"Fondos", "Pecho", 3, 10, 0.0};

    r.dias[1].nombreDia = "Martes";
    r.dias[1].enfoque = "Espalda";
    r.dias[1].cantidadEjercicios = 4;
    r.dias[1].ejercicios[0] = {"Remo con Barra", "Espalda", 4, 8, 0.75};
    r.dias[1].ejercicios[1] = {"Jalones al Pecho", "Espalda", 4, 10, 0.65};
    r.dias[1].ejercicios[2] = {"Remo con Mancuerna", "Espalda", 3, 12, 0.70};
    r.dias[1].ejercicios[3] = {"Pullover con Polea", "Espalda", 3, 15, 0.60};

    r.dias[2].nombreDia = "Miércoles";
    r.dias[2].enfoque = "Piernas";
    r.dias[2].cantidadEjercicios = 5;
    r.dias[2].ejercicios[0] = {"Sentadilla Trasera", "Cuádriceps", 4, 6, 0.80};
    r.dias[2].ejercicios[1] = {"Peso Muerto Rumano", "Isquiotibiales", 4, 8, 0.75};
    r.dias[2].ejercicios[2] = {"Prensa de Piernas", "Cuádriceps/Glúteos", 3, 12, 0.70};
    r.dias[2].ejercicios[3] = {"Curl de Piernas Tumbado", "Isquiotibiales", 3, 12, 0.65};
    r.dias[2].ejercicios[4] = {"Elevación de Talones", "Pantorrillas", 4, 15, 0.60};

    r.dias[3].nombreDia = "Viernes";
    r.dias[3].enfoque = "Hombros";
    r.dias[3].cantidadEjercicios = 4;
    r.dias[3].ejercicios[0] = {"Press Militar", "Hombros", 4, 8, 0.70};
    r.dias[3].ejercicios[1] = {"Elevaciones Laterales", "Hombros", 4, 12, 0.60};
    r.dias[3].ejercicios[2] = {"Pájaros con Mancuerna", "Hombros", 3, 15, 0.55};
    r.dias[3].ejercicios[3] = {"Encogimientos de Hombros", "Trapecio", 3, 12, 0.70};

    r.dias[4].nombreDia = "Sábado";
    r.dias[4].enfoque = "Brazos";
    r.dias[4].cantidadEjercicios = 4;
    r.dias[4].ejercicios[0] = {"Curl de Bíceps con Barra", "Bíceps", 3, 10, 0.65};
    r.dias[4].ejercicios[1] = {"Press Francés", "Tríceps", 3, 10, 0.65};
    r.dias[4].ejercicios[2] = {"Curl Martillo", "Bíceps", 3, 12, 0.60};
    r.dias[4].ejercicios[3] = {"Extensión en Polea Alta", "Tríceps", 3, 12, 0.60};

    return r;
}

Rutina generarRutina(int diasDisponibles) {
    if (diasDisponibles == 2) return crearRutinaFullBody2();
    if (diasDisponibles == 3) return crearRutinaFullBody3();
    if (diasDisponibles == 4) return crearRutinaTorsoPierna();
    return crearRutinaFrecuencia2();  
}

void imprimirRutina(const Rutina& r) {
    cout << "\n========================================\n";
    cout << "          " << r.nombre << "          \n";
    cout << "========================================\n";
    cout << "Dias de entrenamiento por semana: " << r.diasPorSemana << "\n";
    
    for (int i = 0; i < r.diasPorSemana; i++) {
        cout << "\n--> " << r.dias[i].nombreDia << " - Enfoque: " << r.dias[i].enfoque << "\n";
        cout << "----------------------------------------\n";
        
        for (int j = 0; j < r.dias[i].cantidadEjercicios; j++) {
            const EjercicioRutina& ej = r.dias[i].ejercicios[j];
            cout << "  - " << ej.nombre 
                 << " | " << ej.grupoMuscular 
                 << " | " << ej.series << "x" << ej.repeticiones;
            
            if(ej.porcentaje1RM > 0) {
                 cout << " (@ " << ej.porcentaje1RM * 100 << "% 1RM)";
            }
            cout << "\n";
        }
    }
    cout << "========================================\n\n";
}