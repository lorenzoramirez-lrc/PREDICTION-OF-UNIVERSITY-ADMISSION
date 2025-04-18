#include <iostream>
#include <fstream>
#include <sstream>    //Quitar esto despues de hacer la transformacion
#include <iomanip>
#include <cmath>


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

void printHead(string **matriz, int numero_columnas){

    /*
    Se imprimen las 5 filas de la matriz utilizando un ciclo anidado y 
    la libreria iosmanip para tener un output de la matriz mas organizado,
    al asignarle un espacio determinado a cada columna haciendo que no dependa de la longitud del string.
    */
    for(int i=0; i<5; i++){
        int x=0;
        for(int j=0; j<numero_columnas; j++){


            if(x==0){

                cout<<left<<setw(18)<<*(*(matriz+i)+j);

            }else{

                cout<<left<<setw(18)<<*(*(matriz+i)+j);

            }
            x++;
            
        }
        x=0;
        cout<<endl;
    }
}

void printInfo(string **matriz, int numero_columnas, int numero_filas){
    
    //Se imprime numero de filas y columnas obtenido anteriormente en readCSV
    cout<<"Numero de filas (incluyendo header): "<<numero_filas<<endl;
    cout<<"Numero de columnas: "<<numero_columnas<<endl;

    
    //Se crea matriz info
    string info[numero_filas+1][4];

    //Nombres de cadas columna
    info[0][0]="#";
    info[0][1]="Column";
    info[0][2]="Non-Null Count";;
    info[0][3]="Dtype";

    //Numero de cada fila
    for(int i=0;i<numero_columnas;i++){
        info[i+1][0]=to_string(i);

    }


    /*
    Se imprimen los nombres de la fila 1 siendo estos los nombres de cada columna 
    a su vez se guardan en la matriz info
    */
    cout<<"Nombres de columnas: "<<endl;
    for(int i=0; i<numero_columnas; i++){  
            info[i+1][1]= *(*(matriz+0)+i);
            cout<<*(*(matriz+0)+i)<<endl;
    }
    

    
    
    /*
    Se revisan todos los elementos de cada columna usando un ciclo anidado,
    si este no es nulo se increenta el numero de valores no nulos que luego son guardados en info.
    */
    int contador_nonnull=0;
    for (int i = 1; i < numero_columnas+1; i++) {
        contador_nonnull = 0;
        
        for(int j=1;j<numero_filas; j++){

            if(*(*(matriz+j)+(i-1))!="\0"){
                contador_nonnull++;
            }
        }
        info[i][2] = to_string(contador_nonnull);
    }
    

   
    //Se recorren los valores de cada columna para revisar si estos son string float o int
    for (int i = 1; i < numero_columnas+1; i++) {

        bool is_string= false;

        for(int j=0; j<size(*(*(matriz+1)+(i-1))); j++ ){

            if(((*(*(matriz+1)+(i-1)))[j]>57)||((*(*(matriz+1)+(i-1)))[j]<48)){

                is_string=true;  //Se revisa cada caracter de esa celda si alguno no es un numero es un string
            }

        }

        
        if(is_string){   
            info[i][3]="String";  
        }else{
            float particion_flotante=stof((*(*(matriz+1)+(i-1))));
            if((particion_flotante-(int)particion_flotante)==0){  //Sehace verificacion si es float o entero
                info[i][3]="Integer";
            }else{
                info[i][3]="Float";
            }
            
        }
        //Los resultados se guardan en la matriz info
    }
    


    
    //Se imprime la matriz info
    cout<<endl<<"Resumen por columnas: "<<endl;
    cout<<left;
    for(int i=0;i<=numero_columnas;i++){
        for(int j=0;j<4;j++){

            if(j==0){

                cout<<setw(5)<<info[i][j];

            }else if(j==1){

                cout<<setw(25)<<info[i][j];

            }else if(j==2){

                cout<<setw(17)<<info[i][j];


            }else if(j==3){

                cout<<setw(10)<<info[i][j];



            }
            
        }
        cout<<endl;
    }
    
}

void printDescribe(string **matriz, int numero_columnas, int numero_filas){

    int poblacion=numero_filas-1;  //Poblacion de cada columna que es igual al nuemero de filas

    string nombre_columna;
    float std=0;
    float mean=0;
    float max=-1;
    float min=1000;

    //Ciclo que recorre cada columna obteniendo sus estadisticas
    for(int i=0;i<numero_columnas;i++){

        
        nombre_columna=(*(*(matriz+0)+i)); //Se encuentra el nombre de cada columna


        for(int j=1; j<numero_filas; j++){  //Se suman los valores de cada fila

            mean +=stof(*(*(matriz+j)+i));

            if(stof(*(*(matriz+j)+i))>max){
                max=stof(*(*(matriz+j)+i)); 
            }                              
            /*
            Se compara cada celda de la columna con el maximo y el minimo si este es mayor 
            o menos se asigna su valor como nuevo maximo o minimo
            */
            if(stof(*(*(matriz+j)+i))<min){
                min=stof(*(*(matriz+j)+i));
            }
        }

        mean= mean/poblacion; //Se obtiene promedio


        //Se le resta a cada valor el promedio y este se multiplica al cuadrado
        for(int j=1; j<numero_filas; j++){

            std+=(stof(*(*(matriz+j)+i))-mean)*(stof(*(*(matriz+j)+i))-mean);  
            
        }
        //Se obtiene la desviacion estandar
        std= sqrt(std/poblacion);


        //Se imprimen los valores
        cout<<nombre_columna<<": "<<fixed<<setprecision(4)<<"Mean="<<mean<<", "<<"Std="<<std<<", "<<"Min="<<min<<", "<<"Max="<<max<<endl;

        
        //Se reinician valores
        std=0;
        mean=0;
        max=-1;
        min=1000;
    }
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

