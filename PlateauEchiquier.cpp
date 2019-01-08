#include "PlateauEchiquier.h"

PlateauEchiquier::PlateauEchiquier() : PlateauCombinatoireAbstrait(8){
    /*
    getCase(0*getDimension()+0).setPion(Pion("Tour", "\u2656", Couleur::NOIR));
    getCase(0*getDimension()+1).setPion(Pion("Cavalier", "\u2658", Couleur::NOIR));
    getCase(0*getDimension()+2).setPion(Pion("Fou", "\u2657", Couleur::NOIR));
    getCase(0*getDimension()+3).setPion(Pion("Dame", "\u2655", Couleur::NOIR));
    getCase(0*getDimension()+4).setPion(Pion("Roi", "\u2654", Couleur::NOIR));
    getCase(0*getDimension()+5).setPion(Pion("Fou", "\u2657", Couleur::NOIR));
    getCase(0*getDimension()+6).setPion(Pion("Cavalier", "\u2658", Couleur::NOIR));
    getCase(0*getDimension()+7).setPion(Pion("Tour", "\u2656", Couleur::NOIR));

    getCase(1*getDimension()+0).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+1).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+2).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+3).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+4).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+5).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+6).setPion(Pion("Pion", "\u2659", Couleur::NOIR));
    getCase(1*getDimension()+7).setPion(Pion("Pion", "\u2659", Couleur::NOIR));

    getCase(7*getDimension()+0).setPion(Pion("Tour", "\u265C", Couleur::BLANC));
    getCase(7*getDimension()+1).setPion(Pion("Cavalier", "\u265E", Couleur::BLANC));
    getCase(7*getDimension()+2).setPion(Pion("Fou", "\u265D", Couleur::BLANC));
    getCase(7*getDimension()+3).setPion(Pion("Dame", "\u265B", Couleur::BLANC));
    getCase(7*getDimension()+4).setPion(Pion("Roi", "\u265A", Couleur::BLANC));
    getCase(7*getDimension()+5).setPion(Pion("Fou", "\u265D", Couleur::BLANC));
    getCase(7*getDimension()+6).setPion(Pion("Cavalier", "\u265E", Couleur::BLANC));
    getCase(7*getDimension()+7).setPion(Pion("Tour", "\u265C", Couleur::BLANC));

    getCase(6*getDimension()+0).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+1).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+2).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+3).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+4).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+5).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+6).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
    getCase(6*getDimension()+7).setPion(Pion("Pion", "\u265F", Couleur::BLANC));
     */

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
            os << echiquier.getCase(i*echiquier.getDimension()+j).getPion()->getImg() << " | " ;

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

char PlateauEchiquier::getEquivalenceNum(int a) {
    return std::get<1>(alpha[a]);
}

bool PlateauEchiquier::mouvement(std::string x, bool joueur, std::string piece) {
    std::cout << x.at(1) << std::endl;
    int i_dst = (int)(x.at(2)-'0');
    int j_dst = getEquivalenceAlpha(x.at(1));

    if((joueur && getCase(i_dst*getDimension()+j_dst).getPion()->getColor() == Couleur::BLANC) || (!joueur && getCase(i_dst*getDimension()+j_dst).getPion()->getColor() == Couleur::NOIR)){
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
            if(!getCase(i_dst*getDimension()+j_dst).isEmpty()){
                pionDetruit(i_dst, j_dst, !joueur);
            }
            dernier_mouv[0] = {i_src,j_src, piece};
            dernier_mouv[1] = {i_dst, j_dst, piece};

            setCase(i_dst*getDimension()+j_dst,  getCase(i_src*getDimension()+j_src).getPion());
            setCase(i_src*getDimension()+j_src, new Pion());
            if (joueur)joueur1[tmp] = {i_dst, j_dst, piece};
            else joueur2[tmp] = {i_dst, j_dst, piece};
            piece_bouffee = piece;
            return true;
        }else{
            if(joueur){
                int i_src = std::get<0>(joueur1[tmp]);
                if(!getCase(i_dst*getDimension()+j_dst).isEmpty()){
                    pionDetruit(i_dst, j_dst, !joueur);
                }
                dernier_mouv[0] = {i_src,j_src, piece};
                dernier_mouv[1] = {i_dst, j_dst, piece};

                setCase(i_dst*getDimension()+j_dst, getCase(i_src*getDimension()+j_src).getPion());
                setCase(i_src*getDimension()+j_src, new Pion());
                joueur1[tmp] = {i_dst,j_dst, piece};
                piece_bouffee = piece;
                return true;
            }else{
                int i_src = std::get<0>(joueur2[tmp]);
                dernier_mouv[0] = {i_src,j_src, piece};
                dernier_mouv[1] = {i_dst, j_dst, piece};

                setCase(i_dst*getDimension()+j_dst, getCase(i_src*getDimension()+j_src).getPion());
                setCase(i_src*getDimension()+j_src, new Pion());
                joueur2[tmp] = {i_dst,j_dst, piece};
                piece_bouffee = piece;
                return true;
            }
        }
    }else{
        if(!getCase(i_dst*getDimension()+j_dst).isEmpty()){
            pionDetruit(i_dst, j_dst, !joueur);
        }

        dernier_mouv[0] = {std::get<0>(coord),std::get<1>(coord), piece};
        dernier_mouv[1] = {i_dst, j_dst, piece};
        setCase(i_dst*getDimension()+j_dst, getCase(std::get<0>(coord)*getDimension()+std::get<1>(coord)).getPion());
        setCase(std::get<0>(coord)*getDimension()+std::get<1>(coord), new Pion());
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
        piece_bouffee = piece;
        return true;
    }
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
    std::cout << (getCase(i_dst*getDimension()+j_dst).getPion()->getColor()) << std::endl;
    if((joueur && getCase(i_dst*getDimension()+j_dst).getPion()->getColor() == Couleur::BLANC) || (!joueur && getCase(i_dst*getDimension()+j_dst).getPion()->getColor() == Couleur::NOIR)){
        std::cout << "Mouvement impossible" << std::endl;
        return false;
    }

    if(getCase(i_dst*getDimension()+j_dst).isEmpty()){
        if(joueur && i_borne+1 == 6 && !getCase(i_borne+1*getDimension()+j_dst).isEmpty()){
            if(getCase(i_borne+1*getDimension()+j_dst).getPion()->getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            move(i_borne+1, j_dst, i_dst, j_dst);
            return true;
        }else if(!joueur && i_borne-1 == 1 && !getCase(i_borne-1*getDimension()+j_dst).isEmpty()){
            if(getCase(i_borne-1*getDimension()+j_dst).getPion()->getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            move(i_borne-1, j_dst, i_dst, j_dst);
            return true;
        }else if(!getCase(i_borne*getDimension()+j_dst).isEmpty()){
            if(getCase(i_borne*getDimension()+j_dst).getPion()->getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            move(i_borne, j_dst, i_dst, j_dst);
            return true;
        }else{
            std::cout << "Aucune pièce dans cette case" << std::endl;
            return false;
        }
    }else if(!getCase(i_dst*getDimension()+j_dst).isEmpty() && getCase(i_borne*getDimension()+j_dst+1).isEmpty() && !getCase(i_borne*getDimension()+j_dst-1).isEmpty()){
        if(getCase(i_borne*getDimension()+j_dst-1).getPion()->getNom() != "Pion"){
            std::cout << "Mouvement impossible" << std::endl;
            return false;
        }
        pionDetruit(i_dst, j_dst, !joueur);
        setCase(i_dst*getDimension()+j_dst, getCase(i_borne*getDimension()+j_dst-1).getPion());
        setCase(i_borne*getDimension()+j_dst-1, new Pion());
        return true;
    }else if(!getCase(i_dst*getDimension()+j_dst).isEmpty() && !getCase(i_borne*getDimension()+j_dst+1).isEmpty() && getCase(i_borne*getDimension()+j_dst-1).isEmpty()){
        if(getCase(i_borne*getDimension()+j_dst+1).getPion()->getNom() != "Pion"){
            std::cout << "Mouvement impossible" << std::endl;
            return false;
        }
        pionDetruit(i_dst, j_dst, !joueur);
        setCase(i_dst*getDimension()+j_dst, getCase(i_borne*getDimension()+j_dst+1).getPion());
        setCase(i_borne*getDimension()+j_dst+1, new Pion());
        return true;
    }else if(!getCase(i_dst*getDimension()+j_dst).isEmpty() && !getCase(i_borne*getDimension()+j_dst+1).isEmpty() && !getCase(i_borne*getDimension()+j_dst-1).isEmpty()){
        std::cout << "Vous avez deux pièces pouvant faire ce coup.\n Précisez celle que vous voulez bouger" << std::endl;
        std::string ii = "";
        std::cin >> ii;
        int j_src = getEquivalenceAlpha(ii.at(0));
        if(!getCase(i_borne*getDimension()+j_src).isEmpty()){
            if(getCase(i_borne*getDimension()+j_src).getPion()->getNom() != "Pion"){
                std::cout << "Mouvement impossible" << std::endl;
                return false;
            }
            pionDetruit(i_dst, j_dst, !joueur);
            setCase(i_dst*getDimension()+j_dst, getCase(i_borne*getDimension()+j_src).getPion());
            setCase(i_borne*getDimension()+j_src, new Pion());
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
        if (i_dst-2 >= 0 && j_dst-1 >= 0 && getCase(i_dst - 2*getDimension()+j_dst - 1).getPion()->getNom() == "Cavalier" &&
            getCase(i_dst - 2*getDimension()+j_dst - 1).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst-1 >= 0 && j_dst-2 >= 0 && getCase(i_dst - 1*getDimension()+j_dst - 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst - 1*getDimension()+j_dst - 2).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+1 < 8 && j_dst-2 >= 0 && getCase(i_dst + 1*getDimension()+j_dst - 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 1*getDimension()+j_dst - 2).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+2 < 8 && j_dst-1 >= 0 && getCase(i_dst + 2*getDimension()+j_dst - 1).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 2*getDimension()+j_dst - 1).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst+2 < 8 && j_dst+1 < 8 && getCase(i_dst + 2*getDimension()+j_dst + 1).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 2*getDimension()+j_dst + 1).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst + 1;
        }
        if (i_dst+1 < 8 && j_dst+2 < 8 && getCase(i_dst + 1*getDimension()+j_dst + 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 1*getDimension()+j_dst + 2).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - +2;
        }
        if (i_dst-1 >= 0 && j_dst+2 < 8 && getCase(i_dst - 1*getDimension()+j_dst + 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst - 1*getDimension()+j_dst + 2).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst + 2;
        }
        if (i_dst-2 >= 0 && j_dst+1 < 8 && getCase(i_dst - 2*getDimension()+j_dst + 1).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst - 2*getDimension()+j_dst + 1).getPion()->getColor() == Couleur::BLANC && joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst + 1;
        }
    }else{
        if (i_dst-2 >= 0 && j_dst-1 >= 0 && getCase(i_dst - 2*getDimension()+j_dst - 1).getPion()->getNom() == "Cavalier" &&
            getCase(i_dst - 2*getDimension()+j_dst - 1).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst-1 >= 0 && j_dst-2 >= 0 && getCase(i_dst - 1*getDimension()+j_dst - 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst - 1*getDimension()+j_dst - 2).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+1 < 8 && j_dst-2 >= 0 && getCase(i_dst + 1*getDimension()+j_dst - 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 1*getDimension()+j_dst - 2).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - 2;
        }
        if (i_dst+2 < 8 && j_dst-1 >= 0 && getCase(i_dst + 2*getDimension()+j_dst - 1).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 2*getDimension()+j_dst - 1).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst - 1;
        }
        if (i_dst+2 < 8 && j_dst+1 < 8 && getCase(i_dst + 2*getDimension()+j_dst + 1).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 2*getDimension()+j_dst + 1).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 2;
            std::get<1>(coord) = j_dst + 1;
        }
        if (i_dst+1 < 8 && j_dst+2 < 8 && getCase(i_dst + 1*getDimension()+j_dst + 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst + 1*getDimension()+j_dst + 2).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst + 1;
            std::get<1>(coord) = j_dst - +2;
        }
        if (i_dst-1 >= 0 && j_dst+2 < 8 && getCase(i_dst - 1*getDimension()+j_dst + 2).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst - 1*getDimension()+j_dst + 2).getPion()->getColor() == Couleur::NOIR && !joueur) {
            cmp++;
            std::get<0>(coord) = i_dst - 1;
            std::get<1>(coord) = j_dst + 2;
        }
        if (getCase(i_dst - 2*getDimension()+j_dst + 1).getPion()->getNom() == "Cavalier" &&
                   getCase(i_dst - 2*getDimension()+j_dst + 1).getPion()->getColor() == Couleur::NOIR && !joueur) {
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
            if (i_dst-h >= 0 && j_dst-h >= 0 && getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getNom() == "Fou" &&
                getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getNom() == "Fou" &&
                getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getNom() == "Fou" &&
                getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getNom() == "Fou" &&
                getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::BLANC){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }

        }
    }else{
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getNom() == "Fou" &&
                getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getNom() == "Fou" &&
                getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getNom() == "Fou" &&
                getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::NOIR){
                cmp++;
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getNom() == "Fou" &&
                getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::NOIR){
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

bool PlateauEchiquier::mouvement_fou(std::string x, bool joueur) {
    return mouvement(x,joueur,"Fou");
}

std::tuple<int,int> PlateauEchiquier::ouEstDame(int i_dst, int j_dst, bool joueur) {
    if(joueur) {
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getNom() == "Dame" &&
                getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getNom() == "Dame" &&
                getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getNom() == "Dame" &&
                getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getNom() == "Dame" &&
                getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::BLANC){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }
            if (getCase(i_dst*getDimension()+h).getPion()->getNom() == "Dame" && getCase(i_dst*getDimension()+h).getPion()->getColor() == Couleur::BLANC && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (getCase(h*getDimension()+j_dst).getPion()->getNom() == "Dame" && getCase(h*getDimension()+j_dst).getPion()->getColor() == Couleur::BLANC && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
                std::get<0>(coord) = h;
                std::get<1>(coord) = j_dst;
            }

        }
    }else{
        for(int h = 0; h < 8; h++){
            if (i_dst-h >= 0 && j_dst-h >= 0 && getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getNom() == "Dame" &&
                getCase(i_dst - h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst+h < 8 && j_dst+h < 8 && getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getNom() == "Dame" &&
                getCase(i_dst + h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst + h;
            }
            if (i_dst+h < 8 && j_dst-h >= 0 && getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getNom() == "Dame" &&
                getCase(i_dst + h*getDimension()+j_dst - h).getPion()->getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst + h;
                std::get<1>(coord) = j_dst - h;
            }
            if (i_dst-h >= 0 && j_dst+h < 8 && getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getNom() == "Dame" &&
                getCase(i_dst - h*getDimension()+j_dst + h).getPion()->getColor() == Couleur::NOIR){
                std::get<0>(coord) = i_dst - h;
                std::get<1>(coord) = j_dst + h;
            }
            if (getCase(i_dst*getDimension()+h).getPion()->getNom() == "Dame" && getCase(i_dst*getDimension()+h).getPion()->getColor() == Couleur::NOIR && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (getCase(h*getDimension()+j_dst).getPion()->getNom() == "Dame" && getCase(h*getDimension()+j_dst).getPion()->getColor() == Couleur::NOIR && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
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
                if (!getCase(std::get<0>(possibilite[h])*getDimension()+std::get<1>(possibilite[h])).isEmpty() &&
                    getCase(std::get<0>(possibilite[h])*getDimension()+std::get<1>(possibilite[h])).getPion()->getNom() == "Roi" &&
                    getCase(std::get<0>(possibilite[h])*getDimension()+std::get<1>(possibilite[h])).getPion()->getColor() == Couleur::BLANC){
                    std::get<0>(coord) = std::get<0>(possibilite[h]);
                    std::get<1>(coord) = std::get<1>(possibilite[h]);
                }
            }
        }
    }else{
        for (int h = 0; h < 8; h++) {
            if (std::get<0>(possibilite[h]) >= 0 && std::get<0>(possibilite[h]) < 8 &&
                std::get<1>(possibilite[h]) >= 0 && std::get<1>(possibilite[h]) < 8) {
                if (!getCase(std::get<0>(possibilite[h])*getDimension()+std::get<1>(possibilite[h])).isEmpty() &&
                    getCase(std::get<0>(possibilite[h])*getDimension()+std::get<1>(possibilite[h])).getPion()->getNom() == "Roi" &&
                    getCase(std::get<0>(possibilite[h])*getDimension()+std::get<1>(possibilite[h])).getPion()->getColor() == Couleur::NOIR){
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
            if (getCase(i_dst*getDimension()+h).getPion()->getNom() == "Tour" && getCase(i_dst*getDimension()+h).getPion()->getColor() == Couleur::BLANC && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (getCase(h*getDimension()+j_dst).getPion()->getNom() == "Tour" && getCase(h*getDimension()+j_dst).getPion()->getColor() == Couleur::BLANC && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = h;
                std::get<1>(coord) = j_dst;
            }

        }
    }else{
        for (int h = 0; h < 8; h++) {
            if (getCase(i_dst*getDimension()+h).getPion()->getNom() == "Tour" && getCase(i_dst*getDimension()+h).getPion()->getColor() == Couleur::NOIR && tourPeutElleYAller(i_dst, h, i_dst, j_dst)){
                cmp++;
                std::get<0>(coord) = i_dst;
                std::get<1>(coord) = h;
            }
            if (getCase(h*getDimension()+j_dst).getPion()->getNom() == "Tour" && getCase(h*getDimension()+j_dst).getPion()->getColor() == Couleur::NOIR && tourPeutElleYAller(h, j_dst, i_dst, j_dst)){
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
            if(!getCase(i_src*getDimension()+h).isEmpty()) return false;
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
            if(!getCase(h*getDimension()+j_src).isEmpty()) return false;
        }
        return true;
    }else return false;

}

bool PlateauEchiquier::mouvement_tour(std::string x, bool joueur) {
    return mouvement(x,joueur,"Tour");
}

bool PlateauEchiquier::roiEstSurDiagonaleDeFou(bool joueur) {
    if(joueur){
        std::tuple<int,int,std::string> fou1 = joueur1[2];
        std::tuple<int,int,std::string> fou2 = joueur1[5];
        std::tuple<int,int,std::string> dame = joueur1[3];
        std::tuple<int,int,std::string> roi_adverse = joueur2[4];

        int i_fou1 = std::get<0>(fou1);
        int j_fou1 = std::get<1>(fou1);
        int i_fou2 = std::get<0>(fou2);
        int j_fou2 = std::get<1>(fou2);
        int i_dame = std::get<0>(dame);
        int j_dame = std::get<1>(dame);
        int i_roi = std::get<0>(roi_adverse);
        int j_roi = std::get<1>(roi_adverse);

        if(j_fou1 == -1 && j_fou2 == -1) return false;

        for(int h = 0; h < 8; h++){
            if ((i_fou1-h == i_roi && j_fou1-h == j_roi) || (i_fou2-h == i_roi && j_fou2-h == j_roi) || (i_dame-h == i_roi && j_dame-h == j_roi) ||
                    (i_fou1+h == i_roi && j_fou1+h == j_roi) || (i_fou2+h == i_roi && j_fou2+h == j_roi) || (i_dame+h == i_roi && j_dame+h == j_roi) ||
                    (i_fou1+h == i_roi && j_fou1-h == j_roi) || (i_fou2+h == i_roi && j_fou2-h == j_roi) || (i_dame+h == i_roi && j_dame-h == j_roi) ||
                    (i_fou1-h == i_roi && j_fou1+h == j_roi) || (i_fou2-h == i_roi && j_fou2+h == j_roi) || (i_dame-h == i_roi && j_dame+h == j_roi)){
                return true;
            }

        }
        return false;
    }else{
        std::tuple<int,int,std::string> fou1 = joueur2[2];
        std::tuple<int,int,std::string> fou2 = joueur2[5];
        std::tuple<int,int,std::string> roi_adverse = joueur1[4];

        int i_fou1 = std::get<0>(fou1);
        int j_fou1 = std::get<1>(fou1);
        int i_fou2 = std::get<0>(fou2);
        int j_fou2 = std::get<1>(fou2);
        int i_roi = std::get<0>(roi_adverse);
        int j_roi = std::get<1>(roi_adverse);

        if(j_fou1 == -1 && j_fou2 == -1) return false;

        for(int h = 0; h < 8; h++){
            if ((i_fou1-h == i_roi && j_fou1-h == j_roi) || (i_fou2-h == i_roi && j_fou2-h == j_roi) ||
                (i_fou1+h == i_roi && j_fou1+h == j_roi) || (i_fou2+h == i_roi && j_fou2+h == j_roi) ||
                (i_fou1+h == i_roi && j_fou1-h == j_roi) || (i_fou2+h == i_roi && j_fou2-h == j_roi) ||
                (i_fou1-h == i_roi && j_fou1+h == j_roi) || (i_fou2-h == i_roi && j_fou2+h == j_roi)){
                return true;
            }

        }
        return false;
    }
}

bool PlateauEchiquier::roiEstSurCaseCavalier(bool joueur) {
    std::tuple<int, int, std::string> cava1 = {-1,-1,""};
    std::tuple<int, int, std::string> cava2 = {-1,-1,""};
    std::tuple<int, int, std::string> roi_adverse = {-1,-1,""};

    int i_cava1 = -1;
    int j_cava1 = -1;
    int i_cava2 = -1;
    int j_cava2 = -1;
    int i_roi = -1;
    int j_roi = -1;

    if(joueur) {
        cava1 = joueur1[1];
        cava2 = joueur1[6];
        roi_adverse = joueur2[4];

        i_cava1 = std::get<0>(cava1);
        j_cava1 = std::get<1>(cava1);
        i_cava2 = std::get<0>(cava2);
        j_cava2 = std::get<1>(cava2);
        i_roi = std::get<0>(roi_adverse);
        j_roi = std::get<1>(roi_adverse);
    }else {
        cava1 = joueur2[1];
        cava2 = joueur2[6];
        roi_adverse = joueur1[4];

        i_cava1 = std::get<0>(cava1);
        j_cava1 = std::get<1>(cava1);
        i_cava2 = std::get<0>(cava2);
        j_cava2 = std::get<1>(cava2);
        i_roi = std::get<0>(roi_adverse);
        j_roi = std::get<1>(roi_adverse);
    }

        if(j_cava1 == -1 && j_cava2 == -1) return false;

        else if ((i_cava1-2 == i_roi && j_cava1-1 == j_roi) || (i_cava2-2 == i_roi && j_cava2-1 == j_roi) ||
        (i_cava1-1 == i_roi && j_cava1-2 == j_roi) || (i_cava2-1 == i_roi && j_cava2-2 == j_roi) ||
        (i_cava1+1 == i_roi && j_cava1-2 == j_roi) || (i_cava2+1 == i_roi && j_cava2-2 == j_roi) ||
        (i_cava1+2 == i_roi && j_cava1-1 == j_roi) || (i_cava2+2 == i_roi && j_cava2-1 == j_roi) ||
        (i_cava1+2 == i_roi && j_cava1+1 == j_roi) || (i_cava2+2 == i_roi && j_cava2+1 == j_roi) ||
        (i_cava1+1 == i_roi && j_cava1+2 == j_roi) || (i_cava2+1 == i_roi && j_cava2+2 == j_roi) ||
        (i_cava1-1 == i_roi && j_cava1+2 == j_roi) || (i_cava2-1 == i_roi && j_cava2+2 == j_roi) ||
        (i_cava1-2 == i_roi && j_cava1+1 == j_roi) || (i_cava2-2 == i_roi && j_cava2+1 == j_roi) ) {
            return true;
        }
        else return false;
}

bool PlateauEchiquier::roiACotePion(bool joueur) {
    if(joueur){
        std::tuple<int,int,std::string> pion = {-1,-1,""};
        std::tuple<int,int,std::string> roi_adverse = joueur2[4];
        int i_roi = std::get<0>(roi_adverse);
        int j_roi = std::get<1>(roi_adverse);
        for(int h = 8; h < 16; h++){
            pion = joueur1[h];
            int i_pion = std::get<0>(pion);
            int j_pion = std::get<1>(pion);

            if ((i_pion-1 == i_roi && j_pion+1 == j_roi) || (i_pion-1 == i_roi && j_pion-1 == j_roi)){
                return true;
            }
        }
        return false;
    }else{
        std::tuple<int,int,std::string> pion = {-1,-1,""};
        std::tuple<int,int,std::string> roi_adverse = joueur1[4];
        int i_roi = std::get<0>(roi_adverse);
        int j_roi = std::get<1>(roi_adverse);
        for(int h = 8; h < 16; h++){
            pion = joueur2[h];
            int i_pion = std::get<0>(pion);
            int j_pion = std::get<1>(pion);

            if ((i_pion+1 == i_roi && j_pion+1 == j_roi) || (i_pion+1 == i_roi && j_pion-1 == j_roi)){
                return true;
            }
        }
        return false;
    }
}

bool PlateauEchiquier::roiEStEnEchec(bool joueur) {
    if(joueur){
        for(int h = 0; h < 16; h++){
            if((std::get<0>(joueur2[h]) == std::get<0>(joueur1[4]) && (std::get<2>(joueur2[h]) == "Dame" || std::get<2>(joueur2[h]) == "Tour")) || (std::get<1>(joueur2[h]) == std::get<1>(joueur1[4]) && (std::get<2>(joueur2[h]) == "Dame" || std::get<2>(joueur2[h]) == "Tour"))) return true;
            if(roiEstSurDiagonaleDeFou(!joueur) || roiEstSurCaseCavalier(!joueur)) return true;
            if(roiACotePion(!joueur)) return true;
        }
        return  false;
    }else{
        for(int h = 0; h < 16; h++){
            if((std::get<0>(joueur1[h]) == std::get<0>(joueur2[4]) && (std::get<2>(joueur1[h]) == "Dame" || std::get<2>(joueur1[h]) == "Tour")) || (std::get<1>(joueur1[h]) == std::get<1>(joueur2[4]) && (std::get<2>(joueur1[h]) == "Dame" || std::get<2>(joueur1[h]) == "Tour"))) return true;
            if(roiEstSurDiagonaleDeFou(!joueur) || roiEstSurCaseCavalier(!joueur)) return true;
            if(roiACotePion(!joueur)) return true;
        }
        return false;
    }
}

std::string PlateauEchiquier::quelleImage(std::string nom, bool joueur) {
    if(joueur){
        if(piece_bouffee == "Cavalier") return "\u2658";
        else if(piece_bouffee == "Fou") return "\u2657";
        else if(piece_bouffee == "Tour") return "\u2656";
        else if(piece_bouffee == "Dame") return "\u2655";
        else if(piece_bouffee == "Pion") return "\u2659";
        else return "";
    }else{
        if(piece_bouffee == "Cavalier") return "\u265E";
        else if(piece_bouffee == "Fou") return "\u265D";
        else if(piece_bouffee == "Tour") return "\u265C";
        else if(piece_bouffee == "Dame") return "\u265B";
        else if(piece_bouffee == "Pion") return "\u265F";
        else return "";
    }
}

void PlateauEchiquier::posOrdiPiece() {
    int k = 0;
    for(int h = 0; h < 16; h++){
        std::string tmp = "";
        if(std::get<2>(joueur2[h]) != "Pion") {
            tmp = (std::get<2>(joueur2[h])).at(0) + getEquivalenceNum(std::get<1>(joueur2[h]));
            tmp += std::to_string(std::get<0>(joueur2[h]));
        }else{
            tmp = getEquivalenceNum(std::get<1>(joueur2[h]));
            tmp += std::to_string(std::get<0>(joueur2[h]));
        }
            ordiPiece[k] = tmp;
            k++;
    }
}

void PlateauEchiquier::launchEchiquier(bool ordi) {
    bool quiJoue = true; //joueur 1

    std::string ii = "";
    srand(time(NULL));
    while(les2RoisontSurLePlateau) {
        next_loop:
        std::cout << *(this) << std::endl;

        if(quiJoue) std::cout << "Tour joueur 1: " << std::endl;
        else if(!ordi) std::cout << "Tour joueur 2: " << std::endl;


        if(ordi && !quiJoue){
            int i = rand() % 8;
            int j = rand() % 8;
            int jj = getEquivalenceNum(j);
            std::string mouv = "";
            std::cout << "i: "<< i << " et " << "j: " << jj << j << std::endl;
            if(getCase(i*getDimension()+j).getPion()->getColor() == Couleur::NOIR) {
                if (getCase(i*getDimension()+j).getPion()->getNom() == "Pion") {
                    mouv = std::to_string(jj+'0') + std::to_string(i);
                    if (!mouvement_pion(mouv, quiJoue)) goto next_loop;
                } else if (getCase(i*getDimension()+j).getPion()->getNom() == "Tour") {
                    mouv = "T" + std::to_string(jj+'0') + std::to_string(i);
                    if (!mouvement_tour(mouv, quiJoue)) goto next_loop;
                } else if (getCase(i*getDimension()+j).getPion()->getNom() == "Cavalier") {
                    mouv = "C" + std::to_string(jj+'0') + std::to_string(i);
                    if (!mouvement_cavalier(mouv, quiJoue)) goto next_loop;
                } else if (getCase(i*getDimension()+j).getPion()->getNom() == "Fou") {
                    mouv = "F" + std::to_string(jj+'0') + std::to_string(i);
                    if (!mouvement_fou(mouv, quiJoue)) goto next_loop;
                } else if (getCase(i*getDimension()+j).getPion()->getNom() == "Dame") {
                    mouv = "D" + std::to_string(jj+'0') + std::to_string(i);
                    if (!mouvement_dame(mouv, quiJoue)) goto next_loop;
                } else {
                    mouv = "R" + std::to_string(jj+'0') + std::to_string(i);
                    if (!mouvement_roi(mouv, quiJoue)) goto next_loop;
                }
            }else goto next_loop;

        }else {
            std::cin >> ii;
            if(ii.compare("help") == 0){
                std::cout << help(quiJoue) << std::endl;
                goto next_loop;
            }

            if (ii.size() == 2) {
                if (!mouvement_pion(ii, quiJoue)) goto next_loop;
            } else if (ii.at(0) == 'T') {
                if (!mouvement_tour(ii, quiJoue)) goto next_loop;
            } else if (ii.at(0) == 'C') {
                if (!mouvement_cavalier(ii, quiJoue)) goto next_loop;
            } else if (ii.at(0) == 'F') {
                if (!mouvement_fou(ii, quiJoue)) goto next_loop;
            } else if (ii.at(0) == 'D') {
                if (!mouvement_dame(ii, quiJoue)) goto next_loop;
            } else {
                if (!mouvement_roi(ii, quiJoue)) goto next_loop;
            }
        }
        if(roiEStEnEchec(quiJoue)){
            // TODO undo mouvement:: reste a gere cas ou mouvement a detruit une piece
            std::string piece = std::get<2>(dernier_mouv[0]);
            if(quiJoue){
                for(int h = 0; h < 16; h++){
                    if(std::get<0>(joueur1[h]) == std::get<0>(dernier_mouv[1]) && std::get<1>(joueur1[h]) == std::get<1>(dernier_mouv[1]) && std::get<2>(joueur1[h]) == std::get<2>(dernier_mouv[1])){
                        joueur1[h] = {std::get<0>(dernier_mouv[0]), std::get<1>(dernier_mouv[0]), piece};
                        move(std::get<0>(dernier_mouv[1]), std::get<1>(dernier_mouv[1]), std::get<0>(dernier_mouv[0]), std::get<1>(dernier_mouv[0]));
                        break;
                    }
                }
                std::string img = quelleImage(piece_bouffee, !quiJoue);

                for(int h = 0; h < 16; h++){
                    if(std::get<2>(joueur2[h]) == piece_bouffee && std::get<0>(joueur2[h]) == -1){
                        Pion p(piece_bouffee,img,Couleur::NOIR);
                        getCase(std::get<0>(dernier_mouv[1])*getDimension()+std::get<1>(dernier_mouv[1])).setPion(p);
                    }
                }
            }else{

                for(int h = 0; h < 16; h++){
                    if(std::get<0>(joueur2[h]) == std::get<0>(dernier_mouv[1]) && std::get<1>(joueur2[h]) == std::get<1>(dernier_mouv[1]) && std::get<2>(joueur2[h]) == std::get<2>(dernier_mouv[1])){
                        joueur2[h] = {std::get<0>(dernier_mouv[0]), std::get<1>(dernier_mouv[0]), piece};
                        move(std::get<0>(dernier_mouv[1]), std::get<1>(dernier_mouv[1]), std::get<0>(dernier_mouv[0]), std::get<1>(dernier_mouv[0]));
                        break;
                    }
                }

                std::string img = quelleImage(piece_bouffee, !quiJoue);
                for(int h = 0; h < 16; h++){
                    if(std::get<2>(joueur1[h]) == piece_bouffee && std::get<0>(joueur1[h]) == -1){
                        Pion p(piece_bouffee,img,Couleur::BLANC);
                        getCase(std::get<0>(dernier_mouv[1])*getDimension()+std::get<1>(dernier_mouv[1])).setPion(p);
                    }
                }
            }
            std::cout << "Mouvement impossible. Roi en Echec" << std::endl;
            goto next_loop;
        }

        quiJoue = !quiJoue;
    }
    if(std::get<0>(joueur1[4]) == -1) std::cout << "C'est le joueur 2 qui gagne!" << std::endl;
    else if(std::get<0>(joueur2[4]) == -1) std::cout << "C'est le joueur 1 qui gagne!" << std::endl;

}

std::string PlateauEchiquier::helpPion(bool joueur) {
    std::string res = "";
    if(joueur){
        for(int h = 8; h < 16; h++){
            int i = std::get<0>(joueur1[h]);
            int j = std::get<1>(joueur1[h]);
            if(i == 6){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                       getEquivalenceNum(j) + " -> ";
                res += std::to_string(i-2) + " " + getEquivalenceNum(j) + "\n";
            }
            if(i-1 >= 0 && getCase(i-1*getDimension()+j).isEmpty()){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                        getEquivalenceNum(j) + " -> ";
                res += std::to_string(i-1) + " " + getEquivalenceNum(j) + "\n";
            }
            if(i-1 >= 0 && j-1 >= 0 && !getCase(i-1*getDimension()+j-1).isEmpty()){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                        getEquivalenceNum(j) + " -> ";
                res += std::to_string(i-1) + " " + getEquivalenceNum(j-1) + "\n";
            }
            if(i-1 >= 0 && j+1 < 8 && !getCase(i-1*getDimension()+j+1).isEmpty()){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                        getEquivalenceNum(j) + " -> ";
                res += std::to_string(i-1) + " " + getEquivalenceNum(j+1) + "\n";
            }

        }
    }else{
        for(int h = 8; h < 16; h++){
            int i = std::get<0>(joueur2[h]);
            int j = std::get<1>(joueur2[h]);
            if(i == 1){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                       std::to_string(j) + " -> ";
                res += std::to_string(i+2) + " " + getEquivalenceNum(j) + "\n";
            }
            if(i+1 < 8 && getCase(i+1*getDimension()+j).isEmpty()){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                       std::to_string(j) + " -> ";
                res += std::to_string(i+1) + " " + getEquivalenceNum(j) + "\n";
            }
            if(i+1 < 8 && j-1 >= 0 && !getCase(i+1*getDimension()+j-1).isEmpty()){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                       std::to_string(j) + " -> ";
                res += std::to_string(i+1) + " " + getEquivalenceNum(j-1) + "\n";
            }
            if(i+1 < 8 && j+1 < 8 && !getCase(i+1*getDimension()+j+1).isEmpty()){
                res += getCase(i*getDimension()+j).getPion()->getNom() + " " + std::to_string(i) + " " +
                       std::to_string(j) + " -> ";
                res += std::to_string(i+1) + " " + getEquivalenceNum(j+1) + "\n";
            }

        }
    }
    return res;
}

std::string PlateauEchiquier::helpTour(bool joueur) {
    std::string res = "";
    int i_tour1 = -1;
    int j_tour1 = -1;
    int i_tour2 = -1;
    int j_tour2 = -1;
    if(joueur){
        i_tour1 = std::get<0>(joueur1[0]);
        j_tour1 = std::get<1>(joueur1[0]);
        i_tour2 = std::get<0>(joueur1[7]);
        j_tour2 = std::get<1>(joueur1[7]);
    }else{
        i_tour1 = std::get<0>(joueur2[0]);
        j_tour1 = std::get<1>(joueur2[0]);
        i_tour2 = std::get<0>(joueur2[7]);
        j_tour2 = std::get<1>(joueur2[7]);
    }
    int h = i_tour1 + 1;
    while (h < 8 && getCase(h*getDimension()+j_tour1).isEmpty()) {
        h++;
    }
    if(h-1 != i_tour1) {
        res += "Tour " + std::to_string(i_tour1) + " " + getEquivalenceNum(j_tour1) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(j_tour1) + "\n";
    }

    h = i_tour1 - 1;
    while (h >= 0 && getCase(h*getDimension()+j_tour1).isEmpty()) {
        h--;
    }
    if(h+1 != i_tour1) {
        res += "Tour " + std::to_string(i_tour1) + " " + getEquivalenceNum(j_tour1) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(j_tour1) + "\n";
    }

    h = j_tour1 + 1;
    while (h < 8 && getCase(i_tour1*getDimension()+h).isEmpty()) {
        h++;
    }
    if(h-1 != j_tour1){
        res += "Tour " + std::to_string(i_tour1) + " " + getEquivalenceNum(j_tour1) +
               " -> ";
        res += std::to_string(i_tour1) + " " + getEquivalenceNum(h-1) + "\n";
    }

    h = j_tour1 - 1;
    while (h >= 0 && getCase(i_tour1*getDimension()+h).isEmpty()) {
        h--;
    }
    if(h+1 != j_tour1) {
        res += "Tour " + std::to_string(i_tour1) + " " + getEquivalenceNum(j_tour1) +
               " -> ";
        res += std::to_string(i_tour1) + " " + getEquivalenceNum(h+1) + "\n";
    }


    h = i_tour2 + 1;
    while (h < 8 && getCase(h*getDimension()+j_tour2).isEmpty()) {
        h++;
    }
    if(h-1 != i_tour2) {
        res += "Tour " + std::to_string(i_tour2) + " " + getEquivalenceNum(j_tour2) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(j_tour2) + "\n";
    }

    h = i_tour2 - 1;
    while (h >= 0 && getCase(h*getDimension()+j_tour2).isEmpty()) {
        h--;
    }
    if(h+1 != i_tour2) {
        res += "Tour " + std::to_string(i_tour2) + " " + getEquivalenceNum(j_tour2) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(j_tour2) + "\n";
    }

    h = j_tour2 + 1;
    while (h < 8 && getCase(i_tour2*getDimension()+h).isEmpty()) {
        h++;
    }
    if(h-1 != j_tour2){
        res += "Tour " + std::to_string(i_tour2) + " " + getEquivalenceNum(j_tour2) +
               " -> ";
        res += std::to_string(i_tour2) + " " + getEquivalenceNum(h-1) + "\n";
    }

    h = j_tour2 - 1;
    while (h >= 0 && getCase(i_tour2*getDimension()+h).isEmpty()) {
        h--;
    }
    if(h+1 != j_tour2) {
        res += "Tour " + std::to_string(i_tour2) + " " + getEquivalenceNum(j_tour2) +
               " -> ";
        res += std::to_string(i_tour2) + " " + getEquivalenceNum(h+1) + "\n";
    }
    return res;
}

std::string PlateauEchiquier::helpCavalier(bool joueur) {
    Couleur bon = Couleur ::BLANC;
    std::string res = "";
    int i_cava1 = -1;
    int j_cava1 = -1;
    int i_cava2 = -1;
    int j_cava2 = -1;
    if(joueur){
        i_cava1 = std::get<0>(joueur1[1]);
        j_cava1 = std::get<1>(joueur1[1]);
        i_cava2 = std::get<0>(joueur1[6]);
        j_cava2 = std::get<1>(joueur1[6]);
    }else{
        int i_cava1 = std::get<0>(joueur2[1]);
        int j_cava1 = std::get<1>(joueur2[1]);;
        int i_cava2 = std::get<0>(joueur2[6]);
        int j_cava2 = std::get<1>(joueur2[6]);
        bon = Couleur ::NOIR;
    }
    if (i_cava1-2 >= 0 && j_cava1-1 >= 0 &&
    getCase(i_cava1 - 2*getDimension()+j_cava1 - 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1-2) + " " + getEquivalenceNum(j_cava1-1) + "\n";
    }
    if (i_cava2-2 >= 0 && j_cava2-1 >= 0 &&
    getCase(i_cava2 - 2*getDimension()+j_cava2 - 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2-2) + " " + getEquivalenceNum(j_cava2-1) + "\n";
    }
    if (i_cava1-1 >= 0 && j_cava1-2 >= 0 &&
    getCase(i_cava1 - 1*getDimension()+j_cava1 - 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1-1) + " " + getEquivalenceNum(j_cava1-2) + "\n";
    }
    if (i_cava2-1 >= 0 && j_cava2-2 >= 0 &&
    getCase(i_cava2 - 1*getDimension()+j_cava2 - 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2-1) + " " + getEquivalenceNum(j_cava2-2) + "\n";
    }
    if (i_cava1+1 < 8 && j_cava1-2 >= 0 &&
            getCase(i_cava1 + 1*getDimension()+j_cava1 - 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1+1) + " " + getEquivalenceNum(j_cava1-2) + "\n";
    }
    if (i_cava2+1 < 8 && j_cava2-2 >= 0 &&
        getCase(i_cava2 + 1*getDimension()+j_cava2 - 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2+1) + " " + getEquivalenceNum(j_cava2-2) + "\n";
    }
        if (i_cava1+2 < 8 && j_cava1-1 >= 0 &&
            getCase(i_cava1 + 2*getDimension()+j_cava1 - 1).getPion()->getColor() != bon) {
            res += "Cavalier " + std::to_string(i_cava1) + " " +
                    getEquivalenceNum(j_cava1) + " -> ";
            res += std::to_string(i_cava1+2) + " " + getEquivalenceNum(j_cava1-1) + "\n";
        }
    if (i_cava2+2 < 8 && j_cava2-1 >= 0 &&
        getCase(i_cava2 + 2*getDimension()+j_cava2 - 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2+2) + " " + getEquivalenceNum(j_cava2-1) + "\n";
    }
    if (i_cava1+2 < 8 && j_cava1+1 < 8 &&
            getCase(i_cava1 + 2*getDimension()+j_cava1 + 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1+2) + " " + getEquivalenceNum(j_cava1+1) + "\n";
    }
    if (i_cava2+2 < 8 && j_cava2+1 < 8 &&
        getCase(i_cava2 + 2*getDimension()+j_cava2 + 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2+2) + " " + getEquivalenceNum(j_cava2+1) + "\n";
    }
    if (i_cava1+1 < 8 && j_cava1+2 < 8 &&
            getCase(i_cava1 + 1*getDimension()+j_cava1 + 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1+1) + " " + getEquivalenceNum(j_cava1+2) + "\n";
    }
    if (i_cava2+1 < 8 && j_cava2+2 < 8 &&
        getCase(i_cava2 + 1*getDimension()+j_cava2 + 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2+1) + " " + getEquivalenceNum(j_cava2+2) + "\n";
    }
    if (i_cava1-1 >= 0 && j_cava1+2 < 8 &&
    getCase(i_cava1 - 1*getDimension()+j_cava1 + 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1-1) + " " + getEquivalenceNum(j_cava1+2) + "\n";
    }
    if (i_cava2-1 >= 0 && j_cava2+2 < 8 &&
        getCase(i_cava2 - 1*getDimension()+j_cava2 + 2).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2-1) + " " + getEquivalenceNum(j_cava2+2) + "\n";
    }
    if (i_cava1-2 >= 0 && j_cava1+1 < 8 &&
    getCase(i_cava1 - 2*getDimension()+j_cava1 + 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava1) + " " +
                getEquivalenceNum(j_cava1) + " -> ";
        res += std::to_string(i_cava1-2) + " " + getEquivalenceNum(j_cava1+1) + "\n";
    }
    if (i_cava2-2 >= 0 && j_cava2+1 < 8 &&
        getCase(i_cava2 - 2*getDimension()+j_cava2 + 1).getPion()->getColor() != bon) {
        res += "Cavalier " + std::to_string(i_cava2) + " " +
                getEquivalenceNum(j_cava2) + " -> ";
        res += std::to_string(i_cava2-2) + " " + getEquivalenceNum(j_cava2+1) + "\n";
    }
    return res;
}

std::string PlateauEchiquier::helpFou(bool joueur) {
    std::string res = "";
    int i_fou1 = -1;
    int j_fou1 = -1;
    int i_fou2 = -1;
    int j_fou2 = -1;
    if(joueur){
        i_fou1 = std::get<0>(joueur1[2]);
        j_fou1 = std::get<1>(joueur1[2]);
        i_fou2 = std::get<0>(joueur1[5]);
        j_fou2 = std::get<1>(joueur1[5]);
    }else{
        i_fou1 = std::get<0>(joueur2[2]);
        j_fou1 = std::get<1>(joueur2[2]);
        i_fou2 = std::get<0>(joueur2[5]);
        j_fou2 = std::get<1>(joueur2[5]);
    }
    int h = i_fou1 + 1;
    int hh = j_fou1 +1;
    while (h < 8 && hh < 8 && getCase(h*getDimension()+hh).isEmpty()) {
        h++;
        hh++;
    }
    if(h-1 != i_fou1 && hh-1 != j_fou1) {
        res += "Fou " + std::to_string(i_fou1) + " " + getEquivalenceNum(j_fou1) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(hh-1) + "\n";
    }

    h = i_fou1 - 1;
    hh = j_fou1 + 1;
    while (h >= 0 && hh < 8 && getCase(h*getDimension()+hh).isEmpty()) {
        h--;
        hh++;
    }
    if(h+1 != i_fou1 && hh-1 != j_fou1) {
        res += "Fou " + std::to_string(i_fou1) + " " + getEquivalenceNum(j_fou1) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(hh-1) + "\n";
    }

    h = i_fou1 + 1;
    hh = j_fou1 -1;
    while (h < 8 && hh >= 0 && getCase(h*getDimension()+hh).isEmpty()) {
        h++;
        hh--;
    }
    if(h-1 != i_fou1 && hh+1 != j_fou1){
        res += "Fou " + std::to_string(i_fou1) + " " + getEquivalenceNum(j_fou1) +
               " -> ";
        res += std::to_string(h -1) + " " + getEquivalenceNum(hh+1) + "\n";
    }

    h = i_fou1 - 1;
    hh = j_fou1 -1;
    while (h >= 0 && hh >= 0 && getCase(h*getDimension()+hh).isEmpty()) {
        h--;
        hh--;
    }
    if(h+1 != i_fou1 && hh+1 != j_fou1) {
        res += "Fou " + std::to_string(i_fou1) + " " + getEquivalenceNum(j_fou1) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(hh+1) + "\n";
    }


    h = i_fou2 + 1;
    hh = j_fou2 +1;
    while (h < 8 && hh < 8 && getCase(h*getDimension()+hh).isEmpty()) {
        h++;
        hh++;
    }
    if(h-1 != i_fou2 && hh-1 != j_fou2) {
        res += "Fou " + std::to_string(i_fou2) + " " + getEquivalenceNum(j_fou2) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(hh-1) + "\n";
    }

    h = i_fou2 - 1;
    hh = j_fou2 + 1;
    while (h >= 0 && hh < 8 && getCase(h*getDimension()+hh).isEmpty()) {
        h--;
        hh++;
    }
    if(h+1 != i_fou2 && hh-1 != j_fou2) {
        res += "Fou " + std::to_string(i_fou2) + " " + getEquivalenceNum(j_fou2) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(hh-1) + "\n";
    }

    h = i_fou2 + 1;
    hh = j_fou2 -1;
    while (h < 8 && hh >= 0 && getCase(h*getDimension()+hh).isEmpty()) {
        h++;
        hh--;
    }
    if(h-1 != i_fou2 && hh+1 != j_fou2){
        res += "Fou " + std::to_string(i_fou2) + " " + getEquivalenceNum(j_fou2) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(hh+1) + "\n";
    }

    h = i_fou2 - 1;
    hh = j_fou2 -1;
    while (h >= 0 && hh >= 0 && getCase(h*getDimension()+hh).isEmpty()) {
        h--;
        hh--;
    }
    if(h+1 != i_fou2 && hh+1 != j_fou2) {
        res += "Fou " + std::to_string(i_fou2) + " " + getEquivalenceNum(j_fou2) +
               " -> ";
        res += std::to_string(h +1) + " " + getEquivalenceNum(hh+1) + "\n";
    }
    return res;
}

std::string PlateauEchiquier::helpDame(bool joueur) {
    std::string res = "";
    int i_dame = -1;
    int j_dame = -1;
    if(joueur){
        i_dame = std::get<0>(joueur1[3]);
        j_dame = std::get<1>(joueur1[3]);
    }else{
        i_dame = std::get<0>(joueur2[3]);
        j_dame = std::get<1>(joueur2[3]);
    }

    int h = i_dame + 1;
    while (h < 8 && getCase(h*getDimension()+j_dame).isEmpty()) {
        h++;
    }
    if(h-1 != i_dame) {
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(j_dame) + "\n";
    }

    h = i_dame - 1;
    while (h >= 0 && getCase(h*getDimension()+j_dame).isEmpty()) {
        h--;
    }
    if(h+1 != i_dame) {
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(j_dame) + "\n";
    }

    h = j_dame + 1;
    while (h < 8 && getCase(i_dame*getDimension()+h).isEmpty()) {
        h++;
    }
    if(h-1 != j_dame){
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(i_dame) + " " + getEquivalenceNum(h-1) + "\n";
    }

    h = j_dame - 1;
    while (h >= 0 && getCase(i_dame*getDimension()+h).isEmpty()) {
        h--;
    }
    if(h+1 != j_dame) {
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(i_dame) + " " + getEquivalenceNum(h+1) + "\n";
    }

    h = i_dame + 1;
    int hh = j_dame +1;
    while (h < 8 && hh < 8 && getCase(h*getDimension()+hh).isEmpty()) {
        h++;
        hh++;
    }
    if(h-1 != i_dame && hh-1 != j_dame) {
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(h - 1) + " " + getEquivalenceNum(hh-1) + "\n";
    }

    h = i_dame - 1;
    hh = j_dame + 1;
    while (h >= 0 && hh < 8 && getCase(h*getDimension()+hh).isEmpty()) {
        h--;
        hh++;
    }
    if(h+1 != i_dame && hh-1 != j_dame) {
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(hh-1) + "\n";
    }

    h = i_dame + 1;
    hh = j_dame -1;
    while (h < 8 && hh >= 0 && getCase(h*getDimension()+hh).isEmpty()) {
        h++;
        hh--;
    }
    if(h-1 != i_dame && hh+1 != j_dame){
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(h -1) + " " + getEquivalenceNum(hh+1) + "\n";
    }

    h = i_dame - 1;
    hh = j_dame -1;
    while (h >= 0 && hh >= 0 && getCase(h*getDimension()+hh).isEmpty()) {
        h--;
        hh--;
    }
    if(h+1 != i_dame && hh+1 != j_dame) {
        res += "Dame " + std::to_string(i_dame) + " " + getEquivalenceNum(j_dame) +
               " -> ";
        res += std::to_string(h + 1) + " " + getEquivalenceNum(hh+1) + "\n";
    }
    return res;
}

std::string PlateauEchiquier::helpRoi(bool joueur) {
    std::string res = "";
    int i_roi = -1;
    int j_roi = -1;
    if(joueur){
        i_roi = std::get<0>(joueur1[4]);
        j_roi = std::get<1>(joueur1[4]);
    }else{
        i_roi = std::get<0>(joueur2[4]);
        j_roi = std::get<1>(joueur2[4]);
    }
    if(i_roi + 1 < 8 && j_roi + 1 < 8){
        res += "Roi " + std::to_string(i_roi) + " " +
                getEquivalenceNum(j_roi) + " -> ";
        res += std::to_string(i_roi + 1) + " " + getEquivalenceNum(j_roi+1) + "\n";
    }
    if(i_roi + 1 < 8 && j_roi-1 >= 0){
        res += "Roi " + std::to_string(i_roi) + " " +
                getEquivalenceNum(j_roi) + " -> ";
        res += std::to_string(i_roi + 1) + " " + getEquivalenceNum(j_roi-1) + "\n";
    }
    if(i_roi - 1 >= 0 && j_roi + 1 < 8){
        res += "Roi " + std::to_string(i_roi) + " " +
                getEquivalenceNum(j_roi) + " -> ";
        res += std::to_string(i_roi - 1) + " " + getEquivalenceNum(j_roi+1) + "\n";
    }
    if(i_roi - 1 >= 0 && j_roi - 1 >= 0){
        res += "Roi " + std::to_string(i_roi) + " " +
                getEquivalenceNum(j_roi) + " -> ";
        res += std::to_string(i_roi - 1) + " " + getEquivalenceNum(j_roi-1) + "\n";
    }
    if(j_roi - 1 >= 0){
        res += "Roi " + std::to_string(i_roi) + " " +
                getEquivalenceNum(j_roi) + " -> ";
        res += std::to_string(i_roi) + " " + getEquivalenceNum(j_roi-1) + "\n";
    }
    if(j_roi + 1 < 8){
        res += "Roi " + std::to_string(i_roi) + " " +
                getEquivalenceNum(j_roi) + " -> ";
        res += std::to_string(i_roi) + " " + getEquivalenceNum(j_roi+1) + "\n";
    }
    return res;
}

std::string PlateauEchiquier::help(bool joueur) {
    std::string res = "";
    res += helpPion(joueur) +  helpTour(joueur) + helpCavalier(joueur) + helpFou(joueur) + helpDame(joueur) + helpRoi(joueur);
    return res;
}
