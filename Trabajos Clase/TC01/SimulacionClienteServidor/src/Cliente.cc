#include "Cliente.h"
#include "IPC.h"
#include <iostream>

using namespace std;

void* Cliente::ejecutar(void* arg){

    // Conversion de dato
    int id = *((int*)arg);

    // Solicitud que enviara el cliente
    Request req;
    req.cliente_id = id;
    req.indice = id + 1;

    // Enviar al interceptor (con mutex)
    pthread_mutex_lock(&IPC::mutex_ci);
    IPC::cliente_interceptor.push(req);
    pthread_mutex_unlock(&IPC::mutex_ci);

    // Avisar proceso consola
    pthread_mutex_lock(&IPC::mutex_print);
    cout << "Cliente " << id << " solicita nombre #" << req.indice << endl;
    pthread_mutex_unlock(&IPC::mutex_print);

    // Incrementar semaforo, para que interceptor sepa que hay solicitud
    sem_post(&IPC::sem_ci);

    // Bloquearse hasta que interceptor envie una respuesta
    sem_wait(&IPC::sem_rc[id]);

    // Proteger cola
    pthread_mutex_lock(&IPC::mutex_rc[id]);
    // Ver cola
    string respuesta = IPC::respuestas_cliente[id].front();
    // Quitar elemento visto
    IPC::respuestas_cliente[id].pop();
    pthread_mutex_unlock(&IPC::mutex_rc[id]);

    // Mostrar consola
    pthread_mutex_lock(&IPC::mutex_print);
    cout << "Cliente " << id << " recibe: " << respuesta << endl;
    pthread_mutex_unlock(&IPC::mutex_print);

    return NULL;
}