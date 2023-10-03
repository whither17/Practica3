#ifndef METODO1_H
#define METODO1_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

using namespace std;
string convertirbinario(int n);
void desencriptacion1(string texto, int semilla, string ruta);
string desencriptacion1R(string texto, int semilla);
void printtext(string texto);
unsigned int binarioADecimal(string cadenaBinaria, int longitud);
string desencriptacion(string binario,int semilla);
unsigned char *stringtochar(string texto);
void encriptacion1(string texto, int semilla, string ruta);
string encriptacion(string binario,int semilla);
string remplazo1a0(string binario,int salto);
int contador(string binario);
string archivo (string nombreArchivo);
void met1();

#endif // METODO1_H




