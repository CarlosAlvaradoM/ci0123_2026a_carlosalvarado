#include "IPC.h"

// Inicializacion de colas estaticas
std::queue<Message> IPC::cliente_interceptor;
std::queue<Message> IPC::interceptor_servidor;
std::queue<Message> IPC::servidor_interceptor;

// Inicializacion de colas de respuestas por cliente
std::queue<std::string> IPC::respuestas_cliente[NUM_CLIENTES];

// Inicializacion de mutex estaticos
pthread_mutex_t IPC::mutex_ci;
pthread_mutex_t IPC::mutex_is;
pthread_mutex_t IPC::mutex_si;
pthread_mutex_t IPC::mutex_rc[NUM_CLIENTES];
pthread_mutex_t IPC::mutex_print;
pthread_mutex_t IPC::mutex_contador;

// Inicializacion de semaforos estaticos
sem_t IPC::sem_ci;
sem_t IPC::sem_is;
sem_t IPC::sem_si;
sem_t IPC::sem_rc[NUM_CLIENTES];
sem_t IPC::sem_todos_clientes;
sem_t IPC::sem_interceptor_termino;
sem_t IPC::sem_servidor_termino;

// Inicializacion de variables contadoras
int IPC::clientes_listos;

// Funcion que inicializa todos los mecanismos de sincronizacion
void IPC::inicializar(){

    // Inicializar contador de clientes
    clientes_listos = 0;

    // Inicializar mutex
    pthread_mutex_init(&mutex_contador,NULL);
    pthread_mutex_init(&mutex_ci,NULL);
    pthread_mutex_init(&mutex_is,NULL);
    pthread_mutex_init(&mutex_si,NULL);
    pthread_mutex_init(&mutex_print,NULL);

    // Inicializar mutex y semaforos específicos por cliente
    for(int i=0;i<NUM_CLIENTES;i++){
        pthread_mutex_init(&mutex_rc[i],NULL);
        sem_init(&sem_rc[i],0,0);  // Semaforos comienzan en 0 (bloqueados)
    }

    // Inicializar semaforos de colas
    sem_init(&sem_ci,0,0);
    sem_init(&sem_is,0,0);
    sem_init(&sem_si,0,0);

    // Inicializar semaforos de barrera
    sem_init(&sem_todos_clientes,0,0);
    sem_init(&sem_interceptor_termino,0,0);
    sem_init(&sem_servidor_termino,0,0);
}