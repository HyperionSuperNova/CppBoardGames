#include "Case.h"

Case::Case() {}

Case::Case(int ii, int jj) {
    x = ii;
    y = jj;
    pion = new Pion();
}

Pion *Case::getPion() {
    return pion;
}


void Case::setPion(Pion &p) {
    pion = new Pion(p.getNom(), p.getImg(), p.getColor());
}


bool Case::isEmpty() {
    return pion->getNom().compare("") == 0;
}

std:: ostream& operator<<(std::ostream & out, const Case &c) {
    out << c.pion;
    return out;
}



