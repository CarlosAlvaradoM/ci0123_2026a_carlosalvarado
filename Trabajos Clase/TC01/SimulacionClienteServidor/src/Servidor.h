#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

/**
 * @class Servidor
 * @brief Procesa las solicitudes de los clientes leyendo nombres desde un archivo
 */
class Servidor{

public:

    /**
     * @brief Funcion del server
     * 
     * @param arg No utilizado
     * @return void* Siempre retorna NULL
     * 
     * El servidor procesa una solicitud por cada cliente (NUM_CLIENTES veces):
     * 1. Espera una solicitud del interceptor
     * 2. Recoge la solicitud de la cola interceptor_servidor
     * 3. Busca el nombre solicitado usando leerNombre()
     * 4. Enva la respuesta al interceptor
     * 5. Avisa al interceptor
     */
    static void* ejecutar(void* arg);
    
    /**
     * @brief Lee un nombre del archivo "nombres.txt"
     * 
     * @param indice Posicin del nombre a leer (empezando desde 0)
     * @return std::string El nombre en esa posición, o "No encontrado"
     */
    static std::string leerNombre(int indice);
};

#endif