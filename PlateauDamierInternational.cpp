#include "PlateauDamierInternational.h"

PlateauDamierInternational::PlateauDamierInternational() : PlateauDamier(10) {
    setDimension(10);
}

const bool PlateauDamierInternational::playerTurn(int i_src, int j_src, int i_dst, int j_dst) {
    if (turn == 0) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);

        if (getCase(i_src*getDimension()+j_src).getPion().getNom() == "PION") {
            std::cout << "passe par la" << std::endl;
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC, false))) {

                return false;
            }
        } else if (getCase(i_src*getDimension()+j_src).getPion().getNom() == "KING") {
            if ((/* h.size() != 2 || */ !kingMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                return false;
            }
        }

    }
    turn += 1;
    return true;
}

const bool PlateauDamierInternational::playerTurn2(int i_src, int j_src, int i_dst, int j_dst) {
    if (turn == 1) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);

        if (getCase(i_src*getDimension()+j_src).getPion().getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                return false;
            }
        } else if (getCase(i_src*getDimension()+j_src).getPion().getNom() == "KING") {
            if ((!kingMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                return false;
            }
        }

    }
    turn -= 1;
    return true;
}


const bool PlateauDamierInternational::kingMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    int lambda = 1;
        if (i_dst < i_src) {
            i_dst++;
            if (j_dst < j_src) {
                j_dst++;

                while ((i_dst + lambda) != i_src && j_dst + lambda != j_src) {
                    if (!getCase((i_dst + lambda)*getDimension()+j_dst + lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst--;
                if(getCase((i_dst-1)*getDimension()+j_dst-1).isEmpty()){
                    i_dst--;
                    setCase(i_dst*getDimension()+j_dst, Pion());
                    setCase((i_dst-1)*getDimension()+j_dst-1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, Pion());
                    return true;
                }else return false;

            } else if (j_dst > j_src) {
                j_dst--;
                while ((i_dst + lambda) != i_src && (j_dst - lambda) != j_src) {
                    if (!getCase((i_dst + lambda)*getDimension()+j_dst - lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst++;
                if(getCase((i_dst-1)*getDimension()+j_dst+1).isEmpty()){
                    i_dst--;
                    setCase(i_dst*getDimension()+j_dst, Pion());
                    setCase((i_dst-1)*getDimension()+j_dst+1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, Pion());
                    return true;
                }else return false;
            }
            i_dst--;
        } else if (i_dst > i_src) {
            i_dst--;
            if (j_dst < j_src) {
                j_dst++;
                while ((i_dst - lambda) != i_src && j_dst + lambda != j_src) {
                    if (!getCase((i_dst - lambda)*getDimension()+j_dst + lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst--;
                std::cout << "ICIKING" << std::endl;
                if(getCase((i_dst+1)*getDimension()+j_dst-1).isEmpty()){
                    i_dst++;
                    std::cout << "LAKING" << std::endl;
                    setCase(i_dst*getDimension()+j_dst, Pion());
                    setCase((i_dst+1)*getDimension()+j_dst-1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, Pion());
                    return true;
                }else return false;

            } else if (j_dst > j_src) {
                j_dst--;
                while ((i_dst - lambda) != i_src && (j_dst - lambda) != j_src) {
                    if (!getCase((i_dst - lambda)*getDimension()+j_dst - lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst++;
                if(getCase((i_dst+1)*getDimension()+j_dst+1).isEmpty()){
                    i_dst++;
                    setCase(i_dst*getDimension()+j_dst, Pion());
                    setCase((i_dst+1)*getDimension()+j_dst+1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, Pion());
                    return true;
                }else return false;
            }
            i_dst++;
        }
        return false;
}












