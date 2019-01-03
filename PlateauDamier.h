#ifndef CPLUSPROJ_PLATEAUDAMIER_H
#define CPLUSPROJ_PLATEAUDAMIER_H

#include <ostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include "PlateauCombinatoireAbstrait.h"

class PlateauDamier : public PlateauCombinatoireAbstrait {
public:
    PlateauDamier();
    const bool kingMove(int i_src, int j_src,int i_dst, int j_dst, Couleur c);
    const void playerTurn();
    const void playerTurn2();
};


#endif //CPLUSPROJ_PLATEAUDAMIER_H
