#include <iostream>
#include <fstream>
#include <sstream>    //Quitar esto despues de hacer la transformacion
#include <iomanip>
#include <cmath>


using namespace std;

void printHead(string **matriz, int numero_columnas, int numero_filas){

    int opcion;
    cout<<"Ingrese el numero de filas que quiere visualizar (maximo "<<numero_filas<<"): ";
    cin>>opcion;
    /*
    Se imprimen las 5 filas de la matriz utilizando un ciclo anidado y 
    la libreria iosmanip para tener un output de la matriz mas organizado,
    al asignarle un espacio determinado a cada columna haciendo que no dependa de la longitud del string.
    */
    for(int i=0; i<opcion; i++){
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

        for(int j=0; j<(*(*(matriz+1)+(i-1))).size(); j++ ){

            if((((*(*(matriz+1)+(i-1)))[j]>57)||((*(*(matriz+1)+(i-1)))[j]<48))&&((*(*(matriz+1)+(i-1)))[j]!=46)){

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



void printCorrelation(string **matriz, int numero_columnas, int numero_filas){

    //Se crea matriz para almacenar resultados de correlacion
    string matriz_correlacion[numero_columnas+1][numero_columnas+1];


    //Llena los Encabezados de cada dato en filas y columnas
    for(int j=0;j<numero_columnas ;j++){

        matriz_correlacion[0][j+1]=(*(*(matriz+0)+j));
        matriz_correlacion[j+1][0]=(*(*(matriz+0)+j));

    }

    //Variables para el calculo de correlacion
    float n= numero_filas-1;
    float suma_x= 0;
    float suma_y= 0;
    float suma_xy=0;
    float suma_x2=0;
    float suma_y2=0;
    float corr;

    //Recorre todos los posibles pares de columnas
    for(int i=0; i<numero_columnas; i++){
        for(int j=0; j<numero_columnas; j++){
            //De ese par de columnas reccorre todas sus filas
            for(int k=1;k<numero_filas ;k++){
                   //Calcula las sumas necesarias
                suma_x += stof(*(*(matriz+k)+i));
                suma_y += stof(*(*(matriz+k)+j));
                suma_xy += stof(*(*(matriz+k)+i))*stof(*(*(matriz+k)+j));
                suma_x2 += stof(*(*(matriz+k)+i))*stof(*(*(matriz+k)+i));
                suma_y2 += stof(*(*(matriz+k)+j))*stof(*(*(matriz+k)+j));

            }
            //Obtiene el valor de correlacion
            corr= (n*suma_xy-suma_x*suma_y)/sqrt((n*suma_x2-(suma_x*suma_x))*(n*suma_y2-(suma_y*suma_y)));
            matriz_correlacion[i+1][j+1]= to_string(corr); //Almacena en matriz
            //Reinicia Valores
            suma_x= 0;
            suma_y= 0;
            suma_xy=0;
            suma_x2=0;
            suma_y2=0;

        }
    }

    //Imprime la matriz
    for(int i=0; i<numero_columnas+1; i++){
        for(int j=0; j<numero_columnas+1; j++){

            cout<<left<<setw(17)<<matriz_correlacion[i][j];


        
        }
        cout<<endl;
    }
}


void saveAnalysisToTxt(string **matriz, int numero_columnas, int numero_filas){

    /*Se usa Freopen para crear el archivo, el beneficio de este es que se puede utilizar cout para escribir en el
    permitiendo escribir en el archivo utilizando las mismas funciones.*/
    freopen("data/transformacion_resultados.txt","w",stdout);

    cout<<"====INFO===="<<endl;
    printInfo(matriz, numero_columnas, numero_filas);
    cout<<endl<<endl;

    cout<<"====DESCRIBE===="<<endl;
    printDescribe(matriz, numero_columnas, numero_filas);
    cout<<endl<<endl;

    cout<<"====CORRELATION MATRIX===="<<endl;
    printCorrelation(matriz, numero_columnas, numero_filas);
    cout<<endl<<endl;

    //Se utiliza para despues de utilizar la funcion se vuelva a imprimir desde consola y no al archivo
    //Para windows esta linea deberia cambiarse a freopen("CON", "w", stdout);
    freopen("/dev/tty", "w", stdout);


}