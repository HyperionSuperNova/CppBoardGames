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
    const bool kingMove(int i_src, int j_src,int i_dst, int j_dst, Couleur c);
    const bool playerTurn(int, int,int,int);
    const bool playerTurn2(int,int,int,int);

};


#endif //BOARDGAMES_PlateauDamierAnglais_H
