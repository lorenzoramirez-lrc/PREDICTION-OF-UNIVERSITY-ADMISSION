#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

const int col_width = 15;  
const int col1_width = 5;  
const int col2_width = 25; 
const int col3_width = 20; 
const int col4_width = 10;

void head(ifstream& inFile){

    cout << left;
    cout <<setw(col_width) << "Serial"<< setw(col_width) << "GRE_SCORE"<< setw(col_width) << "TOEFL"<< setw(col_width) << "Rating"<< setw(col_width) << "SOP"<< setw(col_width) << "LOR"<< setw(col_width) << "CGPA"<< setw(col_width) << "Research"<< setw(col_width) << "Chance"<< endl;
    
    string linea;

    getline(inFile, linea);
    for(int i=0; i<4;i++){

        getline(inFile, linea);


        string particion;

        stringstream linea_estudiante(linea);
        
            
        getline(linea_estudiante,particion,',');
        int serial=stoi(particion);
        getline(linea_estudiante,particion,',');
        int gre=stoi(particion);
        getline(linea_estudiante,particion,',');
        int toefl=stoi(particion);
        getline(linea_estudiante,particion,',');
        int university_rating=stoi(particion);
        getline(linea_estudiante,particion,',');
        float sop=stof(particion);
        getline(linea_estudiante,particion,',');
        float lor=stof(particion);
        getline(linea_estudiante,particion,',');
        float cgpa=stof(particion);
        getline(linea_estudiante,particion,',');
        int research=stoi(particion);
        getline(linea_estudiante,particion,',');
        float chance_of_admit=stof(particion);

        cout<<left;
        cout<<setw(col_width)<<serial<<setw(col_width)<<gre<<setw(col_width)<<toefl<<setw(col_width)<<university_rating<<setw(col_width)<<sop<<setw(col_width)<<lor<<setw(col_width)<<cgpa<<setw(col_width)<<research<<setw(col_width)<<chance_of_admit<<endl;

    }



}

void info(ifstream& inFile){
    string linea;

    int contador_filas=0;

    while(getline(inFile,linea)){
        contador_filas+=1;
    }

    inFile.clear();
    inFile.seekg(0);

    string particion;
    getline(inFile, linea);

    stringstream numero(linea);
    int contador_columnas=0;       
    while(getline(numero,particion,',')){
        contador_columnas++;
    };

    cout<<"Numero de filas (incluyendo header): "<<contador_filas<<endl;
    cout<<"Numero de columnas: "<<contador_columnas<<endl;

    

    string info[contador_columnas+1][4];


    info[0][0]="#";
    info[0][1]="Column";
    info[0][2]="Non-Null Count";;
    info[0][3]="Dtype";
    for(int i=0;i<contador_columnas;i++){
        info[i+1][0]=to_string(i);

    }

    
    inFile.seekg(0);
    cout<<"Nombres de columnas: "<<endl;
    getline(inFile,linea);
    stringstream columna(linea); 
    for(int i=0; i<contador_columnas; i++){  
        if (getline(columna, particion, ',')) {
            info[i+1][1] = particion;
            cout<<particion<<endl;
            
        }
    }

    getline(stringstream (particion), particion, '\r');
    info[contador_columnas][1] = particion;
    
    inFile.clear();
    inFile.seekg(0);

    int contador_nonnull=0;
    for (int i = 1; i < contador_columnas+1; i++) {
        contador_nonnull = 0;
        inFile.clear();
        inFile.seekg(0); 
        getline(inFile, linea);  
        while (getline(inFile, linea)) {
            stringstream filas_null(linea);
            for(int j=0;j<i;j++){
                getline(filas_null,particion,',');
            }
            if(particion!="\0"){
                contador_nonnull++;
            }
            
        }

        info[i][2] = to_string(contador_nonnull);
    }

    inFile.clear();
    inFile.seekg(0);

    for (int i = 1; i < contador_columnas+1; i++) {
        inFile.clear();
        inFile.seekg(0); 
        getline(inFile, linea);  
        getline(inFile, linea);  
        stringstream filas_null(linea);
        for(int j=0;j<i;j++){
            getline(filas_null,particion,',');
        }
        
        
        if(!stof(particion)){
            info[i][3]="String";
        }else{
            float particion_flotante=stof(particion);
            if((particion_flotante-(int)particion_flotante)==0){
                info[i][3]="Integer";
            }else{
            info[i][3]="Float";
            }
        }

    }

    cout<<endl<<"Resumen por columnas: "<<endl;
    cout<<left;
    for(int i=0;i<=contador_columnas;i++){
        for(int j=0;j<4;j++){

            if(j==0){

                cout<<setw(col1_width)<<info[i][j];

            }else if(j==1){

                cout<<setw(col2_width)<<info[i][j];

            }else if(j==2){

                cout<<setw(col3_width)<<info[i][j];


            }else if(j==3){

                cout<<setw(col4_width)<<info[i][j];



            }
            
            


        }
        cout<<endl;
    }
}

