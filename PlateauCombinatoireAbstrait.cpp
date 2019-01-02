#include <sstream>
#include <algorithm>
#include <map>
#include "PlateauCombinatoireAbstrait.h"

PlateauCombinatoireAbstrait::PlateauCombinatoireAbstrait(int dimension) : Plateau(dimension) {
    if(dimension == 8) anglais = true;
    else anglais = false;
}

std::ostream &operator<<(std::ostream &os, const PlateauCombinatoireAbstrait &damier) {
    os << static_cast<const Plateau &>(damier);
    return os;
}

const void PlateauCombinatoireAbstrait::initialize() const {
    int i_borne = 0;
    if(anglais) i_borne = 3;
    else i_borne = 4;
    Pion p("PION", "\u26C0", Couleur::NOIR);
    for (int i = 0; i < i_borne; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    cases[i][j].setPion(p);
                }
            } else {
                if (j % 2 != 0) {
                    cases[i][j].setPion(p);
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
                if (j % 2 == 0) {
                    cases[i][j].setPionBis(p2);
                }
            } else {
                if (j % 2 != 0) {
                    cases[i][j].setPionBis(p2);
                }
            }
        }
    }
}


const bool PlateauCombinatoireAbstrait::posOk(int i_src, int j_src, int i_dst, int j_dst) const {
    bool cartesianConstraint =
            i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension && i_dst >= 0 && i_dst < dimension &&
            j_dst >= 0 && j_dst < dimension;
    return cartesianConstraint;
}


bool PlateauCombinatoireAbstrait::bot() {
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

std::vector<int> PlateauCombinatoireAbstrait::split(const std::string &s, char delimiter) {
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

const void PlateauCombinatoireAbstrait::launcher() {
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

const void PlateauCombinatoireAbstrait::singlePlayer() {
    this->initialize();
    std::cout << "IT'S P1 TURN !!" << std::endl;
    while (true) {
        std::cout << *(this) << std::endl;
        this->playerTurn();
        this->bot();
        std::cout << *(this) << std::endl;

    }
}

const bool PlateauCombinatoireAbstrait::pionSelect(int i_src, int j_src, Couleur c) {
    bool selectOk = false;
    if (i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension) {
        if (cases[i_src][j_src].getPion().getColor() == c) {
            selectOk = true;
        }
    }
    return selectOk;
}

const bool PlateauCombinatoireAbstrait::pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    if (posOk(i_src, j_src, i_dst, j_dst)) {
        if (cases[i_src][j_src].getPion().getColor() == Couleur::BLANC && c == Couleur::BLANC) {
            ////////////////////////////////////////////////////////////////////////////////
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
                    !(cases[i_dst][j_dst].getPion().getNom() == "KING")) {
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
                   !(cases[i_dst][j_dst].getPion().getNom() == "KING")) {
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
