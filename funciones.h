#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string convertirbinario(int n);
void desencriptacion1(string texto, int semilla);
void printtext(string texto);
unsigned int binarioADecimal(string cadenaBinaria, int longitud);
string desencriptacion(string binario,int semilla);
unsigned char *stringtochar(string texto);
void encriptacion1(string texto, int semilla);
string encriptacion(string binario,int semilla);
string remplazo1a0(string binario,int salto);
int contador(string binario);
string archivo (string nombreArchivo);

class funciones
{
public:
    funciones();
};

#endif // FUNCIONES_H
