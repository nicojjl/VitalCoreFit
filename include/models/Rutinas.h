    #pragma once
    #include <string>


    struct EjercicioRutina {
        std::string nombre;
        std::string grupoMuscular;
        int series;
        int repeticiones;
        double porcentaje1RM;
    };

    struct DiaRutina {
        std::string nombreDia;
        std::string enfoque;
        EjercicioRutina ejercicios[10];
        int cantidadEjercicios;
    };

    struct Rutina {
        std::string nombre;
        int diasPorSemana;
        DiaRutina dias[5];
    };

    Rutina crearRutinaFullBody2();
    Rutina crearRutinaFullBody3();
    Rutina crearRutinaTorsoPierna();
    Rutina crearRutinaFrecuencia2();
    Rutina generarRutina(int diasDisponibles);

    double calcularPesoSugerido(double unRM, double porcentaje);
    void imprimirRutina(const Rutina& r);

// Generador de entrenamientos estructurados. Organiza rutinas, días y ejercicios, adaptando el volumen de trabajo y recomendando pesos específicos según los días disponibles y el nivel del usuario.