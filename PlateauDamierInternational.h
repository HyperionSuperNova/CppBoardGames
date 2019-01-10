#ifndef CPLUSPROJ_PlateauDamierInternational_H
#define CPLUSPROJ_PlateauDamierInternational_H

#include <ostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>
#include "PlateauDamier.h"

class PlateauDamierInternational : public PlateauDamier {
private :
    std::stringstream ss;
public:
    PlateauDamierInternational();
    const bool kingMove(int i_src, int j_src,int i_dst, int j_dst, Couleur c);
    void save();
    void load();
};


#endif //CPLUSPROJ_PlateauDamierInternational_H
