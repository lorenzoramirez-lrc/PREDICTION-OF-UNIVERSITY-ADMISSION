#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "pipeline.h"

using namespace std;

void menu();


int main(){

    CSV csv;
    ifstream archivo("Admissions.csv");
    string enter;

    cout<<endl<<endl;
    cout << "=======================================================\n";
    cout << "\e[1m          PREDICCIÓN DE ADMISIÓN UNIVERSITARIA         \e[0m\n";
    cout << "=======================================================\n";

    cout<<"Ingrese cualquier tecla para iniciar la lectura de la base de datos: ";
    cin>>enter;
    
    if (!archivo.is_open()){
        cerr << "Error: No se pudo abrir el archivo" << endl;
        return 1;
    }else{
        cout<<"\e[1mBase de datos leida exitosamente\e[0m"<<endl;
    }

    csv= readCSV(archivo);

    archivo.close();

    int numero_filas=csv.numero_filas;
    int numero_columnas=csv.numero_columnas;
    string **matriz=csv.matriz;

    int opcion=-1;

    do{

        menu();
        cin>>opcion;
        cout<<endl<<endl;

        switch(opcion){

            case 1:
                cout<<"\e[1m====HEAD====\e[0m"<<endl;
                printHead(matriz, numero_columnas);
                cout<<endl<<endl;
                break;
            case 2:
                cout<<"\e[1m====INFO====\e[0m"<<endl;
                printInfo(matriz, numero_columnas, numero_filas);
                cout<<endl<<endl;
                break;
            case 3:
                cout<<"\e[1m====DESCRIBE====\e[0m"<<endl;

                cout<<endl<<endl;
                break;
            case 4:
                cout<<"\e[1m====CORRELATION MATRIX====\e[0m"<<endl;

                cout<<endl<<endl;
                break;
            case 5:


                cout<<endl<<endl;
                break;
            default: 
                cout<<"Opcion no valida intente nuevamente"<<endl;
        }

    }while(opcion!=5);

    cout<<"Proceso terminado exitosamente"<<endl;

    return 0;
}


void menu(){

    cout << "-------------------------------------\n";
    cout << "  [1] Head\n";
    cout << "  [2] Info\n";
    cout << "  [3] Describe\n";
    cout << "  [4] Correlation Matrix\n";
    cout << "  [5] Guardar resultados del analisis, cargar la base de datos a archivo binario y salir\n";
    cout << "-------------------------------------\n";
    cout << "Ingrese el número de la opción deseada: ";

}


