#include <iostream>
#include <string>
#include <fstream>
#include "funciones.h"

using namespace std;


int main()
{
    string direccion= archivo("C:\\Users\\HP\\OneDrive\\Documentos\\Practica3\\Ejemplotexto.txt");
    int opcion,semilla;
    cout<<"Ingrese la semilla";
    cin>>semilla;
    cout<<"1)Encriptar Archivo      2) Desencriptar Archivo";
    cin>>opcion;
    switch (opcion) {
    case 1:
        encriptacion1(direccion,semilla);
        break;
    case 2:
        desencriptacion1(direccion,semilla);
    default:
        cout<<"Opcion invalida";
        break;
    }

    return 0;
}