void describe(ifstream &inFile){

    string linea;
    string particion;

    getline(inFile, linea);
    stringstream numero(linea);

    int contador_columnas=0;       
    while(getline(numero,particion,',')){
        contador_columnas++;
    };

    inFile.seekg(0);
    int poblacion=0;

    getline(inFile, linea);

    while(getline(inFile, linea)){
        poblacion++;
    };

    inFile.clear();
    inFile.seekg(0);

    string nombre_columna;
    float std=0;
    float mean=0;
    float max=-1;
    float min=1000;

    for(int i=0;i<contador_columnas;i++){

        getline(inFile, linea);

        stringstream columna(linea);

        for(int j=0;j<i+1;j++){

            getline(columna,particion,',');
            
        }


        getline(stringstream (particion), particion, '\r');


        nombre_columna=particion;

        while(getline(inFile, linea)){

            stringstream columna(linea);

            for(int j=0;j<i+1;j++){
                getline(columna,particion,',');
            }

            mean+=stof(particion);

            if(stof(particion)>max){
                max=stof(particion);
            }
            if(stof(particion)<min){
                min=stof(particion);
            }
        }

        mean= mean/poblacion;

        inFile.clear();
        inFile.seekg(0);

        getline(inFile, linea);
        while(getline(inFile, linea)){

            stringstream columna(linea);

            for(int j=0;j<i+1;j++){

                getline(columna,particion,',');
                
            }

            std+=(stof(particion)-mean)*(stof(particion)-mean);
        }

        std= sqrt(std/poblacion);

        cout<<nombre_columna<<": "<<fixed<<setprecision(4)<<"Mean="<<mean<<", "<<"Std="<<std<<", "<<"Min="<<min<<", "<<"Max="<<max<<endl;

        inFile.clear();
        inFile.seekg(0);

        std=0;
        mean=0;
        max=-1;
        min=1000;
    }
}

void menu(){

    cout << "-------------------------------------\n";
    cout << "  [1] Info\n";
    cout << "  [2] Describe\n";
    cout << "  [3] Correlation Matrix\n";
    cout << "  [4] Guardar archivo en binario\n";
    cout << "  [5] Guardar estadísticas y salir\n";
    cout << "-------------------------------------\n";
    cout << "Ingrese el número de la opción deseada: ";

}


int main(){

    string opcion1;

    cout<<endl<<endl;
    cout << "=======================================================\n";
    cout << "\e[1m          PREDICCIÓN DE ADMISIÓN UNIVERSITARIA         \e[0m\n";
    cout << "=======================================================\n";




    cout<<"Ingrese cualquier tecla para iniciar la lectura de la base de datos: ";
    cin>>opcion1;
    


    ifstream archivo("/Users/lorenzoramirez/Developer/Programacion Avanzada/C++/Proyecto/Admissions.csv");


    if (!archivo.is_open()){
        cerr << "Error: No se pudo abrir el archivo" << endl;
        return 1;
    }else{
        cout<<"\e[1mBase de datos leida exitosamente\e[0m"<<endl;
    }

    cout<<endl<<"Primeras 5 filas"<<endl;
    head(archivo);

    cout<<endl;

    archivo.clear();
    archivo.seekg(0);

    int opcion=-1;

    do{

        menu();
        cin>>opcion;
        cout<<endl<<endl;

        if(opcion==1){

            cout<<"\e[1m====INFO====\e[0m"<<endl;
            info(archivo);

            archivo.clear();
            archivo.seekg(0);


            cout<<endl<<endl;


        }else if(opcion==2){

            cout<<"\e[1m====DESCRIBE====\e[0m"<<endl;

            describe(archivo);


            archivo.clear();
            archivo.seekg(0);


            cout<<endl<<endl;



        }else if(opcion==3){

            cout<<"\e[1m====CORRELATION MATRIX====\e[0m"<<endl;


            
        }else if(opcion==4){


            
        }else if(opcion==5){

    
        }else{
            cout<<"Opcion no valida intente nuevamente"<<endl;
        }


    }while(opcion!=5);



    archivo.close();        


    cout<<"Proceso terminado exitosamente"<<endl;


    return 0;
}