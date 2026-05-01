#include "Interceptor.h"
#include "IPC.h"
#include "Protocolo.h"
#include <iostream>

using namespace std;

void* Interceptor::ejecutar(void* arg){

    // Esperar a que todos los clientes estén listos
    sem_wait(&IPC::sem_todos_clientes);

    // Recibir mensajes de clientes y reenviar al servidor
    for(int i=0;i<NUM_CLIENTES;i++) {

        // Esperar mensaje de algún cliente
        sem_wait(&IPC::sem_ci);

        // Extraer mensaje de la cola cliente->interceptor
        pthread_mutex_lock(&IPC::mutex_ci);
        Message msg = IPC::cliente_interceptor.front();
        IPC::cliente_interceptor.pop();
        pthread_mutex_unlock(&IPC::mutex_ci);

        // Mostrar mensaje recibido
        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Interceptor recibe: " << msg.contenido << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        // Reenviar mensaje al servidor
        pthread_mutex_lock(&IPC::mutex_is);
        IPC::interceptor_servidor.push(msg);
        pthread_mutex_unlock(&IPC::mutex_is);

        // Notificar al servidor que hay un mensaje
        sem_post(&IPC::sem_is);

    }

    // Notificar que el interceptor termino lo anterior
    sem_post(&IPC::sem_interceptor_termino);

    // Recibir respuestas del servidor y enviar a clientes
    sem_wait(&IPC::sem_servidor_termino);

    for(int i=0;i<NUM_CLIENTES;i++){

        // Esperar respuesta del servidor
        sem_wait(&IPC::sem_si);

        // Extraer mensaje de la cola servidor->interceptor
        pthread_mutex_lock(&IPC::mutex_si);
        Message msg = IPC::servidor_interceptor.front();
        IPC::servidor_interceptor.pop();
        pthread_mutex_unlock(&IPC::mutex_si);

        // Mostrar respuesta recibida del servidor
        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Interceptor recibe del servidor: " << msg.contenido << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        // Colocar respuesta en la cola específica del cliente
        pthread_mutex_lock(&IPC::mutex_rc[msg.cliente_id]);
        IPC::respuestas_cliente[msg.cliente_id].push(msg.contenido);
        pthread_mutex_unlock(&IPC::mutex_rc[msg.cliente_id]);

        // Notificar al cliente que tiene una respuesta disponible
        sem_post(&IPC::sem_rc[msg.cliente_id]);

    }

    return NULL;
}