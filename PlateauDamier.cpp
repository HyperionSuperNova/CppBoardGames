#include "PlateauDamier.h"

PlateauDamier::PlateauDamier(int dimension) : Plateau(dimension) {}

std::ostream &operator<<(std::ostream &os, const PlateauDamier &damier) {
    os << static_cast<const Plateau &>(damier);
    return os;
}

const void PlateauDamier::initialize() const {
    Pion p("PION", "\u26C0", Couleur::NOIR);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    cases[i][j].setPion(p);
                }
            } else {
                if (j % 2 != 0) {
                    cases[i][j].setPion(p);
                }
            }
        }
    }
    Pion p2("PION", "\u26C2", Couleur::BLANC);
    for (int i = 7; i < dimension; i++) {
        for (int j = 0; j < 10; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    cases[i][j].setPionBis(p2);
                }
            } else {
                if (j % 2 != 0) {
                    cases[i][j].setPionBis(p2);
                }
            }
        }
    }
}


const bool PlateauDamier::posOk(int i_src, int j_src, int i_dst, int j_dst) const {
    bool cartesianConstraint =i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension && i_dst >= 0 && i_dst < dimension && j_dst >= 0 && j_dst < dimension;
    return cartesianConstraint;
}

const void PlateauDamier::pionMove(int i_src, int j_src, int i_dst, int j_dst) {
    if(posOk(i_src,j_src,i_dst,j_dst)){
        if(cases[i_src][j_src].getPion().getColor() == Couleur::BLANC){
            if(i_dst == i_src - 1 && ((j_dst == j_src +1 ) || j_dst == j_src -1)){
                if(!cases[i_dst][j_dst].isEmpty() && cases[i_dst][j_dst].getPion().getColor() == Couleur::NOIR){
                    scoreJ1+=1;
                    cases[i_dst][j_dst] = Case(i_dst,j_dst);
                }
                move(i_src,j_src,i_dst,j_dst);
            }else{
                std::cout << "Illegal movement" << std::endl;
            }
        }else if(cases[i_src][j_src].getPion().getColor() == Couleur::NOIR){
            if(i_dst == i_src + 1 && ((j_dst == j_src +1 ) || j_dst == j_src -1)){
                if(!cases[i_dst][j_dst].isEmpty() && cases[i_dst][j_dst].getPion().getColor() == Couleur::BLANC){
                    scoreJ2+=1;
                    cases[i_dst][j_dst] = Case(i_dst,j_dst);
                }
                move(i_src,j_src,i_dst,j_dst);
            }else{
                std::cout << "Illegal movement" << std::endl;
            }
        }else{
            std::cout << "Illegal movement" << std::endl;
        }
    }else{
        std::cout << "Illegal movement" << std::endl;
    }
}


