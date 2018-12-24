//
// Created by merat on 22/12/18.
//

#include "PlateauEchiquier.h"

PlateauEchiquier::PlateauEchiquier() : Plateau(8){
    cases[0][0].setPion(Pion("Tour", "\u2656", Couleur::NOIR));
    cases[0][1].setPion(Pion("Cavalier", "\u2658", Couleur::NOIR));
    cases[0][2].setPion(Pion("Fou", "\u2657", Couleur::NOIR));
    cases[0][3].setPion(Pion("Dame", "\u2655", Couleur::NOIR));
    cases[0][4].setPion(Pion("Roi", "\u2654", Couleur::NOIR));
    cases[0][5].setPion(Pion("Fou", "\u2657", Couleur::NOIR));
    cases[0][6].setPion(Pion("Cavalier", "\u2658", Couleur::NOIR));
    cases[0][7].setPion(Pion("Tour", "\u2656", Couleur::NOIR));

    cases[1][0].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][1].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][2].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][3].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][4].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][5].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][6].setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    cases[1][7].setPion(Pion("Pion", "\u2659", Couleur::NOIR));

    cases[7][0].setPion(Pion("Tour", "\u265C", Couleur::BLANC));
    cases[7][1].setPion(Pion("Cavalier", "\u265E", Couleur::BLANC));
    cases[7][2].setPion(Pion("Fou", "\u265D", Couleur::BLANC));
    cases[7][3].setPion(Pion("Dame", "\u265B", Couleur::BLANC));
    cases[7][4].setPion(Pion("Roi", "\u265A", Couleur::BLANC));
    cases[7][5].setPion(Pion("Fou", "\u265D", Couleur::BLANC));
    cases[7][6].setPion(Pion("Cavalier", "\u265E", Couleur::BLANC));
    cases[7][7].setPion(Pion("Tour", "\u265C", Couleur::BLANC));

    cases[6][0].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][1].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][2].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][3].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][4].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][5].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][6].setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    cases[6][7].setPion(Pion("Pion", "\u265F", Couleur::BLANC));

    les2RoisontSurLePlateau = true;
}

std::ostream &operator<<(std::ostream &os, const PlateauEchiquier &echiquier) {
    os << "    ";
    char alpha[8] = {'A','B','C','D','E','F','G','H'};
    for(int j = 0; j < 8; j++){
        os << alpha[j] << "   ";
    }
    os << "\n";
    os << "  ---------------------------------\n";

    for(int i = 0; i < 8; i++){
        os << i << "|  ";
        for(int j = 0; j < 8; j++){
            os << echiquier.cases[i][j].getPion().getImg() << " | " ;

        }
        os << "\n";
    }
    os << "  ---------------------------------" << std::endl;
    return os;
}

int PlateauEchiquier::getEquivalenceAlpha(char c) {
    for(int i = 0; i < 8; i++){
        if(std::get<1>(alpha[i]) == c) return std::get<0>(alpha[i]);
    }
    return -1;
}

