#include "CrearDat.h"
#include "ManipularDat.h"
#include <fstream>
#include <iostream>
#include <cstring>

void crearDat(const char* nombreArchivo) {

    // Tamano total del disco 4096 bytes
    int tamanoTotal = 4096;
    
    // Tamano de los bloques - 16 bloques
    int totalBloques = tamanoTotal / 256;
    
    // Crear archivo
    std::ofstream archivo(nombreArchivo, std::ios::binary);
    
    // Verificar
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo crear el archivo" << std::endl;
        return;
    }
    
    // Crear archivo lleno de ceros
    char cero = 0;
    for (int i = 0; i < tamanoTotal; i++) {
        archivo.write(&cero, 1);
    }
    
    // Cerrar archivo
    archivo.close();

    // Consola
    std::cout << "Archivo " << nombreArchivo << " creado." << std::endl;
    std::cout << "  Tamano: " << tamanoTotal << std::endl;
    std::cout << "  Bloques: " << totalBloques << " (cada uno de 256 bytes)" 
        << std::endl;
}

// Funcion para agregar
void extenderDat(const char* nombreArchivo){

    int tamanoActual =
        obtenerTamanoArchivo(nombreArchivo);

    std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary | std::ios::app);

    if (!archivo.is_open()) {

        std::cout << "Error abriendo archivo" << std::endl;

        return;
    }

    char buffer[4096] = {0};

    archivo.write(buffer, 4096);

    archivo.close();

    int nuevoSegmento = tamanoActual / 4096;

    std::fstream archivo2(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary);

    char bitmap[2] = {0};

    bitmap[0] |= (1 << 0);
    bitmap[0] |= (1 << 1);

    int posicionBitmap = nuevoSegmento * 4096;

    archivo2.seekp(posicionBitmap);

    archivo2.write(bitmap, 2);

    Inodo inodos[14];

    for (int i = 0; i < 14; i++) {

        memset(inodos[i].nombre, 0, 9);

        inodos[i].tamano = 0;

        inodos[i].primerBloque = 0;

        inodos[i].activo = 0;
    }

    int posicionInodos = posicionBitmap + 256;

    archivo2.seekp(posicionInodos);

    archivo2.write(reinterpret_cast<char*>(inodos), sizeof(inodos));

    archivo2.close();

    std::cout << "Disco expandido con nuevo segmento" << std::endl;
}

// Obtener tamano del archivo en bytes
long long obtenerTamanoArchivo(const char* nombreArchivo) {
    std::ifstream archivo(nombreArchivo, std::ios::binary | std::ios::ate);
    
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo" << std::endl;
        return -1;
    }
    
    long long tamano = archivo.tellg();
    archivo.close();
    return tamano;
}