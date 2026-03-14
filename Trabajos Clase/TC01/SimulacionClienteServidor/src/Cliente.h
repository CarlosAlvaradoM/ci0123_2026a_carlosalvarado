#ifndef CLIENTE_H
#define CLIENTE_H

/**
 * @class Cliente
 * @brief Representa un cliente que solicita nombres al sistema
 * 
 * Cada cliente se ejecuta en su propio hilo y hace esto:
 * 1. Crea una solicitud con su ID y un indice
 * 2. Envia la solicitud al interceptor
 * 3. Espera la respuesta
 * 4. Muestra la respuesta recibida
 */
class Cliente{

public:
    /**
     * @brief Función del cliente, que hace su cliclo respectivo
     * 
     * @param arg Puntero al ID del cliente (debe convertirse de void* a int*)
     * @return void* Siempre retorna NULL
     */
    static void* ejecutar(void* arg);
};

#endif