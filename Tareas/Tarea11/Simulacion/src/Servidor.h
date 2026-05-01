#ifndef SERVIDOR_H
#define SERVIDOR_H

/**
 * @class Servidor
 * @brief Clase que maneja la ejecucion del servidor
 * 
 * Servidor que procesa mensajes y genera respuestas
 */
class Servidor{
public:
    /**
     * @brief Ejecuta la logica del servidor
     * @param arg no se usa (futuras iteraciones)
     * @return null
     * 
     * Hilo servidor que espera mensajes del interceptor, los procesa segun
     * el comando recibido y envia respuestas
     */
    static void* ejecutar(void* arg);
};

#endif