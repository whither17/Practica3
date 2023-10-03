#include <iostream>
#include <fstream>
#include "metodo1.h"
#include "metodo2.h"
#include "cajero.h"

using namespace std;

void Encriptacion();

int main() {
    unsigned short opcion;
    bool control = true;

    cout << "Practica 3\nAgudelo Zapata Andres Felipe\nCorrea Morales Robinson\n";

    while(control) {

        cout << "\n *** \n\n1 - Programa de encriptacion\n2 - Simulacion de un cajero\n3 - Cerrar\n\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;


        switch (opcion) {
        case 1:
            Encriptacion();
            break;
        case 2:
            Cajero();
            break;
        case 3:
            control = false;
            break;
        default:
            cout << "Opcion no valida";
        }
    }
    return 0;
}

void Encriptacion() {

    unsigned short opcion;

    cout << "\n\n1 - Metodo1\n2 - Metodo2\n\nIngrese una opcion:";
    cin >> opcion;
    switch (opcion) {
    case 1:

        break;
    case 2:

        break;
    default:
        cout << "Opcion no valida";

    }
}

