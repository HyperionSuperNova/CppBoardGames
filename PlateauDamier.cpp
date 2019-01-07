#include <sstream>
#include <algorithm>
#include <map>
#include <time.h>
#include <fstream>
#include "PlateauDamier.h"
#include "Plateau.h"

PlateauDamier::PlateauDamier(int dimension) : PlateauCombinatoireAbstrait(dimension) {
    if(dimension == 8) anglais = true;
    else anglais = false;
}

std::ostream &operator<<(std::ostream &out, const PlateauDamier &damier) {
    if(!damier.anglais)out << "-------------------------------------------          ------------------------------------------- \n";
    else out << "-----------------------------------          ----------------------------------- \n";
    int h = 1;
    for(int i = 0; i < damier.dimension; i++){
        out << "| ";
        for(int j = 0; j < damier.dimension; j++){
            out << damier.cases[i*damier.dimension+j].getPion().getImg() << " | ";
        }
        out << "         | ";
        for(int j = 0; j < damier.dimension; j++){
            if(i%2 == 0){
                if(j%2 == 1) {
                    out << h << " | ";
                    h++;
                }
                else out << "  | ";
            }else{
                if(j%2 != 1){
                    out << h << " | ";
                    h++;
                }else out << "  | ";
            }
        }
        out << "\n";
    }
    if(!damier.anglais) out << "-------------------------------------------          -------------------------------------------";
    else out << "-----------------------------------          ----------------------------------- \n";
    return out;
}

void PlateauDamier::ajoutePosCase(tuple* tmp) {
    posCase.push_back(tmp);
}

const void PlateauDamier::initialize() {
    int i_borne = 0;
    if(anglais) i_borne = 3;
    else i_borne = 4;
    int nb = 0;
    Pion p("PION", "\u26C0", Couleur::NOIR);
    for (int i = 0; i < i_borne; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    cases[i*dimension+j].setPion(p);
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            } else {
                if (j % 2 != 1) {
                    cases[i*dimension+j].setPion(p);
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            }
        }
    }
    int ii_borne = 0;
    if(anglais){
        i_borne = 3;
        ii_borne = 5;
    }
    else {

        i_borne = 4;
        ii_borne = 6;
    }
    for (int i = i_borne; i < ii_borne; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            } else {
                if (j % 2 != 1) {
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            }
        }
    }

    if(anglais) i_borne = 5;
    else i_borne = 6;
    Pion p2("PION", "\u26C2", Couleur::BLANC);
    for (int i = i_borne; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    cases[i*dimension+j].setPionBis(p2);
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            } else {
                if (j % 2 != 1) {
                    cases[i*dimension+j].setPionBis(p2);
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            }
        }
    }
}

std::tuple<int,int> PlateauDamier::nbCasetoCoord(int a) {
    return {std::get<1>(*posCase[a-1]), std::get<2>(*posCase[a-1])};
}


const bool PlateauDamier::posOk(int i_src, int j_src, int i_dst, int j_dst) const {
    bool cartesianConstraint =
            i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension && i_dst >= 0 && i_dst < dimension &&
            j_dst >= 0 && j_dst < dimension;
    return cartesianConstraint;
}


