#ifndef CAJERO_H
#define CAJERO_H
#include <iostream>
#include <string>
#include "metodo1.h"
#include "metodo2.h"
using namespace std;

string arregloAstring(unsigned char *arreglo, int largo);
unsigned char *stringAarray(string datos);
int filas(string datos);
string **matriz(string usuarios, int filas);
bool usuarioExistente(string newUser, string **matriz, int fila);
string *newUser(string **matriz, int filas);



void Cajero();

#endif // CAJERO_H
