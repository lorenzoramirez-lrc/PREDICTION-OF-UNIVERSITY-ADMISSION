#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <fstream>


using namespace std;

struct CSV{

    int numero_filas;
    int numero_columnas;
    string **matriz;

};

CSV readCSV(ifstream& inFile);
void printHead(string **matriz, int numero_columnas);
void printInfo(string **matriz, int numero_columnas, int numero_filas);



#endif