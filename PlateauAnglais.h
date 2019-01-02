#ifndef BOARDGAMES_PLATEAUANGLAIS_H
#define BOARDGAMES_PLATEAUANGLAIS_H


#include <vector>
#include "PlateauCombinatoireAbstrait.h"
#include <sstream>
#include <algorithm>
#include <map>

class PlateauAnglais: public PlateauCombinatoireAbstrait {
public:
    int turn = 0;
    PlateauAnglais(int dimension);
    friend std::ostream &operator<<(std::ostream &os, const PlateauAnglais &damier);
    bool bot();
    const void playerTurn();
    std::vector <int> split(const std::string &s, char delimiter);
    const void launcher();
    const void singlePlayer();
    const bool pionSelect(int i_src,int j_src,Couleur c);
};


#endif //BOARDGAMES_PLATEAUANGLAIS_H
