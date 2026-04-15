#include "IPC.h"

// Definicion de colas
std::queue<Request> IPC::cliente_interceptor;
std::queue<Request> IPC::interceptor_servidor;
std::queue<Response> IPC::servidor_interceptor;

std::queue<std::string> IPC::respuestas_cliente[NUM_CLIENTES];

// Definicion de mutex
pthread_mutex_t IPC::mutex_ci;
pthread_mutex_t IPC::mutex_is;
pthread_mutex_t IPC::mutex_si;
pthread_mutex_t IPC::mutex_rc[NUM_CLIENTES];
pthread_mutex_t IPC::mutex_print;

// Definicion de semaforos
sem_t IPC::sem_ci;
sem_t IPC::sem_is;
sem_t IPC::sem_si;
sem_t IPC::sem_rc[NUM_CLIENTES];

int IPC::clientes_listos;
pthread_mutex_t IPC::mutex_contador;
sem_t IPC::sem_todos_clientes;

int IPC::solicitudes_enviadas;
pthread_mutex_t IPC::mutex_interceptor_contador;
sem_t IPC::sem_interceptor_termino;

int IPC::respuestas_generadas;
pthread_mutex_t IPC::mutex_servidor_contador;
sem_t IPC::sem_servidor_termino;

void IPC::inicializar(){

    clientes_listos = 0;
    pthread_mutex_init(&mutex_contador, NULL);
    sem_init(&sem_todos_clientes, 0, 0);

    solicitudes_enviadas = 0;
    pthread_mutex_init(&mutex_interceptor_contador,NULL);
    sem_init(&sem_interceptor_termino,0,0);

    respuestas_generadas = 0;
    pthread_mutex_init(&mutex_servidor_contador,NULL);
    sem_init(&sem_servidor_termino,0,0);

    // Colas principales
    pthread_mutex_init(&mutex_ci,NULL);
    pthread_mutex_init(&mutex_is,NULL);
    pthread_mutex_init(&mutex_si,NULL);
    // Mutex de print
    pthread_mutex_init(&mutex_print,NULL);

    // Mutex y semaforo para cad cliente
    for(int i=0;i<NUM_CLIENTES;i++){
        pthread_mutex_init(&mutex_rc[i],NULL);
        sem_init(&sem_rc[i],0,0);
    }

    // Semaforos generales
    sem_init(&sem_ci,0,0);
    sem_init(&sem_is,0,0);
    sem_init(&sem_si,0,0);
}