#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;

/**
 * Crear mensaje:
 * P/comando/data
 */
inline string crearMensaje(char comando, const string& data){

    return "P/" + string(1,comando) + "/" + data;
}

/**
 * Separar mensaje por "/"
 */
inline vector<string> dividir(const string& msg){

    vector<string> partes;

    string temp;

    stringstream ss(msg);

    while(getline(ss,temp,'/')){
        partes.push_back(temp);
    }

    return partes;
}

/**
 * Obtener comando
 */
inline char obtenerComando(const string& msg){

    vector<string> partes = dividir(msg);

    if(partes.size() < 2)
        return '?';

    return partes[1][0];
}

/**
 * Obtener data
 */
inline string obtenerData(const string& msg){

    vector<string> partes = dividir(msg);

    if(partes.size() < 3)
        return "";

    return partes[2];
}

/**
 * Validar protocolo
 */
inline bool protocoloValido(const string& msg){

    vector<string> partes = dividir(msg);

    if(partes.size() < 2)
        return false;

    return partes[0] == "P";
}

#endif