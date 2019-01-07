#include "Plateau.h"

Case Plateau::getCase(int i) const{
    return this->cases[i];
}

void Plateau::setCase(int i, Pion p) {
    cases[i].setPion(p);
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

int Plateau::getDimension() const{
    return dimension;
}

void Plateau::setDimension(int d) {
    dimension = d;
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


void Plateau::setCases(int i, Pion p) {
    cases[i].setPion(p);
}



Plateau::~Plateau() {}

