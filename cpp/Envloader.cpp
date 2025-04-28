#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;



bool loadEnv(string ruta_archivo, unordered_map<string, string> &envCred){

    ifstream envFile(ruta_archivo);

    if(!envFile.is_open()){

        cerr<<"Error: No se pudo abrir el archivo"<<endl;
        return false;

    
    }

    string linea;

    while (getline(envFile, linea)) {
        if (linea.empty() || linea[0] == '#') {
            continue;
        }

        stringstream linea_actual(linea);
        string key;

        if (getline(linea_actual, key, '=')) {
            string value;
            if (getline(linea_actual, value)) {
                envCred[key] =value;
            }
        }
    }

    envFile.close();

    // Verificar que existan las claves necesarias
    if (envCred.find("SFTP_URL") == envCred.end() ||
        envCred.find("SFTP_USER") == envCred.end() ||
        envCred.find("SFTP_PASSWORD") == envCred.end()||
        envCred.find("SFTP_PORT") == envCred.end()) {
        cerr << "Error: Faltan una o más variables necesarias (SFTP_URL, SFTP_USER, SFTP_PASSWORD)." << endl;
        return false;
    }

    return true;
}