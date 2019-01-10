#include <sstream>
#include <algorithm>
#include <map>
#include <time.h>
#include <fstream>
#include "PlateauDamier.h"
#include "Plateau.h"

PlateauDamier::PlateauDamier(int dimension) : PlateauCombinatoireAbstrait(dimension) {
    if(getDimension() == 8) anglais = true;
    else anglais = false;
}

std::ostream &operator<<(std::ostream &out, const PlateauDamier &damier) {
    if(!damier.anglais)out << "-------------------------------------------          ------------------------------------------- \n";
    else out << "-----------------------------------          ----------------------------------- \n";
    int h = 1;
    for(int i = 0; i < damier.getDimension(); i++){
        out << "| ";
        for(int j = 0; j < damier.getDimension(); j++){
            out << damier.getCase(i*damier.getDimension()+j).getPion()->getImg() << " | ";
        }
        out << "         | ";
        for(int j = 0; j < damier.getDimension(); j++){
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
    Pion *p = new Pion("PION", "\u26C0", Couleur::NOIR);
    for (int i = 0; i < i_borne; i++) {
        for (int j = 0; j < getDimension(); j++) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    setCases(i*getDimension()+j, *p);
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            } else {
                if (j % 2 != 1) {
                    setCases(i*getDimension()+j, *p);
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
        for (int j = 0; j < getDimension(); j++) {
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
    Pion *p2 = new Pion("PION", "\u26C2", Couleur::BLANC);
    for (int i = i_borne; i < getDimension(); i++) {
        for (int j = 0; j < getDimension(); j++) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    setCases(i*getDimension()+j, *p2);
                    tuple *tmp = new tuple(nb,i,j);
                    ajoutePosCase(tmp);
                }
            } else {
                if (j % 2 != 1) {
                    setCases(i*getDimension()+j, *p2);
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

const bool PlateauDamier::playerTurn(int i_src, int j_src, int i_dst, int j_dst) {
    if (turn == 0) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::BLANC);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::BLANC);

        if (getCase(i_src*getDimension()+j_src).getPion()->getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                return false;
            }
        } else if (getCase(i_src*getDimension()+j_src).getPion()->getNom() == "KING") {
            if ((/* h.size() != 2 || */ !kingMove(i_src, j_src, i_dst, j_dst, Couleur::BLANC))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                return false;
            }
        }

    }
    turn += 1;
    return true;
}

const bool PlateauDamier::playerTurn2(int i_src, int j_src, int i_dst, int j_dst) {
    if (turn == 1) {
        bool pionSel_src = pionSelect(i_src, j_src, Couleur::NOIR);
        bool pionSel_dst = pionSelect(i_dst, j_dst, Couleur::NOIR);

        if (getCase(i_src*getDimension()+j_src).getPion()->getNom() == "PION") {
            if ((!pionMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR, false))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;

                return false;
            }
        } else if (getCase(i_src*getDimension()+j_src).getPion()->getNom() == "KING") {
            if ((!kingMove(i_src, j_src, i_dst, j_dst, Couleur::NOIR))) {
                std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
                return false;
            }
        }

    }
    turn -= 1;
    return true;
}



const bool PlateauDamier::posOk(int i_src, int j_src, int i_dst, int j_dst){
    bool cartesianConstraint =
            i_src >= 0 && i_src < getDimension() && j_src >= 0 && j_src < getDimension() && i_dst >= 0 && i_dst < getDimension() &&
            j_dst >= 0 && j_dst < getDimension();
    return cartesianConstraint;
}


bool PlateauDamier::bot() {
    for (int i = 0; i < getDimension(); i++) {
        for (int j = 0; j < getDimension(); j++) {
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
    if(scoreJ1 >= getDimension()*getDimension()/4 - (getDimension()/2)) std::cout << "Le joueur 1 gagne!" << std::endl;
    else if(scoreJ2 >= getDimension()*getDimension()/4 - (getDimension()/2)) std::cout << "Le joueur 2 gagne!" << std::endl;
}

const void PlateauDamier::twoPlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    std::cout << *(this) << std::endl;
    while (scoreJ1 < getDimension()*getDimension()/4  - (getDimension()/2)|| scoreJ2 < getDimension()*getDimension()/4 - (getDimension()/2)) {
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
    while (scoreJ1 < getDimension()*getDimension()/4  - (getDimension()/2)|| scoreJ2 < getDimension()*getDimension()/4 - (getDimension()/2)) {
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
    if (i_src >= 0 && i_src < getDimension() && j_src >= 0 && j_src < getDimension()) {
        if (getCase(i_src*getDimension()+j_src).getPion()->getColor() == c) {
            selectOk = true;
        }
    }
    return selectOk;
}

const bool PlateauDamier::pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c, bool dejaPasse) {
    if((i_src == 0 && c == Couleur::BLANC && getCase(i_src*getDimension()+j_src).getPion()->getNom() != "KING") || (i_src == getDimension()-1 && c == Couleur::NOIR && getCase(i_src*getDimension()+j_src).getPion()->getNom() != "KING")) return false;
    if (posOk(i_src, j_src, i_dst, j_dst)) {
        if (getCase(i_src*getDimension()+j_src).getPion()->getColor() == Couleur::BLANC && c == Couleur::BLANC) {
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (!getCase(i_dst*getDimension()+j_dst).isEmpty() && getCase(i_dst*getDimension()+j_dst).getPion()->getColor() == Couleur::NOIR) {
                    if (i_dst == i_src - 1) {
                        std::cout << (j_dst == j_src-1) << std::endl;
                        if (j_dst == j_src + 1 && (j_dst+1) < getDimension() && i_dst-1 >= 0) {
                            if (getCase((i_dst-1)*getDimension()+(j_dst+1)).isEmpty()) {
                                scoreJ1 += 1;
                                setCase(i_dst*getDimension()+j_dst, new Pion());
                                move(i_src, j_src, (i_dst-1), (j_dst+1));
                                if (i_dst-1 == 0) {
                                    Pion *p2 = new Pion("KING", "\u26C3", Couleur::BLANC);
                                    Pion *p = new Pion();
                                    setCases(i_dst*getDimension()+j_dst, *p);
                                    setCases((i_dst-1)*getDimension()+(j_dst+1), *p2);
                                    return true;
                                }
                                bool l = pionMove((i_dst-1), (j_dst+1), i_dst - 2, j_dst, Couleur::BLANC, true);
                                bool ld = pionMove((i_dst-1), (j_dst+1), i_dst - 2, (j_dst+1+1), Couleur::BLANC, true);
                                if(!anglais || (anglais && getCase(i_src*getDimension()+j_src).getPion()->getNom() == "KING")) {
                                    bool rd = pionMove((i_dst-1), (j_dst+1), i_dst-1, j_dst, Couleur::BLANC, true); // Attention
                                    bool r = pionMove((i_dst-1), (j_dst+1), i_dst, (j_dst+1 + 1), Couleur::BLANC, true); // Attention
                                }
                                return true;
                            } else return false;

                        } else if (j_dst == j_src - 1 && (j_dst-1) >= 0 && i_dst-1 >= 0) {
                            if (getCase((i_dst-1)*getDimension()+(j_dst-1)).isEmpty()) {
                                scoreJ1 += 1;
                                setCase(i_dst*getDimension()+j_dst, new Pion());
                                move(i_src, j_src, (i_dst-1), (j_dst-1));
                                if (i_dst-1 == 0) {
                                    Pion *p2 = new Pion("KING", "\u26C3", Couleur::BLANC);
                                    Pion *p = new Pion();
                                    setCases(i_dst*getDimension()+j_dst, *p);
                                    setCases((i_dst-1)*getDimension()+(j_dst-1), *p2);
                                    return true;
                                }
                                bool l = pionMove((i_dst-1), (j_dst-1), i_dst - 2, (j_dst-2), Couleur::BLANC, true);
                                bool ld = pionMove((i_dst-1), (j_dst-1), i_dst - 2, j_dst, Couleur::BLANC, true);
                                if(!anglais|| (anglais && getCase(i_src*getDimension()+j_src).getPion()->getNom() == "KING")) {
                                    bool rd = pionMove((i_dst-1), (j_dst-1), i_dst, (j_dst-2), Couleur::BLANC,true);
                                    bool r = pionMove((i_dst-1), (j_dst-1), i_dst+1, j_dst, Couleur::BLANC, true);
                                }
                                return true;
                            } else return false;
                        } else return false;

                    } else if (i_dst == i_src + 1 || !anglais) {
                        if (j_dst == j_src + 1 && (j_dst + 1) < getDimension()) {
                            if (getCase((i_dst + 1) * getDimension() + (j_dst + 1)).isEmpty()) {
                                scoreJ1 += 1;
                                Pion *p = new Pion();
                                setCases(i_dst * getDimension() + j_dst, *p);
                                move(i_src, j_src, (i_dst + 1), (j_dst + 1));


                                bool l = pionMove((i_dst - 1), (j_dst + 1), i_dst - 2, j_dst, Couleur::BLANC, true);
                                bool ld = pionMove((i_dst - 1), (j_dst + 1), i_dst - 2, (j_dst + 2), Couleur::BLANC, true);
                                bool rd = pionMove((i_dst - 1), (j_dst + 1), i_dst, j_dst, Couleur::BLANC, true);
                                bool r = pionMove((i_dst - 1), (j_dst + 1), i_dst, (j_dst + 2), Couleur::BLANC, true);
                            } else return false;

                        } else if (j_dst == j_src - 1 && (j_dst - 1) >= 0) {
                            if (getCase((i_dst + 1) * getDimension() + (j_dst - 1)).isEmpty()) {
                                scoreJ1 += 1;
                                Pion *p = new Pion();
                                setCases(i_dst * getDimension() + j_dst, *p);
                                move(i_src, j_src, (i_dst + 1), (j_dst - 1));


                                bool l = pionMove((i_dst - 1), (j_dst - 1), i_dst - 2, (j_dst - 2), Couleur::BLANC, true);
                                bool ld = pionMove((i_dst - 1), (j_dst - 1), i_dst - 2, j_dst, Couleur::BLANC, true);
                                bool rd = pionMove((i_dst - 1), (j_dst - 1), i_dst, (j_dst - 2), Couleur::BLANC, true);
                                bool r = pionMove((i_dst - 1), (j_dst - 1), i_dst, j_dst, Couleur::BLANC, true);
                            } else return false;

                        } else return false;

                    } else return false;

                } else if ((getCase(i_dst*getDimension()+j_dst).isEmpty() && i_dst == i_src - 1 && !dejaPasse)) {
                    move(i_src, j_src, i_dst, j_dst);
                    if (i_dst == 0) {
                        Pion *p2 = new Pion("KING", "\u26C3", Couleur::BLANC);
                        Pion *p = new Pion();
                        setCases(i_dst*getDimension()+j_dst, *p);
                        setCases(i_dst*getDimension()+j_dst, *p2);
                    }
                } else return false;

            } else {
                std::cout << "Illegal movement" << std::endl;
                return false;
            }
        } else if (getCase(i_src*getDimension()+j_src).getPion()->getColor() == Couleur::NOIR && c == Couleur::NOIR &&
                   (!(getCase(i_dst*getDimension()+j_dst).getPion()->getNom() == "KING"))) {
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (i_dst == i_src + 1) {
                    if (!getCase(i_dst*getDimension()+j_dst).isEmpty() && getCase(i_dst*getDimension()+j_dst).getPion()->getColor() == Couleur::BLANC) {
                        if (j_dst == j_src + 1 && (j_dst+1) < getDimension()) {
                            if (getCase(((i_dst+1))*getDimension()+((j_dst+1))).isEmpty()) {
                                scoreJ2 += 1;
                                Pion *p = new Pion();
                                setCases(i_dst*getDimension()+j_dst, *p);
                                move(i_src, j_src, (i_dst+1), (j_dst+1));
                                if (i_dst+1 == getDimension()-1) {
                                    Pion *p2 = new Pion("KING", "\u26C1", Couleur::NOIR);
                                    setCases(i_dst*getDimension()+j_dst,*p);
                                    setCases((i_dst+1)*getDimension()+(j_dst+1), *p2);
                                    return true;
                                }
                                if(!anglais) {
                                    bool l = pionMove((i_dst+1), (j_dst+1), i_dst-1, j_dst, Couleur::NOIR, true);
                                    bool ld = pionMove((i_dst+1), (j_dst+1), i_dst, j_dst + 1, Couleur::NOIR, true);
                                }
                                bool rd = pionMove((i_dst+1), (j_dst+1), i_dst + 2, j_dst, Couleur::NOIR, true);
                                bool r = pionMove((i_dst+1), (j_dst+1), i_dst + 2, j_dst + 1, Couleur::NOIR, true);
                            } else return false;

                        } else if (j_dst == j_src-1 && (j_dst-1) >= 0) {
                            if (getCase((i_dst+1)*getDimension()+(j_dst-1)).isEmpty()) {
                                scoreJ2 += 1;
                                Pion *p = new Pion();
                                setCases(i_dst*getDimension()+j_dst, *p);
                                move(i_src, j_src, (i_dst+1), (j_dst-1));
                                if ((i_dst+1) == getDimension()-1) {
                                    Pion *p2 = new Pion("KING", "\u26C1", Couleur::NOIR);
                                    setCases(i_dst*getDimension()+j_dst, *p);
                                    setCases((i_dst+1)*getDimension()+(j_dst-1), *p2);
                                    return true;
                                }
                                if(!anglais) {
                                    bool l = pionMove((i_dst+1), (j_dst-1), i_dst, j_dst - 2, Couleur::NOIR, true);
                                    bool ld = pionMove((i_dst+1), (j_dst-1), i_dst+1, j_dst, Couleur::NOIR, true);
                                }
                                bool rd = pionMove((i_dst+1), (j_dst-1), i_dst + 2, j_dst - 2, Couleur::NOIR, true);
                                bool r = pionMove((i_dst+1), (j_dst-1), i_dst + 2, j_dst, Couleur::NOIR, true);
                            } else return false;
                            return true;
                        } else return false;

                    } else if (i_dst == i_src + 1 && getCase(i_dst*getDimension()+j_dst).isEmpty() && !dejaPasse) {
                        move(i_src, j_src, i_dst, j_dst);
                        if (i_dst == getDimension()-1) {
                            Pion *p2 = new Pion("KING", "\u26C1", Couleur::NOIR);
                            Pion *p = new Pion();
                            setCases(i_dst*getDimension()+j_dst, *p);
                            setCases(i_dst*getDimension()+j_dst, *p2);
                            return true;
                        }
                    } else return false;

                } else if (i_dst == i_src - 1) {
                    if (j_dst == j_src + 1 && (j_dst+1) < getDimension()) {
                        if (getCase((i_dst-1)*getDimension()+(j_dst+1)).isEmpty()) {
                            scoreJ2 += 1;
                            Pion *p = new Pion();
                            setCases(i_dst*getDimension()+j_dst, *p);
                            move(i_src, j_src, (i_dst-1), (j_dst+1));
                            bool l = pionMove((i_dst-1), (j_dst+1), (i_dst-2), (j_dst+1), Couleur::NOIR, true);
                            bool ld = pionMove((i_dst-1), (j_dst+1), (i_dst), (j_dst+1), Couleur::NOIR, true);
                            bool rd = pionMove((i_dst-1), (j_dst+1), (i_dst), (j_dst), Couleur::NOIR, true);
                            bool r = pionMove((i_dst-1), (j_dst+1), (i_dst-2), (j_dst-2), Couleur::NOIR, true);
                        } else return false;

                    } else if (j_dst == j_src - 1 && (j_dst-1) < getDimension() && (j_dst-1) >= 0) {
                        if (getCase((i_dst-1)*getDimension()+(j_dst-1)).isEmpty()) {
                            scoreJ1 += 1;
                            Pion *p = new Pion();
                            setCases(i_dst*getDimension()+j_dst, *p);
                            move(i_src, j_src, (i_dst-1), (j_dst-1));
                            bool l = pionMove((i_dst-1), (j_dst-1), (i_dst-2), (j_dst-2), Couleur::NOIR, true);
                            bool ld = pionMove((i_dst-1), (j_dst-1), (i_dst-2), (j_dst), Couleur::NOIR, true);
                            bool rd = pionMove((i_dst-1), (j_dst-1), (i_dst), (j_dst-2), Couleur::NOIR, true);
                            bool r = pionMove((i_dst-1), (j_dst-1), (i_dst), (j_dst), Couleur::NOIR, true);
                        } else return false;

                    } else return false;

                } else if (getCase(i_dst*getDimension()+j_dst).isEmpty() && i_dst == i_src - 1) {
                    move(i_src, j_src, i_dst, j_dst);
                    if (i_dst == getDimension()-1) {
                        Pion *p2 = new Pion("KING", "\u26C1", Couleur::NOIR);
                        Pion *p = new Pion();
                        setCases(i_dst*getDimension()+j_dst, *p);
                        setCases(i_dst*getDimension()+j_dst, *p2);
                        return true;
                    }
                } else return false;

            } else return false;

        } else return false;

    } else return false;

    return true;
}

void PlateauDamier::help(Couleur joueur) {
    for(int i = 0; i < getDimension(); i++){
        for(int j = 0; j < getDimension(); j++){
            if(joueur == Couleur::BLANC) {
                if(getCase(i*getDimension()+j).getPion()->getColor() == joueur) {
                    if (anglais) {
                        if (i+1 < getDimension() && j+1 < getDimension() && getCase(i +1*getDimension()+j + 1).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+1) + " " + std::to_string(j+1) << std::endl;
                        else if (getCase(i+1*getDimension()+j+1).getPion()->getColor() == Couleur::NOIR && i+2 < getDimension() && j+2 < getDimension() && getCase(i +2*getDimension()+j + 2).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+2) + " " + std::to_string(j+2) << std::endl;
                        if (i+1 < getDimension() && j-1 >= 0 && getCase(i +1*getDimension()+j - 1).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+1) + " " + std::to_string(j-1) << std::endl;
                        else if (getCase(i+1*getDimension()+j-1).getPion()->getColor() == Couleur::NOIR && i+2 < getDimension() && j-2 >= 0 && getCase(i +2*getDimension()+j - 2).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i+2) + " " + std::to_string(j-2) << std::endl;
                    }
                    if (i-1 >= 0 && j+1 < getDimension() && getCase(i -1*getDimension()+j + 1).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-1) + " " + std::to_string(j+1) << std::endl;
                    else if(getCase(i-1*getDimension()+j+1).getPion()->getColor() == Couleur::NOIR && i-2 >= 0 && j+2 < getDimension() && getCase(i -2*getDimension()+j + 2).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-2) + " " + std::to_string(j+2) << std::endl;
                    if (i-1 >= 0 && j-1 >= 0 && getCase(i -1*getDimension()+j - 1).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-1) + " " + std::to_string(j-1) << std::endl;
                    else if (getCase(i-1*getDimension()+j-1).getPion()->getColor() == Couleur::NOIR && i-2 >= 0 && j-2 >= 0 && getCase(i -2*getDimension()+j - 2).isEmpty()) std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i-2) + " " + std::to_string(j-2) << std::endl;


                }
            }else{
                if(getCase(i*getDimension()+j).getPion()->getColor() == joueur) {
                    if (anglais) {
                        if (i - 1 >= 0 && j + 1 < getDimension() && getCase(i - 1*getDimension()+j + 1).isEmpty())
                            std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 1) + " " +
                                   std::to_string(j + 1) << std::endl;
                        else if (getCase(i-1*getDimension()+j+1).getPion()->getColor() == Couleur::BLANC && i - 2 >= 0 && j + 2 < getDimension() && getCase(i - 2*getDimension()+j + 2).isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 2) + " " +
                               std::to_string(j + 2) << std::endl;
                        if (i - 1 >= 0 && j - 1 >= 0 && getCase(i - 1*getDimension()+j - 1).isEmpty())
                            std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 1) + " " +
                                   std::to_string(j - 1) << std::endl;
                        else if (getCase(i-1*getDimension()+j-1).getPion()->getColor() == Couleur::BLANC && i - 2 >= 0 && j - 2 >= 0 && getCase(i - 2*getDimension()+j - 2).isEmpty())
                            std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i - 2) + " " +
                                   std::to_string(j - 2) << std::endl;

                    }
                    if (i + 1 < getDimension() && j + 1 < getDimension() && getCase(i + 1*getDimension()+j + 1).isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 1) + " " +
                               std::to_string(j + 1) << std::endl;
                    else if (getCase(i+1*getDimension()+j+1).getPion()->getColor() == Couleur::BLANC && i + 2 < getDimension() && j + 2 < getDimension() && getCase(i + 2*getDimension()+j + 2).isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 2) + " " +
                               std::to_string(j + 2) << std::endl;
                    if (i + 1 < getDimension() && j - 1 >= 0 && getCase(i + 1*getDimension()+j - 1).isEmpty())
                        std::cout << std::to_string(i) + " " + std::to_string(j) + " -> " + std::to_string(i + 1) + " " +
                               std::to_string(j - 1) << std::endl;
                    else if (getCase(i+1*getDimension()+j-1).getPion()->getColor() == Couleur::BLANC && i + 2 < getDimension() && j - 2 >= 0 && getCase(i + 2*getDimension()+j - 2).isEmpty())
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
        usleep(2000000);
        std::cout << *(this) << std::endl;

    }
    affichageVainqueur();
}
