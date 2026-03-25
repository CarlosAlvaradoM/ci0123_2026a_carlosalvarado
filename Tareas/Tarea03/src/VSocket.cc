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
#include <errno.h>
#include <stdio.h>
#include <net/if.h> // Para if_nametoindex
/*
#include <cstddef>
#include <cstdio>

//#include <sys/types.h>
*/
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
void VSocket::Init(char t, bool IPv6)
{

   // Atributos
   int st = -1;
   this->type = t;
   this->IPv6 = IPv6;

   // IPV6
   int domain = IPv6 ? AF_INET6 : AF_INET;
   int socktype = (t == 's') ? SOCK_STREAM : SOCK_DGRAM;

   // Socket
   st = socket(domain, socktype, 0);

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::BuildSocket, socket creation failed");
   }

   this->sockId = st;
}

/**
 *  Initialize with existing socket descriptor
 *
 *  @param     int id: existing socket descriptor
 *
 **/
void VSocket::Init(int id)
{
   this->sockId = id;
   this->type = 's'; // Assume stream by default
   this->IPv6 = false;
   // We don't create a new socket, just use the existing one
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
         throw std::runtime_error("VSocket::Close()");
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

   struct sockaddr_in6 addr6;
   memset(&addr6, 0, sizeof(addr6));
   addr6.sin6_family = AF_INET6;
   addr6.sin6_port = htons(port);

   char ipv6_addr[128];
   strncpy(ipv6_addr, hostip, sizeof(ipv6_addr) - 1);

   // Buscar la interfaz después del %
   char *percent = strchr(ipv6_addr, '%');
   if (percent)
   {
      *percent = '\0';
      // Obtener el indice de la interfaz
      addr6.sin6_scope_id = if_nametoindex(percent + 1);
      if (addr6.sin6_scope_id == 0)
      {
         printf("Interfaz no encontrada: %s\n", percent + 1);
         throw std::runtime_error("VSocket::TryToConnect, invalid interface");
      }
   }

   // Convertir la direccion IPv6
   if (inet_pton(AF_INET6, ipv6_addr, &addr6.sin6_addr) <= 0)
   {
      throw std::runtime_error("VSocket::TryToConnect, invalid IPv6 address");
   }

   st = connect(this->sockId, (struct sockaddr *)&addr6, sizeof(addr6));

   if (-1 == st)
   {
      perror("connect");
      throw std::runtime_error("VSocket::TryToConnect, connection failed");
   }

   this->port = port;
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

   memset(&hints, 0, sizeof(hints));

   // IPV6
   hints.ai_family = AF_INET6;
   hints.ai_socktype = (this->type == 's') ? SOCK_STREAM : SOCK_DGRAM;

   // Obtener informacion de direccion
   st = getaddrinfo(host, service, &hints, &res);
   if (st != 0)
   {
      throw std::runtime_error("VSocket::TryToConnect, getaddrinfo failed (IPv6)");
   }

   // Intentar la conexion
   st = connect(this->sockId, res->ai_addr, res->ai_addrlen);

   // Liberar la memoria
   freeaddrinfo(res);

   if (-1 == st)
   {
      throw std::runtime_error("VSocket::TryToConnect, connection failed");
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
   struct sockaddr_in addr;

   memset(&addr, 0, sizeof(addr));
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = INADDR_ANY;

   st = bind(this->sockId, (struct sockaddr *)&addr, sizeof(addr));

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

   st = sendto(this->sockId, buffer, size, 0, (struct sockaddr *)addr, sizeof(struct sockaddr_in));

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
   socklen_t addrlen = sizeof(struct sockaddr_in);

   st = recvfrom(this->sockId, buffer, size, 0, (struct sockaddr *)addr, &addrlen);

   return st;
}
