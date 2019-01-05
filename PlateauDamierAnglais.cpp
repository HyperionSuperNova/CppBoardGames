#include "PlateauDamierAnglais.h"

PlateauDamierAnglais::PlateauDamierAnglais() : PlateauDamier(8) {
    dimension = 8;
}


const void PlateauDamierAnglais::playerTurn() {
    firstSelect:
    if (turn == 0) {
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 14"
                  << std::endl;
        std::string s;
        std::cin >> s;

        int nbCase_src = std::stoi(s);
        std::tuple<int,int> coord_src = nbCasetoCoord(nbCase_src);

        int i_src = std::get<0>(coord_src);
        int j_src = std::get<1>(coord_src);
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        std::cout << "i_src: " << i_src << " et j_src: " << j_src << std::endl;


        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 14"
                  << std::endl;
        std::string x;
        std::cin >> x;

        int nbCase_dst = std::stoi(x);
        std::tuple<int,int> coord_dst = nbCasetoCoord(nbCase_dst);

        int i_dst = std::get<0>(coord_dst);
        int j_dst = std::get<1>(coord_dst);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);
        std::cout << "i_dst: " << i_dst << " et j_dst: " << j_dst << std::endl;
        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            std::cout << "passe par la" << std::endl;
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        }

    }
    turn += 1;
    return;
}

const void PlateauDamierAnglais::playerTurn2() {
    firstSelect:
    if (turn == 0) {
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 14"
                  << std::endl;
        std::string s;
        std::cin >> s;

        int nbCase = std::stoi(s);
        std::tuple<int,int> coord_src = nbCasetoCoord(nbCase);

        int i_src = std::get<0>(coord_src);
        int j_src = std::get<1>(coord_src);
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);

        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 14"
                  << std::endl;
        std::string x;
        std::cin >> x;

        int nbCase_dst = std::stoi(x);
        std::tuple<int,int> coord_dst = nbCasetoCoord(nbCase_dst);

        int i_dst = std::get<0>(coord_dst);
        int j_dst = std::get<1>(coord_dst);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);
        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                goto firstSelect;
            }
        }

    }
    turn += 1;
    return;
}












