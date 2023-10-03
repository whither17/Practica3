#include <iostream>
#include <string>
#include <fstream>
#include "metodo1.h"
using namespace std;

string archivo (string nombreArchivo) {
    ifstream archivo;
    string linea,textof="";
    archivo.open(nombreArchivo,ios::in | ios::binary);
    if (archivo.fail()){
        cout<<"El programa fallo";
    }
    while(!archivo.eof()){
        getline(archivo,linea);
        textof=textof+linea;

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
char *stringtochar(string texto){
    unsigned long long n=texto.length();
    char* array= new char [n+1];
    array[n] = '\0';
    for (unsigned long long i=0;i<n;i++){
        array[i] = texto[i];
    }
    return array;
}
void encriptacion1(string texto, int semilla, string ruta){
    char* array= stringtochar(texto);
    string binfinal="";
    int valorascii=0;
    for(int j=0;*(array+j)!='\0';j++){
        valorascii=int(*(array+j));
        string valorbin=convertirbinario(valorascii);
        binfinal=binfinal+valorbin;
    }
    delete array;
    cout<<binfinal;
    binfinal=encriptacion(binfinal,semilla);
    binfinal=binfinal+"\n";
    printtext(binfinal, ruta);
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
string desencriptacion1(string texto, int semilla){
    string textfinal="",orden=desencriptacion(texto,semilla),bloque;
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
    cantbloques=tt/semilla;
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

void met1(){

}
