//
// Created by merat on 30/12/18.
//

#ifndef BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H
#define BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H


#include "Plateau.h"

class PlateauCombinatoireAbstrait: public Plateau {
private:
    bool anglais = false;
    int scoreJ1 = 0;
    int scoreJ2 = 0;
public:
    PlateauCombinatoireAbstrait(int dimension);
    const void initialize() const;
    friend std::ostream &operator<<(std::ostream &, const Plateau &);
    const bool pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c);
    const bool posOk(int i_src, int j_src, int i_dst, int j_dst) const;


};


#endif //BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H
