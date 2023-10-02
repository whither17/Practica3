#ifndef METODO1_H
#define METODO1_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
string convertirbinario(int n);
string desencriptacion1(string texto, int semilla);
void printtext(string texto, string ruta);
unsigned int binarioADecimal(string cadenaBinaria, int longitud);
string desencriptacion(string binario,int semilla);
char *stringtochar(string texto);
void encriptacion1(string texto, int semilla, string ruta);
string encriptacion(string binario,int semilla);
string remplazo1a0(string binario,int salto);
int contador(string binario);
string archivo (string nombreArchivo);

class funciones
{
public:
    funciones();
};
#endif // METODO1_H
