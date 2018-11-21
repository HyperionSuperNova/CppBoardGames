#include <iostream>
#include "Plateau.h"
#include "PlateauDamier.h"
#include "PlateauStratego.h"

int main() {

    PlateauDamier p(10);
    p.initialize();
    std::cout << p << std::endl;
    p.pionMove(2,0,3,1);
    p.pionMove(3,1,4,2);
    p.pionMove(4,2,5,3);
    p.pionMove(5,3,6,4);
    p.pionMove(6,4,7,5);
    std::cout << p << std::endl;
    std::cout << "Score J1 : "  << p.scoreJ1 << "\n Score J2 : " << p.scoreJ2 << std::endl;

}