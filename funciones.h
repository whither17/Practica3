#ifndef FUNCIONES_H
#define FUNCIONES_H
using namespace std;
int tamArchivo(string ruta);
int cant_retornos(string ruta);
unsigned char *archivo(string ruta);
unsigned char *Abinario(string ruta,unsigned char *archivo);
unsigned char *cambiarBits(string ruta, unsigned char *arreglo, int semilla);
unsigned char *Acaracter(string ruta, unsigned char *arreglo, int semilla);
#endif // FUNCIONES_H
