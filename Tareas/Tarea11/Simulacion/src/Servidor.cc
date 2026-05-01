#include "Servidor.h"
#include "IPC.h"
#include "Protocolo.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Funcion auxiliar para leer todas las figuras
vector<string> leerFiguras()
{

    vector<string> figuras;

    ifstream archivo("figuras.txt");

    string linea;

    while (getline(archivo, linea)) {

        if (linea != "") {
            figuras.push_back(linea);
        }
    }

    archivo.close();

    return figuras;
}

// Funcion principal del hilo servidor
void *Servidor::ejecutar(void *arg)
{

    // Esperar a que el interceptor termine su fase 1
    sem_wait(&IPC::sem_interceptor_termino);

    // Procesar un mensaje por cada cliente
    for (int i = 0; i < NUM_CLIENTES; i++) {

        // Esperar mensaje del interceptor
        sem_wait(&IPC::sem_is);

        // Extraer mensaje de la cola interceptor->servidor
        pthread_mutex_lock(&IPC::mutex_is);

        Message msg = IPC::interceptor_servidor.front();
        IPC::interceptor_servidor.pop();

        pthread_mutex_unlock(&IPC::mutex_is);

        // Obtener comando y data
        char cmd = obtenerComando(msg.contenido);
        string data = obtenerData(msg.contenido);

        // Mostrar mensaje recibido
        pthread_mutex_lock(&IPC::mutex_print);

        cout << "Servidor procesa: " << msg.contenido << endl;

        pthread_mutex_unlock(&IPC::mutex_print);

        // Crear respuesta
        Message resp;
        resp.cliente_id = msg.cliente_id;

        // Leer archivo figuras.txt
        vector<string> figuras = leerFiguras();

        // REQUEST
        if (cmd == 'R') {

            string directorio = "";

            for (size_t j = 0; j < figuras.size(); j++) {

                directorio += figuras[j];

                if (j != figuras.size() - 1){
                    directorio += ",";
                }
            }

            resp.contenido = crearMensaje('D', directorio);
        }

        // GET
        else if (cmd == 'G') {

            bool encontrada = false;

            for (size_t j = 0; j < figuras.size(); j++) {

                if (figuras[j] == data) {

                    encontrada = true;

                    resp.contenido = crearMensaje('D', figuras[j]);

                    break;
                }
            }

            // ACK ERROR
            if (!encontrada) {

                resp.contenido = crearMensaje('A', "404");
            }
        }

        // COMANDO INVALIDO
        else {

            resp.contenido = crearMensaje('A', "INVALID");
        }

        // Mostrar respuesta
        pthread_mutex_lock(&IPC::mutex_print);

        cout << "Servidor responde: " << resp.contenido << endl;

        pthread_mutex_unlock(&IPC::mutex_print);

        // Enviar respuesta al interceptor
        pthread_mutex_lock(&IPC::mutex_si);

        IPC::servidor_interceptor.push(resp);

        pthread_mutex_unlock(&IPC::mutex_si);

        // Notificar respuesta disponible
        sem_post(&IPC::sem_si);

    }

    // Notificar fin del servidor
    sem_post(&IPC::sem_servidor_termino);

    return NULL;
}