#include "Servidor.h"
#include "IPC.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

string Servidor::leerNombre(int indice){

    // Archivo de entrada
    ifstream archivo("nombres.txt");
    // Nombres del archivo
    vector<string> nombres;
    // Linea actual leida del archivo
    string linea;

    // Leer todas las lineas
    while(getline(archivo,linea)) {
        nombres.push_back(linea);
    }   

    // Verificar indice valido
    if(indice >= 0 && (size_t)indice < nombres.size()) {
        return nombres[indice];
    }

    archivo.close();
    
    return "No encontrado";
}

void* Servidor::ejecutar(void* arg){

    // Una solicitud por cliente
    for(int i=0;i<NUM_CLIENTES;i++){

        // Esperar solicitud del interceptor
        sem_wait(&IPC::sem_is);

        // Bloqueo
        pthread_mutex_lock(&IPC::mutex_is);
        // Recoger solicitud
        Request req = IPC::interceptor_servidor.front();
        // Eliminarla
        IPC::interceptor_servidor.pop();
        pthread_mutex_unlock(&IPC::mutex_is);

        // Consola
        pthread_mutex_lock(&IPC::mutex_print);
        cout << "Servidor busca nombre #" << req.indice << endl;
        pthread_mutex_unlock(&IPC::mutex_print);

        // Buscar nombre
        Response resp;
        resp.cliente_id = req.cliente_id;
        resp.nombre = leerNombre(req.indice);

        // Enviar al interceptor
        pthread_mutex_lock(&IPC::mutex_si);
        IPC::servidor_interceptor.push(resp);
        pthread_mutex_unlock(&IPC::mutex_si);

        // Avisar interceptor
        sem_post(&IPC::sem_si);
    }

    return NULL;
}