bool PlateauDamier::bot() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (pionSelect(i, j, Couleur::NOIR)) {
                bool move1 = pionMove(i, j, i + 1, j - 1, Couleur::NOIR, false);
                bool move2 = pionMove(i, j, i + 1, j + 1, Couleur::NOIR, false);
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

const void PlateauDamier::launcher() {
    std::cout << "Jeu de dames International:" << std::endl;
    std::cout << "Menu Principal:" << std::endl;
    again:
    std::cout << "Selectionnez votre type de jeu :" << std::endl;
    std::cout << "\t 1) Single Player" << std::endl;
    std::cout << "\t 2) 2P Game" << std::endl;
    std::cout << "\t 3) lancer partie automatique" << std::endl;
    std::string gameType = "";
    std::cin >> gameType;
    if (gameType != "1" && gameType != "2" && gameType != "3") {
        std::cout << "Mauvais Choix : Veuillez Selectionner 1 ou 2" << std::endl;
        goto again;
    } else {
        if (gameType == "1") {
            this->singlePlayer();
        }else if(gameType == "2"){
            this->twoPlayer();
        }else if(gameType == "3"){
            this->lectureFichierTest();
        }
    }
    return;
}
void PlateauDamier::affichageVainqueur() {
    if(scoreJ1 == dimension*dimension/2) std::cout << "Le joueur 1 gagne!" << std::endl;
    else if(scoreJ2 == dimension*dimension/2) std::cout << "Le joueur 2 gagne!" << std::endl;
}

const void PlateauDamier::twoPlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    std::cout << *(this) << std::endl;
    while (scoreJ1 < dimension*dimension/2 || scoreJ2 < dimension*dimension/2) {
        first:
        std::cout << "Pour avoir de l'aide, Tapez help" <<std::endl;
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 14"
                  << std::endl;
        std::string s;
        std::cin >> s;
        if(s == "help"){
            help(Couleur::BLANC);
            std::cin >> s;
        }

        int nbCase = std::stoi(s);
        std::tuple<int,int> coord_src = nbCasetoCoord(nbCase);

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
        std::cout << *(this) << std::endl;
        if(!this->playerTurn(i_src, j_src, i_dst, j_dst)){
            std::cout << "Coup impossible" << std::endl;
            goto first;
        };
        std::cout << *(this) << std::endl;


        second:
        std::cout << "Pour avoir de l'aide, Tapez help" <<std::endl;
        std::cout << *(this) << std::endl;
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 14"
                  << std::endl;

        std::cin >> s;
        if(s == "help"){
            help(Couleur::NOIR);
            std::cin >> s;
        }

        nbCase = std::stoi(s);
        coord_src = nbCasetoCoord(nbCase);

        i_src = std::get<0>(coord_src);
        j_src = std::get<1>(coord_src);
        pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        std::cout << "i_src: " << i_src << " et j_src: " << j_src << std::endl;


        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 14"
                  << std::endl;
                std::cin >> x;
        nbCase_dst = std::stoi(x);
        coord_dst = nbCasetoCoord(nbCase_dst);
        i_dst = std::get<0>(coord_dst);
        j_dst = std::get<1>(coord_dst);
        pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);
        if(!this->playerTurn2(i_src, j_src, i_dst, j_dst)){
            std::cout << "Coup impossible" << std::endl;
            goto second;
        };
        std::cout << *(this) << std::endl;

    }
    affichageVainqueur();
}

const void PlateauDamier::singlePlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    std::cout << *(this) << std::endl;
    while (scoreJ1 < dimension*dimension/2 || scoreJ2 < dimension*dimension/2) {
        first:
        std::cout << "Pour avoir de l'aide, tapez help" << std::endl;
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 14"
                  << std::endl;
        std::string s;
        std::cin >> s;

        if(s == "help"){
            help(Couleur::BLANC);
            std::cin >> s;
        }
        int nbCase = std::stoi(s);
        std::tuple<int,int> coord_src = nbCasetoCoord(nbCase);

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
        if(!this->playerTurn(i_src, j_src, i_dst, j_dst)){
            std::cout << "Coup impossible" << std::endl;
            goto first;
        };
        this->bot();
        std::cout << *(this) << std::endl;

    }
    affichageVainqueur();
}

const bool PlateauDamier::pionSelect(int i_src, int j_src, Couleur c) {
    bool selectOk = false;
    if (i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension) {
        if (cases[i_src*dimension+j_src].getPion().getColor() == c) {
            selectOk = true;
        }
    }
    return selectOk;
}

