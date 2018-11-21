//
// Created by stryker on 16/11/18.
//

#ifndef CPLUSPROJ_PLATEAUDAMIER_H
#define CPLUSPROJ_PLATEAUDAMIER_H

#include <ostream>
#include <vector>
#include "Plateau.h"

class PlateauDamier : public Plateau {
public:
    PlateauDamier(int dimension);
    friend std::ostream &operator<<(std::ostream &os, const PlateauDamier &damier);
    const void initialize() const;
    
};


#endif //CPLUSPROJ_PLATEAUDAMIER_H
