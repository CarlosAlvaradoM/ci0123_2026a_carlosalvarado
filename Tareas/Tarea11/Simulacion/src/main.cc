#include <pthread.h>
#include "Cliente.h"
#include "Interceptor.h"
#include "Servidor.h"
#include "IPC.h"

int main(){

    // Declarar hilos
    pthread_t clientes[NUM_CLIENTES];
    pthread_t interceptor;
    pthread_t servidor;

    // Array para almacenar los IDs de los clientes
    int ids[NUM_CLIENTES];

    // Inicializar todos los mecanismos de IPC
    IPC::inicializar();

    // Crear hilo interceptor
    pthread_create(&interceptor, NULL, Interceptor::ejecutar, NULL);
    
    // Crear hilo servidor
    pthread_create(&servidor, NULL, Servidor::ejecutar, NULL);

    // Crear hilos clientes con sus respectivos IDs
    for(int i=0;i<NUM_CLIENTES;i++){
        ids[i] = i;
        pthread_create(&clientes[i], NULL, Cliente::ejecutar, &ids[i]);
    }

    // Esperar a que todos los clientes terminen
    for(int i=0;i<NUM_CLIENTES;i++)
        pthread_join(clientes[i], NULL);

    // Esperar a que el interceptor termine
    pthread_join(interceptor, NULL);
    
    // Esperar a que el servidor termine
    pthread_join(servidor, NULL);

    return 0;
}