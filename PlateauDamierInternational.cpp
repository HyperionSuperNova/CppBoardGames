#include "PlateauDamierInternational.h"

PlateauDamierInternational::PlateauDamierInternational() : PlateauDamier(10) {
    dimension = 10;
}


const void PlateauDamierInternational::playerTurn(int i_src, int j_src, int i_dst, int j_dst) {
    firstSelect:
    if (turn == 0) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);

        std::cout << "i_dst: " << i_dst << " et j_dst: " << j_dst << std::endl;
        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            std::cout << "passe par la" << std::endl;
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {

                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((/* h.size() != 2 || */ !kingMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                goto firstSelect;
            }
        }

    }
    turn += 1;
    return;
}


const void PlateauDamierInternational::playerTurn2(int i_src, int j_src, int i_dst, int j_dst) {
    firstSelect:
    if (turn == 1) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);

        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((!kingMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        }

    }
    turn -= 1;
    return;
}


const bool PlateauDamierInternational::kingMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    int lambda = 1;
    int alpha = 1;
    std::map<int, int> m;
    if (cases[i_dst][j_dst].isEmpty()) {
        if (i_dst < i_src) {
            if (j_dst < j_src) {

                while (i_dst + lambda != i_src && j_dst + lambda != j_src) {
                    if (!cases[i_dst + lambda][j_dst + lambda].isEmpty() &&
                        c != cases[i_dst + lambda][j_dst + lambda].getPion().getColor()) {
                        m[i_dst + lambda] = j_dst + lambda;
                    } else if (c != cases[i_dst + lambda][j_dst + lambda].getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }

            } else if (j_dst > j_src) {
                while (i_dst + lambda != i_src && (j_dst - lambda) != j_src) {
                    if (!cases[i_dst + lambda][j_dst - lambda].isEmpty() &&
                        c != cases[i_dst + lambda][j_dst - lambda].getPion().getColor()) {
                        m[i_dst + lambda] = j_dst - lambda;
                    } else if (c != cases[i_dst + lambda][j_dst - lambda].getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }
            }
        } else if (i_dst > i_src) {
            if (j_dst < j_src) {

                while (i_dst - lambda != i_src && j_dst + lambda != j_src) {
                    if (!cases[i_dst - lambda][j_dst + lambda].isEmpty() &&
                        c != cases[i_dst - lambda][j_dst + lambda].getPion().getColor()) {
                        m[i_dst - lambda] = j_dst + lambda;
                    } else if (c != cases[i_dst - lambda][j_dst + lambda].getPion().getColor()) {
                        return false;
                    }
                    lambda++;
                }

            } else if (j_dst > j_src) {
                while (i_dst - lambda != i_src && (j_dst - lambda) != j_src) {
                    if (!cases[i_dst - lambda][j_dst - lambda].isEmpty() &&
                        c != cases[i_dst - lambda][j_dst - lambda].getPion().getColor()) {
                        m[i_dst - lambda] = j_dst - lambda;
                    } else if (c != cases[i_dst - lambda][j_dst - lambda].getPion().getColor()) {
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
        cases[it->first][it->second] = Case(it->first,it->second);
    }
    return true;
}













