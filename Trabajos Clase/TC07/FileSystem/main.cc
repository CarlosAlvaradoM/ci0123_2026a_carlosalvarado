#include "CrearDat.h"
#include "BitMap.h"
#include "Inodos.h"
#include "Bloques.h"
#include "ManipularDat.h"
#include <string>
#include <iostream>

int main() {
    // Crear y formatear el disco
    crearDat("figuras.dat");
    convertirBloque0ABitmap("figuras.dat");
    convertirBloque1AInodo("figuras.dat");
    limpiarBloquesDesde2("figuras.dat");

    // Figura grande, necesita varios bloques
    // Figura con 700-800 bytes, necesita 3-4 bloques
    escribirStringEnBloquesLibres("figuras.dat", "dragon", 
        "                              __====-_  _-====___\n"
        "                     _--^^^#####//      \\#####^^^--_\n"
        "                  _-^##########// (    ) \\##########^-_\n"
        "                 -############//  |\\^^/|  \\############-\n"
        "               _/############//   (@::@)   \\############\\_\n"
        "              /#############((     \\//     ))#############\\\n"
        "             -###############\\    (oo)    //###############-\n"
        "            -#################\\  / UUU \\  //#################-\n"
        "            -###################\\/  (_)  \\/###################-\n"
        "           _#/|##########/#####\\  (   )  /#####\\##########|\\#_\n"
        "           |/ |############\\####/     \\  \\####/############| \\|\n"
        "           /   \\############/ \\     (     ) \\  \\############/   \\\n"
        "          /     \\#########/   \\     U     /   \\  \\#########/     \\\n"
        "         /       \\######/     \\     :     /     \\  \\######/       \\\n"
        "        /         \\####/       \\_____:_____/       \\  \\####/         \\\n"
        "       /           \\##/         \\_____/             \\  \\##/           \\\n"
        "      /             \\/                             \\  \\/             \\\n"
        "     /                                                               \\\n"
        "    /                                                                 \\\n"
        "   /                                                                   \\\n"
        "  /                                                                     \\\n"
        " /                                                                       \\\n"
        "/                                                                         \\\n"
        "\\                                                                         /\n"
        " \\                                                                       /\n"
        "  \\                                                                     /\n"
        "   \\                                                                   /\n"
        "    \\                                                                 /\n"
        "     \\                                                               /\n"
        "      \\                                                             /\n"
        "       \\                                                           /\n"
        "        \\                                                         /\n"
        "         \\                                                       /\n"
        "          \\                                                     /\n"
        "           \\                                                   /\n"
        "            \\                                                 /\n"
        "             \\                                               /\n"
        "              \\                                             /\n"
        "               \\                                           /\n"
        "                \\                                         /\n"
        "                 \\                                       /\n"
        "                  \\                                     /\n"
        "                   \\                                   /\n"
        "                    \\                                 /\n"
        "                     \\                               /\n"
        "                      \\                             /\n"
        "                       \\                           /\n"
        "                        \\                         /\n"
        "                         \\                       /\n"
        "                          \\                     /\n"
        "                           \\                   /\n"
        "                            \\                 /\n"
        "                             \\               /\n"
        "                              \\             /\n"
        "                               \\           /\n"
        "                                \\         /\n"
        "                                 \\       /\n"
        "                                  \\     /\n"
        "                                   \\   /\n"
        "                                    \\ /\n"
        "                                     V\n");
    
    // Leer la figura
    std::cout << "\nLEYENDO FIGURA GRANDE\n";
    leerFigura("figuras.dat", "dragon");
    
    return 0;
}
