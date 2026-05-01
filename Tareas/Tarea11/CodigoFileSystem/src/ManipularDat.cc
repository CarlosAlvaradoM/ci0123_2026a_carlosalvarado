#include "ManipularDat.h"
#include "CrearDat.h"
#include <fstream>
#include <iostream>
#include <cstring>

// Constantes

const int EOF_VALOR = 65535;
const int TAMANO_BLOQUE = 256;
const int TAMANO_INODO = 16;

const int TAMANO_SEGMENTO = 4096;
const int BLOQUES_POR_SEGMENTO = 16;
const int BLOQUES_DATOS_POR_SEGMENTO = 14;

// Funciones auxiliares
int obtenerSegmento(int bloqueGlobal) {
    return bloqueGlobal / BLOQUES_POR_SEGMENTO;
}

int obtenerBloqueLocal(int bloqueGlobal) {
    return bloqueGlobal % BLOQUES_POR_SEGMENTO;
}

int obtenerBloqueBitmap(int segmento) {
    return segmento * BLOQUES_POR_SEGMENTO;
}

int obtenerBloqueInodos(int segmento) {
    return (segmento * BLOQUES_POR_SEGMENTO) + 1;
}

// Struct bloque de datos
struct BloqueDatos {
    char datos[240];
    short siguienteBloque;
};

// Funcion para tamano

int obtenerTamanoDisco(const char* nombreArchivo) {

    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    if (!archivo.is_open()) {
        return 0;
    }

    int tamano = archivo.tellg();
    archivo.close();
    return tamano;
}

// Funciones del bitmap

void leerBitmapSegmento(const char* nombreArchivo, int segmento, char* bitmap) {

    std::ifstream archivo(nombreArchivo, std::ios::binary);

    if (!archivo.is_open()) {
        return;
    }

    int bloqueBitmap = obtenerBloqueBitmap(segmento);

    archivo.seekg(bloqueBitmap * TAMANO_BLOQUE);

    archivo.read(bitmap, 2);

    archivo.close();
}

void escribirBitmapSegmento(const char* nombreArchivo, int segmento, char* bitmap) {

    std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary);

    if (!archivo.is_open()) {
        return;
    }

    int bloqueBitmap = obtenerBloqueBitmap(segmento);

    archivo.seekp(bloqueBitmap * TAMANO_BLOQUE);

    archivo.write(bitmap, 2);

    archivo.close();
}

// Funciones de inodos

void leerInodo(const char* nombreArchivo, int segmento, int indice, Inodo& inodo) {

    std::ifstream archivo(nombreArchivo, std::ios::binary);

    if (!archivo.is_open()) {
        return;
    }

    int posicion = (segmento * TAMANO_SEGMENTO) + TAMANO_BLOQUE + (indice * TAMANO_INODO);

    archivo.seekg(posicion);

    archivo.read(reinterpret_cast<char*>(&inodo), TAMANO_INODO);

    archivo.close();
}

void escribirInodo(const char* nombreArchivo, int segmento, int indice, const Inodo& inodo) {

    std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary);

    if (!archivo.is_open()) {
        return;
    }

    int posicion = (segmento * TAMANO_SEGMENTO) + TAMANO_BLOQUE + (indice * TAMANO_INODO);

    archivo.seekp(posicion);

    archivo.write(reinterpret_cast<const char*>(&inodo), TAMANO_INODO);

    archivo.close();
}

int buscarInodoPorNombre(const char* nombreArchivo, const char* nombreFigura) {

    int tamanoDisco = obtenerTamanoDisco(nombreArchivo);

    int totalSegmentos = tamanoDisco / TAMANO_SEGMENTO;

    for (int seg = 0; seg < totalSegmentos; seg++) {

        for (int i = 0; i < 14; i++) {

            Inodo inodo;

            leerInodo(nombreArchivo, seg, i, inodo);

            if (inodo.activo == 1 &&
                strcmp(inodo.nombre, nombreFigura) == 0) {

                return (seg * 14) + i;
            }
        }
    }

    return -1;
}

