#include "metodo1.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int tamArchivo1(string ruta) {

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

string archivo (string nombreArchivo) {
    ifstream archivo;
    string textof="";
    char caracter;
    int largo = tamArchivo1(nombreArchivo);
    int i = 0;
    archivo.open(nombreArchivo,ios::in | ios::binary);
    if (archivo.fail()){
        cout<<"El programa fallo";
    }
    while(i < largo){
        archivo.get(caracter);
        textof=textof+caracter;
        i++;
    }

    archivo.close();
    return textof;
}
void printtext(string texto, string ruta){
    ofstream archivo;
    archivo.open(ruta,ios::out | ios::binary);
    if (archivo.fail()){
        cout<<"El programa fallo";
    }
    archivo<<texto.c_str();
    archivo.close();
}
string convertirbinario(int n){
    string binario="";
    if(n>0){
        while(n>0){
            if (n%2==0)
                binario="0"+binario;
            else
                binario="1"+binario;
            n=n/2;
        }
    }
    while(binario.length()<8)
        binario="0"+binario;
    return binario;
}
unsigned char *stringtochar(string texto){
    unsigned long long n=texto.length();
    unsigned char* array= new unsigned char [n+1];
    array[n] = '\0';
    for (unsigned long long i=0;i<n;i++){
        array[i] = texto[i];
    }
    return array;
}

string binAchar(string binarios) {
    string textfinal="",bloque;
    int n=binarios.length(),limabajo=0;
    for (int i=0;i<n;i=i+8){
        bloque=binarios.substr(limabajo,8);
        unsigned int binparcial=binarioADecimal(bloque,8);
        char letra=(binparcial);
        textfinal+=letra;
        limabajo=limabajo+8;
    }
    return textfinal;
}

string charAbin(string doc) {
    unsigned char* array= stringtochar(doc);
    string binfinal="";
    string text_final;
    int valorascii=0;
    for(int j=0;*(array+j)!='\0';j++){
        valorascii=int(*(array+j));
        string valorbin=convertirbinario(valorascii);
        binfinal=binfinal+valorbin;
    }
    delete array;
    return binfinal;
}

void encriptacion1(string texto, int semilla, string ruta_salida){
    unsigned char* array= stringtochar(texto);
    string binfinal="";
    string text_final;
    int valorascii=0;
    for(int j=0;*(array+j)!='\0';j++){
        valorascii=int(*(array+j));
        string valorbin=convertirbinario(valorascii);
        binfinal=binfinal+valorbin;
    }
    delete array;
    binfinal=encriptacion(binfinal,semilla);
    text_final = binAchar(binfinal);

    printtext(text_final, ruta_salida);

}
string encriptacion(string binario,int semilla){
    int tt,cantbloques,limabajo,n;
    string resulatadoparcial,resultadofinal="";
    tt=binario.length();
    if(tt%semilla==0){
        cantbloques=tt/semilla;
    }else{
        cantbloques=(tt/semilla)+1;
    }
    limabajo=0;
    for(int i=1;i<=cantbloques;i++){
        string exe=binario.substr(limabajo,semilla);
        limabajo=limabajo+semilla;
        if(i==1){
            int next=contador(exe);
            resulatadoparcial=remplazo1a0(exe,1);
            n=next;
        }
        else{
            int next=contador(exe);
            resulatadoparcial=remplazo1a0(exe,n);
            n=next;}
        resultadofinal=resultadofinal+resulatadoparcial;
    }
    return resultadofinal;
}
string remplazo1a0(string binario,int salto){
    int sizze=binario.length();
    for (int j=salto-1;j<sizze;j=j+salto){
        if(binario[j]=='0')
            binario[j]='1';
        else
            binario[j]='0';
    }
    return binario;
}
int contador(string binario){
    int cantuno=0,cantcero=0,sizze=binario.length(),retu;
    for (int j=0;j<sizze;j++){
        if(binario[j]=='0')
            cantcero++;
        else
            cantuno++;
    }
    if(cantcero>cantuno){
        retu=2;
    }else if(cantuno>cantcero)
        retu=3;
    else
        retu=1;
    return retu;
}
void desencriptacion1(string texto, int semilla, string ruta_salida){
    string textfinal="",orden,bloque, binarios;
    binarios = charAbin(texto);
    orden=desencriptacion(binarios,semilla);


    int n=orden.length(),limabajo=0;
    for (int i=0;i<n;i=i+8){
        bloque=orden.substr(limabajo,8);
        unsigned int binparcial=binarioADecimal(bloque,8);
        char letra=(binparcial);
        textfinal+=letra;
        limabajo=limabajo+8;
    }
    printtext(textfinal, ruta_salida);
}

