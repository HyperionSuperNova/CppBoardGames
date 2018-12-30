#ifndef CPLUSPROJ_PLATEAUDAMIER_H
#define CPLUSPROJ_PLATEAUDAMIER_H

#include <ostream>
#include <vector>
#include "Plateau.h"

class PlateauDamier : public Plateau {
public:
    int scoreJ1 = 0;
    int scoreJ2 = 0;
    int turn = 0;
    PlateauDamier(int dimension);
    friend std::ostream &operator<<(std::ostream &os, const PlateauDamier &damier);
    const void initialize() const;
    const bool posOk(int i_src, int j_src,int i_dst, int j_dst) const;
    const bool pionMove(int i_src, int j_src,int i_dst, int j_dst, Couleur c);
    bool bot();
    const void playerTurn();
    std::vector <int> split(const std::string &s, char delimiter);
    const void launcher();
    const void singlePlayer();
    const bool pionSelect(int i_src,int j_src,Couleur c);
};


#endif //CPLUSPROJ_PLATEAUDAMIER_H