int buscarInodoLibre(const char* nombreArchivo) {

    int tamanoDisco = obtenerTamanoDisco(nombreArchivo);

    int totalSegmentos = tamanoDisco / TAMANO_SEGMENTO;

    for (int seg = 0; seg < totalSegmentos; seg++) {

        for (int i = 0; i < 14; i++) {

            Inodo inodo;

            leerInodo(nombreArchivo, seg, i, inodo);

            if (inodo.activo == 0) {

                return (seg * 14) + i;
            }
        }
    }

    return -1;
}

int obtenerSegmentoInodo(int inodoGlobal) {
    return inodoGlobal / 14;
}

int obtenerIndiceLocalInodo(int inodoGlobal) {
    return inodoGlobal % 14;
}

// Funcion de liberar 

void liberarBloques(const char* nombreArchivo, short primerBloque) {

    short bloqueActual = primerBloque;

    int totalBloques = obtenerTamanoDisco(nombreArchivo) / TAMANO_BLOQUE;

    while (bloqueActual != EOF_VALOR && bloqueActual < totalBloques && bloqueActual >= 0) {

        int segmento = obtenerSegmento(bloqueActual);

        int local = obtenerBloqueLocal(bloqueActual);

        char bitmap[2] = {0};

        leerBitmapSegmento(nombreArchivo, segmento, bitmap);

        int byteIndex = local / 8;
        int bitIndex = local % 8;

        bitmap[byteIndex] &= ~(1 << bitIndex);

        escribirBitmapSegmento(nombreArchivo, segmento, bitmap);

        std::ifstream archivo(nombreArchivo, std::ios::binary);

        BloqueDatos bloque;

        archivo.seekg(bloqueActual * TAMANO_BLOQUE);

        archivo.read(reinterpret_cast<char*>(&bloque), sizeof(BloqueDatos));

        bloqueActual = bloque.siguienteBloque;

        archivo.close();
    }
}

// Funcion de lectura

void leerFigura(const char* nombreArchivo, const char* nombreFigura) {
    int indiceInodo = buscarInodoPorNombre(nombreArchivo, nombreFigura);
    if (indiceInodo == -1) {
        std::cout << "Figura '" << nombreFigura << "' no encontrada" << std::endl;
        return;
    }
    
    Inodo inodo;
    int segInodo = obtenerSegmentoInodo(indiceInodo);

    int indiceLocal = obtenerIndiceLocalInodo(indiceInodo);

    leerInodo(nombreArchivo, segInodo, indiceLocal, inodo);
    
    std::cout << "Leyendo figura '" << nombreFigura << "':" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    std::ifstream archivo(nombreArchivo, std::ios::binary);
    short bloqueActual = inodo.primerBloque;
    int bytesLeidos = 0;
    
    while (bloqueActual != EOF_VALOR && bytesLeidos < inodo.tamano) {
        BloqueDatos bloque;
        archivo.seekg(bloqueActual * TAMANO_BLOQUE);
        archivo.read(reinterpret_cast<char*>(&bloque), sizeof(BloqueDatos));
        
        for (int i = 0; i < 240 && bytesLeidos < inodo.tamano; i++) {
            if (bloque.datos[i] != '\0') {
                std::cout << bloque.datos[i];
                bytesLeidos++;
            }
        }
        
        bloqueActual = bloque.siguienteBloque;
    }
    
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    archivo.close();
}

// Funcion de escritura

