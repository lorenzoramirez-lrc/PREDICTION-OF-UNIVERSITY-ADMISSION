#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "pipeline.h"

using namespace std;



int main(){
    //Se crea csv
    CSV csv;
    ifstream archivo("cpp/Admissions.csv");  //Se abre el archivo
    string enter;

    cout<<endl<<endl;
    cout << "=======================================================\n";
    cout << "\e[1m          PREDICCIÓN DE ADMISIÓN UNIVERSITARIA         \e[0m\n";
    cout << "=======================================================\n";

    cout<<"Ingrese cualquier tecla para iniciar la lectura de la base de datos: ";
    cin>>enter;
    
    //Revision de que se haya abierto correctamente
    if (!archivo.is_open()){
        cerr << "Error: No se pudo abrir el archivo" << endl;
        return 1;
    }else{
        cout<<"\e[1mBase de datos leida exitosamente\e[0m"<<endl;
    }

    //Se lee csv
    csv= readCSV(archivo);

    archivo.close();
    
    //Se asigna numero de filas columnas y matrizx
    int numero_filas=csv.numero_filas;
    int numero_columnas=csv.numero_columnas;
    string **matriz=csv.matriz;
    Student lista[numero_filas-1];
    size_t tamaño_arreglo_bits;

    int opcion=-1;

    do{
        //Menu
        cout << "-------------------------------------\n";
        cout << "  [1] Head\n";
        cout << "  [2] Info\n";
        cout << "  [3] Describe\n";
        cout << "  [4] Correlation Matrix\n";
        cout << "  [5] Guardar resultados del analisis, cargar la base de datos a archivo binario y salir\n";
        cout << "-------------------------------------\n";
        cout << "Ingrese el número de la opción deseada: ";
        cin>>opcion;
        cout<<endl<<endl;

        switch(opcion){

            //Head con su respectiva funcion
            case 1:
                cout<<"\e[1m====HEAD====\e[0m"<<endl;
                printHead(matriz, numero_columnas,numero_filas);
                cout<<endl<<endl;
                break;
            case 2:  //Info con su respectiva funcion
                cout<<"\e[1m====INFO====\e[0m"<<endl;
                printInfo(matriz, numero_columnas, numero_filas);
                cout<<endl<<endl;
                break;
            case 3: //Describe con su respectiva funcion
                cout<<"\e[1m====DESCRIBE====\e[0m"<<endl;
                printDescribe(matriz, numero_columnas, numero_filas);
                cout<<endl<<endl;
                break;
            case 4:  //Correlation matrix con su respectiva funcion
                cout<<"\e[1m====CORRELATION MATRIX====\e[0m"<<endl;
                printCorrelation(matriz, numero_columnas, numero_filas);
                cout<<endl<<endl;
                break;
            case 5:  //Archivo txt y binario


                saveAnalysisToTxt(matriz,numero_columnas,numero_filas);
                convertTableToStudents(matriz, numero_columnas, numero_filas, lista);
                tamaño_arreglo_bits= sizeof(lista);
                writeStudentsBinary(lista, tamaño_arreglo_bits);


                cout<<endl<<endl;
                break;
            default: 
                cout<<"Opcion no valida intente nuevamente"<<endl;
        }

    }while(opcion!=5);

    //Se libera memoria dinamica de la matriz
    for(int i=0; i<numero_filas;i++){

        delete[] *(matriz+i);
    }
    delete[] matriz;
    cout<<"Proceso terminado exitosamente"<<endl;

    return 0;
}




