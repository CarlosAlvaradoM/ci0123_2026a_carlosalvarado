#include "Interceptor.h"
#include "IPC.h"
#include <iostream>

using namespace std;

void* Interceptor::ejecutar(void* arg){

    // Esperar clientes
    sem_wait(&IPC::sem_todos_clientes);

    // Recibir y reenviar todo al servidor
    for(int i=0;i<NUM_CLIENTES;i++){

        sem_wait(&IPC::sem_ci);

        pthread_mutex_lock(&IPC::mutex_ci);
        Request req = IPC::cliente_interceptor.front();
        IPC::cliente_interceptor.pop();
        pthread_mutex_unlock(&IPC::mutex_ci);

        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Interceptor recibe solicitud de cliente " << req.cliente_id << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        pthread_mutex_lock(&IPC::mutex_is);
        IPC::interceptor_servidor.push(req);
        pthread_mutex_unlock(&IPC::mutex_is);

        sem_post(&IPC::sem_is);
    }

    // Avisar que ya termino de mandar todo al servidor
    sem_post(&IPC::sem_interceptor_termino);

    // Esperar que servidor termine todo
    sem_wait(&IPC::sem_servidor_termino);

    // Recibir todas las respuestas y enviarlas a clientes
    for(int i=0;i<NUM_CLIENTES;i++){

        sem_wait(&IPC::sem_si);

        pthread_mutex_lock(&IPC::mutex_si);
        Response resp = IPC::servidor_interceptor.front();
        IPC::servidor_interceptor.pop();
        pthread_mutex_unlock(&IPC::mutex_si);

        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Interceptor recibe del servidor: " << resp.nombre << " del cliente " << resp.cliente_id << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        pthread_mutex_lock(&IPC::mutex_rc[resp.cliente_id]);
        IPC::respuestas_cliente[resp.cliente_id].push(resp.nombre);
        pthread_mutex_unlock(&IPC::mutex_rc[resp.cliente_id]);

        sem_post(&IPC::sem_rc[resp.cliente_id]);
    }

    return NULL;
}