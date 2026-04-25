# Funcionamineto

## Conexion

Conecte mi FS con el servidor, de modo que, en el ForkMirrorServer, se incluyen los archivos del FS, y se hace el llamado a las funciones necesarias segun el caso.

# Ejecucion

## Como ejecutarlo

En la terminal 1, ejecutar:
```bash 
./ForkMirrorServer
```
Que hace:
- Si hay un disco, lo lee y empieza a escuchar solicitudes
- Si no hay un disco, lo crea y empieza a escuchar solicitudes

En la terminal 2, ejecutar:
```bash
./MirrorClient "ListData"
```
o 

```bash
./MirrorCLient "GET 'animal'
```

Que hace:
- Se conecta con el server y pide lo que se solicita y lo muestra.
