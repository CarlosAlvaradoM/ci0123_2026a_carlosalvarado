#include "Interceptor.h"
#include "IPC.h"
#include <iostream>

using namespace std;

void* Interceptor::ejecutar(void* arg){

    // Procesar una solicitud por cliente
    for(int i=0;i<NUM_CLIENTES;i++){

        // Bloquearse hasta esperar solicitud
        sem_wait(&IPC::sem_ci);

        // Bloqueo
        pthread_mutex_lock(&IPC::mutex_ci);
        // Coger la solicitud
        Request req = IPC::cliente_interceptor.front();
        // Quitarla
        IPC::cliente_interceptor.pop();
        pthread_mutex_unlock(&IPC::mutex_ci);

        // Consola
        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Interceptor recibe solicitud de cliente " << req.cliente_id << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        // Mandar solicitud al servidor
        pthread_mutex_lock(&IPC::mutex_is);
        IPC::interceptor_servidor.push(req);
        pthread_mutex_unlock(&IPC::mutex_is);

        // Avisar al servidor
        sem_post(&IPC::sem_is);

        // Esperar respuesta
        sem_wait(&IPC::sem_si);

        // Bloqueo
        pthread_mutex_lock(&IPC::mutex_si);
        // Coger respuesta
        Response resp = IPC::servidor_interceptor.front();
        // Quitarla
        IPC::servidor_interceptor.pop();
        pthread_mutex_unlock(&IPC::mutex_si);

        // Consola
        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Interceptor recibe del servidor: " << resp.nombre << " del cliente " << req.cliente_id << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        // Reenvio a cliente
        pthread_mutex_lock(&IPC::mutex_rc[resp.cliente_id]);
        IPC::respuestas_cliente[resp.cliente_id].push(resp.nombre);
        pthread_mutex_unlock(&IPC::mutex_rc[resp.cliente_id]);

        // Avisar al cliente
        sem_post(&IPC::sem_rc[resp.cliente_id]);
    }

    return NULL;
}