const bool PlateauDamier::pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c, bool dejaPasse) {
    if((i_src == 0 && c == Couleur::BLANC && cases[i_src*dimension+j_src].getPion().getNom() != "KING") || (i_src == dimension-1 && c == Couleur::NOIR && cases[i_src*dimension+j_src].getPion().getNom() != "KING")) return false;
    if (posOk(i_src, j_src, i_dst, j_dst)) {
        if (cases[i_src*dimension+j_src].getPion().getColor() == Couleur::BLANC && c == Couleur::BLANC) {

            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (!cases[i_dst*dimension+j_dst].isEmpty() && cases[i_dst*dimension+j_dst].getPion().getColor() == Couleur::NOIR) {
                    std::cout << "la20" << std::endl;
                    if (i_dst == i_src - 1) {
                        if (j_dst == j_src + 1 && (j_dst+1) < dimension && (j_dst+1) > 0 && i_dst-1 >= 0) {
                            if (cases[(i_dst-1)*dimension+(j_dst+1)].isEmpty()) {
                                std::cout << "la1" << std::endl;
                                scoreJ1 += 1;
                                cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst - 1, (j_dst+1));
                                if (i_dst-1 == 0) {
                                    Pion p2("KING", "\u26C1", Couleur::BLANC);
                                    cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                    cases[(i_dst-1)*dimension+(j_dst+1)].setPionBis(p2);
                                    return true;
                                }
                                bool l = pionMove((i_dst-1), (j_dst+1), i_dst - 2, j_dst, Couleur::BLANC, true);
                                bool ld = pionMove((i_dst-1), (j_dst+1), i_dst - 2, (j_dst+1)+1, Couleur::BLANC, true);
                                if(!anglais || (anglais && cases[i_src*dimension+j_src].getPion().getNom() == "KING")) {
                                    bool rd = pionMove((i_dst-1), (j_dst+1), i_dst, j_dst, Couleur::BLANC, true);
                                    bool r = pionMove((i_dst-1), (j_dst+1), i_dst, (j_dst+1) + 1, Couleur::BLANC, true);
                                }

                            } else {
                                std::cout << "la4" << std::endl;
                                return false;
                            }
                        } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0 && i_dst-1 >= 0) {
                            std::cout << "la2" << std::endl;
                            if (cases[(i_dst-1)*dimension+(i_dst-1)].isEmpty()) {
                                scoreJ1 += 1;
                                cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, (i_dst-1), j_dst - 1);
                                if (i_dst-1 == 0) {
                                    Pion p2("KING", "\u26C1", Couleur::BLANC);
                                    cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                    cases[(i_dst-1)*dimension+(j_dst-1)].setPionBis(p2);
                                    return true;
                                }
                                bool l = pionMove((i_dst-1), j_dst - 1, i_dst - 2, j_dst - 1-1, Couleur::BLANC, true);
                                bool ld = pionMove((i_dst-1), j_dst - 1, i_dst - 2, j_dst, Couleur::BLANC, true);
                                if(!anglais|| (anglais && cases[i_src*dimension+j_src].getPion().getNom() == "KING")) {
                                    bool rd = pionMove((i_dst-1), j_dst - 1, i_dst, j_dst - 1 - 1, Couleur::BLANC,true);
                                    bool r = pionMove((i_dst-1), j_dst - 1, i_dst, j_dst, Couleur::BLANC, true);
                                }
                            } else {
                                std::cout << "la5" << std::endl;
                                return false;
                            }
                        } else {
                            std::cout << "la6" << std::endl;
                            return false;
                        }
                    } else if (cases[i_dst*dimension+j_dst].isEmpty() && i_dst == i_src - 1 && !dejaPasse) {
                        std::cout << "la3" << std::endl;
                        move(i_src, j_src, i_dst, j_dst);
                        if (i_dst == 0) {
                            Pion p2("KING", "\u26C1", Couleur::BLANC);
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            cases[i_dst*dimension+j_dst].setPionBis(p2);
                            return true;
                        }
                    } else {
                        std::cout << "la7" << std::endl;
                        return false;
                    }
                } else if (i_dst == i_src + 1) {
                    if (j_dst == j_src + 1 && (j_dst+1) < dimension && (j_dst+1) > 0) {
                        std::cout << "la8" << std::endl;
                        if (cases[(i_dst+1)*dimension+(j_dst+1)].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst+1), (j_dst+1));


                            bool l = pionMove((i_dst-1), (j_dst+1), i_dst - 2, j_dst, Couleur::BLANC, true);
                            bool ld = pionMove((i_dst-1), (j_dst+1), i_dst - 2, (j_dst+1)+1, Couleur::BLANC, true);
                            bool rd = pionMove((i_dst-1), (j_dst+1), i_dst, j_dst, Couleur::BLANC, true);
                            bool r = pionMove((i_dst-1), (j_dst+1), i_dst, (j_dst+1) + 1, Couleur::BLANC, true);
                        } else {
                            std::cout << "la14" << std::endl;
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 > 0) {
                        if (cases[(i_dst+1)*dimension+(i_dst-1)].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst+1), j_dst - 1);



                            bool l = pionMove((i_dst-1), j_dst - 1, i_dst - 2, j_dst - 1-1, Couleur::BLANC, true);
                            bool ld = pionMove((i_dst-1), j_dst - 1, i_dst - 2, j_dst, Couleur::BLANC, true);
                            bool rd = pionMove((i_dst-1), j_dst - 1, i_dst, j_dst - 1 - 1, Couleur::BLANC,true);
                                bool r = pionMove((i_dst-1), j_dst - 1, i_dst, j_dst, Couleur::BLANC, true);
                        } else {
                            std::cout << "la15" << std::endl;
                            return false;
                        }
                    } else {
                        std::cout << "la16" << std::endl;
                        return false;
                    }
                } else if ((cases[i_dst*dimension+j_dst].isEmpty() && i_dst == i_src - 1 && !dejaPasse)) {
                    move(i_src, j_src, i_dst, j_dst);
                    if (i_dst == 0) {
                        Pion p2("KING", "\u26C3", Couleur::BLANC);
                        cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                        cases[i_dst*dimension+j_dst].setPionBis(p2);
                    }
                } else {
                    std::cout << "la17" << std::endl;
                    return false;
                }

            } else {
                std::cout << "Illegal movement" << std::endl;
                return false;
            }
        } else if (cases[i_src*dimension+j_src].getPion().getColor() == Couleur::NOIR && c == Couleur::NOIR &&
                   (!(cases[i_dst*dimension+j_dst].getPion().getNom() == "KING"))) {
            std::cout << "la111" << std::endl;
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                std::cout << "la112" << std::endl;
                if (i_dst == i_src + 1) {
                    std::cout << "la113" << std::endl;
                    if (!cases[i_dst*dimension+j_dst].isEmpty() && cases[i_dst*dimension+j_dst].getPion().getColor() == Couleur::BLANC) {
                        std::cout << "la1114" << std::endl;
                        if (j_dst == j_src + 1 && (j_dst+1) < dimension && (j_dst+1) > 0) {
                            std::cout << "la115" << std::endl;
                            if (cases[((i_dst+1))*dimension+((j_dst+1))].isEmpty()) {
                                std::cout << "la116" << std::endl;
                                scoreJ2 += 1;
                                cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, (i_dst+1), (j_dst+1));
                                if (i_dst+1 == dimension-1) {
                                    Pion p2("KING", "\u26C1", Couleur::NOIR);
                                    cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                    cases[(i_dst+1)*dimension+(j_dst+1)].setPionBis(p2);
                                    return true;
                                }
                                if(!anglais) {
                                    bool l = pionMove((i_dst+1), (j_dst+1), i_dst, j_dst, Couleur::NOIR, true);
                                    bool ld = pionMove((i_dst+1), (j_dst+1), i_dst, j_dst + 2, Couleur::NOIR, true);
                                }
                                bool rd = pionMove((i_dst+1), (j_dst+1), i_dst + 2, j_dst, Couleur::NOIR, true);
                                bool r = pionMove((i_dst+1), (j_dst+1), i_dst + 2, j_dst + 2, Couleur::NOIR, true);
                            } else {
                                std::cout << "la117" << std::endl;
                                return false;
                            }
                        } else if (j_dst - 1 < dimension && j_dst - 1 > 0) {
                            std::cout << "la118" << std::endl;
                            if (cases[(i_dst+1)*dimension+(i_dst-1)].isEmpty()) {
                                std::cout << "la119" << std::endl;
                                scoreJ1 += 1;
                                cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, (i_dst+1), j_dst - 1);
                                if ((i_dst+1) == dimension-1) {
                                    Pion p2("KING", "\u26C1", Couleur::NOIR);
                                    cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                                    cases[(i_dst+1)*dimension+(j_dst-1)].setPionBis(p2);
                                    return true;
                                }
                                if(!anglais) {
                                    bool l = pionMove((i_dst+1), j_dst - 1, i_dst, j_dst - 2, Couleur::NOIR, true);
                                    bool ld = pionMove((i_dst+1), j_dst - 1, i_dst, j_dst, Couleur::NOIR, true);
                                }
                                bool rd = pionMove((i_dst+1), j_dst - 1, i_dst + 2, j_dst - 2, Couleur::NOIR, true);
                                bool r = pionMove((i_dst+1), j_dst - 1, i_dst + 2, j_dst, Couleur::NOIR, true);
                            } else {
                                std::cout << "la120" << std::endl;
                                return false;
                            }
                        } else if ((i_dst-1) > 0 && (i_dst-1)) {
                            std::cout << "la121" << std::endl;
                            return false;
                        }
                    } else if (i_dst == i_src + 1 && cases[i_dst*dimension+j_dst].isEmpty() && !dejaPasse) {
                        std::cout << "la122" << std::endl;
                        move(i_src, j_src, i_dst, j_dst);
                        if (i_dst == dimension-1) {
                            Pion p2("KING", "\u26C1", Couleur::NOIR);
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            cases[i_dst*dimension+j_dst].setPionBis(p2);
                            return true;
                        }
                    } else {
                        return false;
                    }
                } else if (i_dst == i_src - 1) {
                    std::cout << "la123" << std::endl;
                    if (j_dst == j_src + 1 && (j_dst+1) < dimension && (j_dst+1) > 0) {
                        if (cases[(i_dst-1)*dimension+(j_dst+1)].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst-1), (j_dst+1));
                            bool l = pionMove((i_dst-1), (j_dst+1), (i_dst-1), j_dst - 1, Couleur::NOIR, true);
                            bool ld = pionMove((i_dst-1), (j_dst+1), (i_dst-1), (j_dst+1), Couleur::NOIR, true);
                            bool rd = pionMove((i_dst-1), (j_dst+1), (i_dst+1), j_dst - 1, Couleur::NOIR, true);
                            bool r = pionMove((i_dst-1), (j_dst+1), (i_dst+1), (j_dst+1), Couleur::NOIR, true);
                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                        std::cout << "la125" << std::endl;
                        if (cases[(i_dst-1)*dimension+(i_dst-1)].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, (i_dst-1), j_dst - 1);
                            bool l = pionMove((i_dst-1), j_dst - 1, (i_dst-1), j_dst - 1, Couleur::NOIR, true);
                            bool ld = pionMove((i_dst-1), j_dst - 1, (i_dst-1), (j_dst+1), Couleur::NOIR, true);
                            bool rd = pionMove((i_dst-1), j_dst - 1, (i_dst+1), j_dst - 1, Couleur::NOIR, true);
                            bool r = pionMove((i_dst-1), j_dst - 1, (i_dst+1), (j_dst+1), Couleur::NOIR, true);
                        } else {
                            return false;
                        }
                    } else {
                        std::cout << "la126" << std::endl;
                        return false;
                    }
                } else if (cases[i_dst*dimension+j_dst].isEmpty() && i_dst == i_src - 1) {
                    std::cout << "la127" << std::endl;
                    move(i_src, j_src, i_dst, j_dst);
                    if (i_dst == dimension-1) {
                        Pion p2("KING", "\u26C1", Couleur::NOIR);
                        cases[i_dst*dimension+j_dst] = Case(i_dst, j_dst);
                        cases[i_dst*dimension+j_dst].setPionBis(p2);
                        return true;
                    }
                } else {
                    std::cout << "la12" << std::endl;
                    return false;
                }

            } else {
                std::cout << "la11" << std::endl;
                return false;
            }
        } else {
            std::cout << "la10" << std::endl;
            return false;
        }

    } else {
        std::cout << "la9" << std::endl;
        return false;
    }
    return true;
}

