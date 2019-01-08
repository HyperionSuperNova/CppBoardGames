#include "Case.h"

Case::Case() {}

Case::Case(int ii, int jj) {
    x = ii;
    y = jj;
    pion = Pion();
}

Pion Case::getPion() {
    return pion;
}

int Case::getX() {
    return x;
}

int Case::getY() {
    return y;
}

void Case::setPion(Pion p) {
    pion = p;
}

void Case::setPionImg(std::string im) {
    pion.setImg(im);
}

bool Case::isEmpty() {
    return pion.getNom().compare("") == 0;
}

std:: ostream& operator<<(std::ostream & out, const Case &c) {
    out << c.pion;
    return out;
}

void Case::setPionBis(Pion &p) {
    this->pion = p;
}



