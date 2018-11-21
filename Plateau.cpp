//
// Created by merat on 15/11/18.
//

#include "Plateau.h"

Case Plateau::getCase(int i, int j) {
    return this->cases[i][j];
}

void Plateau::setCase(int i, int j, Pion p) {
    this->cases[i][j].setPion(p);
}

std:: ostream& operator<<(std::ostream & out, const Plateau &p) {
    out << "---------------------------------\n";
    out << "  ";
    for(int j = 0; j < p.dimension; j++){
        out << j << "  ";
    }
    out << "\n";
    for(int i = 0; i < p.dimension; i++){
        out << i << "| ";
        for(int j = 0; j < p.dimension; j++){
            out << p.cases[i][j].getPion().getImg() << " | ";
        }
        out << "\n";
    }
    out << "---------------------------------";
    return out;
}

Plateau::Plateau(int dimension) : dimension(dimension) {
    cases = new Case * [dimension];
    for(int i = 0; i < dimension; i++){
        cases[i] = new Case[dimension];
        for(int j = 0; j < dimension; j++){
            cases[i][j] = Case(i,j);
        }
    }
}

Plateau::~Plateau() {}

