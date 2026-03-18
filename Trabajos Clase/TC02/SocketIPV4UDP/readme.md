# Cliente Socket IPv4 UDP

Este readme explica los pasos necesarios para ejecutar el cliente socket con direccionamiento IPv4.

## Instrucciones para ejecutar el cliente socket IPv4

Sigue estos pasos en orden para poner en funcionamiento el cliente con direccionamiento IPv4:

### 1. Configurar los parámetros de conexión en ipv4-udp-client.cc

Edita el archivo `ipv4-udp-client.cc` para configurar:
- Tu localhost (ej: 127.0.0.1)

### 2. Compilar con el Makefile

En una terminal, compila los programas:

```bash
make
```
Este comando compila el código y genera los ejecutables `cliente` y `servidor`.

### 3. Ejecutar el servidor

Una vez compilado, ejecuta el programa servidor en terminal 1:

```bash
./servidor
```

### 4. Ejecutar el cliente

Una vez compilado, ejecuta el programa cliente en terminal 2:

```bash
./cliente
```

### 5. Verificar la conexión

Revisa que la conexión se haya realizado correctamente. Deberías ver mensajes de confirmación en las dos terminales.

