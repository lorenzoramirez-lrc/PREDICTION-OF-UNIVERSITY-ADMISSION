#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <fstream>

using namespace std;



//Funciones SFTP Client

//Funciones Data Transformer
struct CSV{

    int numero_filas;
    int numero_columnas;
    string **matriz;

};
CSV readCSV(ifstream& inFile);

//Funciones Analysis Module
void printHead(string **matriz, int numero_columnas);
void printInfo(string **matriz, int numero_columnas, int numero_filas);
void printDescribe(string **matriz, int numero_columnas, int numero_filas);


//Funciones Conversion Module



#endif