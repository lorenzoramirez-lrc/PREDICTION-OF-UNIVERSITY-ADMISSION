#include <iostream>
#include <fstream>


using namespace std;

//Definicion de la estructura que representa al estudiante junto a sus datos
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

void convertTableToStudents(string **matriz, int numero_columnas, int numero_filas, Student estudiantes[]){




    //Se recorre filas y columnas de la matriz
    for(int i=1; i<numero_filas  ;i++){

        for(int j=0; j<numero_columnas; j++){

            //Segun el numero de columna se asigna al valor correspondiente haciendo la conversion necesaria
            if(j==0){

                estudiantes[i-1].SerialNo=  stoi((*(*(matriz+i)+j)));

            }else if(j==1){

                estudiantes[i-1].greScore= stoi((*(*(matriz+i)+j)));

            }else if(j==2){

                estudiantes[i-1].toeflScore= stoi((*(*(matriz+i)+j)));


            }else if(j==3){

                estudiantes[i-1].universityRating= stoi((*(*(matriz+i)+j)));

            }else if(j==4){

                estudiantes[i-1].sop= stof((*(*(matriz+i)+j)));


            }else if(j==5){

                estudiantes[i-1].lor= stof((*(*(matriz+i)+j)));


            }else if(j==6){

                estudiantes[i-1].cgpa= stof((*(*(matriz+i)+j)));


            }else if(j==7){

                estudiantes[i-1].research= stoi((*(*(matriz+i)+j)));


            }else if(j==8){

                estudiantes[i-1].ChanceofAdmit= stof((*(*(matriz+i)+j)));


            }
            
        }
    }

}

void writeStudentsBinary(Student lista[], size_t tamaño_arreglo_bits){

    //Calcula numero de registros en el arreglo
    size_t numero_de_registros= tamaño_arreglo_bits/sizeof(Student);

    //Crea archivo binario
    ofstream archivo("data/Admission_Predict_new.bin", ios::binary);

    //Verificacion que este abierto
    if(archivo.is_open()){

        //Escribe el numero de registros al principio del archivo
        archivo.write(reinterpret_cast<char*>(&numero_de_registros), sizeof(numero_de_registros));
        archivo.write(reinterpret_cast<char*>(lista), numero_de_registros*sizeof(Student));
        //Escribe el contenido del arreglo de estructuras (Estudiantes)

        cout<<"Archivo Binario guardado exitosamente en Admission_Predict_new.bin"<<endl;
    }else{
        
        cout<<"Archivo  binario no se pudo abrir correctamente"<<endl;
    }

    archivo.close();


    //Se abre archivo en modo lectura
    ifstream archivo_lectura("data/Admission_Predict_new.bin", ios::binary); 

    //Guardar datos leidos
    Student lectura_estudiantes[numero_de_registros];


    if(archivo_lectura.is_open()){

        size_t num;

        //Lee numero de registros
        archivo_lectura.read(reinterpret_cast<char*>(&num), sizeof(size_t));

        cout<<"Numero de registros leido: "<< num<<endl;

        //Lee los datos del binario y los almacena en el arreglo de estructura
        archivo_lectura.read(reinterpret_cast<char*>(lectura_estudiantes), num*sizeof(Student));

        //Se imprimen primer y ultimo registro leido para verificacion
        cout<<"Primer y ultimos registros leidos del archivo binario"<<endl;

        cout<<lectura_estudiantes[0].SerialNo<<";"<<lectura_estudiantes[0].greScore<<";"<<lectura_estudiantes[0].toeflScore<<";"<<lectura_estudiantes[0].universityRating<<";"<<lectura_estudiantes[0].sop<<";"<<lectura_estudiantes[0].lor<<";"<<lectura_estudiantes[0].cgpa<<";"<<lectura_estudiantes[0].research<<";"<<lectura_estudiantes[0].ChanceofAdmit<<endl;

        cout<<lectura_estudiantes[num-1].SerialNo<<";"<<lectura_estudiantes[num-1].greScore<<";"<<lectura_estudiantes[num-1].toeflScore<<";"<<lectura_estudiantes[num-1].universityRating<<";"<<lectura_estudiantes[num-1].sop<<";"<<lectura_estudiantes[num-1].lor<<";"<<lectura_estudiantes[num-1].cgpa<<";"<<lectura_estudiantes[num-1].research<<";"<<lectura_estudiantes[num-1].ChanceofAdmit<<endl;

    }else{

        cout<<"Archivo  binario no se pudo abrir correctamente"<<endl;
    }



}


