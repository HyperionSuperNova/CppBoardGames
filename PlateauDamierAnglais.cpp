#include "PlateauDamierAnglais.h"

PlateauDamierAnglais::PlateauDamierAnglais() : PlateauDamier(8) {
    dimension = 8;
}


const bool PlateauDamierAnglais::playerTurn(int i_src, int j_src, int i_dst, int j_dst) {
    if (turn == 0) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);

        if (cases[i_src*dimension+j_src].getPion().getNom() == "PION") {
            std::cout << "passe par la" << std::endl;
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                return false;
            }
        } else if (cases[i_src*dimension+j_src].getPion().getNom() == "KING") {
            if ((/* h.size() != 2 || */ !kingMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                return false;
            }
        }

    }
    turn += 1;
    return true;
}

const bool PlateauDamierAnglais::playerTurn2(int i_src, int j_src, int i_dst, int j_dst) {
    if (turn == 1) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);

        if (cases[i_src*dimension+j_src].getPion().getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                return false;
            }
        } else if (cases[i_src*dimension+j_src].getPion().getNom() == "KING") {
            if ((/* h.size() != 2 || */ !kingMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                return false;
            }
        }

    }
    turn -= 1;
    return true;
}

const bool PlateauDamierAnglais::kingMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    if(posOk(i_src, j_src, i_dst, j_dst)){
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                Couleur bon = Couleur::NOIR;
                if(c == Couleur::NOIR) bon = Couleur::BLANC;
                if (!cases[i_dst*dimension+j_dst].isEmpty() && cases[i_dst*dimension+j_dst].getPion().getColor() == bon) {

                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0 && i_dst-1 >= 0) {
                        if (cases[(i_dst - 1)*dimension+j_dst + 1].isEmpty()) {
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst - 1), j_dst + 1);
                            if(c == Couleur::BLANC) scoreJ1++;
                            else scoreJ2++;
                            bool l = pionMove((i_dst - 1), j_dst + 1, i_dst - 2, j_dst, c, true);
                            bool ld = pionMove((i_dst - 1), j_dst + 1, i_dst - 2, j_dst + 1+1, c, true);
                            bool rd = pionMove((i_dst - 1), j_dst + 1, i_dst, j_dst, c, true);
                            bool r = pionMove((i_dst - 1), j_dst + 1, i_dst, j_dst + 1 + 1, c, true);

                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0 && i_dst-1 >= 0) {
                        if (cases[(i_dst - 1)*dimension+j_dst - 1].isEmpty()) {
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst - 1), j_dst - 1);
                            if(c == Couleur::BLANC) scoreJ1++;
                            else scoreJ2++;
                            bool l = pionMove((i_dst - 1), j_dst - 1, i_dst - 2, j_dst - 1-1, c, true);
                            bool ld = pionMove((i_dst - 1), j_dst - 1, i_dst - 2, j_dst, c, true);
                            bool rd = pionMove((i_dst - 1), j_dst - 1, i_dst, j_dst - 1 - 1, c,true);
                            bool r = pionMove((i_dst - 1), j_dst - 1, i_dst, j_dst, c, true);
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (i_dst == i_src + 1) {

                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && i_dst+1 < dimension) {
                        if (cases[(i_dst + 1)*dimension+j_dst + 1].isEmpty()) {

                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst + 1), j_dst + 1);
                            if(c == Couleur::BLANC) scoreJ1++;
                            else scoreJ2++;
                            bool l = pionMove((i_dst - 1), j_dst + 1, i_dst - 2, j_dst, c, true);
                            bool ld = pionMove((i_dst - 1), j_dst + 1, i_dst - 2, j_dst + 1+1, c, true);
                            bool rd = pionMove((i_dst - 1), j_dst + 1, i_dst, j_dst, c, true);
                            bool r = pionMove((i_dst - 1), j_dst + 1, i_dst, j_dst + 1 + 1, c, true);
                        } else if(cases[i_dst*dimension+j_dst].isEmpty()) {
                            move(i_src, j_src, i_dst, j_dst);
                            return true;
                        }else{
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 >= 0) {

                        if (cases[(i_dst + 1)*dimension+j_dst - 1].isEmpty()) {
                            if(c == Couleur::BLANC) scoreJ1 += 1;
                            else scoreJ2 += 2;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst + 1), j_dst - 1);
                            bool l = pionMove((i_dst - 1), j_dst - 1, i_dst - 2, j_dst - 1 - 1, c, true);
                            bool ld = pionMove((i_dst - 1), j_dst - 1, i_dst - 2, j_dst, c, true);
                            bool rd = pionMove((i_dst - 1), j_dst - 1, i_dst, j_dst - 1 - 1, c, true);
                            bool r = pionMove((i_dst - 1), j_dst - 1, i_dst, j_dst, c, true);
                        } else if(cases[i_dst*dimension+j_dst].isEmpty()) {
                            move(i_src, j_src, i_dst, j_dst);
                            return true;
                        }else {
                            return false;
                        }
                    } else if (i_dst == i_src - 1) {
                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                        if (cases[(i_dst - 1)*dimension+j_dst + 1].isEmpty()) {
                            if(c == Couleur::BLANC) scoreJ1 += 1;
                            else scoreJ2 += 2;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst - 1), j_dst + 1);
                            bool l = pionMove((i_dst - 1), j_dst + 1, (i_dst - 1), j_dst - 1, c, true);
                            bool ld = pionMove((i_dst - 1), j_dst + 1, (i_dst - 1), j_dst + 1, c, true);
                            bool rd = pionMove((i_dst - 1), j_dst + 1, (i_dst + 1), j_dst - 1, c, true);
                            bool r = pionMove((i_dst - 1), j_dst + 1, (i_dst + 1), j_dst + 1, c, true);
                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                        if (cases[(i_dst - 1)*dimension+j_dst - 1].isEmpty()) {
                            if(c == Couleur::BLANC) scoreJ1 += 1;
                            else scoreJ2 += 2;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst - 1), j_dst - 1);
                            bool l = pionMove((i_dst - 1), j_dst - 1, (i_dst - 1), j_dst - 1, c, true);
                            bool ld = pionMove((i_dst - 1), j_dst - 1, (i_dst - 1), j_dst + 1, c, true);
                            bool rd = pionMove((i_dst - 1), j_dst - 1, (i_dst + 1), j_dst - 1, c,true);
                            bool r = pionMove((i_dst - 1), j_dst - 1, (i_dst + 1), j_dst + 1, c, true);
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (cases[i_dst*dimension+j_dst].isEmpty() && i_dst == i_src - 1) {
                    move(i_src, j_src, i_dst, j_dst);
                    return true;
                    } else {
                        return false;
                    }
                } else if ((cases[i_dst*dimension+j_dst].isEmpty() && i_dst == i_src - 1)) {
                    move(i_src, j_src, i_dst, j_dst);
                    return true;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
}