bool PlateauEchiquier::mouvement(std::string x, bool joueur, std::string piece) {
    std::cout << x.at(1) << std::endl;
    int i_dst = (int)(x.at(2)-'0');
    int j_dst = getEquivalenceAlpha(x.at(1));

    if((joueur && cases[i_dst][j_dst].getPion().getColor() == Couleur::BLANC) || (!joueur && cases[i_dst][j_dst].getPion().getColor() == Couleur::NOIR)){
        std::cout << "Mouvement impossible" << std::endl;
        return false;
    }
    if(piece == "Cavalier")coord = ouEstCavalier(i_dst,j_dst,joueur);
    else if(piece == "Fou") coord = ouEstFou(i_dst,j_dst, joueur);
    else if(piece == "Tour") coord = ouEstTour(i_dst, j_dst, joueur);
    else if(piece == "Roi") coord = ouEstRoi(i_dst, j_dst, joueur);
    else if(piece == "Dame") coord = ouEstDame(i_dst,j_dst,joueur);

    if(std::get<0>(coord) == -1){
        std::cout << "Mouvement impossible" << std::endl;
        return false;
    }else if(std::get<0>(coord) == -2){
        std::cout << "Vous avez plusieurs possibilité de mouvement.\n Choisissez en une." << std::endl;
        std::string ii = "";
        std::cin >> ii;
        int j_src = getEquivalenceAlpha(ii.at(0));
        int cmp = 0;
        int tmp = -1;
        for(int i = 0; i < 16; i++){
            if(joueur){
                if(std::get<1>(joueur1[i]) == j_src && std::get<2>(joueur1[i]) == piece) cmp++;
                tmp = i;
            }else{
                if(std::get<1>(joueur2[i]) == j_src && std::get<2>(joueur2[i]) == piece) cmp++;
                tmp = i;
            }
        }
        if(cmp > 1){
            std::cout << "Vous avez plusieurs possibilité de mouvement.\n Choisissez en une." << std::endl;
            std::string jj = "";
            std::cin >> jj;
            int i_src = (int)(jj.at(0)-'0');
            if(!cases[i_dst][j_dst].isEmpty()){
                pionDetruit(i_dst, j_dst, !joueur);
            }
            cases[i_dst][j_dst] = cases[i_src][j_src];
            cases[i_src][j_src] = Case(i_src,j_src);
            if (joueur)joueur1[tmp] = {i_dst, j_dst, piece};
            else joueur2[tmp] = {i_dst, j_dst, piece};
            return true;
        }else{
            if(joueur){
                int i_src = std::get<0>(joueur1[tmp]);
                if(!cases[i_dst][j_dst].isEmpty()){
                    pionDetruit(i_dst, j_dst, !joueur);
                }
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src,j_src);
                joueur1[tmp] = {i_dst,j_dst, piece};
                return true;
            }else{
                int i_src = std::get<0>(joueur2[tmp]);
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src,j_src);
                joueur2[tmp] = {i_dst,j_dst, piece};
                return true;
            }
        }
    }else{
        if(!cases[i_dst][j_dst].isEmpty()){
            pionDetruit(i_dst, j_dst, !joueur);
        }
        cases[i_dst][j_dst] = cases[std::get<0>(coord)][std::get<1>(coord)];
        cases[std::get<0>(coord)][std::get<1>(coord)] = Case(std::get<0>(coord),std::get<1>(coord));
        if(joueur) {
            for(int i = 0; i < 16; i++){
                if(std::get<0>(joueur1[i]) == std::get<0>(coord) && std::get<1>(joueur1[i]) == std::get<1>(coord)){
                    joueur1[i] = {std::get<0>(coord), std::get<1>(coord), piece};
                }
            }
        }else{
            for(int i = 0; i < 16; i++){
                if(std::get<0>(joueur2[i]) == std::get<0>(coord) && std::get<1>(joueur2[i]) == std::get<1>(coord)){
                    joueur2[i] = {std::get<0>(coord), std::get<1>(coord), piece};
                }
            }
        }
        return true;
    }
}

bool PlateauEchiquier::pieceASoi(int i_src, int j_src, bool joueur) {
    if(joueur && cases[i_src][j_src].getPion().getColor() == Couleur::NOIR){
        std::cout << "Ce n'est pas un pion à vous" << std::endl;
        return false;
    }else if(!joueur && cases[i_src][j_src].getPion().getColor() == Couleur::BLANC){
        std::cout << "Ce n'est pas un pion à vous" << std::endl;
        return false;
    }
    return true;
}

void PlateauEchiquier::pionDetruit(int i_dst, int j_dst, bool joueur) {
    if(joueur){
        for(int h = 0; h < 16; h++){
            if(std::get<0>(joueur1[h]) == i_dst && std::get<1>(joueur1[h]) == j_dst){
                joueur1[h] = {-1,-1,""};
                return;
            }
        }
    }else{
        for(int h = 0; h < 16; h++){
            if(std::get<0>(joueur2[h]) == i_dst && std::get<1>(joueur2[h]) == j_dst){
                joueur2[h] = {-1,-1,""};
                return;
            }
        }
    }
}

