//
// Created by merat on 03/01/19.
//

#ifndef BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H
#define BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H

#include "Plateau.h"

class PlateauCombinatoireAbstrait: public Plateau {
public:
    int dimension;
    PlateauCombinatoireAbstrait(int dimension);
};


#endif //BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H
