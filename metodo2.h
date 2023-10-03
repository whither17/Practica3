#ifndef METODO2_H
#define METODO2_H
#include <iostream>
using namespace std;
void liberarArray(unsigned char *ptr);
void liberarArraySigno(char *ptr);
int tamArchivo(string ruta);
int cantLineas(unsigned char *texto, int largo);
int cant_retornos(string ruta);
unsigned char *archivo(string ruta, int largo);
unsigned char *Abinario(unsigned char *archivo, int largo);
unsigned char *cambiarBits(unsigned char *arreglo, int semilla, int largo);
unsigned char *cambiarbit(unsigned char *arreglo, int semilla, int largo);
unsigned char bitAint(unsigned char *bloque);
unsigned char *Achar(unsigned char *arreglo, int largo);
void escritura(unsigned char *datos, int largo, string ruta);
void encripMet2(string ruta, int semilla);
void descripMet2(string ruta, int semilla);
unsigned char *descriptMet2R(string ruta, int semilla);
void met2();
#endif // METODO2_H
