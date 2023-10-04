#include <iostream>
#include <string>
#include "metodo1.h"
#include "metodo2.h"
using namespace std;

//Administrador

void liberarMatriz(string **matriz, int filas) {
    for(int i = 0; i < filas; i++) {
        delete []matriz[i];
    }
    delete []matriz;
}

unsigned char *stringAarray(string datos) {
    int largo = datos.size();
    unsigned char *data = new unsigned char[largo];

    for(int i = 0; i < largo; i++) {
        data[i] = datos[i];
    }

    return data;
}

void escribir(string **matriz, int filas, string nuevo_dato, string ruta, int metodo, int seed) {
    string datos = "";
    unsigned char *data, *doc_bin, *codificado;
    int largo;

    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < 3; j++) {
            datos += matriz[i][j];
            if(j < 2) datos += ", ";
        }
        if(i < filas - 1) datos += "\r\n";
    }

    if(nuevo_dato.size() > 0) {
        datos += "\r\n" + nuevo_dato;
    }

    if(metodo == 1) {
        encriptacion1(datos, seed, ruta);
    }
    if(metodo == 2) {

        largo = datos.size();
        data = stringAarray(datos);
        doc_bin = Abinario(data, largo);
        data = NULL;
        codificado = cambiarBits(doc_bin, seed, largo);
        doc_bin = NULL;
        data = Achar(codificado, largo);
        escritura(data, largo, ruta);

        }

    liberarMatriz(matriz, filas);
}

string arregloAstring(unsigned char *arreglo, int largo) {
    char* datos = new char[largo+1];
    int letra;

    for(int i = 0; i < largo; i++) {
        letra = arreglo[i];
            datos[i] = letra;
    }
    liberarArray(arreglo);
    datos[largo] = '\r';
    string usuarios(datos);
    liberarArraySigno(datos);

    return usuarios;
}

int filas(string datos) {
    int filas = 0, comas = 0;

    for(int i = 0; i < datos.size(); i++) {
        if(datos[i] == ',') {
            comas++;
        }
    }
    filas = comas/2;
    return filas;
}

string **matriz(string usuarios, int filas) {

    string **matriz = new string *[filas];
    string aux;
    string linea = "";
    string caracter;
    int pos_user = 0, pos_col = 0;

    for(int f = 0; f < filas; f++) {
        matriz[f] = new string[3];
    }

    for(int j = 0; j < filas; j++) {
        while (caracter != "\r") {
            caracter = usuarios[pos_user];
            if(caracter != "\r") linea += caracter;
            pos_user++;
        }
        caracter = "";
        for(int k = 0; k < 3; k++) {
            while ((caracter != ",") && (pos_col < linea.size())) {
                caracter = linea[pos_col];
                if(caracter != ",") aux += caracter;
                pos_col++;
            }
            matriz[j][k] = aux;
            pos_col++;
            aux = "";
            caracter = "";
        }
        caracter = "";
        pos_user++;
        pos_col = 0;
        linea = "";
    }

    return matriz;
}

string **actualizarMatriz(string **matriz, int filas, int filas_n, string *n_dato) {

    string **matx = new string *[filas_n];
    for(int i = 0; i < filas_n; i++) {
        matx[i] = new string[3];
    }

    for(int j = 0; j < filas; j++) {
        for(int k = 0; k < 3; k++) {
            matx[j][k] = matriz[j][k];
        }
    }

    liberarMatriz(matriz, filas);

    for(int l = 0; l < 3; l++) {
        matx[filas_n-1][l] = n_dato[l];
    }
    delete []n_dato;

    return matx;
}

