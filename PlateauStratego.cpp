//
// Created by merat on 16/11/18.
//

#include <fstream>
#include "PlateauStratego.h"

PlateauStratego::PlateauStratego(): Plateau(10) {};

std::ostream &operator<<(std::ostream &os, const PlateauStratego &stratego) {
    os << static_cast<const Plateau &>(stratego);
    return os;
}

void PlateauStratego::afficher() {
    std::cout << "---------------------------------\n";
    std::cout << "  ";
    for(int j = 0; j < 10; j++){
        std::cout << j << "   ";
    }
    std::cout << "\n";
    for(int i = 0; i < 10; i++){
        std::cout << i << "|  ";
        for(int j = 0; j < 10; j++){
            if((i == 4 || i == 5) && (j == 2 || j == 6)) std::cout << "    ";
            else std::cout <<this->cases[i][j].getPion().getImg() << " | " ;

        }
        std::cout << "\n";
    }
    std::cout << "---------------------------------" << std::endl;
}

bool PlateauStratego::mouvement_eclaireur(int i_src, int j_src, int i_dst, int j_dst, bool joueur) {
    bool ok = true;
    int min = 0;
    int max = 0;
    if( i_dst < 10 && j_dst < 10){
        if(i_dst == i_src){
            if(j_dst > j_src) {
                min = j_src + 1;
                max = j_dst;
            }else {
                min = j_dst;
                max = j_src - 1;
            }
            for(int j = min; j < max; j++){
                std::cout << "j: " << cases[i_src][j].getPion().getNom() << std::endl;
                if(!cases[i_src][j].isEmpty() || ((i_src == 4 || i_src == 5) && (j == 2 || j == 3 || j == 6 || j == 7))){
                    std::cout << "Mouvement impossible. Case non vide sur le chemin";
                    return 0;
                }
            }
                if(cases[i_dst][j_dst].isEmpty() || estPlusFortQue(cases[i_src][j_src].getPion(), cases[i_dst][j_dst].getPion()) ){
                    if(joueur){
                        joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                    }else{
                        joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                    }
                    cases[i_dst][j_dst] = cases[i_src][j_src];
                    cases[i_src][j_src] = Case(i_src, j_src);
                    return 1;
                }else{
                    if(cases[i_src][j_src].getPion().getNom().compare(cases[i_dst][j_dst].getPion().getNom()) == 0){
                        if(joueur){
                            joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                            joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                        }else{
                            joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                            joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        }
                        cases[i_src][j_src] = Case(i_src, j_src);
                        cases[i_dst][j_dst] = Case(i_dst, j_dst);
                    }else {
                        revelerUnePiece(i_dst, j_dst);
                        if(joueur){ // si c'est le joueur 1 qui joue
                            joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        }else{
                            joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        }
                        cases[i_src][j_src] = Case(i_src, j_src);
                    }
                    return 1;
                }



        }else if (j_dst == j_src){
            if(i_dst > i_src) {
                min = i_src + 1;
                max = i_dst;
            }else {
                min = i_dst;
                max = i_src - 1;
            }
            for(int i = min; i < max; i++){
                if(!cases[i][j_src].isEmpty() ||  ((i == 4 || i == 5) && (j_src == 2 || j_src == 3 || j_src == 6 || j_src == 7))){
                    std::cout << "Mouvement impossible. Case non vide sur le chemin";
                    return 0;
                }
            }
                if(cases[i_dst][j_dst].isEmpty() || estPlusFortQue(cases[i_src][j_src].getPion(), cases[i_dst][j_dst].getPion()) ){
                    if(joueur){
                        joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                    }else{
                        joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                    }
                    cases[i_dst][j_dst] = cases[i_src][j_src];
                    cases[i_src][j_src] = Case(i_src, j_src);
                    return 1;
                }else{
                    if(cases[i_src][j_src].getPion().getNom().compare(cases[i_dst][j_dst].getPion().getNom()) == 0){
                        if(joueur){
                            joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                            joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                        }else{
                            joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                            joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        }
                        cases[i_src][j_src] = Case(i_src, j_src);
                        cases[i_dst][j_dst] = Case(i_dst, j_dst);
                    }else {
                        revelerUnePiece(i_dst, j_dst);
                        if(joueur){ // si c'est le joueur 1 qui joue
                            joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        }else{
                            joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        }
                        cases[i_src][j_src] = Case(i_src, j_src);
                    }
                    return 1;
                }
        }else{
            std::cout << "mouvement impossible";
            return 0;
        }
    }else{
        std::cout << "Out of Bounds" << std::endl;
        return 0;
    }
}

