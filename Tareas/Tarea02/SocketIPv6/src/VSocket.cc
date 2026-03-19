/**
 *  Universidad de Costa Rica
 *  ECCI
 *  CI0123 Proyecto integrador de redes y sistemas operativos
 *  2026-i
 *  Grupos: 2 y 3
 *
 ****** VSocket base class implementation
 *
 * (Fedora version)
 *
 **/

#include <sys/socket.h>
#include <arpa/inet.h> // ntohs, htons
#include <stdexcept>   // runtime_error
#include <cstring>     // memset
#include <netdb.h>     // getaddrinfo, freeaddrinfo
#include <unistd.h>    // close

#include <cstddef>
#include <cstdio>

// #include <sys/types.h>

#include "VSocket.h"

/**
 *  Class creator (constructor)
 *     use Unix socket system call
 *
 *  @param     char t: socket type to define
 *     's' for stream
 *     'd' for datagram
 *  @param     bool ipv6: if we need a IPv6 socket
 *
 **/
void VSocket::Init(char t, bool ipv6)
{

   int st = -1;
   // Dominio y tipo
   int domain = AF_INET6;
   int type = SOCK_DGRAM;

   // Atributos
   this->type = t;
   this->IPv6 = ipv6;

   this->addrLen = sizeof(struct sockaddr_in6);

   st = socket(domain, type, 0);

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::Init, socket creation failed");
   }

   this->sockId = st;
}

/**
 * Class destructor
 *
 **/
VSocket::~VSocket()
{

   this->Close();
}

/**
 * Close method
 *    use Unix close system call (once opened a socket is managed like a file in Unix)
 *
 **/
void VSocket::Close()
{
   int st = -1;

   if (this->sockId != -1)
   {
      st = close(this->sockId);

      if (-1 == st)
      {
         throw std::runtime_error("VSocket::Close() close failed");
      }

      this->sockId = -1;
   }
}

/**
 * TryToConnect method
 *   use "connect" Unix system call
 *
 * @param      char * host: host address in dot notation, example "10.84.166.62"
 * @param      int port: process address, example 80
 *
 **/
int VSocket::TryToConnect(const char *hostip, int port)
{

   int st = -1;

   // Estructura para dirección IPv6
   struct sockaddr_in6 host6;

   // Limpiar estructura
   memset(&host6, 0, sizeof(host6));
   // Familia de direcciones
   host6.sin6_family = AF_INET6;
   host6.sin6_port = htons(port);

   // Ip a txt
   if (inet_pton(AF_INET6, hostip, &host6.sin6_addr) <= 0)
   {
      throw std::runtime_error("VSocket::TryToConnect invalid IPv6 address");
   }

   // Establecer conexion
   st = connect(this->sockId, (struct sockaddr *)&host6, sizeof(host6));

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::TryToConnect connect failed");
   }

   return st;
}

/**
 * TryToConnect method
 *   use "connect" Unix system call
 *
 * @param      char * host: host address in dns notation, example "os.ecci.ucr.ac.cr"
 * @param      char * service: process address, example "http"
 *
 **/
int VSocket::TryToConnect(const char *host, const char *service)
{
   int st = -1;
   struct addrinfo hints, *res;

   // Configurar los criterios de busqueda para getaddrinfo()
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = this->IPv6 ? AF_INET6 : AF_INET;
   hints.ai_socktype = (this->type == 's') ? SOCK_STREAM : SOCK_DGRAM;

   // Nombre de host a direccion IP
   st = getaddrinfo(host, service, &hints, &res);

   if (st != 0)
   {
      throw std::runtime_error("VSocket::TryToConnect getaddrinfo failed");
   }

   // Establecer conexion con la primera direccion obtenida
   st = connect(this->sockId, res->ai_addr, res->ai_addrlen);
   freeaddrinfo(res);

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::TryToConnect connect failed");
   }

   return st;
}

/**
 * Bind method
 *    use "bind" Unix system call (man 3 bind) (server mode)
 *
 * @param      int port: bind a unamed socket to a port defined in sockaddr structure
 *
 *  Links the calling process to a service at port
 *
 **/
int VSocket::Bind(int port)
{
   int st = -1;

   // Estructura para direccion IPv6
   struct sockaddr_in6 host6;

   // Configurar la estructura sockaddr_in6 para el bind
   memset(&host6, 0, sizeof(host6));
   host6.sin6_family = AF_INET6;
   host6.sin6_addr = in6addr_any; // Listen on all IPv6 interfaces
   host6.sin6_port = htons(port);

   // Enlazar el socket al puerto
   st = bind(this->sockId, (struct sockaddr *)&host6, sizeof(host6));

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::Bind bind failed");
   }

   this->port = port;

   return st;
}

/**
 *  sendTo method
 *
 *  @param	const void * buffer: data to send
 *  @param	size_t size data size to send
 *  @param	void * addr address to send data
 *
 *  Send data to another network point (addr) without connection (Datagram)
 *
 **/
size_t VSocket::sendTo(const void *buffer, size_t size, void *addr)
{
   int st = -1;

   st = sendto(this->sockId, buffer, size, 0, (struct sockaddr *)addr, this->addrLen);

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::sendTo sendto failed");
   }

   // Bytes enviados
   return st;
}

/**
 *  recvFrom method
 *
 *  @param	const void * buffer: data to send
 *  @param	size_t size data size to send
 *  @param	void * addr address to receive from data
 *
 *  @return	size_t bytes received
 *
 *  Receive data from another network point (addr) without connection (Datagram)
 *
 **/
size_t VSocket::recvFrom(void *buffer, size_t size, void *addr)
{
   int st = -1;
   socklen_t addrlen = this->addrLen;

   st = recvfrom(this->sockId, buffer, size, 0, (struct sockaddr *)addr, &addrlen);

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::recvFrom recvfrom failed");
   }

   // bytes recibidos
   return st;
}
