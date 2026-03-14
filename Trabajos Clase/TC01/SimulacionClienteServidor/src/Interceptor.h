#ifndef INTERCEPTOR_H
#define INTERCEPTOR_H

/**
 * @class Interceptor
 * @brief Es el intermediario entre clientes y servidor
 * 
 * El interceptor hace:
 * - Recibe solicitudes de los clientes
 * - Las reenvia al servidor
 * - Recibe respuestas del servidor
 * - Las reenvía al cliente correspondiente
 */
class Interceptor{

public:
    /**
     * @brief Función del interceptor haciendo su ciclo
     * 
     * @param arg No utilizado (puede ser NULL)
     * @return void* Siempre retorna NULL
     */
    static void* ejecutar(void* arg);
};

#endif