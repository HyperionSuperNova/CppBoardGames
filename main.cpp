#include <iostream>
#include "Plateau.h"
#include "PlateauDamier.h"
#include "PlateauStratego.h"

int main() {

    //PlateauDamier p(10);
    PlateauStratego p;
    std::cout << p << std::endl;
    p.launchStratego(true);
    return 0;
}