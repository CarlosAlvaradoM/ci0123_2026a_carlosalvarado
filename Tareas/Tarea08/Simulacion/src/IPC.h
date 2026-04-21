#ifndef IPC_H
#define IPC_H

#include <queue>
#include <string>
#include <pthread.h>
#include <semaphore.h>

#define NUM_CLIENTES 3  ///< Número de clientes en el sistema

/**
 * @struct Message
 * @brief Estructura que representa un mensaje en el sistema
 * 
 */
struct Message{
    int cliente_id;           ///< ID del cliente que envía o recibe el mensaje
    std::string contenido;    ///< Contenido del mensaje en formato de protocolo
};

/**
 * @class IPC
 * @brief Clase que gestiona todos los mecanismos de IPC
 * 
 * Clase con colas, mutex y semaforos estaticos
 * para la comunicacion sincronizada entre hilos
 */
class IPC{

public:

    // Variables de barrera para clientes
    static int clientes_listos;  ///< Contador de clientes listos
    static pthread_mutex_t mutex_contador;  ///< Mutex para proteger clientes_listos
    static sem_t sem_todos_clientes;  ///< Semaforo para esperar a todos los clientes

    // Variables de barrera interceptor - servidor
    static sem_t sem_interceptor_termino;  ///< Semaforo para indicar fin del interceptor
    static sem_t sem_servidor_termino;  ///< Semaforo para indicar fin del servidor

    // Colas de mensajes
    static std::queue<Message> cliente_interceptor;  ///< Cola de clientes hacia interceptor
    static std::queue<Message> interceptor_servidor;  ///< Cola de interceptor hacia servidor
    static std::queue<Message> servidor_interceptor;  ///< Cola de servidor hacia interceptor

    static std::queue<std::string> respuestas_cliente[NUM_CLIENTES];  ///< Colas de respuestas por cliente

    // Mutex para proteger colas
    static pthread_mutex_t mutex_ci;  ///< Mutex para cola cliente_interceptor
    static pthread_mutex_t mutex_is;  ///< Mutex para cola interceptor_servidor
    static pthread_mutex_t mutex_si;  ///< Mutex para cola servidor_interceptor
    static pthread_mutex_t mutex_rc[NUM_CLIENTES]; ///< Mutex para cada cola de respuestas
    static pthread_mutex_t mutex_print;  ///< Mutex para proteger la salida por consola

    // Semaforos para sincronizacion
    static sem_t sem_ci;  ///< Semaforo para notificar mensaje en cola cliente->interceptor
    static sem_t sem_is;  ///< Semaforo para notificar mensaje en cola interceptor->servidor
    static sem_t sem_si;  ///< Semaforo para notificar mensaje en cola servidor->interceptor
    static sem_t sem_rc[NUM_CLIENTES];  ///< Semaforo sespecificos para cada cliente

    /**
     * @brief Inicializa todos los mecanismos de IPC
     * 
     * Inicializa mutex, semaforos y variables contadoras
     * antes de iniciar los hilos
     */
    static void inicializar();
};

#endif