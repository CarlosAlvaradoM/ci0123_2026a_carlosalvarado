#include "Cliente.h"
#include "IPC.h"
#include "Protocolo.h"
#include <iostream>

using namespace std;

void* Cliente::ejecutar(void* arg){

    // Obtener el ID del cliente desde el argumento
    int id = *((int*)arg);

    // Crear mensaje con comando 'R' y data "dir"
    Message msg;
    msg.cliente_id = id;
    if(id == 0)
    msg.contenido = crearMensaje('R',"dir");

    else if(id == 1)
        msg.contenido = crearMensaje('G',"carro.txt");

    else
        msg.contenido = crearMensaje('G',"casa.txt");

    // Enviar mensaje a la cola cliente->interceptor
    pthread_mutex_lock(&IPC::mutex_ci);
    IPC::cliente_interceptor.push(msg);
    pthread_mutex_unlock(&IPC::mutex_ci);

    // Mostrar mensaje enviado
    pthread_mutex_lock(&IPC::mutex_print);
    cout << "Cliente " << id << " envia: " << msg.contenido << endl;
    pthread_mutex_unlock(&IPC::mutex_print);

    // Notificar que hay un mensaje disponible
    sem_post(&IPC::sem_ci);

    // Barrera de sincronizacion, esperar a que todos los clientes esten listos
    pthread_mutex_lock(&IPC::mutex_contador);
    IPC::clientes_listos++;
    if(IPC::clientes_listos == NUM_CLIENTES)
        sem_post(&IPC::sem_todos_clientes);  // Ultimo cliente despierta al interceptor
    pthread_mutex_unlock(&IPC::mutex_contador);

    // Esperar respuesta del servidor especifica para este cliente
    sem_wait(&IPC::sem_rc[id]);

    // Extraer respuesta de la cola de respuestas
    pthread_mutex_lock(&IPC::mutex_rc[id]);
    string resp = IPC::respuestas_cliente[id].front();
    IPC::respuestas_cliente[id].pop();
    pthread_mutex_unlock(&IPC::mutex_rc[id]);

    // Mostrar respuesta recibida
    pthread_mutex_lock(&IPC::mutex_print);
    cout << "Cliente " << id << " recibe: " << resp << endl;
    pthread_mutex_unlock(&IPC::mutex_print);

    return NULL;
}