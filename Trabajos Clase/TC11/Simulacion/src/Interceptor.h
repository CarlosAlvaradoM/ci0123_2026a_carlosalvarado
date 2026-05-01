#ifndef INTERCEPTOR_H
#define INTERCEPTOR_H

/**
 * @class Interceptor
 * @brief Clase que maneja la ejecución del interceptor
 * 
 * Esta clase proporciona funcionalidad para ejecutar
 * la lógica del interceptor que reenvía mensajes
 * entre clientes y servidor.
 */
class Interceptor{
public:
    /**
     * @brief Método estático que ejecuta la lógica del interceptor
     * @param arg Argumento no utilizado (puede ser NULL)
     * @return void* Siempre retorna NULL
     * 
     * Este método es la función principal del hilo interceptor.
     * Recibe mensajes de los clientes, los reenvía al servidor,
     * y luego devuelve las respuestas a los clientes respectivos.
     */
    static void* ejecutar(void* arg);
};

#endif