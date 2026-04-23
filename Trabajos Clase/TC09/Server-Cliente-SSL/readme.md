# Servidor SSL TCP (IPv4 / IPv6) con Threads y Fork

## Descripción

Este trabajo implementa un servidor seguro utilizando SSL/TLS sobre TCP, mediante:

* **Hilos (Threads)**
* **Procesos (Fork)**

Además, el servidor soporta:

* **IPv4**
* **IPv6**

---

### Activar IPv4 o IPv6

El servidor soporta IPv6 mediante un parámetro booleano:

```cpp
SSLSocket server("ci0123.pem", "key0123.pem", true); // IPv6
SSLSocket server("ci0123.pem", "key0123.pem", false); // IPv4
```
---


## Generar certificado

Ejecutar una vez:

```bash
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
-keyout key0123.pem -out ci0123.pem
```

---

## Compilación

```bash
make
```

Esto genera:

* `server_thread`
* `server_fork`
* `client`

---

## Ejecución

### Servidor con threads

```bash
./server_thread
```

### Servidor con fork

```bash
./server_fork
```

### Cliente

```bash
./client
```