bool PlateauEchiquier::mouvement_pion(std::string x, bool joueur) {
    int i_dst = (int)(x.at(1)-'0');
    int j_dst = getEquivalenceAlpha(x.at(0));
    int i_borne = 0;
    if(joueur) i_borne = i_dst+1;
    else i_borne = i_dst-1;
    std::cout << (cases[i_dst][j_dst].getPion().getColor()) << std::endl;
    if((joueur && cases[i_dst][j_dst].getPion().getColor() == Couleur::BLANC) || (!joueur && cases[i_dst][j_dst].getPion().getColor() == Couleur::NOIR)){
        std::cout << "Mouvement impossible" << std::endl;
        return false;
    }

    if(cases[i_dst][j_dst].isEmpty()){
        if(joueur && i_borne+1 == 6 && !cases[i_borne+1][j_dst].isEmpty()){
            if(cases[i_borne+1][j_dst].getPion().getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            move(i_borne+1, j_dst, i_dst, j_dst);
            return true;
        }else if(!joueur && i_borne-1 == 1 && !cases[i_borne-1][j_dst].isEmpty()){
            if(cases[i_borne-1][j_dst].getPion().getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            move(i_borne-1, j_dst, i_dst, j_dst);
            return true;
        }else if(!cases[i_borne][j_dst].isEmpty()){
            if(cases[i_borne][j_dst].getPion().getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            move(i_borne, j_dst, i_dst, j_dst);
            return true;
        }else{
            std::cout << "Aucune pièce dans cette case" << std::endl;
            return false;
        }
    }else if(!cases[i_dst][j_dst].isEmpty() && cases[i_borne][j_dst+1].isEmpty() && !cases[i_borne][j_dst-1].isEmpty()){
        if(cases[i_borne][j_dst-1].getPion().getNom() != "Pion"){
            std::cout << "Mouvement impossible" << std::endl;
            return false;
        }
        pionDetruit(i_dst, j_dst, !joueur);
        cases[i_dst][j_dst] = cases[i_borne][j_dst-1];
        cases[i_borne][j_dst-1] = Case(i_borne, j_dst-1);
        return true;
    }else if(!cases[i_dst][j_dst].isEmpty() && !cases[i_borne][j_dst+1].isEmpty() && cases[i_borne][j_dst-1].isEmpty()){
        if(cases[i_borne][j_dst+1].getPion().getNom() != "Pion"){
            std::cout << "Mouvement impossible" << std::endl;
            return false;
        }
        pionDetruit(i_dst, j_dst, !joueur);
        cases[i_dst][j_dst] = cases[i_borne][j_dst+1];
        cases[i_borne][j_dst+1] = Case(i_borne, j_dst+1);
        return true;
    }else if(!cases[i_dst][j_dst].isEmpty() && !cases[i_borne][j_dst+1].isEmpty() && !cases[i_borne][j_dst-1].isEmpty()){
        std::cout << "Vous avez deux pièces pouvant faire ce coup.\n Précisez celle que vous voulez bouger" << std::endl;
        std::string ii = "";
        std::cin >> ii;
        int j_src = getEquivalenceAlpha(ii.at(0));
        if(!cases[i_borne][j_src].isEmpty()){
            if(cases[i_borne][j_src].getPion().getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            pionDetruit(i_dst, j_dst, !joueur);
            cases[i_dst][j_dst] = cases[i_borne][j_src];
            cases[i_borne][j_src] = Case(i_borne, j_src);
            return true;
        }else{
            std::cout << "Vous n'avez pas de pièce à cet endroit" << std::endl;
            return false;
        }
    }else{
        std::cout << "Mouvement impossible" << std::endl;
        return false;
    }
}

std::tuple<int,int> PlateauEchiquier::ouEstCavalier(int i_dst, int j_dst, bool joueur) {
    int cmp = 0;
    if(joueur) {
        if (i_dst-2 >= 0 && j_dst-1 >= 0 && cases[i_dst - 2][j_dst - 1].getPion().getNom() == "Cavalier" &&
            cases[i_dst - 2][j_dst - 1].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst-1 >= 0 && j_dst-2 >= 0 && cases[i_dst - 1][j_dst - 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst - 1][j_dst - 2].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+1 < 8 && j_dst-2 >= 0 && cases[i_dst + 1][j_dst - 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 1][j_dst - 2].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+2 < 8 && j_dst-1 >= 0 && cases[i_dst + 2][j_dst - 1].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 2][j_dst - 1].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst+2 < 8 && j_dst+1 < 8 && cases[i_dst + 2][j_dst + 1].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 2][j_dst + 1].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst + 1;
        }
        if (i_dst+1 < 8 && j_dst+2 < 8 && cases[i_dst + 1][j_dst + 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 1][j_dst + 2].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - +2;
        }
        if (i_dst-1 >= 0 && j_dst+2 < 8 && cases[i_dst - 1][j_dst + 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst - 1][j_dst + 2].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst + 2;
        }
        if (i_dst-2 >= 0 && j_dst+1 < 8 && cases[i_dst - 2][j_dst + 1].getPion().getNom() == "Cavalier" &&
                   cases[i_dst - 2][j_dst + 1].getPion().getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst + 1;
        }
    }else{
        if (i_dst-2 >= 0 && j_dst-1 >= 0 && cases[i_dst - 2][j_dst - 1].getPion().getNom() == "Cavalier" &&
            cases[i_dst - 2][j_dst - 1].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst-1 >= 0 && j_dst-2 >= 0 && cases[i_dst - 1][j_dst - 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst - 1][j_dst - 2].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+1 < 8 && j_dst-2 >= 0 && cases[i_dst + 1][j_dst - 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 1][j_dst - 2].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+2 < 8 && j_dst-1 >= 0 && cases[i_dst + 2][j_dst - 1].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 2][j_dst - 1].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst+2 < 8 && j_dst+1 < 8 && cases[i_dst + 2][j_dst + 1].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 2][j_dst + 1].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst + 1;
        }
        if (i_dst+1 < 8 && j_dst+2 < 8 && cases[i_dst + 1][j_dst + 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst + 1][j_dst + 2].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - +2;
        }
        if (i_dst-1 >= 0 && j_dst+2 < 8 && cases[i_dst - 1][j_dst + 2].getPion().getNom() == "Cavalier" &&
                   cases[i_dst - 1][j_dst + 2].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst + 2;
        }
        if (cases[i_dst - 2][j_dst + 1].getPion().getNom() == "Cavalier" &&
                   cases[i_dst - 2][j_dst + 1].getPion().getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst + 1;
        }
    }
    std::cout << cmp << "  cmp: " << std::endl;
    if(cmp > 1) return {-2,-2};
    else if(cmp == 0) return {-1,-1};
    else return coord;
}

