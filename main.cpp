#include <iostream>
#include "Plateau.h"
#include "PlateauDamier.h"
#include "PlateauStratego.h"

int main() {

    /*
    PlateauDamier p(10);
    p.initialize();
    std::cout << p << std::endl;
    p.pionMove(2,0,3,1, Couleur::NOIR);
    p.pionMove(3,1,4,2, Couleur::NOIR);
    p.pionMove(4,2,5,3, Couleur::NOIR);
    p.pionMove(5,3,6,4, Couleur::NOIR);
    p.pionMove(6,4,7,5, Couleur::NOIR);
    std::cout << p << std::endl;
    std::cout << "Score J1 : "  << p.scoreJ1 << "\n Score J2 : " << p.scoreJ2 << std::endl;
    std::string s;
    std::cin>>s;
    std::cout << s << std::endl;
    p.launcher();
    std::cout << p << std::endl;
     */
    PlateauStratego p;
    p.launchStratego(true);
}