bool PlateauStratego::mouvement_autre(int i_src, int j_src, int i_dst, int j_dst, bool joueur) {
    if( i_dst < 10 && j_dst < 10){
        if((i_dst == i_src -1 && j_dst == j_src) || (i_dst == i_src +1 && j_dst == j_src) || (i_dst == i_src && j_dst == j_src -1) || (i_dst == i_src && j_dst == j_src + 1)){
            if(cases[i_dst][j_dst].isEmpty() || estPlusFortQue(cases[i_src][j_src].getPion(), cases[i_dst][j_dst].getPion()) ) {
                if(joueur){
                    joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }else{
                    joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src, j_src);
            }else{
                if(cases[i_src][j_src].getPion().getNom().compare(cases[i_dst][j_dst].getPion().getNom()) == 0){
                    if(joueur){
                        joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                    }else{
                        joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                        joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }
                    cases[i_src][j_src] = Case(i_src, j_src);
                    cases[i_dst][j_dst] = Case(i_dst, j_dst);
                }else {
                    if(joueur){ // si c'est le joueur 1 qui joue
                        joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }else{
                        joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }
                    cases[i_src][j_src] = Case(i_src, j_src);
                }
            }
        }else{
            std::cout << "mouvement impossible";
            return 0;
        }
        return 1;
    }else{
        std::cout << "Out of Bounds" << std::endl;
        return 0;
    }
}

bool PlateauStratego::estPlusFortQue(Pion p1, Pion p2) {
    int p1_value = 0;
    int p2_value = 0;
    for(int i = 0; i < 12; i++){
        if(p1.getNom().compare(std::get<1>(pions[i])) == 0){
            p1_value = std::get<0>(pions[i]);
        }
        if(p2.getNom().compare(std::get<1>(pions[i])) == 0){
            p2_value = std::get<0>(pions[i]);
        }
    }
    return (p1_value > p2_value) || (p1_value == 1 && p2_value == 10) || (p1_value == 3 && p2_value == 11);

}

int PlateauStratego::getNbrBombe(bool joueur) {
    if(joueur){ // joueur1
        return joueur1[11];
    }else return joueur2[11];
}

int PlateauStratego::getNbrCapitaine(bool joueur) {
    if(joueur) return joueur1[6];
    else return joueur2[6];
}

int PlateauStratego::getNbrColonnel(bool joueur) {
    if(joueur) return joueur1[8];
    else return joueur2[8];
}

int PlateauStratego::getNbrCommandant(bool joueur) {
    if(joueur) return joueur1[7];
    else return joueur2[7];
}

int PlateauStratego::getNbrDemineur(bool joueur) {
    if(joueur) return joueur1[3];
    else return joueur2[3];
}

int PlateauStratego::getNbrDrapeau(bool joueur) {
    if(joueur) return joueur1[0];
    else return joueur2[0];
}

int PlateauStratego::getNbrEclaireur(bool joueur) {
    if(joueur) return joueur1[2];
    else return joueur2[2];
}

int PlateauStratego::getNbrEspion(bool joueur) {
    if(joueur) return joueur1[1];
    else return joueur2[1];
}

int PlateauStratego::getNbrGeneral(bool joueur) {
    if(joueur) return joueur1[9];
    else return joueur2[9];
}

int PlateauStratego::getNbrLieutenant(bool joueur) {
    if(joueur) return joueur1[5];
    else return joueur2[5];
}

int PlateauStratego::getNbrMarechal(bool joueur) {
    if(joueur) return joueur1[10];
    else return joueur2[10];
}

int PlateauStratego::getNbrSergent(bool joueur) {
    if(joueur) return joueur1[4];
    else return joueur2[4];
}

int PlateauStratego::renvoiePionsNbr(std::string s) {
    for(int i = 0; i < 12; i++){
        if(std::get<1>(pions[i]).compare(s) == 0) return std::get<0>(pions[i]);
    }
    return -1;
}

