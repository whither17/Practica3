#ifndef CAJERO_H
#define CAJERO_H
#include <iostream>
#include <string>
#include "metodo1.h"
#include "metodo2.h"
using namespace std;

string decod_met2(string ruta, int semilla);
void Versaldo(string **matrix,int fila,int usuario,string ruta);
string arregloAstring(unsigned char *arreglo, int largo);
unsigned char *stringAarray(string datos);
int filas(string datos);
string **matriz(string usuarios, int filas);
bool usuarioExistente(string newUser, string **matriz, int fila);
void newUser(string **matriz, int filas);
void escribir(string **matriz, int filas, string nuevo_dato, string ruta, int metodo);



void Cajero();

#endif // CAJERO_H
