#include "Servidor.h"
#include "IPC.h"
#include "Protocolo.h"
#include <iostream>

using namespace std;

// Función principal del hilo servidor
void* Servidor::ejecutar(void* arg){

    // Esperar a que el interceptor termine su fase 1
    sem_wait(&IPC::sem_interceptor_termino);

    // Procesar un mensaje por cada cliente
    for(int i=0;i<NUM_CLIENTES;i++){

        // Esperar mensaje del interceptor
        sem_wait(&IPC::sem_is);

        // Extraer mensaje de la cola interceptor->servidor
        pthread_mutex_lock(&IPC::mutex_is);
        Message msg = IPC::interceptor_servidor.front();
        IPC::interceptor_servidor.pop();
        pthread_mutex_unlock(&IPC::mutex_is);

        // Obtener el comando del mensaje
        char cmd = obtenerComando(msg.contenido);

        // Mostrar mensaje procesado
        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Servidor procesa: " << msg.contenido << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        // Preparar mensaje de respuesta
        Message resp;
        resp.cliente_id = msg.cliente_id;

        // Procesar según el comando recibido
        if(cmd == 'R'){
            // Respuesta para comando 'R' (Read)
            resp.contenido = crearMensaje('D',"fig1,fig2,fig3");
        } else if(cmd == 'G'){
            // Respuesta para comando 'G' (Get)
            resp.contenido = crearMensaje('D',"bloques lego");
        } else {
            // Respuesta genérica para otros comandos
            resp.contenido = crearMensaje('A',"OK");
        }

        // Enviar respuesta al interceptor
        pthread_mutex_lock(&IPC::mutex_si);
        IPC::servidor_interceptor.push(resp);
        pthread_mutex_unlock(&IPC::mutex_si);

        // Notificar que hay una respuesta disponible
        sem_post(&IPC::sem_si);
    }

    // Notificar que el servidor terminó su procesamiento
    sem_post(&IPC::sem_servidor_termino);

    return NULL;
}