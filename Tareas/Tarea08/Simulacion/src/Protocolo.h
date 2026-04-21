#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <string>

/**
 * @brief Crea un mensaje con el formato del protocolo
 * @param comando Caracter que representa el comando ('R', 'G', 'A')
 * @param data Datos a incluir en el mensaje
 * @return std::string Mensaje formateado como "P/comando/data"
 */
inline std::string crearMensaje(char comando, const std::string& data){
    return "P/" + std::string(1, comando) + "/" + data;
}

/**
 * @brief Extrae el comando de un mensaje
 * @param msg Mensaje en formato de protocolo
 * @return char Caracter del comando (posicion 2 del mensaje)
 * 
 * Asume que el mensaje tiene al menos 3 caracteres y formato "P/X/..."
 */
inline char obtenerComando(const std::string& msg){
    return msg[2];
}

/**
 * @brief Extrae los datos de un mensaje
 * @param msg Mensaje en formato de protocolo
 * @return std::string Datos del mensaje (despues de "P/X/")
 */
inline std::string obtenerData(const std::string& msg){
    if(msg.size() <= 4) return "";
    return msg.substr(4);
}

#endif