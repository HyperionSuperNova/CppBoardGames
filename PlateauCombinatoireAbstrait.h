//
// Created by merat on 30/12/18.
//

#ifndef BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H
#define BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H


#include "Plateau.h"

class PlateauCombinatoireAbstrait: public Plateau {
public:
    friend std::ostream &operator<<(std::ostream &, const Plateau &);

};


#endif //BOARDGAMES_PLATEAUCOMBINATOIREABSTRAIT_H