bool PlateauEchiquier::mouvement_cavalier(std::string x, bool joueur) {
    return mouvement(x,joueur, "Cavalier");
}


std::tuple<int,int> PlateauEchiquier::ouEstFou(int i_dst, int j_dst, bool joueur) {
    int cmp = 0;
    if(joueur) {
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && cases[i_dst - h][j_dst - h].getPion().getNom() == "Fou" &&
                cases[i_dst - h][j_dst - h].getPion().getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && cases[i_dst + h][j_dst + h].getPion().getNom() == "Fou" &&
                cases[i_dst + h][j_dst + h].getPion().getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && cases[i_dst + h][j_dst - h].getPion().getNom() == "Fou" &&
                cases[i_dst + h][j_dst - h].getPion().getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && cases[i_dst - h][j_dst + h].getPion().getNom() == "Fou" &&
                cases[i_dst - h][j_dst + h].getPion().getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }

        }
    }else{
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && cases[i_dst - h][j_dst - h].getPion().getNom() == "Fou" &&
                cases[i_dst - h][j_dst - h].getPion().getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && cases[i_dst + h][j_dst + h].getPion().getNom() == "Fou" &&
                cases[i_dst + h][j_dst + h].getPion().getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && cases[i_dst + h][j_dst - h].getPion().getNom() == "Fou" &&
                cases[i_dst + h][j_dst - h].getPion().getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && cases[i_dst - h][j_dst + h].getPion().getNom() == "Fou" &&
                cases[i_dst - h][j_dst + h].getPion().getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }

        }
    }
    if(cmp > 1) return {-2,-2};
    else if(cmp == 0) return {-1,-1};
    else return coord;
}

bool PlateauEchiquier::fouPeutIlYAller(int i_src, int j_src, int i_dst, int j_dst) {
    if(i_src < i_dst && j_src > j_dst){
        for(int h = 1; h < j_src-j_dst; h++){
            if(i_src+h < 8 && j_src-h >= 0 && !cases[i_src+h][j_src-h].isEmpty()) return false;
        }
        return true;
    }else if(i_src < i_dst && j_src < j_dst){
        for(int h = 1; h < j_dst-j_src; h++){
            if(i_src+h < 8 && j_src+h < 8 && !cases[i_src+h][j_src+h].isEmpty()) return false;
        }
        return true;
    }else if(i_src > i_dst && j_src >j_dst){
        for(int h = 1; h < j_src-j_dst; h++){
            if(i_src-h >= 0 && j_src-h >= 0 && !cases[i_src-h][j_src-h].isEmpty()) return false;
        }
        return true;
    }else if(i_src > i_dst && j_src < j_dst){
        for(int h = 1; h < j_dst-j_src; h++){
            if(i_src-h >= 0 && j_src+h < 8 && !cases[i_src-h][j_src+h].isEmpty()) return false;
        }
        return true;
    }else return true;
}

