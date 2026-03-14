#ifndef IPC_H
#define IPC_H

#include <queue>
#include <string>
#include <pthread.h>
#include <semaphore.h>

// Numero de clientes del sistema
#define NUM_CLIENTES 3

// Datos de la solicitud
struct Request{
    // Identificador del cliente
    int cliente_id;
    // Indice del archivo server
    int indice;
};

// Datos de la respuesta
struct Response{
    // Identificador del cliente
    int cliente_id;
    // Dato de respuesta
    std::string nombre;
};

/**
 * @class IPC
 * @brief Clase que gestiona la comunicacion entre hilos
 * 
 * Esta clase proporciona las colas, mutex y semaforos necesarios para
 * la comunicacion sincronizada entre los hilos cliente, interceptor y servidor
 */
class IPC{

public:
    /**
     * @brief Cola de solicitudes de clientes hacia el interceptor
     * 
     * Los clientes solicitan aca
     * El interceptor consume de esta cola
     */
    static std::queue<Request> cliente_interceptor;
    
    /**
     * @brief Cola de solicitudes del interceptor hacia el servidor
     * 
     * El interceptor solicita al server aca
     * El servidor consume de esta cola
     */
    static std::queue<Request> interceptor_servidor;
    
    /**
     * @brief Cola de respuestas del servidor hacia el interceptor
     * 
     * El servidor produce aca las respuestas
     * El interceptor consume de esta cola
     */
    static std::queue<Response> servidor_interceptor;
    
    /**
     * @brief Colas de respuestas del interceptor hacia cada cliente
     * 
     * Array de colas, una por cada cliente
     * El interceptor produce en la cola correspondiente al cliente
     * Cada cliente consume de su propia cola
     */
    static std::queue<std::string> respuestas_cliente[NUM_CLIENTES];

    
    /**
     * @brief Mutex para proteger cliente_interceptor
     */
    static pthread_mutex_t mutex_ci;
    
    /**
     * @brief Mutex para proteger interceptor_servidor
     */
    static pthread_mutex_t mutex_is;
    
    /**
     * @brief Mutex para proteger servidor_interceptor
     */
    static pthread_mutex_t mutex_si;
    
    /**
     * @brief Mutex para proteger cada cola de respuestas_cliente
     */
    static pthread_mutex_t mutex_rc[NUM_CLIENTES];
    
    /**
     * @brief Mutex para proteger la salida por consola prints
     * 
     * Evita que los mensajes de diferentes hilos se mezclen
     */
    static pthread_mutex_t mutex_print;

    
    /**
     * @brief Semáforo para avisar de datos en cliente_interceptor
     * 
     * Los clientes hacen post() cuando añaden una solicitud
     * El interceptor hace wait() para esperar solicitudes
     */
    static sem_t sem_ci;
    
    /**
     * @brief Semáforo para avisar de datos en interceptor_servidor
     * 
     * El interceptor hace post() cuando reenvia una solicitud
     * El servidor hace wait() para esperar solicitudes
     */
    static sem_t sem_is;
    
    /**
     * @brief Semaforo para avisar de datos en servidor_interceptor
     * 
     * El servidor hace post() cuando envia una respuesta
     * El interceptor hace wait() para esperar respuestas
     */
    static sem_t sem_si;
    
    /**
     * @brief Semaforos para avisar de respuestas a cada cliente
     * 
     * El interceptor hace post() cuando hay respuesta para un cliente
     * Cada cliente hace wait() en su semaforo para esperar su respuesta
     */
    static sem_t sem_rc[NUM_CLIENTES];

    /**
     * @brief Inicializa todos los mecanismos de sincronización
     * 
     * Debe llamarse antes de crear cualquier hilo
     * Inicializa todos los mutex y semaforos con sus valores por defecto
     */
    static void inicializar();

};

#endif
