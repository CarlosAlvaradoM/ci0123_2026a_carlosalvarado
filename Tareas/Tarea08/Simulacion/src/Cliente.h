#ifndef CLIENTE_H
#define CLIENTE_H

/**
 * @class Cliente
 * @brief Clase que maneja la ejecución de un cliente
 * 
 * Esta clase proporciona funcionalidad para ejecutar
 * la lógica de un cliente que envía mensajes al sistema.
 */
class Cliente{
public:
    /**
     * @brief Método estático que ejecuta la lógica del cliente
     * @param arg Puntero al ID del cliente (entero)
     * @return void* Siempre retorna NULL
     * 
     * Este método es la función principal del hilo cliente.
     * Envía un mensaje, espera respuesta y la muestra.
     */
    static void* ejecutar(void* arg);
};

#endif