void escribirStringEnBloquesLibres(const char* nombreArchivo, const char* nombreFigura, const char* string) {
    if (buscarInodoPorNombre(nombreArchivo, nombreFigura) != -1) {
        std::cout << "La figura '" << nombreFigura << "' ya existe. Use modificarFigura() en su lugar." << std::endl;
        return;
    }
    
    int longitudNombre = strlen(nombreFigura);
    if (longitudNombre >= 8) {
        std::cout << "Error: Nombre muy largo (max 7 caracteres)" << std::endl;
        return;
    }
    
    int longitudTotal = strlen(string);
    std::cout << "Escribiendo '" << nombreFigura << "' (" << longitudTotal << " bytes)" << std::endl;
    
    int tamanoDisco = obtenerTamanoDisco(nombreArchivo);
    if (tamanoDisco == 0) {
        std::cout << "Error: El disco no existe" << std::endl;
        return;
    }
    
    int totalBloques = tamanoDisco / TAMANO_BLOQUE;
    
    int bloquesNecesarios = (longitudTotal + 239) / 240;
    
    int bloquesLibres[100];
    int encontrados = 0;
    
    int totalSegmentos = tamanoDisco / TAMANO_SEGMENTO;

    for (int seg = 0; seg < totalSegmentos && encontrados < bloquesNecesarios; seg++) {

        char bitmap[2] = {0};

        leerBitmapSegmento(nombreArchivo, seg, bitmap);

        int inicioGlobal = seg * BLOQUES_POR_SEGMENTO;

        for (int local = 2; local < 16 && encontrados < bloquesNecesarios; local++) {

            int byteIndex = local / 8;
            int bitIndex = local % 8;

            if (!((bitmap[byteIndex] >> bitIndex) & 1)) {

                bloquesLibres[encontrados] = inicioGlobal + local;

                encontrados++;
            }
        }
    }
    
    if (encontrados < bloquesNecesarios) {

        std::cout << "Expandiendo disco" << std::endl;

        extenderDat(nombreArchivo);

        escribirStringEnBloquesLibres(nombreArchivo, nombreFigura, string);

        return;
    }
    
    std::cout << "Bloques asignados: ";
    for (int i = 0; i < bloquesNecesarios; i++) {
        std::cout << bloquesLibres[i] << " " << std::endl;
    }
    std::cout << std::endl;
    
    std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary);
    int bytesEscritos = 0;
    
    for (int i = 0; i < bloquesNecesarios; i++) {
        BloqueDatos bloque;
        memset(&bloque, 0, sizeof(BloqueDatos));
        
        int bytesEnEste = longitudTotal - bytesEscritos;
        if (bytesEnEste > 240) bytesEnEste = 240;
        
        memcpy(bloque.datos, string + bytesEscritos, bytesEnEste);
        
        if (i == bloquesNecesarios - 1) {
            bloque.siguienteBloque = EOF_VALOR;
        } else {
            bloque.siguienteBloque = bloquesLibres[i + 1];
        }
        
        archivo.seekp(bloquesLibres[i] * TAMANO_BLOQUE);
        archivo.write(reinterpret_cast<char*>(&bloque), sizeof(BloqueDatos));
        
        int segmento = obtenerSegmento(bloquesLibres[i]);

        int local = obtenerBloqueLocal(bloquesLibres[i]);

        char bitmap[2] = {0};

        leerBitmapSegmento(nombreArchivo, segmento, bitmap);

        int byteIndex = local / 8;
        int bitIndex = local % 8;

        bitmap[byteIndex] |= (1 << bitIndex);

        escribirBitmapSegmento(nombreArchivo, segmento, bitmap);
        
        bytesEscritos += bytesEnEste;
    }
    
    
    Inodo nuevoInodo;
    memset(&nuevoInodo, 0, sizeof(Inodo));
    strcpy(nuevoInodo.nombre, nombreFigura);
    nuevoInodo.tamano = longitudTotal;
    nuevoInodo.primerBloque = bloquesLibres[0];
    nuevoInodo.activo = 1;
    
    int inodoLibre = buscarInodoLibre(nombreArchivo);
    if (inodoLibre != -1) {
        int segInodo = obtenerSegmentoInodo(inodoLibre);

        int indiceLocal = obtenerIndiceLocalInodo(inodoLibre);

        escribirInodo(nombreArchivo, segInodo, indiceLocal, nuevoInodo);
        std::cout << "Figura guardada en " << bloquesNecesarios << " bloques" << std::endl;
    } else {
        std::cout << "Error: No hay inodos libres" << std::endl;
    }
    
    archivo.close();
}

// Funcion de modificar

