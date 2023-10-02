#include <iostream>
#include <string>
#include "metodo2.h"
#include "metodo1.h"
using namespace std;

//Administrador

string arregloAstring(unsigned char *arreglo, int largo) {
    char* datos = new char[largo+1];
    int letra;

    for(int i = 0; i < largo; i++) {
        letra = arreglo[i];
            datos[i] = letra;
    }
    liberarArray(arreglo);
    datos[largo] = '\r';
    string usuarios(datos);
    liberarArraySigno(datos);

    return usuarios;
}

int filas(string datos) {
    int filas = 0, comas = 0;

    for(int i = 0; i < datos.size(); i++) {
        if(datos[i] == ',') {
            comas++;
        }
    }
    filas = comas/2;
    return filas;
}

string **matriz(string usuarios, int filas) {

    string **matriz = new string *[filas];
    string aux;
    string linea = "";
    string caracter;
    int pos_user = 0, pos_col = 0;

    for(int f = 0; f < filas; f++) {
        matriz[f] = new string[3];
    }

    for(int j = 0; j < filas; j++) {
        while (caracter != "\r") {
            caracter = usuarios[pos_user];
            if(caracter != "\r") linea += caracter;
            pos_user++;
        }
        caracter = "";
        for(int k = 0; k < 3; k++) {
            while ((caracter != ",") && (pos_col < linea.size())) {
                caracter = linea[pos_col];
                if(caracter != ",") aux += caracter;
                pos_col++;
            }
            matriz[j][k] = aux;
            pos_col++;
            aux = "";
            caracter = "";
        }
        caracter = "";
        pos_user++;
        pos_col = 0;
        linea = "";
    }

    return matriz;
}

bool usuarioExistente(string newUser, string **matriz) {

    bool user = true;                                   //si el usuarion no existe
    for(int i = 0; i < fila; i++) {

        size_t posicion = matriz[i].find(newUser);

        if (posicion != string::npos) {
            user = false;
            break;
        }
    }
    return user;
}


int posUsuario(string newUser, string **matriz, int fila) {

    for(int i = 0; i < fila; i++) {

        size_t position = matriz[i].find(newUser);

        if (position != string::npos) {
            break;
        }
    }
    return position;
}