bool PlateauEchiquier::mouvement_fou(std::string x, bool joueur) {
    return mouvement(x,joueur,"Fou");
}

std::tuple<int,int> PlateauEchiquier::ouEstDame(int i_dst, int j_dst, bool joueur) {
    if(joueur) {
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && cases[i_dst - h][j_dst - h].getPion().getNom() == "Dame" &&
                cases[i_dst - h][j_dst - h].getPion().getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && cases[i_dst + h][j_dst + h].getPion().getNom() == "Dame" &&
                cases[i_dst + h][j_dst + h].getPion().getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && cases[i_dst + h][j_dst - h].getPion().getNom() == "Dame" &&
                cases[i_dst + h][j_dst - h].getPion().getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && cases[i_dst - h][j_dst + h].getPion().getNom() == "Dame" &&
                cases[i_dst - h][j_dst + h].getPion().getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }
            if (cases[i_dst][h].getPion().getNom() == "Dame" && cases[i_dst][h].getPion().getColor() == Couleur::BLANC && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (cases[h][j_dst].getPion().getNom() == "Dame" && cases[h][j_dst].getPion().getColor() == Couleur::BLANC && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
                std::get<0>(coord) = h;
                std::get<1>(coord) = j_dst;
            }

        }
    }else{
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && cases[i_dst - h][j_dst - h].getPion().getNom() == "Dame" &&
                cases[i_dst - h][j_dst - h].getPion().getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && cases[i_dst + h][j_dst + h].getPion().getNom() == "Dame" &&
                cases[i_dst + h][j_dst + h].getPion().getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && cases[i_dst + h][j_dst - h].getPion().getNom() == "Dame" &&
                cases[i_dst + h][j_dst - h].getPion().getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && cases[i_dst - h][j_dst + h].getPion().getNom() == "Dame" &&
                cases[i_dst - h][j_dst + h].getPion().getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }
            if (cases[i_dst][h].getPion().getNom() == "Dame" && cases[i_dst][h].getPion().getColor() == Couleur::NOIR && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (cases[h][j_dst].getPion().getNom() == "Dame" && cases[h][j_dst].getPion().getColor() == Couleur::NOIR && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
                std::get<0>(coord) = h;
                std::get<1>(coord) = j_dst;
            }

        }
    }
    return  coord;
}

bool PlateauEchiquier::mouvement_dame(std::string x, bool joueur) {
    return mouvement(x, joueur, "Dame");
}

std::tuple<int,int> PlateauEchiquier::ouEstRoi(int i_dst, int j_dst, bool joueur) {
    std::tuple<int,int>possibilite[8] = {{i_dst+1, j_dst},{i_dst-1, j_dst},{i_dst-1,j_dst-1},{i_dst-1, j_dst+1},{i_dst+1, j_dst-1},{i_dst+1, j_dst+1},{i_dst, j_dst-1}, {i_dst, j_dst+1}};
    if(joueur) {
        for (int h = 0; h < 8; h++) {
            if (std::get<0>(possibilite[h]) >= 0 && std::get<0>(possibilite[h]) < 8 &&
                std::get<1>(possibilite[h]) >= 0 && std::get<1>(possibilite[h]) < 8) {
                if (!cases[std::get<0>(possibilite[h])][std::get<1>(possibilite[h])].isEmpty() &&
                    cases[std::get<0>(possibilite[h])][std::get<1>(possibilite[h])].getPion().getNom() == "Roi" &&
                    cases[std::get<0>(possibilite[h])][std::get<1>(possibilite[h])].getPion().getColor() == Couleur::BLANC){
                    std::get<0>(coord) = std::get<0>(possibilite[h]);
                    std::get<1>(coord) = std::get<1>(possibilite[h]);
                }
            }
        }
    }else{
        for (int h = 0; h < 8; h++) {
            if (std::get<0>(possibilite[h]) >= 0 && std::get<0>(possibilite[h]) < 8 &&
                std::get<1>(possibilite[h]) >= 0 && std::get<1>(possibilite[h]) < 8) {
                if (!cases[std::get<0>(possibilite[h])][std::get<1>(possibilite[h])].isEmpty() &&
                    cases[std::get<0>(possibilite[h])][std::get<1>(possibilite[h])].getPion().getNom() == "Roi" &&
                    cases[std::get<0>(possibilite[h])][std::get<1>(possibilite[h])].getPion().getColor() == Couleur::NOIR){
                    std::get<0>(coord) = std::get<0>(possibilite[h]);
                    std::get<1>(coord) = std::get<1>(possibilite[h]);
                }
            }
        }
    }
    return coord;
}