void PlateauDamier::help(Couleur joueur) {
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            if(joueur == Couleur::BLANC) {
                if(cases[i*dimension+j].getPion().getColor() == joueur) {
                    if (anglais) {
                        if (i+1 < dimension && j+1 < dimension && cases[i +1*dimension+j + 1].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+1) + " " + std::to_string(j+1) << std::endl;
                        else if (cases[i+1*dimension+j+1].getPion().getColor() == Couleur::NOIR && i+2 < dimension && j+2 < dimension && cases[i +2*dimension+j + 2].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+2) + " " + std::to_string(j+2) << std::endl;
                        if (i+1 < dimension && j-1 >= 0 && cases[i +1*dimension+j - 1].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+1) + " " + std::to_string(j-1) << std::endl;
                        else if (cases[i+1*dimension+j-1].getPion().getColor() == Couleur::NOIR && i+2 < dimension && j-2 >= 0 && cases[i +2*dimension+j - 2].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+2) + " " + std::to_string(j-2) << std::endl;
                    }
                    if (i-1 >= 0 && j+1 < dimension && cases[i -1*dimension+j + 1].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-1) + " " + std::to_string(j+1) << std::endl;
                    else if(cases[i-1*dimension+j+1].getPion().getColor() == Couleur::NOIR && i-2 >= 0 && j+2 < dimension && cases[i -2*dimension+j + 2].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-2) + " " + std::to_string(j+2) << std::endl;
                    if (i-1 >= 0 && j-1 >= 0 && cases[i -1*dimension+j - 1].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-1) + " " + std::to_string(j-1) << std::endl;
                    else if (cases[i-1*dimension+j-1].getPion().getColor() == Couleur::NOIR && i-2 >= 0 && j-2 >= 0 && cases[i -2*dimension+j - 2].isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-2) + " " + std::to_string(j-2) << std::endl;


                }
            }else{
                if(cases[i*dimension+j].getPion().getColor() == joueur) {
                    if (anglais) {
                        if (i - 1 >= 0 && j + 1 < dimension && cases[i - 1*dimension+j + 1].isEmpty())
                            std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 1) + " " +
                                   std::to_string(j + 1) << std::endl;
                        else if (cases[i-1*dimension+j+1].getPion().getColor() == Couleur::BLANC && i - 2 >= 0 && j + 2 < dimension && cases[i - 2*dimension+j + 2].isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 2) + " " +
                               std::to_string(j + 2) << std::endl;
                        if (i - 1 >= 0 && j - 1 >= 0 && cases[i - 1*dimension+j - 1].isEmpty())
                            std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 1) + " " +
                                   std::to_string(j - 1) << std::endl;
                        else if (cases[i-1*dimension+j-1].getPion().getColor() == Couleur::BLANC && i - 2 >= 0 && j - 2 >= 0 && cases[i - 2*dimension+j - 2].isEmpty())
                            std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 2) + " " +
                                   std::to_string(j - 2) << std::endl;

                    }
                    if (i + 1 < dimension && j + 1 < dimension && cases[i + 1*dimension+j + 1].isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 1) + " " +
                               std::to_string(j + 1) << std::endl;
                    else if (cases[i+1*dimension+j+1].getPion().getColor() == Couleur::BLANC && i + 2 < dimension && j + 2 < dimension && cases[i + 2*dimension+j + 2].isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 2) + " " +
                               std::to_string(j + 2) << std::endl;
                    if (i + 1 < dimension && j - 1 >= 0 && cases[i + 1*dimension+j - 1].isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 1) + " " +
                               std::to_string(j - 1) << std::endl;
                    else if (cases[i+1*dimension+j-1].getPion().getColor() == Couleur::BLANC && i + 2 < dimension && j - 2 >= 0 && cases[i + 2*dimension+j - 2].isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 2) + " " +
                               std::to_string(j - 2) << std::endl;
                }

            }

        }
    }
}

