#include <iostream>
#include <fstream>
#include "metodo2.h"
using namespace std;

void liberarArray(unsigned char *ptr) {
    delete []ptr;
}

void liberarArraySigno(char *ptr) {
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

int cantLineas(unsigned char *texto, int largo) {
    int lineas = 0;

    for(int i = 0; i < largo; i++) {
        if(texto[i] == '\r') {
            lineas = lineas++;
        }
    }
    return lineas;
}

unsigned char *archivo(string ruta, int largo) {

    unsigned char *contenido = new unsigned char[largo];
    int i = 0;
    char caracter;
    fstream archivo;

    archivo.open(ruta, ios::in | ios::binary);
    if(archivo.fail()){
        cout << "No se pudo abrir el archivo\n";
        exit(EXIT_FAILURE);
    }
    while(i  < largo) {
        archivo.get(caracter);
        contenido[i] = caracter;
        i++;
    }
    archivo.close();

    return contenido;
}

unsigned char *Abinario(unsigned char *archivo, int largo) {

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

void aplicarRegla(unsigned char *bloque, int largo) {

    unsigned char char_;

    char_ = bloque[largo-1];
    for(int i = (largo - 1); i > 0; i--) {
        bloque[i] = bloque[i-1];
    }
    bloque[0] = char_;
}

void deshacerRegla(unsigned char *bloque, int largo) {

    unsigned char char_;

    char_ = bloque[0];
    for(int i = 0; i < largo; i++) {
        bloque[i] = bloque[i+1];
    }
    bloque[largo-1] = char_;
}

unsigned char *cambiarBits(unsigned char *arreglo, int semilla, int largo) {

    unsigned char *chars = new unsigned char[largo*8];
    unsigned char bloque[semilla];
    int nuevo_bloque = 0;
    int limite = (((largo*8)/semilla)*semilla);

    while(nuevo_bloque < limite) {
        for(int i = 0; i < semilla; i++) {
            bloque[i] = arreglo[i + nuevo_bloque];
        }
        aplicarRegla(bloque, semilla);
        for(int i = 0; i < semilla; i++) {
            chars[i + nuevo_bloque] = bloque[i];
        }
        nuevo_bloque = nuevo_bloque + semilla;
    }

    for(int i = 0; i < (largo*8)-limite; i++) {
        bloque[i] = arreglo[limite + i];
    }

    aplicarRegla(bloque,(largo*8)-limite );

    for(int i = 0; i < (largo*8)-limite; i++) {
        chars[i + limite] = bloque[i];
    }
    liberarArray(arreglo);
    return chars;
}

unsigned char *cambiarbit(unsigned char *arreglo, int semilla, int largo) {

    unsigned char *chars = new unsigned char[largo*8];
    unsigned char bloque[semilla];
    int nuevo_bloque = 0;
    int limite = (((largo*8)/semilla)*semilla);

    while(nuevo_bloque < limite) {
        for(int i = 0; i < semilla; i++) {
            bloque[i] = arreglo[i + nuevo_bloque];
        }
        deshacerRegla(bloque, semilla);
        for(int i = 0; i < semilla; i++) {
            chars[i + nuevo_bloque] = bloque[i];
        }
        nuevo_bloque = nuevo_bloque + semilla;
    }

    for(int i = 0; i < (largo*8)-limite; i++) {
        bloque[i] = arreglo[limite + i];
    }

    deshacerRegla(bloque,(largo*8)-limite );

    for(int i = 0; i < (largo*8)-limite; i++) {
        chars[i + limite] = bloque[i];
    }
    liberarArray(arreglo);
    return chars;
}

unsigned char bitAint(unsigned char *bloque) {

    unsigned char caracter;
    unsigned char binario;

    caracter = 0b00000000;
    binario = 0b10000000;
    for(int i = 0; i < 8; i++) {
        if(bloque[i] == '1') {
            caracter = caracter | binario;
            binario  = binario >> 1;
        }
        else {
            binario = binario >> 1;
        }
    }
    return caracter;
}

unsigned char *Achar(unsigned char *arreglo, int largo) {

    unsigned char *caracteres = new unsigned char[largo*8];
    unsigned int caracter;
    unsigned char bloque[8];
    int nuevo_bloque = 0;

    while(((nuevo_bloque)/8) < largo) {
        for(int i = 0; i < 8; i++) {
            bloque[i] = arreglo[i + nuevo_bloque];
        }
        caracter = bitAint(bloque);
        caracteres[(nuevo_bloque)/8] = caracter;
        nuevo_bloque = nuevo_bloque + 8;
    }

    for(int i = 0; i < largo*8; i++) {
    }
    liberarArray(arreglo);
    return caracteres;

}

void escritura(unsigned char *datos, int largo, string ruta) {
    ofstream archivo;
    archivo.open(ruta, ios::out | ios::binary);
    if(archivo.fail()) {
        cout << "No se pudo escribir el archivo\n";
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < largo; i++) {
        cout << datos[i];
        archivo << datos[i];
    }
    liberarArray(datos);
    archivo.close();
}

void encripMet2(string ruta, int semilla) {
    int largo = tamArchivo(ruta);
    unsigned char *documento = archivo(ruta, largo);
    unsigned char *doc_bin = Abinario(documento, largo);
    documento = NULL;
    unsigned char *codificado = cambiarBits(doc_bin, semilla, largo);
    doc_bin = NULL;
    documento = Achar(codificado, largo);
    escritura(documento, largo, "codificado.dat");
}

void descripMet2(string ruta, int semilla) {
    int largo = tamArchivo(ruta);
    unsigned char *documento = archivo(ruta, largo);
    unsigned char *doc_bin = Abinario(documento, largo);
    documento = NULL;
    unsigned char *codificado = cambiarbit(doc_bin, semilla, largo);
    doc_bin = NULL;
    documento = Achar(codificado, largo);
    escritura(documento, largo, "natural.txt");
}
unsigned char *descriptMet2R(string ruta, int semilla) {
    int largo = tamArchivo(ruta);
    unsigned char *documento = archivo(ruta, largo);
    unsigned char *doc_bin = Abinario(documento, largo);
    documento = NULL;
    unsigned char *codificado = cambiarbit(doc_bin, semilla, largo);
    doc_bin = NULL;
    documento = Achar(codificado, largo);
    return documento;
}








