//
// Created by stryker on 16/11/18.
//

#include "PlateauDamier.h"

PlateauDamier::PlateauDamier(int dimension) : Plateau(dimension) {}

std::ostream &operator<<(std::ostream &os, const PlateauDamier &damier) {
    os << static_cast<const Plateau &>(damier);
    return os;
}

const void PlateauDamier::initialize() const {
    Pion p("\u26C2");
    for(int i = 0; i < 3;i++){
        for(int j = 0; j < 10;j++){
            if(i%2 == 0){
                cases[i][j%2].setPion(p);
            }else if(j%2+1 <10){
                cases[i][j%2+1].setPion(p);
            }
        }
    }
    Pion p2("NOIR");
    for(int i = 7; i < dimension;i++){
        for(int j = 0; j < 10;j++){
            if(i%2 == 0){
                cases[i][j%2].setPion(p2);
            }else if(j%2+1 <10){
                cases[i][j%2+1].setPion(p2);
            }
        }
    }
}
