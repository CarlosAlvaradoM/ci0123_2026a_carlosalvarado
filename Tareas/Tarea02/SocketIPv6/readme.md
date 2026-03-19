# Cliente Socket IPv6 UDP

Este readme explica los pasos necesarios para ejecutar el cliente socket con direccionamiento IPv6.

## Instrucciones para ejecutar el cliente socket IPv6

Sigue estos pasos en orden para poner en funcionamiento el cliente con direccionamiento IPv6:

### 1. Compilar con el Makefile

En una terminal, compila los programas:

```bash
make
```
Este comando compila el código y genera los ejecutables `cliente` y `servidor`.

### 2. Ejecutar el servidor

Una vez compilado, ejecuta el programa servidor en terminal 1:

```bash
./servidor
```

### 3. Ejecutar el cliente

Una vez compilado, ejecuta el programa cliente en terminal 2:

```bash
./cliente
```

### 4. Verificar la conexión

Revisa que la conexión se haya realizado correctamente. Deberías ver mensajes de confirmación en las dos terminales.

