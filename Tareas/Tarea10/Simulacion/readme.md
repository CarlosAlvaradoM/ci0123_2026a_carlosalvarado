# Sistema de Comunicación Cliente-Interceptor-Servidor

## Descripción

Simulación del protocolo

- **Clientes**: Envían mensajes al sistema y esperan respuestas
- **Interceptor**: Actúa como intermediario, reenviando mensajes entre clientes y servidor
- **Servidor**: Procesa los mensajes y genera respuestas según el comando recibido

## Arquitectura

```
Clientes → Interceptor → Servidor → Interceptor → Clientes
```

## Mecanismos de Sincronización

- **Mutex**: Protegen el acceso a colas compartidas y salida por consola
- **Semáforos**: Coordinan la comunicación entre hilos
- **Barreras**: Sincronizan fases de procesamiento

## Protocolo de Mensajes

Formato: `P/[comando]/[datos]`

- `R`: Read - Solicita lectura de datos
- `G`: Get - Solicita obtener información
- `A`: Acknowledge - Respuesta genérica
- `D`: Data - Respuesta con datos

## Compilación

```bash
make
```

## Ejecución

```bash
make run
```

## Flujo de Trabajo

1. Todos los clientes se preparan y envían sus mensajes
2. El interceptor recopila los mensajes y los reenvía al servidor
3. El servidor procesa cada mensaje y genera respuestas
4. El interceptor distribuye las respuestas a los clientes correspondientes
5. Cada cliente muestra su respuesta recibida