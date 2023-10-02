#include <iostream>
#include <fstream>
#include "metodo1.h"
#include "metodo2.h"
#include "cajero.h"

using namespace std;

int main() {
    string ruta = "usuario.dat";
    int largo = tamArchivo(ruta);
    string datos;
    unsigned char *arreglo = descriptMet2R(ruta, 10);
    datos = arregloAstring(arreglo, largo);
    int fila = filas(datos);
    matriz(datos, fila);

    return 0;
}


