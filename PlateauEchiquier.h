#ifndef BOARDGAMES_PLATEAUECHIQUIER_H
#define BOARDGAMES_PLATEAUECHIQUIER_H

#include "PlateauCombinatoireAbstrait.h"
#include <tuple>

class PlateauEchiquier: public PlateauCombinatoireAbstrait {
private:
    std::tuple<int,char>alpha[8] = {{0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}, {4, 'E'}, {5, 'F'}, {6, 'G'}, {7, 'H'}};
    std::tuple<int, int, std::string>joueur1[16] = {{7,0, "Tour"},{7,1,"Cavalier"},{7,2,"Fou"},{7,3,"Dame"},{7,4,"Roi"},{7,5,"Fou"},{7,6,"Cavalier"},{7,7,"Tour"},{6,0,"Pion"},{6,1,"Pion"},{6,2,"Pion"},{6,3,"Pion"},{6,4,"Pion"},{6,5,"Pion"},{6,6,"Pion"},{6,7,"Pion"}};
    std::tuple<int, int, std::string>joueur2[16] = {{0,0, "Tour"},{0,1,"Cavalier"},{0,2,"Fou"},{0,3,"Dame"},{0,4,"Roi"},{0,5,"Fou"},{0,6,"Cavalier"},{0,7,"Tour"},{1,0,"Pion"},{1,1,"Pion"},{1,2,"Pion"},{1,3,"Pion"},{1,4,"Pion"},{1,5,"Pion"},{1,6,"Pion"},{1,7,"Pion"}};
    std::string ordiPiece[16] = {"","","","","","","","","","","","","","","",""};
    std::tuple<int, int>coord = {0,0};

    std::tuple<int,int,std::string>dernier_mouv[2] = {{-1,-1,""}, {-1,-1,""}};
    std::string piece_bouffee = "";

    bool les2RoisontSurLePlateau;
public:
    PlateauEchiquier();

    friend std::ostream &operator<<(std::ostream &os, const PlateauEchiquier &echiquier);

    bool pieceASoi(int, int, bool);

    bool mouvement_pion(std::string, bool);
    bool mouvement_tour(std::string, bool);
    bool mouvement_cavalier(std::string, bool);
    bool mouvement_fou(std::string, bool);
    bool mouvement_dame(std::string, bool);
    bool mouvement_roi(std::string, bool);

    bool mouvement(std::string,bool, std::string);

    bool roiEStEnEchec(bool);
    bool roiEstSurDiagonaleDeFou(bool);
    bool roiEstSurCaseCavalier(bool);
    bool roiACotePion(bool);

    std::tuple<int,int> ouEstCavalier(int, int, bool);
    std::tuple<int,int> ouEstFou(int,int,bool);
    std::tuple<int,int> ouEstTour(int, int, bool);
    std::tuple<int,int> ouEstRoi(int, int, bool);
    std::tuple<int,int> ouEstDame(int, int, bool);


    std::string quelleImage(std::string, bool);

    std::string helpCavalier(bool);
    std::string helpTour(bool);
    std::string helpFou(bool);
    std::string helpPion(bool);
    std::string helpDame(bool);
    std::string helpRoi(bool);
    std::string help(bool);

    void posOrdiPiece();


    bool fouPeutIlYAller(int, int, int, int);
    bool tourPeutElleYAller(int, int, int, int);

    int getEquivalenceAlpha(char);
    char getEquivalenceNum(int);

    void pionDetruit(int, int, bool);

    void launchEchiquier(bool);
};


#endif //BOARDGAMES_PLATEAUECHIQUIER_H
