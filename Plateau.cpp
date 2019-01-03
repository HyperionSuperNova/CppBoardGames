#include "Plateau.h"

Case Plateau::getCase(int i, int j) {
    return this->cases[i][j];
}

void Plateau::setCase(int i, int j, Pion p) {
    this->cases[i][j].setPion(p);
}

std:: ostream& operator<<(std::ostream & out, const Plateau &p) {
    out << "-------------------------------------------\n";
    for(int i = 0; i < p.dimension; i++){
        out << "| ";
        for(int j = 0; j < p.dimension; j++){
            out << p.cases[i][j].getPion().getImg() << " | ";
        }
        out << "\n";
    }
    out << "-------------------------------------------";
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

const void Plateau::move(int i_src, int j_src, int i_dst, int j_dst) const {
    Case c = cases[i_dst][j_dst];
    cases[i_dst][j_dst] = cases[i_src][j_src];
    cases[i_src][j_src] = c;
}


Plateau::~Plateau() {}

