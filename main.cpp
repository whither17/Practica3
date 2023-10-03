#include <iostream>
#include <fstream>
#include "metodo1.h"
#include "metodo2.h"
#include "cajero.h"

using namespace std;

int main() {

    cout << "Practica 3\nAgudelo Zapata Andres Felipe\nCorrea Morales Robinson\n";
    cout << "\n ---- \n\n1 - Programa de encriptacion\n2 - simulacion de un cajero\n";
    cout << "Ingrese una opcion: ";
    unsigned short opcion;
    cin >> opcion;
    switch (opcion) {
    case 1:
       // Encriptacion();
        break;
    case 2:
        Cajero();
        break;
    default:
        cout << "Opcion no valida";

    }
    return 0;
}


