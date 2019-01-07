#include "Plateau.h"

Case Plateau::getCase(int i, int j) {
    return this->cases[i*dimension+j];
}

void Plateau::setCase(int i, int j, Pion p) {
    cases[i*dimension+j].setPion(p);
}

std:: ostream& operator<<(std::ostream & out, const Plateau &p) {
    out << "-------------------------------------------\n";
    for(int i = 0; i < p.dimension; i++){
        out << "| ";
        for(int j = 0; j < p.dimension; j++){
            out << p.cases[i*p.dimension+j].getPion().getImg() << " | ";
        }
        out << "\n";
    }
    out << "-------------------------------------------";
    return out;
}

Plateau::Plateau(int dimension) : dimension(dimension) {
    cases = new Case [dimension*dimension];
    for(int i = 0; i < dimension; i++){
        for(int j = 0; j < dimension; j++){
            cases[i*dimension+j] = Case(i,j);
        }
    }
}

const void Plateau::move(int i_src, int j_src, int i_dst, int j_dst) const {
    Case c = cases[i_dst*dimension+j_dst];
    cases[i_dst*dimension+j_dst] = cases[i_src*dimension+j_src];
    cases[i_src*dimension+j_src] = c;
}

Case* Plateau::getCases() {
    return cases;
}

void Plateau::setCases(int i, int j, Pion p) {
    setCase(i,j,p);
}


Plateau::~Plateau() {}

