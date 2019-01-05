#include "PlateauDamierAnglais.h"

PlateauDamierAnglais::PlateauDamierAnglais() : PlateauDamier(8) {
    dimension = 8;
}


const void PlateauDamierAnglais::playerTurn() {
    firstSelect:
    if (turn == 0) {
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                  << std::endl;
        std::string s;
        std::cin >> s;
        //std::vector<int> t = split(s, ',');
        int nbCase_src = std::stoi(s);
        std::tuple<int,int> coord_src = nbCasetoCoord(nbCase_src);
        //long sizeEntry = t.size();
        int i_src = std::get<0>(coord_src);
        int j_src = std::get<1>(coord_src);
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        std::cout << "i_src: " << i_src << " et j_src: " << j_src << std::endl;
        /*
        std::cout << pionSel << std::endl << sizeEntry << std::endl;
        while ((sizeEntry != 2 || !pionSel)) {
            std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
            std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                      << std::endl;
            std::cin >> s;
            t = split(s, ',');
            sizeEntry = t.size();
            pionSel = pionSelect(t[0], t[1], Couleur::BLANC);
        }
         */

        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 2,0"
                  << std::endl;
        std::string x;
        std::cin >> x;
        //std::vector<int> h = split(x, ',');
        int nbCase_dst = std::stoi(x);
        std::tuple<int,int> coord_dst = nbCasetoCoord(nbCase_dst);
        //long sizeEntry = t.size();
        int i_dst = std::get<0>(coord_dst);
        int j_dst = std::get<1>(coord_dst);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);
        std::cout << "i_dst: " << i_dst << " et j_dst: " << j_dst << std::endl;
        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            std::cout << "passe par la" << std::endl;
            if ((/*h.size() != 2 ||*/ !pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                /*std::cin >> x;
                h = split(x, ',');*/
                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((/* h.size() != 2 || */ !pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                /*std::cin >> x;
                h = split(x, ',');*/
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
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                  << std::endl;
        std::string s;
        std::cin >> s;
        //std::vector<int> t = split(s, ',');
        int nbCase = std::stoi(s);
        std::tuple<int,int> coord_src = nbCasetoCoord(nbCase);
        //long sizeEntry = t.size();
        int i_src = std::get<0>(coord_src);
        int j_src = std::get<1>(coord_src);
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        /*
        std::cout << pionSel << std::endl << sizeEntry << std::endl;
        while ((sizeEntry != 2 || !pionSel)) {
            std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
            std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                      << std::endl;
            std::cin >> s;
            t = split(s, ',');
            sizeEntry = t.size();
            pionSel = pionSelect(t[0], t[1], Couleur::BLANC);
        }
         */

        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 2,0"
                  << std::endl;
        std::string x;
        std::cin >> x;
        //std::vector<int> h = split(x, ',');
        int nbCase_dst = std::stoi(x);
        std::tuple<int,int> coord_dst = nbCasetoCoord(nbCase_dst);
        //long sizeEntry = t.size();
        int i_dst = std::get<0>(coord_dst);
        int j_dst = std::get<1>(coord_dst);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);
        if (cases[i_src][j_src].getPion().getNom() == "PION") {
            if ((/*h.size() != 2 ||*/ !pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                /*std::cin >> x;
                h = split(x, ',');*/
                goto firstSelect;
            }
        } else if (cases[i_src][j_src].getPion().getNom() == "KING") {
            if ((/* h.size() != 2 || */ !pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                /*std::cin >> x;
                h = split(x, ',');*/
                goto firstSelect;
            }
        }

    }
    turn += 1;
    return;
}












