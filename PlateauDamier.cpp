#include "PlateauDamier.h"

PlateauDamier::PlateauDamier() : PlateauCombinatoireAbstrait(10) {
    dimension = 10;
}

const void PlateauDamier::playerTurn() {
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
            if ((h.size() != 2 || !kingMove(t[0], t[1], h[0], h[1], Couleur::BLANC))) {
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

const bool PlateauDamier::kingMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
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












