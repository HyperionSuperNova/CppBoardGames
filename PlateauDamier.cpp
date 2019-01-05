#include <sstream>
#include <algorithm>
#include <map>
#include <fstream>
#include "PlateauDamier.h"
#include "Plateau.h"

PlateauDamier::PlateauDamier(int dimension) : PlateauCombinatoireAbstrait(dimension) {
    posCase = new std::tuple<int,int,int>;
    if(dimension == 8) anglais = true;
    else anglais = false;
}

std::ostream &operator<<(std::ostream &out, const PlateauDamier &damier) {
    if(!damier.anglais)out << "-------------------------------------------          ------------------------------------------- \n";
    else out << "-----------------------------------          ----------------------------------- \n";
    int h = 0;
    for(int i = 0; i < damier.dimension; i++){
        out << "| ";
        for(int j = 0; j < damier.dimension; j++){
            out << damier.cases[i][j].getPion().getImg() << " | ";
        }
        out << "         | ";
        for(int j = 0; j < damier.dimension; j++){
            if(i%2 == 0){
                if(j%2 == 1) {
                    out << std::get<0>(damier.posCase[h])+1 << " | ";
                    h++;
                }
                else out << "  | ";
            }else{
                if(j%2 != 1){
                    out << std::get<0>(damier.posCase[h])+1 << " | ";
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

const void PlateauDamier::initialize() const {
    int i_borne = 0;
    if(anglais) i_borne = 3;
    else i_borne = 4;
    int nb = 0;
    Pion p("PION", "\u26C0", Couleur::NOIR);
    for (int i = 0; i < i_borne; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 1) {
                    cases[i][j].setPion(p);
                    std::tuple<int, int,int> tmp  = {nb,i,j};
                    posCase[nb] = tmp;
                    nb++;
                }
            } else {
                if (j % 2 != 1) {
                    cases[i][j].setPion(p);
                    std::tuple<int,int,int> tmp = {nb,i,j};
                    posCase[nb] = tmp;
                    nb++;
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
                    std::tuple<int,int,int> tmp = {nb,i,j};
                    posCase[nb] = tmp;
                    nb++;
                }
            } else {
                if (j % 2 != 1) {
                    std::tuple<int,int,int> tmp = {nb,i,j};
                    posCase[nb] = tmp;
                    nb++;
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
                    cases[i][j].setPionBis(p2);
                    std::tuple<int,int,int> tmp = {nb,i,j};
                    posCase[nb] = tmp;
                    nb++;
                }
            } else {
                if (j % 2 != 1) {
                    cases[i][j].setPionBis(p2);
                    std::tuple<int,int,int> tmp = {nb,i,j};
                    posCase[nb] = tmp;
                    nb++;
                }
            }
        }
    }
}

std::tuple<int,int> PlateauDamier::nbCasetoCoord(int a) {
    int i_borne = 0;
    if(anglais) i_borne = 32;
    else i_borne = 50;
    for(int i = 0; i < i_borne; i++){
        if(std::get<0>(posCase[i]) == a-1) return {std::get<1>(posCase[i]), std::get<2>(posCase[i])};
    }
    return {-1,-1};
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

const void PlateauDamier::launcher() {
    std::cout << "Jeu de dames International:" << std::endl;
    std::cout << "Menu Principal:" << std::endl;
    again:
    std::cout << "Selectionnez votre type de jeu :" << std::endl;
    std::cout << "\t 1) Single Player" << std::endl;
    std::cout << "\t 2) 2P Game" << std::endl;
    std::string gameType = "";
    std::cin >> gameType;
    if (gameType != "1" && gameType != "2") {
        std::cout << "Mauvais Choix : Veuillez Selectionner 1 ou 2" << std::endl;
        goto again;
    } else {
        if (gameType == "1") {
            this->singlePlayer();
        }else if(gameType == "2"){
            this->twoPlayer();
        }
    }
    return;
}

const void PlateauDamier::twoPlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    while (true) {
        std::cout << *(this) << std::endl;
        this->playerTurn();
        std::cout << *(this) << std::endl;
        this->playerTurn2();
        std::cout << *(this) << std::endl;

    }
}

const void PlateauDamier::singlePlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    while (true) {
        std::cout << *(this) << std::endl;
        this->playerTurn();
        this->bot();
        std::cout << *(this) << std::endl;

    }
}

const bool PlateauDamier::pionSelect(int i_src, int j_src, Couleur c) {
    bool selectOk = false;
    if (i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension) {
        if (cases[i_src][j_src].getPion().getColor() == c) {
            selectOk = true;
        }
    }
    return selectOk;
}

const bool PlateauDamier::pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    if (posOk(i_src, j_src, i_dst, j_dst)) {
        if (cases[i_src][j_src].getPion().getColor() == Couleur::BLANC && c == Couleur::BLANC) {
            ////////////////////////////////////////////////////////////////////////////////
            //TODO: king anglais peut bouger dans tous les sens
            //TODO: if check gut : SET WHITE DAME HERE DUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUDE
            if (i_dst == 0) {
                Pion p2("KING", "\u26C1", Couleur::BLANC);
                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                cases[i_dst][j_dst].setPionBis(p2);
                return true;
            } else if (i_dst == dimension - 1 && !anglais) {
                Pion p2("KING", "\u26C3", Couleur::NOIR);
                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                cases[i_dst][j_dst].setPionBis(p2);
                return true;
            }
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (!cases[i_dst][j_dst].isEmpty() && cases[i_dst][j_dst].getPion().getColor() == Couleur::NOIR &&
                        (!(cases[i_dst][j_dst].getPion().getNom() == "KING") || (cases[i_dst][j_dst].getPion().getNom() == "KING" && anglais))) {
                    if (i_dst == i_src - 1) {
                        if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                            if (cases[i_dst - 1][j_dst + 1].isEmpty()) {
                                scoreJ1 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst - 1, j_dst + 1);
                                bool l = pionMove(i_dst - 1, j_dst + 1, i_dst - 1, j_dst - 1, Couleur::BLANC);
                                bool ld = pionMove(i_dst - 1, j_dst + 1, i_dst - 1, j_dst + 1, Couleur::BLANC);
                                if(!anglais) bool rd = pionMove(i_dst - 1, j_dst + 1, i_dst + 1, j_dst - 1, Couleur::BLANC);
                                if(!anglais) bool r = pionMove(i_dst - 1, j_dst + 1, i_dst + 1, j_dst + 1, Couleur::BLANC);
                            } else {
                                return false;
                            }
                        } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                            if (cases[i_dst - 1][j_dst - 1].isEmpty()) {
                                std::cout << "here" << std::endl;
                                scoreJ1 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst - 1, j_dst - 1);
                                bool l = pionMove(i_dst - 1, j_dst - 1, i_dst - 1, j_dst - 1, Couleur::BLANC);
                                bool ld = pionMove(i_dst - 1, j_dst - 1, i_dst - 1, j_dst + 1, Couleur::BLANC);
                                if(!anglais) bool rd = pionMove(i_dst - 1, j_dst - 1, i_dst + 1, j_dst - 1, Couleur::BLANC);
                                if(!anglais) bool r = pionMove(i_dst - 1, j_dst - 1, i_dst + 1, j_dst + 1, Couleur::BLANC);
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    } else if (cases[i_dst][j_dst].isEmpty() && i_dst == i_src - 1) {
                        move(i_src, j_src, i_dst, j_dst);
                    } else {
                        return false;
                    }
                } else if (i_dst == i_src + 1 && (!anglais || (anglais && cases[i_src][j_src].getPion().getNom() == "KING"))) {
                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                        if (cases[i_dst + 1][j_dst + 1].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst + 1, j_dst + 1);
                            bool l = pionMove(i_dst + 1, j_dst + 1, i_dst - 1, j_dst - 1, Couleur::BLANC);
                            bool ld = pionMove(i_dst + 1, j_dst + 1, i_dst - 1, j_dst + 1, Couleur::BLANC);
                            bool rd = pionMove(i_dst + 1, j_dst + 1, i_dst + 1, j_dst - 1, Couleur::BLANC);
                            bool r = pionMove(i_dst + 1, j_dst + 1, i_dst + 1, j_dst + 1, Couleur::BLANC);
                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                        if (cases[i_dst + 1][j_dst - 1].isEmpty()) {
                            std::cout << "here" << std::endl;
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst + 1, j_dst - 1);
                            bool l = pionMove(i_dst + 1, j_dst - 1, i_dst - 1, j_dst - 1, Couleur::BLANC);
                            bool ld = pionMove(i_dst + 1, j_dst - 1, i_dst - 1, j_dst + 1, Couleur::BLANC);
                            bool rd = pionMove(i_dst + 1, j_dst - 1, i_dst + 1, j_dst - 1, Couleur::BLANC);
                            bool r = pionMove(i_dst + 1, j_dst - 1, i_dst + 1, j_dst + 1, Couleur::BLANC);
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (cases[i_dst][j_dst].isEmpty() && i_dst == i_src - 1) {
                    move(i_src, j_src, i_dst, j_dst);
                    if (i_dst == 0) {
                        Pion p2("DAME", "\u26C1", Couleur::BLANC);
                        cases[i_dst][j_dst] = Case(i_dst, j_dst);
                        cases[i_dst][j_dst].setPionBis(p2);
                    }
                } else {
                    return false;
                }

            } else {
                std::cout << "Illegal movement" << std::endl;
                return false;
            }
        } else if (cases[i_src][j_src].getPion().getColor() == Couleur::NOIR && c == Couleur::NOIR &&
                (!(cases[i_dst][j_dst].getPion().getNom() == "KING") || (cases[i_dst][j_dst].getPion().getNom() == "KING" && anglais))) {
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (i_dst == i_src + 1) {
                    if (!cases[i_dst][j_dst].isEmpty() && cases[i_dst][j_dst].getPion().getColor() == Couleur::BLANC) {
                        if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                            if (cases[i_dst + 1][j_dst + 1].isEmpty()) {
                                scoreJ2 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst + 1, j_dst + 1);
                                if(!anglais) bool l = pionMove(i_dst + 1, j_dst + 1, i_dst - 1, j_dst - 1, Couleur::NOIR);
                                if(!anglais) bool ld = pionMove(i_dst + 1, j_dst + 1, i_dst - 1, j_dst + 1, Couleur::NOIR);
                                bool rd = pionMove(i_dst + 1, j_dst + 1, i_dst + 1, j_dst - 1, Couleur::NOIR);
                                bool r = pionMove(i_dst + 1, j_dst + 1, i_dst + 1, j_dst + 1, Couleur::NOIR);
                            } else {
                                return false;
                            }
                        } else if (j_dst - 1 < dimension && j_dst - 1 > 0) {
                            if (cases[i_dst + 1][j_dst - 1].isEmpty()) {
                                scoreJ1 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst + 1, j_dst - 1);
                                if(!anglais) bool l = pionMove(i_dst + 1, j_dst - 1, i_dst - 1, j_dst - 1, Couleur::NOIR);
                                if(!anglais) bool ld = pionMove(i_dst + 1, j_dst - 1, i_dst - 1, j_dst + 1, Couleur::NOIR);
                                bool rd = pionMove(i_dst + 1, j_dst - 1, i_dst + 1, j_dst - 1, Couleur::NOIR);
                                bool r = pionMove(i_dst + 1, j_dst - 1, i_dst + 1, j_dst + 1, Couleur::NOIR);
                            } else {
                                return false;
                            }
                        } else if (i_dst - 1 > 0 && i_dst - 1) {
                            return false;
                        }
                    } else if (i_dst == i_src + 1 && cases[i_dst][j_dst].isEmpty()) {
                        move(i_src, j_src, i_dst, j_dst);
                    } else {
                        return false;
                    }
                } else if (i_dst == i_src - 1 && (!anglais || (anglais && cases[i_src][j_src].getPion().getNom() == "KING"))) {
                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                        if (cases[i_dst - 1][j_dst + 1].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst - 1, j_dst + 1);
                            bool l = pionMove(i_dst - 1, j_dst + 1, i_dst - 1, j_dst - 1, Couleur::NOIR);
                            bool ld = pionMove(i_dst - 1, j_dst + 1, i_dst - 1, j_dst + 1, Couleur::NOIR);
                            bool rd = pionMove(i_dst - 1, j_dst + 1, i_dst + 1, j_dst - 1, Couleur::NOIR);
                            bool r = pionMove(i_dst - 1, j_dst + 1, i_dst + 1, j_dst + 1, Couleur::NOIR);
                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                        if (cases[i_dst - 1][j_dst - 1].isEmpty()) {
                            std::cout << "here" << std::endl;
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst - 1, j_dst - 1);
                            bool l = pionMove(i_dst - 1, j_dst - 1, i_dst - 1, j_dst - 1, Couleur::NOIR);
                            bool ld = pionMove(i_dst - 1, j_dst - 1, i_dst - 1, j_dst + 1, Couleur::NOIR);
                            bool rd = pionMove(i_dst - 1, j_dst - 1, i_dst + 1, j_dst - 1, Couleur::NOIR);
                            bool r = pionMove(i_dst - 1, j_dst - 1, i_dst + 1, j_dst + 1, Couleur::NOIR);
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (cases[i_dst][j_dst].isEmpty() && i_dst == i_src - 1) {
                    move(i_src, j_src, i_dst, j_dst);
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else {
            return false;
        }

    } else {
        return false;
    }
    return true;
}

void PlateauDamier::lectureFichierTest() {
    std::string path = "";
    if(anglais) path = "../dame_anglaise/test1.txt";
    else path = "../dame_international/test1.txt";
    std::ifstream infile(path);
    std::string line = "";
    std::string delimiter = " ";
    Couleur c = Couleur ::BLANC;
    int case_src = 0;
    int case_dst = 0;
    while(std::getline(infile, line)){
        case_src = std::stoi(line.substr(0, line.find(delimiter)));
        case_dst = std::stoi(line.substr(std::to_string(case_src).length()+1, 1));
        std::tuple<int,int> src = nbCasetoCoord(case_src);
        std::tuple<int,int> dst = nbCasetoCoord(case_dst);
        int i_src = std::get<0>(src);
        int j_src = std::get<1>(src);
        int i_dst = std::get<0>(dst);
        int j_dst = std::get<1>(dst);
        if(!anglais) {
            if (cases[i_src][j_src].getPion().getNom() == "Pion") pionMove(i_src, j_src, i_dst, j_dst, c);
        }

    }
}