void mostrarDatos(string **matriz, int filas) {

    cout << "\n -------------- \n Usuario   Clave   Saldo\n\n";
    for(int i = 0; i < filas; i++) {
        for(int j = 0; j < 3; j++) {
            cout << matriz[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

bool KeyAdmin(string ruta, int seed, string c_intento, int metodo){

    bool c = true;
    int largo = tamArchivo(ruta);
    unsigned char *array;
    string key;

    if(metodo == 1) key = desencriptacion1R(archivo(ruta), seed);
    if(metodo == 2) array = descriptMet2R(ruta, seed);

    for(int i = 0; i < largo; i++) {
        if(array[i] != c_intento[i]) c = false;
    }

    return c;
}

bool usuarioExistente(string newUser, string **matriz, int filas) {

    bool user = true;                                   //si el usuarion no existe

    for(int i = 0; i < filas; i++) {
        if(matriz[i][0] == newUser) {
            user = false;
        }
    }
    return user;
}

int posUser(string **matriz, int filas, string user) {
    int posicion = -1;

    for(int i = 0; i < filas; i++) {
        if(matriz[i][0] == user) {
            posicion = i;
            break;
        }
    }

    return posicion;
}

bool numValido(string numero) {

    bool n = true;

    for(int i = 0; i < numero.size(); i++) {
        if((numero[i] < 48) || (numero[i] > 57)) {
            n = false;
            break;
        }
    }
    return n;
}

string *newUser(string **matriz, int filas) {

    string *n_user = new string[3];
    string cedula = "";
    string clave = "";
    string dinero = "";

    cout << endl << "-------------------------" << endl;

    while(true) {
        cout << "ingrese la cedula: ";
        cin >> cedula;
        if(!numValido(cedula)) {
            cout << "\nIngrese un documento valido\n";
        }
        else {
            if(!usuarioExistente(cedula,matriz, filas)) {
                cout << "\nEl usuario ya existe\n";
            }
            else {
                break;
            }
        }
    }

    while(true) {
        cout << "ingrese la clave: ";
        cin >> clave;
        if(!numValido(clave)) {
            cout << "\nIngrese una clave valida (nnnn)\n";
        }
        else {
            if(clave.size() != 4) {
                cout << "\nLa clave debe tener 4 digitos\n";
            }
            else {
                break;
            }
        }
    }

    while(true) {
        cout << "ingrese el saldo: ";
        cin >> dinero;
        if(!numValido(dinero)) {
            cout << "\nIngrese un monto valido\n";
        }
        else {
            break;
        }
    }

    n_user[0] = cedula;
    n_user[1] = clave;
    n_user[2] = dinero;

    return n_user;
}

bool claveUsuario(string **matriz, int filas, string user, string clave) {
    bool key = false;

    int pos = posUser(matriz, filas, user);

    if(matriz[pos][1] == clave) {
        key = true;
    }

    return key;
}

void eliminarUsuario(string **matriz, int filas, int posicion) {

    string cc, cv, sl;
    if(posicion < filas - 1) {
        for(int i = posicion; i < filas-1; i++) {
            matriz[i][0] = matriz[i+1][0];
            matriz[i][1] = matriz[i+1][1];
            matriz[i][2] = matriz[i+1][2];
        }
        matriz[filas-2][0] = matriz[filas-1][0];
        matriz[filas-2][1] = matriz[filas-1][1];
        matriz[filas-2][2] = matriz[filas-1][2];
        delete []matriz[filas-1];
    }
    else {
        delete []matriz[posicion];
    }
}

void cambiarClave(string **matriz, int pos) {

    string clave;

    while(true) {
        cout << "Ingrese nueva clave: ";
        cin >> clave;
        if(numValido(clave)) {
            if(clave.size() == 4) {
                break;
            }
        }
        else {
            cout << "\nClave no valida\n";
        }
    }

    matriz[pos][1] = clave;
}

void cambiarDinero(string **matriz, int filas, int pos) {

    string dinero;

    while(true) {
        cout << "Ingrese el nuevo valor: ";
        cin >> dinero;
        if(numValido(dinero)) {
            break;
        }
        else {
            cout << "\nValor no valido\n";
        }
    }

    matriz[pos][2] = dinero;
}

string decod_met1(string ruta, int semilla) {
    string direccion, datos;
    direccion = archivo(ruta);
    datos = desencriptacion1R(direccion,semilla);
    return datos;
}

string decod_met2(string ruta, int semilla) {
    unsigned char *archivo;
    string datos = "";
    int largo = tamArchivo(ruta);

    archivo = descriptMet2R(ruta, semilla);
    datos = arregloAstring(archivo, largo);

    return datos;
}

void Admin(string key, int semilla, string ruta, int seed_admin, string data, int metodo) {

    string **matrix;
    string clave = "";
    string usuarios = "";
    string documento;
    int intentos = 5;
    int fila = 0;
    int posicion = 0;
    int opcion = 0;
    int opcion2 = 0;

    cout << "\n----------------\n";
    while(true) {
        cout <<"Ingrese la clave: ";
        cin >> clave;
        if(KeyAdmin(key, seed_admin, clave, metodo)) {
            cout << "\nInicio exitoso\n";
            break;
        }
        else {
            cout << "\nclave incorrecta\n";
            intentos--;
            if(intentos == 0) {
                exit(0);
            }
        }
    }

    fila = filas(data);
    matrix = matriz(data, fila);


    while(true) {

        mostrarDatos(matrix, fila);
        cout << "\n1 - Ingresar nuevo usuario\n2 - Modificar usuario\n3 - Salir y guardar\n";

        while(true) {
            cout << "Ingrese una opcion: ";
            cin >> opcion;
            if((opcion < 1) || (opcion > 3)) cout << "Opcion no valida\n";
           else break;
        }

        if(opcion == 1){

           matrix = actualizarMatriz(matrix, fila, fila+1, newUser(matrix, fila));
           fila++;

        }

        if(opcion == 2) {

            while(true) {
                cout << "Ingrese el documento del usuario: ";
                cin >> documento;
                posicion = posUser(matrix, fila, documento);
                if(posicion == -1) {
                    cout << "\nEl usuario no existe\n";
                }
                else break;
            }

            cout << "\n1 - Modificar clave\n2 - Modificar dinero\n3 - Eliminar usuario\n4 - Atras\n";
            while(true) {
                cout << "Ingrese una opcion: ";
                cin >> opcion2;
                if((opcion2 < 1) || (opcion2 > 4)) {
                    cout << "\nOpcion no valida\n";
                }
                else break;
            }

            if(opcion2 == 1) {
                cambiarClave(matrix, posicion);
                mostrarDatos(matrix, fila);
            }

            if(opcion2 == 2) {
                cambiarDinero(matrix, fila, posicion);
                mostrarDatos(matrix, fila);
            }

            if(opcion2 == 3) {
                eliminarUsuario(matrix, fila, posicion);
                fila--;
            }

            if(opcion2 == 4) {
                break;
            }

        }

        if(opcion == 3) {

            escribir(matrix, fila, "", ruta, metodo, semilla);
            break;
        }
    }
}

void Versaldo(string **matrix,int fila,int usuario,string ruta, int semilla, int metodo){
    string saldo=matrix[usuario][2],aux;
    int money=stoi(saldo);
    if(money-1000<0){
        cout<<"Saldo Insuficiente";
    }else{
        cout<<"\n -------------------------\n Su saldo es de: "<<money;
        aux=to_string(money-1000);
        cout <<"\n -------------------------\n Se debitaron 1000, nuevo saldo: "<<aux;
        matrix[usuario][2]=aux;
        escribir(matrix,fila,"",ruta,metodo,semilla);
    }

}
void RetirarSaldo(string **matrix,int fila,int usuario,string ruta, int semilla, int metodo){
    string saldo=matrix[usuario][2],aux;
    int money=stoi(saldo),retiro;
    if(money-1000<0){
        cout<<"Saldo Insuficiente";
    }else{
        cout<<"\nCuanto desea retirar: ";
        cin>>retiro;
        if(money-1000-retiro<0){
            cout<<"\nSaldo Insuficiente";
        }else{
            aux=to_string(money-1000-retiro);
            matrix[usuario][2]=aux;
            cout<<"\nEl nuevo saldo es: "<<matrix[usuario][2];
        }
    }

}
void User(int semilla, string ruta, string data, int metodo) {

    string usu,key;
    int fila,i,opcion;
    string **matrix;
    bool control=false;

    fila = filas(data);
    matrix = matriz(data, fila);

    cout<<"\nIngrese su numero de documento: ";
    cin>>usu;
    for(i=0;i<fila;i++){
        if(matrix[i][0]==usu){
            while(true){
                cout<<"\nIngrese su clave: ";
                cin>>key;
                if(matrix[i][1]==key){
                    control=true;
                    break;
                }else{
                    cout<<"Clave incorrecta";
                }}
            break;
        }else if(i==fila-1){
            cout<<"Usuario no encontrado";
        }
    }
    if(control){
        cout<<"\nQue quiere realizar: ";
        cout << "\n1 - Ver saldo\n2 - Retirar dinero\n\nIngrese una opcion: ";
        cin>>opcion;
        switch (opcion) {
        case 1:{
            Versaldo(matrix,fila,i,ruta,semilla,metodo);
            break;
        }case 2:{
            RetirarSaldo(matrix,fila,i,ruta,semilla,metodo);
            break;
        }
        default:
            cout << "Opcion no valida";
        }
        }

}

void Cajero() {

    int semilla;
    int seed_admin;
    int metodo;
    int opcion;
    string key_admin;
    string ruta_data;
    string datos;

    while(true) {
        cout << "\nIngrese metodo de codificacion a usar (1 o 2): ";
        cin >> metodo;
        if((metodo == 1) || (metodo == 2)) break;
        else cout << "\nvalor incorrecto";
    }

    cout << "\nIngrese el nombre de la base de datos: ";
    cin >> ruta_data;
    cout << "\nIngrese el nombre del archivo -clave admin-: ";
    cin >> key_admin;
    cout << "\ningrese la semilla de la base de datos: ";
    cin >> semilla;
    cout << "\ningrese la semilla de la clave administrador: ";
    cin >> seed_admin;
    cout << "\nCajero\n\n";
    cout << "1 - Administrador\n2 - Usuario\n";
    cout << "Ingrese una opcion: ";
    cin >> opcion;

    if(metodo == 1) {
        datos = decod_met1(ruta_data, semilla);
    }
    if(metodo == 2) {
        datos = decod_met2(ruta_data, semilla);
    }

    switch (opcion) {
    case 1:
        Admin(key_admin, semilla, ruta_data, seed_admin, datos, metodo);
        break;
    case 2:
        User(semilla, ruta_data, datos, metodo);
        break;
    default:
        cout << "Opcion no valida";
    }
}
