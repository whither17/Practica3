#include <iostream>
#include <fstream>

#include "funciones.h"
using namespace std;

void liberarArray(unsigned char *ptr) {
    delete []ptr;
}

int tamArchivo(string ruta) {

    fstream archivo;
    archivo.open(ruta, ios::in | ios::binary);
    if(archivo.fail()){
        cout << "No se pudo abrir el archivo\n";
        exit(EXIT_FAILURE);
    }
    archivo.seekg(0, ios::end);
    streampos largo = archivo.tellg();
    archivo.seekg(0, std::ios::beg);
    archivo.close();
    return largo;
}



unsigned char *archivo(string ruta) {
    int i = 0;
    int retornos = 0;
    int largo;
    char caracter;
    fstream archivo;
    largo = tamArchivo(ruta);

    archivo.open(ruta, ios::in | ios::binary);
    if(archivo.fail()){
        cout << "No se pudo abrir el archivo\n";
        exit(EXIT_FAILURE);
    }
    unsigned char *contenido = new unsigned char[largo];

    while(i  < largo) {
        archivo.get(caracter);
        contenido[i] = caracter;
        i++;
    }
    for(int j = 0; j < (largo);j++){
        cout << contenido[j];
    }
    archivo.close();
    cout << endl;

    return contenido;
}

unsigned char *Abinario(string ruta,unsigned char *archivo) {

    int largo = tamArchivo(ruta);
    int cociente, residuo;
    int pos, pos_binarios = 0;
    unsigned char *binarios = new unsigned char[largo*8];
    unsigned char bin[8];

    for(int i = 0; i < largo; i++) {
        for(int c = 0; c < 8; c++) {
            bin[c] = '0';
        }

        cociente = archivo[i];
        pos = 0;
        while(cociente >= 1) {
            residuo = (cociente % 2);
            cociente = (cociente/2);
            bin[pos] = 48 + residuo;
            pos++;
        }
        for(int j = 7; j >= 0; j--) {
            binarios[pos_binarios + j] = bin[7 - j];
        }
        pos_binarios = pos_binarios + 8;
    }
    liberarArray(archivo);
    return binarios;
}

void aplicarRegla(unsigned char *bloque, int semilla) {
    int largo = 0 ;
    unsigned char char_;
    for(int j = 0; j < semilla; j++) {
        if((bloque[j] == '0')||(bloque[j] == '1')) {
            largo++;
        }
        else {
            break;
        }
    }
    char_ = bloque[largo-1];
    for(int i = (largo - 1); i > 0; i--) {
        bloque[i] = bloque[i-1];
    }
    bloque[0] = char_;
    cout << bloque << endl;
}

unsigned char *cambiarBits(string ruta, unsigned char *arreglo, int semilla) {
    int largo = tamArchivo(ruta);
    unsigned char *codificados = new unsigned char[largo*8];
    unsigned char bloque[semilla];
    int nuevo_bloque = 0;

    while(nuevo_bloque < largo*8) {
        for(int i = 0; i < semilla; i++) {
            bloque[i] = arreglo[i + nuevo_bloque];
        }
        aplicarRegla(bloque, semilla);
        for(int i = 0; i < semilla; i++) {
            codificados[i + nuevo_bloque]= bloque[i];
        }
        nuevo_bloque = nuevo_bloque + semilla;
    }
    liberarArray(arreglo);
    return codificados;
}

void desRegla(unsigned char *bloque, int semilla) {
    int largo = 0 ;
    unsigned char char_;
    for(int j = 0; j < semilla; j++) {
        if((bloque[j] == '0')||(bloque[j] == '1')) {
            largo++;
        }
        else {
            break;
        }
    }
    char_ = bloque[0];
    for(int i = 0; i < largo; i++) {
        bloque[i] = bloque[i+1];
    }
    bloque[largo-1] = char_;
    cout << bloque << endl;
}

unsigned char *Acaracter(string ruta, unsigned char *arreglo, int semilla) {
    int largo = tamArchivo(ruta);
    unsigned char *chars = new unsigned char[largo];
    unsigned char bloque[semilla];
    int nuevo_bloque = 0;

    while(nuevo_bloque < largo*8) {
        for(int i = 0; i < semilla; i++) {
            bloque[i] = arreglo[i + nuevo_bloque];
        }
        desRegla(bloque, semilla);
        for(int i = 0; i < semilla; i++) {
            chars[i + nuevo_bloque]= bloque[i];
        }
        nuevo_bloque = nuevo_bloque + semilla;
    }
    liberarArray(arreglo);
    return chars;
}




