//
// Created by merat on 15/11/18.
//

#include "Pion.h"


std::ostream &operator<<(std::ostream &os, const Pion &pion) {
    return os;
}

Pion::Pion(const std::string &name) : name(name) {}

Pion::Pion(const std::string &name, const std::string &img, Couleur c) : name(name), img(img), color(c) {}

Pion::Pion() {

}

std::string Pion::getNom() {
    return name;
}

Couleur Pion::getColor() {
    return color;
}

void Pion::setNom(std::string n) {
    name = n;
}

void Pion::setImg(std::string i) {
    img = i;
}

std::string Pion::getImg() {
    return img;
}

