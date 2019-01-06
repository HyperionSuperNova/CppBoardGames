#ifndef BOARDGAMES_PlateauDamier_H
#define BOARDGAMES_PlateauDamier_H


#include <vector>
#include "PlateauCombinatoireAbstrait.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>

typedef std::tuple<int,int,int> tuple;

class PlateauDamier: public PlateauCombinatoireAbstrait {
protected:
    bool anglais = false;
    int scoreJ1 = 0;
    int scoreJ2 = 0;
    std::vector<tuple*> posCase;
    friend class boost::serialization::access;
    template<class Archive> void serialize(Archive &ar, const unsigned int version){
        ar &scoreJ1;
        ar &scoreJ2;
        ar &anglais;
        ar &cases;
    }
public:
    void ajoutePosCase(tuple*);
    int turn = 0;
    explicit PlateauDamier(int dimension);
    const void initialize();
    const bool pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c);
    const bool posOk(int i_src, int j_src, int i_dst, int j_dst) const;
    std::tuple<int,int> nbCasetoCoord(int);

    const void lectureFichierTest();

    bool bot();
    virtual const void playerTurn(int,int,int,int) = 0;
    virtual const void playerTurn2(int,int,int,int) = 0;
    void help(Couleur);
    const void launcher();
    const void singlePlayer();
    const void twoPlayer();
    const bool pionSelect(int i_src,int j_src,Couleur c);

    friend std::ostream &operator<<(std::ostream &os, const PlateauDamier &damier);


};


#endif //BOARDGAMES_PlateauDamier_H