void modificarFigura(const char* nombreArchivo, const char* nombreFigura, const char* nuevaFigura) {

    int indiceInodo = buscarInodoPorNombre(nombreArchivo, nombreFigura);

    if (indiceInodo == -1) {
        std::cout << "Error: Figura '" << nombreFigura << "' no encontrada" << std::endl;
        return;
    }

    std::cout << "\n=== FIGURA ACTUAL ===" << std::endl;
    leerFigura(nombreArchivo, nombreFigura);

    Inodo inodoActual;

    int segInodo = obtenerSegmentoInodo(indiceInodo);

    int indiceLocal = obtenerIndiceLocalInodo(indiceInodo);

    leerInodo(nombreArchivo, segInodo, indiceLocal, inodoActual);

    // Liberar bloques anteriores
    liberarBloques(nombreArchivo, inodoActual.primerBloque);

    int longitudTotal = strlen(nuevaFigura);

    // Cantidad de bloques necesarios
    int bloquesNecesarios = (longitudTotal + 239) / 240;

    int bloquesLibres[1000];
    int encontrados = 0;

    // Buscar bloques libres
    while (encontrados < bloquesNecesarios) {

        encontrados = 0;

        int tamanoDisco = obtenerTamanoDisco(nombreArchivo);

        int totalBloques = tamanoDisco / TAMANO_BLOQUE;

        for (int bloque = 0; bloque < totalBloques && encontrados < bloquesNecesarios; bloque++) {

            // Saltar bitmap e inodos
            if (bloque % 16 == 0 || bloque % 16 == 1) {
                continue;
            }

            int segmento = bloque / 16;

            char bitmap[16];

            leerBitmapSegmento(nombreArchivo, segmento, bitmap);

            int bloqueLocal = bloque % 16;

            int byteIndex = bloqueLocal / 8;
            int bitIndex = bloqueLocal % 8;

            if (!((bitmap[byteIndex] >> bitIndex) & 1)) {

                bloquesLibres[encontrados] = bloque;
                encontrados++;
            }
        }

        // Si todavía faltan bloques → expandir
        if (encontrados < bloquesNecesarios) {

            std::cout << "Expandiendo disco" << std::endl;

            extenderDat(nombreArchivo);
        }
    }

    std::cout << "Bloques nuevos asignados: ";

    for (int i = 0; i < bloquesNecesarios; i++) {
        std::cout << bloquesLibres[i] << " ";
    }

    std::cout << std::endl;

    std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary);

    int bytesEscritos = 0;

    for (int i = 0; i < bloquesNecesarios; i++) {

        BloqueDatos bloque;
        memset(&bloque, 0, sizeof(BloqueDatos));

        int bytesEnEste = longitudTotal - bytesEscritos;

        if (bytesEnEste > 240) {
            bytesEnEste = 240;
        }

        memcpy(bloque.datos, nuevaFigura + bytesEscritos, bytesEnEste);

        // Enlace
        if (i == bloquesNecesarios - 1) {
            bloque.siguienteBloque = EOF_VALOR;
        }
        else {
            bloque.siguienteBloque = bloquesLibres[i + 1];
        }

        // Escribir bloque
        archivo.seekp( bloquesLibres[i] * TAMANO_BLOQUE);

        archivo.write( reinterpret_cast<char*>(&bloque), sizeof(BloqueDatos));

        // Marcar bitmap
        int segmento = bloquesLibres[i] / 16;

        char bitmap[16];

        leerBitmapSegmento(nombreArchivo, segmento, bitmap);

        int bloqueLocal = bloquesLibres[i] % 16;

        int byteIndex = bloqueLocal / 8;

        int bitIndex = bloqueLocal % 8;

        bitmap[byteIndex] |= (1 << bitIndex);

        escribirBitmapSegmento(nombreArchivo, segmento, bitmap);

        bytesEscritos += bytesEnEste;
    }

    archivo.close();

    // Actualizar inodo
    inodoActual.tamano = longitudTotal;

    inodoActual.primerBloque = bloquesLibres[0];

    escribirInodo(nombreArchivo, segInodo, indiceLocal, inodoActual);

    std::cout << "\nFIGURA MODIFICADA" << std::endl;

    leerFigura(nombreArchivo, nombreFigura);
}

// Funcion de eliminar

void eliminarFigura(const char* nombreArchivo, const char* nombreFigura) {
    int indiceInodo = buscarInodoPorNombre(nombreArchivo, nombreFigura);
    if (indiceInodo == -1) {
        std::cout << "Error: Figura '" << nombreFigura << "' no encontrada" << std::endl;
        return;
    }
    
    Inodo inodo;
    int segInodo =
    obtenerSegmentoInodo(indiceInodo);

    int indiceLocal = obtenerIndiceLocalInodo(indiceInodo);

    leerInodo(nombreArchivo, segInodo, indiceLocal, inodo);
    liberarBloques(nombreArchivo, inodo.primerBloque);
    
    inodo.activo = 0;

    std::cout << "Figura '" << nombreFigura << "' eliminada correctamente" << std::endl;
}