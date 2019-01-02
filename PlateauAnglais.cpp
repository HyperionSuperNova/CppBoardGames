#include "PlateauAnglais.h"

PlateauAnglais::PlateauAnglais(int dimension) : PlateauCombinatoireAbstrait(dimension) {}

std::ostream &operator<<(std::ostream &os, const PlateauAnglais &damier) {
    os << static_cast<const Plateau &>(damier);
    return os;
}

bool PlateauAnglais::bot() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (pionSelect(i, j, Couleur::NOIR)) {
                bool move1 = pionMove(i, j, i + 1, j - 1, Couleur::NOIR);
                bool move2 = pionMove(i, j, i + 1, j + 1, Couleur::NOIR);
                if (move1) {
                    turn -= 1;
                    return true;
                } else if (move2) {
                    turn -= 1;
                    return true;
                }
            }
        }
    }
    return false;
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

std::vector<int> PlateauAnglais::split(const std::string &s, char delimiter) {
    std::vector<int> Data;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    std::transform(tokens.begin(), tokens.end(), std::back_inserter(Data),
                   [](const std::string &str) { return std::stoi(str); });
    return Data;
}

const void PlateauAnglais::launcher() {
    std::cout << "Jeu de dames International:" << std::endl;
    std::cout << "Menu Principal:" << std::endl;
    std::cout << "Selectionnez votre type de jeu :" << std::endl;
    std::cout << "\t 1) Single Player" << std::endl;
    std::cout << "\t 2) 2P Game" << std::endl;
    int gameType = 0;
    std::cin >> gameType;
    if (gameType != 1 && gameType != 2) {
        std::cout << "Mauvais Choix : Veuillez Selectionner 1 ou 2" << std::endl;
        launcher();
    } else {
        if (gameType == 1) {
            this->singlePlayer();
        }
    }
    return;
}

const void PlateauAnglais::singlePlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    while (true) {
        std::cout << *(this) << std::endl;
        this->playerTurn();
        this->bot();
        std::cout << *(this) << std::endl;

    }
}

const bool PlateauAnglais::pionSelect(int i_src, int j_src, Couleur c) {
    bool selectOk = false;
    if (i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension) {
        if (cases[i_src][j_src].getPion().getColor() == c) {
            selectOk = true;
        }
    }
    return selectOk;
}












