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
    int alpha = 1;
    std::map<int, int> m;
    if (getCase(i_dst*getDimension()+j_dst).isEmpty()) {
        if (i_dst < i_src) {
            if (j_dst < j_src) {

                while ((i_dst + lambda) != i_src && j_dst + lambda != j_src) {
                    if (!getCase((i_dst + lambda)*getDimension()+j_dst + lambda).isEmpty() &&
                        c != getCase((i_dst + lambda)*getDimension()+j_dst + lambda).getPion().getColor()) {
                        m[(i_dst + lambda)] = j_dst + lambda;
                    } else if (c != getCase((i_dst + lambda)*getDimension()+j_dst + lambda).getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }

            } else if (j_dst > j_src) {
                while ((i_dst + lambda) != i_src && (j_dst - lambda) != j_src) {
                    if (!getCase((i_dst + lambda)*getDimension()+j_dst - lambda).isEmpty() &&
                        c != getCase((i_dst + lambda)*getDimension()+j_dst - lambda).getPion().getColor()) {
                        m[(i_dst + lambda)] = j_dst - lambda;
                    } else if (c != getCase((i_dst + lambda)*getDimension()+j_dst - lambda).getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }
            }
        } else if (i_dst > i_src) {
            if (j_dst < j_src) {

                while ((i_dst - lambda) != i_src && j_dst + lambda != j_src) {
                    if (!getCase((i_dst - lambda)*getDimension()+j_dst + lambda).isEmpty() &&
                        c != getCase((i_dst - lambda)*getDimension()+j_dst + lambda).getPion().getColor()) {
                        m[(i_dst - lambda)] = j_dst + lambda;
                    } else if (c != getCase((i_dst - lambda)*getDimension()+j_dst + lambda).getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }

            } else if (j_dst > j_src) {
                while ((i_dst - lambda) != i_src && (j_dst - lambda) != j_src) {
                    if (!getCase((i_dst - lambda)*getDimension()+j_dst - lambda).isEmpty() &&
                        c != getCase((i_dst - lambda)*getDimension()+j_dst - lambda).getPion().getColor()) {
                        m[(i_dst - lambda)] = j_dst - lambda;
                    } else if (c != getCase((i_dst - lambda)*getDimension()+j_dst - lambda).getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }
            }
        }
    } else {
        return false;
    }
    std::map<int,int>::iterator it;
    for(it = m.begin();it != m.end();++it){
        setCases(it->first*getDimension()+it->second, Pion());
    }
    return true;
}












