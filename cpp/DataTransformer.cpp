#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Estructura CSV para guardar toda su informacion
struct CSV{

    int numero_filas;
    int numero_columnas;
    string **matriz;

};

CSV readCSV(ifstream& inFile){


    CSV csv;    //Se crea estructura
    
    string linea;
    string particion;
    int numero_filas=0;
    int numero_columnas=0;

    while(getline(inFile,linea)){
        numero_filas+=1;   //Se obtiene numero de filas
    } 

    inFile.clear();
    inFile.seekg(0);   //Se regresa archivo al principio

    getline(inFile, linea);
    stringstream numero(linea);
     
    while(getline(numero,particion,',')){
        numero_columnas++;   //Se obtiene numero de columnas
    };

    inFile.seekg(0);   //Se regresa archivo al principio



    string **matriz= new string *[numero_filas];  

    for(int i=0; i<numero_filas; i++){
        *(matriz+i)= new string[numero_columnas];   //Se crea matriz utilizando memoria dinamica
    }


    for(int i=0; i<numero_filas; i++){

        getline(inFile, linea);
        stringstream fila(linea);    //Se obtiene cada fila del CSV

        for(int j=0; j<numero_columnas; j++){

            getline(fila,particion,',');
            getline(stringstream (particion), particion, '\r');   //Cada fila del CSV se particiona en sus columnas

            *(*(matriz+i)+j)=particion;   //Cada particion se añade a una celda de la matriz

        }
    }

    csv.matriz=matriz;
    csv.numero_filas=numero_filas;     //Se asignan los valores a la estructura
    csv.numero_columnas=numero_columnas;

    //Se retorna estructura
    return csv;
}   