void PlateauStratego::mettrePionJoueurSurPlateau(bool joueur) {
    if(joueur) cacherPieceJoueur(false);
    else cacherPieceJoueur(true);
    std::string piece= "";
    std::string ii = "";
    std::string jj = "";
    int j = 0;
    std::string delimiter = " ";
    for(int h = 0; h < 2; h++){ // valeur h a changer
        afficher();
        std::cout << "\nEspion (" << getNbrEspion(joueur) << ") Drapeau (" << getNbrDrapeau(joueur) << ") Eclaireur (" << getNbrEclaireur(joueur) << ") Demineur (" << getNbrDemineur(joueur) << ") Sergent (" << getNbrSergent(joueur) << ") Lieutenant (" << getNbrLieutenant(joueur) << ") Capitaine (" << getNbrCapitaine(joueur) << ") Commandant (" << getNbrCommandant(joueur) << ") Colonnel (" << getNbrColonnel(joueur) << ") General (" << getNbrGeneral(joueur) << ") Marechal (" << getNbrMarechal(joueur) << ") Bombe (" << getNbrBombe(joueur) << ")" << std::endl;
        std::cout << "Format: Nom de la piece  cordonnées: x y" << std::endl;
        std::cout << "Par exemple: Demineur 1 1" << std::endl;

        std::cin >> piece;
        std::cin >> ii;
        std::cin >> jj;

        int i = std::stoi(ii);
        int j = std::stoi(jj);

        int borne = 0;
        if(joueur) borne = 3;
        else borne = 6;
        if( (joueur && i <= borne) || (!joueur && i >= borne)){ // pour que joueur place leur pièce du bon cote
            if((i == 4 || i == 5) && (j == 2 || j == 3 || j == 6 || j == 7)){
                std::cout << "Vous ne pouvez pas mettre de pièce ici." << std::endl;
                h--;
            }else if(cases[i][j].isEmpty()){
                if(joueur) {
                    if (joueur1[renvoiePionsNbr(piece)] > 0) {
                        std::string imag = std::get<1>(img[renvoiePionsNbr(piece)]);
                        std::cout << "i: " << i << " j: " << j << std::endl;
                        cases[i][j].setPion(Pion(piece, imag, Couleur::BLANC));
                        joueur1[renvoiePionsNbr(piece)]--;
                    } else {
                        std::cout << "Vous n'avez plus ce genre de pièce." << std::endl;
                        h--;
                    }
                }else{
                    if (joueur2[renvoiePionsNbr(piece)] > 0) {
                        std::string img = std::to_string(renvoiePionsNbr(piece));
                        cases[i][j].setPion(Pion(piece, img, Couleur::NOIR));
                        joueur2[renvoiePionsNbr(piece)]--;
                    } else {
                        std::cout << "Vous n'avez plus ce genre de pièce." << std::endl;
                        h--;
                    }
                }
            }
            else{
                std::cout << "La case n'est pas vide. réésayez\n";
                h--;
            }
        }else{
            std::cout << "Vous ne pouvez pas mettre pièce ici.\n";
            h--;
        }
    }
    std::cout << "Let's the game begin!" << std::endl;
}

void PlateauStratego::mettrePionOrdiSurPlateau() {
    int r = rand() % 2 + 1;
    std::string piece = "";
    int i = 0;
    int j = 0;
    std::string delimiter = " ";

    std::string nom = "ordi" + std::to_string(r) + ".txt";
    std::string path = "/home/merat/Bureau/Master/M1/CppBoardGames/ordi/" + nom;
    std::cout << path << std::endl;
    std::ifstream infile(path);
    std::string line = "";
    while(std::getline(infile, line)){
        piece = line.substr(0, line.find(delimiter));
        i = std::stoi(line.substr(piece.length()+1, 1));
        j = std::stoi(line.substr(piece.length()+3, 1));
        std::cout << i << " " << j << " " << piece << std::endl;
        cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::NOIR));
    }}

