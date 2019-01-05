#ifndef BOARDGAMES_PlateauDamier_H
#define BOARDGAMES_PlateauDamier_H


#include <vector>
#include "PlateauCombinatoireAbstrait.h"
#include <sstream>
#include <algorithm>
#include <iostream>

class PlateauDamier: public PlateauCombinatoireAbstrait {
private:
    bool anglais = false;
    int scoreJ1 = 0;
    int scoreJ2 = 0;
    std::tuple<int,int,int> *posCase;
public:
    int turn = 0;
    explicit PlateauDamier(int dimension);
    const void initialize() const;
    friend std::ostream &operator<<(std::ostream &, const PlateauDamier &);
    const bool pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c);
    const bool posOk(int i_src, int j_src, int i_dst, int j_dst) const;
    std::tuple<int,int> nbCasetoCoord(int);

    bool bot();
    virtual const void playerTurn() = 0;
    virtual const void playerTurn2() = 0;
    const void launcher();
    const void singlePlayer();
    const void twoPlayer();
    const bool pionSelect(int i_src,int j_src,Couleur c);


};


#endif //BOARDGAMES_PlateauDamier_H
