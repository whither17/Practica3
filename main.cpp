#include <iostream>
#include <fstream>
#include "funciones.h"

using namespace std;

int main() {
    string ruta =  "H:\\ProyectosInfo2\\practica3\\build-practica3-Desktop_Qt_6_5_2_MinGW_64_bit-Debug\\prueba.txt";
    int semilla = 4;


    Acaracter(ruta,cambiarBits(ruta, Abinario(ruta,archivo(ruta)), semilla) ,semilla);

    return 0;
}


