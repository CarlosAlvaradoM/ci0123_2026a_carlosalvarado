#include "Inodos.h"
#include <fstream>
#include <iostream>
#include <cstring>

struct Inodo {
    char nombre[9];  // Nombre del archivo  -- 9 bytes
    int tamano;  // Tamaño en bytes  -- 4 bytes
    short primerBloque;  // Bloque donde empieza  -- 2 bytes
    char activo;  // 1 = activo, 0 = libre  -- 1 byte
};

void convertirBloqueAInodo(const char* nombreArchivo, int bloqueAInodo) {
    std::fstream archivo(nombreArchivo, std::ios::in | std::ios::out | std::ios::binary);
    
    if (!archivo.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo" << std::endl;
        return;
    }
    
    // Bloque 1: posicion 256
    // Capacidad para 16 inodos (16 * 14 = 224 bytes) 32 bytes free
    // Pero se usaran solo 14, porque hay 14 bloques para datos
    
    Inodo inodosVacios[14];
    
    // Inicializar todos los inodos como libres
    for (int i = 0; i < 14; i++) {
        memset(inodosVacios[i].nombre, 0, 9);
        inodosVacios[i].tamano = 0;
        inodosVacios[i].primerBloque = 0;
        inodosVacios[i].activo = 0;
    }
    
    // Escribir en la posicion bloqueAInodo
    archivo.seekp(bloqueAInodo);
    archivo.write(reinterpret_cast<char*>(inodosVacios), bloqueAInodo);
    
    archivo.close();
    std::cout << "Bloque " << bloqueAInodo << " convertido a tabla de inodos. 14 inodos vacios." << std::endl;
}
