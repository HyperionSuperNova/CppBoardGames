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
    const void playerTurn(int, int,int,int);
    const void playerTurn2(int,int,int,int);

};


#endif //BOARDGAMES_PlateauDamierAnglais_H