const void PlateauDamier::lectureFichierTest() {
    this->initialize();
    std::string file = "";
    file = "../dame_international/test1.txt";
    if(this->anglais) file = "../dame_anglaise/test1.txt";
    std::ifstream infile(file);
    std::string line = "";
    std::string delimiter = " ";
    Couleur c = Couleur ::BLANC;
    int case_src = 0;
    int case_dst = 0;
    std::cout << *(this) << std::endl;
    while(std::getline(infile, line)){
        case_src = std::stoi(line.substr(0, line.find(delimiter)));
        case_dst = std::stoi(line.substr(std::to_string(case_src).length()+1, 2));
        std::tuple<int,int> src = this->nbCasetoCoord(case_src);
        std::tuple<int,int> dst = this->nbCasetoCoord(case_dst);
        int i_src = std::get<0>(src);
        int j_src = std::get<1>(src);
        int i_dst = std::get<0>(dst);
        int j_dst = std::get<1>(dst);
        if(c == Couleur::BLANC) this->playerTurn(i_src, j_src, i_dst, j_dst);
        else this->playerTurn2(i_src,j_src,i_dst,j_dst);
        if(c == Couleur::BLANC) c = Couleur::NOIR;
        else c = Couleur::BLANC;
        usleep(1000);//2500000);
        std::cout << *(this) << std::endl;

    }
    affichageVainqueur();
}