bool PlateauEchiquier::mouvement_roi(std::string x, bool joueur) {
    return mouvement(x,joueur,"Roi");
}

std::tuple<int,int> PlateauEchiquier::ouEstTour(int i_dst, int j_dst, bool joueur) {
    int cmp = 0;
    if(joueur) {
        for (int h = 0; h < 8; h++) {
            if (cases[i_dst][h].getPion().getNom() == "Tour" && cases[i_dst][h].getPion().getColor() == Couleur::BLANC && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (cases[h][j_dst].getPion().getNom() == "Tour" && cases[h][j_dst].getPion().getColor() == Couleur::BLANC && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = h;
                std::get<1>(coord) = j_dst;
            }

        }
    }else{
        for (int h = 0; h < 8; h++) {
            if (cases[i_dst][h].getPion().getNom() == "Tour" && cases[i_dst][h].getPion().getColor() == Couleur::NOIR && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (cases[h][j_dst].getPion().getNom() == "Tour" && cases[h][j_dst].getPion().getColor() == Couleur::NOIR && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = h;
                std::get<1>(coord) = j_dst;
            }

        }
    }
    if(cmp > 1) return {-2,-2};
    else if(cmp == 0) return {-1,-1};
    else return coord;
}

bool PlateauEchiquier::tourPeutElleYAller(int i_src, int j_src, int i_dst, int j_dst) {
    int min = 0;
    int max = 0;
    if(i_src == i_dst){
        if(j_dst > j_src) {
            min = j_src + 1;
            max = j_dst;
        }else {
            min = j_dst;
            max = j_src - 1;
        }
        for(int h = min; h < max; h++){
            if(!cases[i_src][h].isEmpty()) return false;
        }
        return true;
    }else if(j_src == j_dst){
        if(i_dst > i_src) {
            min = i_src + 1;
            max = i_dst;
        }else {
            min = i_dst + 1;
            max = i_src;
        }
        for(int h = min; h < max; h++){
            if(!cases[h][j_src].isEmpty()) return false;
        }
        return true;
    }else return false;

}

bool PlateauEchiquier::mouvement_tour(std::string x, bool joueur) {
    return mouvement(x,joueur,"Tour");
}

void PlateauEchiquier::launchEchiquier(bool ordi) {
    bool quiJoue = true; //joueur 1

    std::string ii = "";
    while(les2RoisontSurLePlateau) {
        next_loop:
        std::cout << *(this) << std::endl;

        if(quiJoue) std::cout << "Tour joueur 1: " << std::endl;
        else if(!ordi) std::cout << "Tour joueur 2: " << std::endl;

        std::cin >> ii;
        if(ii.compare("help") == 0){
            std::cout << help(quiJoue) << std::endl;
            goto next_loop;
        }

        if(ii.size() == 2){
            if(!mouvement_pion(ii, quiJoue)) goto next_loop;
        }
        else if(ii.at(0) == 'T'){
            if(!mouvement_tour(ii, quiJoue)) goto next_loop;
        }
        else if(ii.at(0) == 'C'){
            if(!mouvement_cavalier(ii, quiJoue)) goto next_loop;
        }
        else if(ii.at(0) == 'F'){
            if(!mouvement_fou(ii, quiJoue)) goto next_loop;
        }
        else if(ii.at(0) == 'D'){
            if(!mouvement_dame(ii, quiJoue)) goto next_loop;
        }
        else{
            if(!mouvement_roi(ii, quiJoue)) goto next_loop;
        }

        quiJoue = !quiJoue;
    }

}

std::string PlateauEchiquier::help(bool joueur) {

}
