#include "PlateauDamierAnglais.h"

PlateauDamierAnglais::PlateauDamierAnglais() : PlateauDamier(8) {
    dimension = 8;
}


const void PlateauDamierAnglais::playerTurn(int i_src, int j_src, int i_dst, int j_dst) {
    firstSelect:
    if (turn == 0) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        std::cout << "i_src: " << i_src << " et j_src: " << j_src << std::endl;
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);
        std::cout << "i_dst: " << i_dst << " et j_dst: " << j_dst << std::endl;

        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            std::cout << "passe par la" << std::endl;
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        }

    }
    turn += 1;
    return;
}

const void PlateauDamierAnglais::playerTurn2(int i_src, int j_src, int i_dst, int j_dst) {
    firstSelect:
    if (turn == 1) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);

        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        }

    }
    turn -= 1;
    return;
}