string desencriptacion1R(string texto, int semilla) {
    string textfinal="",orden,bloque, binarios;
    binarios = charAbin(texto);
    orden=desencriptacion(binarios,semilla);


    int n=orden.length(),limabajo=0;
    for (int i=0;i<n;i=i+8){
        bloque=orden.substr(limabajo,8);
        unsigned int binparcial=binarioADecimal(bloque,8);
        char letra=(binparcial);
        textfinal+=letra;
        limabajo=limabajo+8;
    }
    return textfinal;

}
string desencriptacion(string binario,int semilla){
    int tt,cantbloques,limabajo,n;
    string resulatadoparcial,resultadofinal="";
    tt=binario.length();
    if(tt%semilla==0){
        cantbloques=tt/semilla;
    }else{
        cantbloques=(tt/semilla)+1;
    }
    limabajo=0;
    for(int i=1;i<=cantbloques;i++){
        string exe=binario.substr(limabajo,semilla);
        limabajo=limabajo+semilla;
        if(i==1){
            resulatadoparcial=remplazo1a0(exe,1);
            int next=contador(resulatadoparcial);
            n=next;
        }
        else{
            resulatadoparcial=remplazo1a0(exe,n);
            int next=contador(resulatadoparcial);
            n=next;
        }
        resultadofinal=resultadofinal+resulatadoparcial;
    }
    return resultadofinal;
}
unsigned int binarioADecimal(string cadenaBinaria, int longitud) {
    unsigned int decimal = 0;
    int multiplicador = 1;
    string numero;
    for (int i = longitud - 1; i >= 0; i--) {
        numero = cadenaBinaria[i];
        if (numero == "1") {
            decimal += multiplicador;
        }
        multiplicador = multiplicador * 2;
    }
    return decimal;
}

void met1() {

    string ruta_entrada, direccion;
    string ruta_salida;
    int seed;
    int opcion = 0;


    while(true) {

        cout << "\n1 - Codificar\n2 - Decodificar\n3 - Atras\n\ningrese una opcion: ";
        cin >> opcion;

        if(opcion == 1) {

            cout << "\nIngrese la ruta o nombre del archivo sin codificar: ";
            cin >> ruta_entrada;
            cout << "\nIngrese nombre del archivo resultante: ";
            cin >> ruta_salida;
            cout << "\n\nIngrese la semilla: ";
            cin >> seed;

            direccion = archivo(ruta_entrada);
            encriptacion1(direccion,seed, ruta_salida);
            cout << "\n\n **Finalizado**\n\n";
        }

        if(opcion == 2) {

            cout << "\nIngrese la ruta o nombre del archivo codificado: ";
            cin >> ruta_entrada;
            cout << "\nIngrese el nombre del archivo resulatnte: ";
            cin >> ruta_salida;
            cout << "\n\nIngrese la semilla: ";
            cin >> seed;
            direccion = archivo(ruta_entrada);
            desencriptacion1(direccion,seed, ruta_salida);
            cout << "\n\n **Finalizado**\n\n";
        }

        if(opcion == 3) {
            break;
        }

    }
}
