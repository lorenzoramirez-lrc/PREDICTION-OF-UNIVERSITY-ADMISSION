#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


struct CSV{

    int numero_filas;
    int numero_columnas;
    string **matriz;

};

CSV readCSV(ifstream& inFile){


    CSV csv;
    
    string linea;
    string particion;
    int numero_filas=0;
    int numero_columnas=0;

    while(getline(inFile,linea)){
        numero_filas+=1;
    }

    inFile.clear();
    inFile.seekg(0);

    getline(inFile, linea);
    stringstream numero(linea);
     
    while(getline(numero,particion,',')){
        numero_columnas++;
    };

    inFile.seekg(0);



    string **matriz= new string *[numero_filas];

    for(int i=0; i<numero_filas; i++){
        *(matriz+i)= new string[numero_columnas];
    }


    for(int i=0; i<numero_filas; i++){

        getline(inFile, linea);
        stringstream fila(linea);

        for(int j=0; j<numero_columnas; j++){

            getline(fila,particion,',');
            getline(stringstream (particion), particion, '\r');

            *(*(matriz+i)+j)=particion;

        }
    }

    csv.matriz=matriz;

    csv.numero_filas=numero_filas;
    csv.numero_columnas=numero_columnas;


    return csv;
}   



