#include <pthread.h>
#include "Cliente.h"
#include "Interceptor.h"
#include "Servidor.h"
#include "IPC.h"

int main(){

    // Tipo hilo
    pthread_t clientes[NUM_CLIENTES];
    pthread_t hilo_interceptor;
    pthread_t hilo_servidor;

    // Numero de clientes
    int ids[NUM_CLIENTES];

    // Iniciarlizar mecanismos de sincr.
    IPC::inicializar();

    // Crear hilos
    pthread_create(&hilo_interceptor,NULL,Interceptor::ejecutar,NULL);
    pthread_create(&hilo_servidor,NULL,Servidor::ejecutar,NULL);

    // Hilos clientes
    for(int i=0;i<NUM_CLIENTES;i++){
        ids[i] = i;
        pthread_create(&clientes[i],NULL,Cliente::ejecutar,&ids[i]);
    }

    // Esperar clientes
    for(int i=0;i<NUM_CLIENTES;i++)
        pthread_join(clientes[i],NULL);

    // Espear servidor e interceptor
    pthread_join(hilo_interceptor,NULL);
    pthread_join(hilo_servidor,NULL);

    return 0;
}