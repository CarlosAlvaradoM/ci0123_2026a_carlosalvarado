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

#include <iostream>
#include <cstddef>
#include <cstdio>

#include <sys/socket.h>
#include <arpa/inet.h>		// ntohs, htons
#include <stdexcept>            // runtime_error
#include <cstring>		// memset
#include <netdb.h>		// getaddrinfo, freeaddrinfo
#include <unistd.h>		// close
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
void VSocket::Init( char t, bool ipv6 ){

   int st = -1;
   // Dominio para tipo de Ip
   int domain = ipv6 ? AF_INET6 : AF_INET;
   // TCP, UDP
   int type = (t == 's') ? SOCK_STREAM : SOCK_DGRAM;
   
   // Guardar en atributos
   this->type = t;
   this->IPv6 = ipv6;
   
   // Crear socket
   st = socket(domain, type, 0);
   
   if ( -1 == st ) {
      throw std::runtime_error( "VSocket::Init, socket creation failed" );
   }
   
   this->sockId = st;
}


/**
  * Class destructor
  *
 **/
VSocket::~VSocket() {

   this->Close();

}


/**
  * Close method
  *    use Unix close system call (once opened a socket is managed like a file in Unix)
  *
 **/
void VSocket::Close(){
   int st = -1;
   
   // Ver si es valido antes de cerrar
   if (this->sockId != -1) {
      st = close(this->sockId);
      
      if ( -1 == st ) {
         throw std::runtime_error( "VSocket::Close() close failed" );
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
int VSocket::TryToConnect( const char * hostip, int port ) {

   int st = -1;
   // IPv4
   struct sockaddr_in host4;
   
   // Limpiar estructura
   memset(&host4, 0, sizeof(host4));
   // Familia IPV4
   host4.sin_family = AF_INET;
   // Convertir puerto a network byte order
   host4.sin_port = htons(port);
   
   // Convertir IP
   if (inet_pton(AF_INET, hostip, &host4.sin_addr) <= 0) {
      throw std::runtime_error( "VSocket::TryToConnect invalid address" );
   }
   
   // Establecer conexion
   st = connect(this->sockId, (struct sockaddr *)&host4, sizeof(host4));
   
   if ( -1 == st ) {
      throw std::runtime_error( "VSocket::TryToConnect connect failed" );
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
int VSocket::TryToConnect( const char *host, const char *service ) {
   int st = -1;
   // hints, criterios de busqueda y res, resultados
   struct addrinfo hints, *res;
   
   // Criterios de busqueda
   memset(&hints, 0, sizeof(hints));
   hints.ai_family = this->IPv6 ? AF_INET6 : AF_INET;
   hints.ai_socktype = (this->type == 's') ? SOCK_STREAM : SOCK_DGRAM;
   
   // Nombre a IP
   st = getaddrinfo(host, service, &hints, &res);
   
   if (st != 0) {
      throw std::runtime_error( "VSocket::TryToConnect getaddrinfo failed" );
   }
   
   // Establecer conexion con la primera direccion obtenida
   st = connect(this->sockId, res->ai_addr, res->ai_addrlen);
   freeaddrinfo(res);
   
   if ( -1 == st ) {
      throw std::runtime_error( "VSocket::TryToConnect connect failed" );
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
int VSocket::Bind( int port ) {
   int st = -1;
   // IPv4
   struct sockaddr_in host4;
   
   // Configurar la estructura sockaddr_in
   memset(&host4, 0, sizeof(host4));
   // Famlia IPv4
   host4.sin_family = AF_INET;
   // Aceptar conexiones de cualquier interfaz
   host4.sin_addr.s_addr = htonl(INADDR_ANY);
   // Convertir puerto a network byte order
   host4.sin_port = htons(port);
   // Rellenar con ceros
   memset(host4.sin_zero, '\0', sizeof(host4.sin_zero));
   
   // Enlazar el socket al puerto
   st = bind(this->sockId, (struct sockaddr *)&host4, sizeof(host4));
   
   if ( -1 == st ) {
      throw std::runtime_error( "VSocket::Bind bind failed" );
   }
   
   // Puerto usado
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
size_t VSocket::sendTo( const void * buffer, size_t size, void * addr ) {
   int st = -1;
   
   // descriptor, datos, tamano, flags, direccion destino, tamano direccion
   st = sendto(this->sockId, buffer, size, 0, (struct sockaddr *)addr, sizeof(struct sockaddr_in));
   
   if ( -1 == st ) {
      throw std::runtime_error( "VSocket::sendTo sendto failed" );
   }

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
size_t VSocket::recvFrom( void * buffer, size_t size, void * addr ) {
   int st = -1;
   socklen_t addrlen = sizeof(struct sockaddr_in);
   
   // descriptor, buffer, tamano, flags, direccion origen, tamano direccion
   st = recvfrom(this->sockId, buffer, size, 0, (struct sockaddr *)addr, &addrlen);
   
   if ( -1 == st ) {
      throw std::runtime_error( "VSocket::recvFrom recvfrom failed" );
   }

   return st;

}

