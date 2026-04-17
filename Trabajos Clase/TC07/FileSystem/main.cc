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

    // Figura caballo OS
    escribirStringEnBloquesLibres("figuras.dat", "caballo", 
        "1 brick 2x2 yellow\n"
        "4 brick 2x4 white\n"
        "2 brick 2x4 yellow\n"
        "1 brick 2x6 yellow\n"
        "1 brick 2x3 yellow\n"
        "2 brick 1x1 yellow eye\n"
        "2 brick 2x1 yellow\n"
        "1 brick 2x2 white"
    );

    // Figura con 754 bytes aproximadamente, requiere 3-4 bloques de 256 bytes
    escribirStringEnBloquesLibres("figuras.dat", "gotica", 
        "12 brick 2x4 light_gray base\n"
        "8 brick 2x10 dark_gray foundation\n"
        "24 brick 1x2 light_gray main_wall\n"
        "16 brick 1x4 light_gray side_wall\n"
        "4 slope 2x2 45_deg dark_gray roof\n"
        "8 slope 1x2 45_deg dark_gray roof_edge\n"
        "2 cone 1x1 light_gray spire_top\n"
        "6 cylinder 1x1 trans_blue window\n"
        "1 arch 1x6x2 light_gray main_entrance\n"
        "4 plate 4x6 dark_gray floor_section\n"
        "2 door 1x4x6 brown main_gate\n"
        "10 tile 1x1 white floor_pattern\n"
        "10 tile 1x1 black floor_pattern\n"
        "8 brick 1x1x5 light_gray pillar\n"
        "4 modified_brick 1x1_with_stud light_gray\n"
        "12 technic_brick 1x2 light_gray support\n"
        "2 dish 2x2 trans_clear rose_window\n"
        "16 brick 2x2 dark_gray buttress\n"
        "8 plate 1x1 gold decorative_trim\n"
        "1 flag 2x2 blue kingdom_banner\n"
        "1 fence 1x4x2 black garden_wall\n"
        "4 slope_inverted 2x2 light_gray cornice\n"
        "6 brick 1x1 trans_yellow altar_light\n"
        "2 ladder 1x2x10 silver bell_tower\n"
        "1 bell 2x2 gold tower_interior\n"
        "12 brick 1x3 light_gray clerestory\n"
        "4 wedge_plate 4x4 light_gray corner\n"
        "8 brick 1x1 light_gray crenelation\n"
        "2 hinge_brick 1x2 light_gray transept\n"
        "1 baseplate 16x16 green landscape"
    );

    // Lectura
    std::cout << "\nCabllo:\n";
    leerFigura("figuras.dat", "caballo");

    std::cout << "\nGotica:\n";
    leerFigura("figuras.dat", "gotica");
    
    return 0;
}
