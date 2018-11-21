//
// Created by merat on 16/11/18.
//

#ifndef CPLUSPROJ_PLATEAUSTRATEGO_H
#define CPLUSPROJ_PLATEAUSTRATEGO_H


#include "Plateau.h"
#include <tuple>

class PlateauStratego: public Plateau {
private:
    std::tuple<int, std::string> pions[12] = {{0,"Drapeau"},{1,"Espion"},{2,"Eclaireur"},{3,"Demineur"},{4,"Sergent"},{5,"Lieutenant"},{6,"Capitaine"},{7,"Commandant"},{8,"Colonnel"},{9,"General"},{10,"Marechal"},{11,"Bombe"}};
    std::tuple<int, std::string> img[12] = {{0,"\u26FF"},{1,"\u2460"},{2,"\u2461"},{3,"\u2462"},{4,"\u2463"},{5,"\u2464"},{6,"\u2465"},{7,"\u2466"},{8,"\u2467"},{9,"\u2468"},{10,"\u2469"},{11,"\u2688"}};
    // 11 -> Bombe | 1 -> Espion | 2 -> Eclaireur | 3 -> Demineur | 4 -> Sergent | 5 -> Lieutenant | 6 -> Capitaine | 7 -> Commandant | 8 -> Colonnel | 9 -> General | 10 -> Marechal | 0 -> drapeau
    int joueur1[12] = {1,1,8,5,4,4,4,3,2,1,1,6};
    int joueur2[12] = {1,1,8,5,4,4,4,3,2,1,1,6};
public:
    PlateauStratego();
    friend std::ostream &operator<<(std::ostream &os, const PlateauStratego &stratego);
    bool mouvement_eclaireur(int , int, int, int, bool);
    bool mouvement_autre(int, int, int, int, bool);
    bool estPlusFortQue(Pion p1, Pion p2);
    void mettrePionJoueurSurPlateau(bool);
    void cacherPieceJoueur(bool);
    void revelerUnePiece(int, int);
    void mettrePionOrdiSurPlateau();

    int getNbrBombe(bool joueur);
    int getNbrDrapeau(bool joueur);
    int getNbrEspion(bool joueur);
    int getNbrEclaireur(bool joueur);
    int getNbrDemineur(bool joueur);
    int getNbrSergent(bool joueur);
    int getNbrLieutenant(bool joueur);
    int getNbrCapitaine(bool joueur);
    int getNbrCommandant(bool joueur);
    int getNbrColonnel(bool joueur);
    int getNbrGeneral(bool joueur);
    int getNbrMarechal(bool joueur);

    void afficher();

    int renvoiePionsNbr(std::string);

    void launchStratego();
};


#endif //CPLUSPROJ_PLATEAUSTRATEGO_H