# Sistema Cliente-Interceptor-Servidor

## Descripción

Programa en C++ que implementa un sistema de comunicación entre hilos usando un Interceptor como intermediario. Demuestra el uso de:

- **Mutex** para exclusión mutua
- **Semáforos** para sincronización
- **Colas** como buffers FIFO
- Múltiples hilos coordinados

### Flujo del programa

1. **Clientes** (3) solicitan nombres enviando un índice
2. **Interceptor** recibe, reenvía al servidor y retransmite respuestas
3. **Servidor** lee el nombre desde `nombres.txt` y responde

## Ejecución

```bash
# Ubicarse en el directorio src/
cd src/

# Compilar y generar ejecutable
make

# Ejecutar el programa
make run

# Limpiar archivos generados
make clean
```

## Ejemplo de salida

```
Servidor busca nombre #1
Interceptor recibe del servidor: Luis del cliente 0
Interceptor recibe solicitud de cliente 1
Servidor busca nombre #2
Cliente 0 recibe: Luis
Interceptor recibe del servidor: Carlos del cliente 1
Interceptor recibe solicitud de cliente 2
Servidor busca nombre #3
Cliente 1 recibe: Carlos
Interceptor recibe del servidor: Maria del cliente 2
Cliente 2 recibe: Maria
```
