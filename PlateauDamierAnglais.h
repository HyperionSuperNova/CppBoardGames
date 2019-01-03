#ifndef BOARDGAMES_PlateauDamierAnglais_H
#define BOARDGAMES_PlateauDamierAnglais_H


#include <vector>
#include "PlateauDamier.h"
#include <sstream>
#include <algorithm>
#include <map>

class PlateauDamierAnglais: public PlateauDamier {
public:
    PlateauDamierAnglais();
    const void playerTurn();
    const void playerTurn2();
};


#endif //BOARDGAMES_PlateauDamierAnglais_H
