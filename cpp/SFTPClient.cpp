#include <curl/curl.h>
#include <fstream>
#include <iostream>

using namespace std;

// Función para escribir datos en un archivo local
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
    ofstream* out = static_cast<ofstream*>(stream);
    size_t written = size * nmemb;
    out->write(static_cast<char*>(ptr), written);
    return written;
}

bool downloadFileSFTP(const string& host, int port, const string& user, const string& password, const string& remote_path, const string& local_path) {
    CURL *curl;
    CURLcode res;
    ofstream file(local_path, ios::binary);

    if (!file.is_open()) {
        cerr << "Error abriendo archivo local para escribir" << endl;
        return false;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        string sftp_url = "sftp://" + host + ":" + to_string(port) + remote_path;

        // Establecer la URL, usuario y contraseña para la conexión SFTP
        curl_easy_setopt(curl, CURLOPT_URL, sftp_url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERPWD, (user + ":" + password).c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            curl_easy_cleanup(curl);
            file.close();
            return false;
        }

        curl_easy_cleanup(curl);
    } else {
        cerr << "Error iniciando libcurl" << endl;
        file.close();
        return false;
    }

    file.close();
    curl_global_cleanup();
    cout << "Archivo descargado exitosamente!" << endl;
    return true;
}