#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

const int col_width = 15;  
const int col1_width = 5;  
const int col2_width = 25; 
const int col3_width = 17; 
const int col4_width = 10;
const int col5_width = 25;



const int filamatriz=100;
const int colmatriz=9;
double datosmatriz[filamatriz][colmatriz];
double matrizcorr[colmatriz][colmatriz];

void head(ifstream& inFile){
    
    string linea;

    cout<<endl;


    for(int i=0; i<5;i++){

        getline(inFile, linea);


        string particion;

        stringstream linea_partida(linea);

        int x=0;
    
        while(getline(linea_partida,particion,',')){

            if(x==0){

                cout<<left<<setw(20)<<particion;

            }else{

                cout<<right<<setw(20)<<particion;

            }
            x++;
        }
        x=0;
        cout<<"\n";
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

double calcmedia(double matriz[100][9], int n,int filamatriz){
    double acumulador=0;
    for(int j=0;j<filamatriz;j++){
        acumulador+=matriz[j][n];
    }
    acumulador/=filamatriz;

    return acumulador;
}



//variables para lo de la matriz


const int colserial=0;
double calcserial=calcmedia(datosmatriz,colserial,filamatriz);//media de la variable

const int colgre=1;
double calcgre=calcmedia(datosmatriz,colgre,filamatriz);

const int coltoefl=2;
double calctoefl=calcmedia(datosmatriz,coltoefl,filamatriz);

const int colrating=3;
double calcrating=calcmedia(datosmatriz,colrating,filamatriz);

const int colSOP=4;
double calcSOP=calcmedia(datosmatriz,colSOP,filamatriz);

const int colLOR=5;
double calcLOR=calcmedia(datosmatriz,colLOR,filamatriz);

const int colCGPA=6;
double calcCGPA=calcmedia(datosmatriz,colCGPA,filamatriz);

const int colResearch=7;
double calcResearch=calcmedia(datosmatriz,colResearch,filamatriz);

const int colchance=8;
double calcchance=calcmedia(datosmatriz,colchance,filamatriz);



void correlationmatrix(ifstream &file,double matrix[100][9],double matrizcorr[9][9]){
    int fila=0;
    string linea;

    if(getline(file,linea)){

    };

        cout <<left<<setw(col5_width) <<" "<<setw(col_width)<< "Serial"<< setw(col_width) << "GRE_SCORE"<< setw(col_width) << "TOEFL"<< setw(col_width) << "Rating"<< setw(col_width) << "SOP"<< setw(col_width) << "LOR"<< setw(col_width) << "CGPA"<< setw(col_width) << "Research"<< setw(col_width) << "Chance"<< endl;


    while(getline(file, linea)){
            if(linea.empty()){
                continue;
            }
            stringstream ss(linea);
            string serial, grescore, toefl, rating, sop, lor, cgpa, research, chance;
            if(getline(ss, serial, ',') && getline(ss, grescore, ',') && getline(ss, toefl, ',') && getline(ss, rating, ',') && getline(ss, sop, ',') && getline(ss, lor, ',')&&getline(ss, cgpa, ',')&&getline(ss, research, ',')&&getline(ss, chance)){
                if(fila>=100){break;}
                matrix[fila][0]=stoi(serial);
                matrix[fila][1]=stoi(grescore);
                matrix[fila][2]=stoi(toefl);
                matrix[fila][3]=stoi(rating);
                matrix[fila][4]=stof(sop);
                matrix[fila][5]=stof(lor);
                matrix[fila][6]=stof(cgpa);
                matrix[fila][7]=stoi(research);
                matrix[fila][8]=stof(chance);
                fila++;

            }
        }
    //Calculo de la matriz de correlacion, lo de arriba fue apenas guardarlos en otra matriz para hacer la formula esa.


    for(int i=0;i<colmatriz;i++){

        double sumserial=0; //numerador
        double totalserial=0; //denominador
        double sumSOP=0;
        double totalSOP=0;
        double sumLOR=0;
        double totalLOR=0;
        double sumCGPA=0;
        double totalCGPA=0;
        double sumResearch=0;
        double totalResearch=0;
        double sumchance=0;
        double totalchance=0;
        double sumrating=0;
        double totalrating=0;
        double sumtoefl=0;
        double totaltoefl=0;
        double sumgre=0;
        double totalgre=0;
        double calcx=calcmedia(datosmatriz,i,filamatriz);
        double totalx=0;
        double sumax=0;

        for (int j=0;j<filamatriz;j++) {
            double diffX=datosmatriz[j][i]-calcx;
            sumax+=diffX;
            totalx+=pow(diffX,2);
            
            sumserial+=(datosmatriz[j][colserial]-calcserial)*diffX;
            totalserial+=pow(datosmatriz[j][colserial]-calcserial,2);
            
            sumgre+=(datosmatriz[j][colgre]-calcgre)*diffX;
            totalgre+=pow(datosmatriz[j][colgre]-calcgre,2);
            
            sumtoefl+=(datosmatriz[j][coltoefl]-calctoefl)*diffX;
            totaltoefl+=pow(datosmatriz[j][coltoefl]-calctoefl,2);
            
            sumrating+=(datosmatriz[j][colrating]-calcrating)*diffX;
            totalrating+=pow(datosmatriz[j][colrating]-calcrating,2);
            
            sumSOP+=(datosmatriz[j][colSOP]-calcSOP)*diffX;
            totalSOP+=pow(datosmatriz[j][colSOP]-calcSOP,2);
            
            sumLOR+=(datosmatriz[j][colLOR]-calcLOR)*diffX;
            totalLOR+=pow(datosmatriz[j][colLOR]-calcLOR,2);
            
            sumCGPA+=(datosmatriz[j][colCGPA]-calcCGPA)*diffX;
            totalCGPA+=pow(datosmatriz[j][colCGPA]-calcCGPA,2);
            
            sumResearch+=(datosmatriz[j][colResearch]-calcResearch)*diffX;
            totalResearch+=pow(datosmatriz[j][colResearch] - calcResearch,2);
        
            sumchance+= (datosmatriz[j][colchance] - calcchance) * diffX;
            totalchance+=pow(datosmatriz[j][colchance] - calcchance,2);
        }
        
            
        
    //aqui queda la sumatoria de x del primer ciclo j entonces la usamos para calcular el primer coeficiente de pearson (Valor de la correlacion)
    totalserial=sumserial/sqrt(totalserial*totalx);
    totalgre=sumgre/sqrt(totalgre*totalx);
    totaltoefl=sumtoefl/sqrt(totaltoefl*totalx);
    totalrating=sumrating/sqrt(totalrating*totalx);
    totalSOP=sumSOP/sqrt(totalSOP*totalx);
    totalLOR=sumLOR/sqrt(totalLOR*totalx);
    totalCGPA=sumCGPA/sqrt(totalCGPA*totalx);
    totalResearch=sumResearch/sqrt(totalResearch*totalx);
    totalchance=sumchance/sqrt(totalchance*totalx);

    switch (i){
        case 0:
        matrizcorr[colserial][colserial]=totalserial;
        matrizcorr[colserial][colgre]=totalgre;
        matrizcorr[colserial][coltoefl]=totaltoefl;
        matrizcorr[colserial][colrating]=totalrating;
        matrizcorr[colserial][colSOP]=totalSOP;
        matrizcorr[colserial][colLOR]=totalLOR;
        matrizcorr[colserial][colCGPA]=totalCGPA;
        matrizcorr[colserial][colResearch]=totalResearch;
        matrizcorr[colserial][colchance]=totalchance;
        break;
        case 1:
        matrizcorr[colgre][colserial]=totalserial;
        matrizcorr[colgre][colgre]=totalgre;
        matrizcorr[colgre][coltoefl]=totaltoefl;
        matrizcorr[colgre][colrating]=totalrating;
        matrizcorr[colgre][colSOP]=totalSOP;
        matrizcorr[colgre][colLOR]=totalLOR;
        matrizcorr[colgre][colCGPA]=totalCGPA;
        matrizcorr[colgre][colResearch]=totalResearch;
        matrizcorr[colgre][colchance]=totalchance;
        break;
        case 2:
        matrizcorr[coltoefl][colserial]=totalserial;
        matrizcorr[coltoefl][colgre]=totalgre;
        matrizcorr[coltoefl][coltoefl]=totaltoefl;
        matrizcorr[coltoefl][colrating]=totalrating;
        matrizcorr[coltoefl][colSOP]=totalSOP;
        matrizcorr[coltoefl][colLOR]=totalLOR;
        matrizcorr[coltoefl][colCGPA]=totalCGPA;
        matrizcorr[coltoefl][colResearch]=totalResearch;
        matrizcorr[coltoefl][colchance]=totalchance;
        break;
        case 3:
        matrizcorr[colrating][colserial]=totalserial;
        matrizcorr[colrating][colgre]=totalgre;
        matrizcorr[colrating][coltoefl]=totaltoefl;
        matrizcorr[colrating][colrating]=totalrating;
        matrizcorr[colrating][colSOP]=totalSOP;
        matrizcorr[colrating][colLOR]=totalLOR;
        matrizcorr[colrating][colCGPA]=totalCGPA;
        matrizcorr[colrating][colResearch]=totalResearch;
        matrizcorr[colrating][colchance]=totalchance;
        break;
        case 4:
        matrizcorr[colSOP][colserial]=totalserial;
        matrizcorr[colSOP][colgre]=totalgre;
        matrizcorr[colSOP][coltoefl]=totaltoefl;
        matrizcorr[colSOP][colrating]=totalrating;
        matrizcorr[colSOP][colSOP]=totalSOP;
        matrizcorr[colSOP][colLOR]=totalLOR;
        matrizcorr[colSOP][colCGPA]=totalCGPA;
        matrizcorr[colSOP][colResearch]=totalResearch;
        matrizcorr[colSOP][colchance]=totalchance;
        break;
        case 5:
        matrizcorr[colLOR][colserial]=totalserial;
        matrizcorr[colLOR][colgre]=totalgre;
        matrizcorr[colLOR][coltoefl]=totaltoefl;
        matrizcorr[colLOR][colrating]=totalrating;
        matrizcorr[colLOR][colSOP]=totalSOP;
        matrizcorr[colLOR][colLOR]=totalLOR;
        matrizcorr[colLOR][colCGPA]=totalCGPA;
        matrizcorr[colLOR][colResearch]=totalResearch;
        matrizcorr[colLOR][colchance]=totalchance;
        break;
        case 6:
        matrizcorr[colCGPA][colserial]=totalserial;
        matrizcorr[colCGPA][colgre]=totalgre;
        matrizcorr[colCGPA][coltoefl]=totaltoefl;
        matrizcorr[colCGPA][colrating]=totalrating;
        matrizcorr[colCGPA][colSOP]=totalSOP;
        matrizcorr[colCGPA][colLOR]=totalLOR;
        matrizcorr[colCGPA][colCGPA]=totalCGPA;
        matrizcorr[colCGPA][colResearch]=totalResearch;
        matrizcorr[colCGPA][colchance]=totalchance;
        break;
        case 7:
        matrizcorr[colResearch][colserial]=totalserial;
        matrizcorr[colResearch][colgre]=totalgre;
        matrizcorr[colResearch][coltoefl]=totaltoefl;
        matrizcorr[colResearch][colrating]=totalrating;
        matrizcorr[colResearch][colSOP]=totalSOP;
        matrizcorr[colResearch][colLOR]=totalLOR;
        matrizcorr[colResearch][colCGPA]=totalCGPA;
        matrizcorr[colResearch][colResearch]=totalResearch;
        matrizcorr[colResearch][colchance]=totalchance;
        break;
        case 8:
        matrizcorr[colchance][colserial]=totalserial;
        matrizcorr[colchance][colgre]=totalgre;
        matrizcorr[colchance][coltoefl]=totaltoefl;
        matrizcorr[colchance][colrating]=totalrating;
        matrizcorr[colchance][colSOP]=totalSOP;
        matrizcorr[colchance][colLOR]=totalLOR;
        matrizcorr[colchance][colCGPA]=totalCGPA;
        matrizcorr[colchance][colResearch]=totalResearch;
        matrizcorr[colchance][colchance]=totalchance;
        break;

    }

    }
    //mostrar matriz

    cout<<endl;


    for(int i=0;i<9;i++){
        
        switch (i){
            case 0:
            cout<<left<<setw(col5_width)<<"Serial No.";
            break;
            case 1:
            cout<<left<<setw(col5_width)<<"GRE Score";
            break;
            case 2:
            cout<<left<<setw(col5_width)<<"TOEFL Score";
            break;
            case 3:
            cout<<left<<setw(col5_width)<<"University Rating";
            break;
            case 4:
            cout<<left<<setw(col5_width)<<"SOP";
            break;
            case 5:
            cout<<left<<setw(col5_width)<<"LOR";
            break;
            case 6:
            cout<<left<<setw(col5_width)<<"CGPA";
            break;
            case 7:
            cout<<left<<setw(col5_width)<<"Research";
            break;
            case 8:
            cout<<left<<setw(col5_width)<<"Chance of admit";
            break;
        }

        for(int j=0;j<9;j++){ 
            cout<<left<<fixed<<setprecision(6)<<setw(col_width)<<matrizcorr[i][j];
        }
        cout<<endl<<endl;
    }

    //RESETEAMOS LA UBICACION DEL ARCHIVO QUE LEIMOS PORQUE SINO TIRA UNOS DATOS RAROS QUE NO ENTRAN EN EL INTERVALO [-1,1]

    file.seekg(0); // Volver al principio del archivo
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

    cout<<endl<<"Primeras 5 filas";
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
            correlationmatrix(archivo,datosmatriz,matrizcorr);

            archivo.clear();
            archivo.seekg(0);


            cout<<endl<<endl;


            
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