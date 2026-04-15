# Borrador con mejoras para el FileSystem

Este readme contiene las ideas de las correcciones que se le van a aplicar al FileSystem.

## A eliminar

Se va a eliminar el sector de arranque, ya que no es necesario para efectos del curso.
Tambien, la tabla de particiones se va a eliminar, ya que se asume que el espacio en disco con el que se va a trabajar cuenta con solo una particion
El apartado de super bloque tambien, ya que no es necesario para el curso.

## A mantener

BitMap, tabla de metadatos y bloque de datos.

## A analizar y colocar en el protocolo formal

Si unifico la funcion de BitMap y metadatos. Tambien pensar si puedo llegar a usar la cabeza de los punteros.