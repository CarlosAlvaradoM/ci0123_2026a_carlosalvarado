#ifndef MANIPULARDAT_H
#define MANIPULARDAT_H

// Estructura del Inodo (16 bytes)
struct Inodo {
    char nombre[8];  // Nombre de la figura
    int tamano;  // Tamano en bytes
    short primerBloque;  // Indice del bloque inicial
    short activo;  // 1 si esta en uso, 0 si esta libre
    char padding[2];  // Relleno para alinear a 16 bytes si es necesario
};


// Obtiene el tamano total del archivo en bytes
int obtenerTamanoDisco(const char* nombreArchivo);


// Lee los 2 bytes de bitmap de un segmento especifico
void leerBitmapSegmento(const char* nombreArchivo, int segmento, char* bitmap);

// Escribe los 2 bytes de bitmap de un segmento especifico
void escribirBitmapSegmento(const char* nombreArchivo, int segmento, char* bitmap);


// Lee un inodo especifico dentro de un segmento
void leerInodo(const char* nombreArchivo, int segmento, int indice, Inodo& inodo);

// Escribe un inodo especifico en un segmento
void escribirInodo(const char* nombreArchivo, int segmento, int indice, const Inodo& inodo);

// Busca un inodo por su nombre y devuelve su indice global
int buscarInodoPorNombre(const char* nombreArchivo, const char* nombreFigura);

// Busca el primer inodo con el flag activo en 0
int buscarInodoLibre(const char* nombreArchivo);

// Conversion de indices globales a locales
int obtenerSegmentoInodo(int inodoGlobal);
int obtenerIndiceLocalInodo(int inodoGlobal);


// Muestra el contenido de una figura en consola
void leerFigura(const char* nombreArchivo, const char* nombreFigura);

// Crea una nueva figura y reserva bloques usando la logica de segmentos
void escribirStringEnBloquesLibres(const char* nombreArchivo, const char* nombreFigura, const char* string);

// Reemplaza el contenido de una figura existente
void modificarFigura(const char* nombreArchivo, const char* nombreFigura, const char* nuevaFigura);

// Libera los bloques en el bitmap y marca el inodo como inactivo
void eliminarFigura(const char* nombreArchivo, const char* nombreFigura);

// Recorrer la lista de bloques y marcarlos como libres
void liberarBloques(const char* nombreArchivo, short primerBloque);

#endif