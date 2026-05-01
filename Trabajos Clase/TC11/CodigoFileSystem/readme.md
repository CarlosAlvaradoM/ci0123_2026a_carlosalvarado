# Simulador de FileSystem

Sistema de archivos simulado usando un archivo `.dat` como disco.

## Características

- Disco inicial de 4 KiB
- Bloques de 256 bytes
- Bitmap para control de bloques libres
- Tabla de inodos/metadatos
- Sistema enlazado de bloques
- Lectura, escritura
- Expansión dinámica del disco
- Soporte para múltiples segmentos de almacenamiento

---

# Estructura del Disco

Distribución:

| Bloque | Uso |
|---|---|
| 0 | Bitmap |
| 1 | Tabla de inodos |
| 2 - 15 | Bloques de datos |

Cada expansión agrega un nuevo segmento con la misma estructura.

---

# Sistema de Bloques

Los bloques de datos usan estructura enlazada:

```cpp
struct BloqueDatos {
    char datos[240];
    short siguienteBloque;
};
```

Cada bloque apunta al siguiente bloque de la figura.

---

# Inodos

Cada figura posee un inodo:

```cpp
struct Inodo {
    char nombre[9];
    int tamano;
    short primerBloque;
    char activo;
};
```

--- 

# Funcionalidades

## Crear disco

```bash
crearDat("figuras.dat");
```

---

## Extender disco

```bash
extenderDat("figuras.dat");
```

Agrega automáticamente otro segmento de 4 KiB.

---

## Guardar figura

```bash
escribirStringEnBloquesLibres(...)
```

---

## Leer figura

```bash
leerFigura(...)
```

---

# Compilación

```bash
make
```

---

# Ejecución

```bash
make run
```

---

# Autor

Carlos Alvarado Meneses