void PlateauStratego::cacherPieceJoueur(bool joueur) {
    if(joueur){// ici joueur1
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(cases[i][j].getPion().getColor() == Couleur::BLANC) cases[i][j].setPionImg("\u2610");
                else if(cases[i][j].getPion().getColor() == Couleur::NOIR){
                    std::string nom = cases[i][j].getPion().getNom();
                    std::string im = std::get<1>(img[renvoiePionsNbr(nom)]);
                    cases[i][j].setPionImg(im);
                }

            }
        }
    }else{
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(cases[i][j].getPion().getColor() == Couleur::NOIR){
                    cases[i][j].setPionImg("\u2610");
                }
                else if(cases[i][j].getPion().getColor() == Couleur::BLANC){
                    std::string nom = cases[i][j].getPion().getNom();
                    std::string im = std::get<1>(img[renvoiePionsNbr(nom)]);
                    cases[i][j].setPionImg(im);
                }
            }
        }
    }
}

void PlateauStratego::revelerUnePiece(int i, int j) {
    std::string nom = cases[i][j].getPion().getNom();
    int n = renvoiePionsNbr(nom);
    cases[i][j].setPionImg(std::get<1>(img[n]));
}

void PlateauStratego::launchStratego() {
    mettrePionOrdiSurPlateau();
    mettrePionJoueurSurPlateau(true);
    //mettrePionJoueurSurPlateau(false);
    bool quiJoue = true; //joueur 1

    joueur1[0] = 1; joueur1[1] = 1; joueur1[2] = 8; joueur1[3] = 5; joueur1[4] = 4; joueur1[5] = 4; joueur1[6] = 4; joueur1[7] = 3; joueur1[8] = 2; joueur1[9] = 1; joueur1[10] = 1; joueur1[11] = 6;
    joueur2[0] = 1; joueur2[1] = 1; joueur2[2] = 8; joueur2[3] = 5; joueur2[4] = 4; joueur2[5] = 4; joueur2[6] = 4; joueur2[7] = 3; joueur2[8] = 2; joueur2[9] = 1; joueur2[10] = 1; joueur2[11] = 6;


    std::string ii = "";
    std::string jj = "";
    while(joueur1[0] != 0 && joueur2[0] != 0){
        next_loop:
        afficher();
        if(quiJoue){
            std::cout << "Tour joueur 1: " << std::endl;
            cacherPieceJoueur(!quiJoue);
        }else{
            std::cout << "Tour joueur 2: " << std::endl;
            cacherPieceJoueur(!quiJoue);
        }
        std::cin >> ii;
        std::cin >> jj;

        int i_src = std::stoi(ii);
        int j_src = std::stoi(jj);

        std::cin >> ii;
        std::cin >> jj;

        int i_dst = std::stoi(ii);
        int j_dst = std::stoi(jj);

        if(quiJoue){
            if(cases[i_src][j_src].getPion().getColor() == Couleur::NOIR){
                std::cout << "Ce n'est pas une pièce à vous." << std::endl;
                goto next_loop;
            }
        }else {
            if (cases[i_src][j_src].getPion().getColor() == Couleur::BLANC) {
                goto next_loop;
            }
        }
        if((i_dst == 4 || i_dst == 5) && (j_dst == 2 || j_dst == 3 || j_dst == 6 || j_dst == 7)){
            std::cout << "Case invalide" << std::endl;
            std::cout << "Veuillez entrer de nouvelles valeurs" << std::endl;
            goto next_loop;
        }


        if (cases[i_src][j_src].getPion().getNom().compare("Bombe") == 0 || cases[i_src][j_src].getPion().getNom().compare("Drapeau") == 0 || cases[i_src][j_src].getPion().getNom().compare("") == 0){
            std::cout << "Mouvement impossible" << std::endl;
            goto next_loop;
        }else if (cases[i_src][j_src].getPion().getNom().compare("Eclaireur") == 0){
            if(!mouvement_eclaireur(i_src, j_src, i_dst, j_dst, quiJoue)) goto next_loop;
        }
        else{
            if(!mouvement_autre(i_src, j_src, i_dst, j_dst, quiJoue)) goto next_loop;
        }
        quiJoue = !quiJoue;
    }
    if(joueur1[0] == 0) std::cout << "C'est le joueur 2 qui gagne!" << std::endl;
    else std::cout << "C'est le joueur 1 qui gagne!" << std::endl;
}