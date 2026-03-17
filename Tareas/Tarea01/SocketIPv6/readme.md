# Cliente Socket IPv6

Este readme explica los pasos necesarios para ejecutar el cliente socket con direccionamiento IPv6.

## Requisitos Previos

- Python 3 instalado en el sistema
- Servidor socket Python proporcionado por los docentes
- Makefile y archivo `ipv6-test.cc` en el directorio
- Acceso a terminal/consola

## Instrucciones para ejecutar el cliente socket IPv4

Sigue estos pasos en orden para poner en funcionamiento el cliente con direccionamiento IPv6:

### 1. Correr el servidor Python

Inicia el servidor socket en una terminal:

```bash
python3 server.py
```

### 2. Configurar los parámetros de conexión

Edita el archivo `ipv6-test.cc` para configurar:
- Tu dirección IPv6
- Tu puerto (el mismo que utiliza el servidor)
- El request

### 3. Compilar con el Makefile

En otra terminal, compila el programa cliente:

```bash
make
```
Este comando compila el código y genera el ejecutable `ipv6-testout`.

### 4. Ejecutar el cliente

Una vez compilado, ejecuta el programa cliente:

```bash
./ipv6-testout
```

### 5. Verificar la conexión

Revisa que la conexión se haya realizado correctamente. Deberías ver mensajes de confirmación tanto en el cliente como en el servidor indicando que la comunicación se estableció exitosamente.


