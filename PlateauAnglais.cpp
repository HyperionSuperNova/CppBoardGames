#include "PlateauAnglais.h"

PlateauAnglais::PlateauAnglais() : PlateauCombinatoireAbstrait(8) {
    dimension = 8;
}

const void PlateauAnglais::playerTurn() {
    firstSelect:
    if (turn == 0) {
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                  << std::endl;
        std::string s;
        std::cin >> s;
        std::vector<int> t = split(s, ',');
        long sizeEntry = t.size();
        bool pionSel = pionSelect(t[0], t[1], Couleur::BLANC);
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

        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 2,0"
                  << std::endl;
        std::string x;
        std::cin >> x;
        std::vector<int> h = split(x, ',');
        if (cases[t[0]][t[1]].getPion().getNom() == "PION") {
            if ((h.size() != 2 || !pionMove(t[0], t[1], h[0], h[1], Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                /*std::cin >> x;
                h = split(x, ',');*/
                goto firstSelect;
            }
        } else if (cases[t[0]][t[1]].getPion().getNom() == "KING") {
            if ((h.size() != 2)) {
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













