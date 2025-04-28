#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <fstream>

using namespace std;


//Funciones Envloader

bool loadEnv(string ruta_archivo, unordered_map<string, string> &envCred);


//Funciones SFTP Client

bool downloadFileSFTP(const string& host, int port, const string& user, const string& password, const string& remote_path, const string& local_path);

//Funciones Data Transformer
struct CSV{

    int numero_filas;
    int numero_columnas;
    string **matriz;

};
CSV readCSV(ifstream& inFile);

//Funciones Analysis Module
void printHead(string **matriz, int numero_columnas, int numero_filas);
void printInfo(string **matriz, int numero_columnas, int numero_filas);
void printDescribe(string **matriz, int numero_columnas, int numero_filas);
void printCorrelation(string **matriz, int numero_columnas, int numero_filas);
void saveAnalysisToTxt(string **matriz, int numero_columnas, int numero_filas);


//Funciones Conversion Module
struct Student {
    int SerialNo;
    int greScore;
    int toeflScore;
    int universityRating;
    float sop;
    float lor;
    float cgpa;
    int research;
    float ChanceofAdmit;
};

void convertTableToStudents(string **matriz, int numero_columnas, int numero_filas, Student estudiantes[]);

void writeStudentsBinary(Student lista[], size_t tamaño_arreglo);




#endif