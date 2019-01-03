#include <iostream>
#include "Plateau.h"
#include "PlateauDamierInternational.h"
#include "PlateauStratego.h"
#include "PlateauEchiquier.h"
#include "PlateauDamierAnglais.h"

int main() {
    std::cout << "A quel jeu voulez vous jouer?" << std::endl;
    std::cout << "D pour dame, E pour Echec, S pour stratego" << std::endl;
    std::string rep = "";
    std::cin >> rep;
    if(rep == "D"){
        again1:
        std::cout << "I pour dame international, A pour dame anglaise" << std::endl;
        std::cin >> rep;
        if(rep == "I"){
            PlateauDamierInternational d;
            d.launcher();
        }else if(rep == "A"){
            PlateauDamierAnglais a;
            a.launcher();
        }else goto again1;
    }else if(rep == "E"){
        PlateauEchiquier p;
        again2:
        std::cout << "Voulez vous jouer avec un robot? Y/N" << std::endl;
        std::cin >> rep;
        if(rep == "Y") p.launchEchiquier(true);
        else if(rep == "N") p.launchEchiquier(false);
        else goto again2;
    }else if(rep == "S"){
        PlateauStratego s;
        again3:
        std::cout << "Voulez vous jouer avec un robot? Y/N" << std::endl;
        std::cin >> rep;
        if(rep == "Y") s.launchStratego(true);
        else if(rep == "N") s.launchStratego(false);
        else goto again3;
    }else{
    }
}