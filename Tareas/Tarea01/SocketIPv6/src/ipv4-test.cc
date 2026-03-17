/**
  *  Universidad de Costa Rica
  *  ECCI
  *  CI0123 Proyecto integrador de redes y sistemas operativos
  *  2026-i
  *  Grupos: 2 y 3
  *
  *
  *  Ejemplo de sockets con IPv4
  *
 **/

#include <stdio.h>
#include <string.h>

#include "VSocket.h"
#include "Socket.h"

int main( int argc, char * argv[] ) {
   // Mi direccion IPv4
   const char* miIPv4 = "192.168.7.4";
   // Puerto del server
   int puerto = 8080;

   // Peticion HTTP para /ip
   const char* peticion = "GET /ip HTTP/1.1\r\nHost: 192.168.7.4\r\nConnection: close\r\n\r\n";

   const char * os = "http://os.ecci.ucr.ac.cr/";
   const char * osi = "10.84.166.62";
   const char * ose = "163.178.104.62";
   const char * elephant = (char *) "GET /lego/list.php?figure=elephant&part=1\r\nHTTP/v1.1\r\nhost: redes.ecci\r\n\r\n";

   VSocket * s;	
   char a[512];

   s = new Socket( 's', false );

   s->Connect( miIPv4, puerto );	// usar "osi" en la ECCI, "ose" de sus casas  osi, 80
   s->Write( peticion );  // elephant
   s->Read( a, 512 );
   printf( "%s\n", a);

}