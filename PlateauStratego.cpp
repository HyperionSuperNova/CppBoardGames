#include <fstream>
#include <time.h>
#include "PlateauStratego.h"

PlateauStratego::PlateauStratego(): Plateau(10) {};

std::ostream &operator<<(std::ostream &os, const PlateauStratego &stratego) {
    os << "    ";
    for(int j = 0; j < 10; j++){
        os << j << "   ";
    }
    os << "\n";
    os << "  -----------------------------------------\n";

    for(int i = 0; i < 10; i++){
        os << i << "|  ";
        for(int j = 0; j < 10; j++){
            if((i == 4 || i == 5) && (j == 2 || j == 6)) os << "    ";
            else os << stratego.cases[i][j].getPion().getImg() << " | " ;

        }
        os << "\n";
    }
    os << "  -----------------------------------------" << std::endl;
    return os;
}


bool PlateauStratego::mouvement_eclaireur(int i_src, int j_src, int i_dst, int j_dst, bool joueur, bool ordi) {
    bool ok = true;
    int min = 0;
    int max = 0;
    if( i_dst < 10 && j_dst < 10){
        if(i_dst == i_src){
            if(j_dst > j_src) {
                min = j_src + 1;
                max = j_dst;
            }else {
                min = j_dst + 1;
                max = j_src;
            }
            for(int j = min; j < max; j++){
                if(!cases[i_src][j].isEmpty() || ((i_src == 4 || i_src == 5) && (j == 2 || j == 3 || j == 6 || j == 7))){
                    if(ordi && joueur) std::cout << "Mouvement impossible. Case non vide sur le chemin";
                    return 0;
                }
            }
            if(cases[i_dst][j_dst].isEmpty()){
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src, j_src);
                return 1;
            }else if(estPlusFortQue(cases[i_src][j_src].getPion(), cases[i_dst][j_dst].getPion()) ){
                if(joueur){
                    joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }else{
                     joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }
                std:: cout << "Pièce mangée: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src, j_src);
                return 1;
            }else{
                 if(cases[i_src][j_src].getPion().getNom().compare(cases[i_dst][j_dst].getPion().getNom()) == 0){
                     std::cout << "Battu par: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                     if(joueur){
                         joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                         joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                     }else{
                         joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                         joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                     }
                     cases[i_src][j_src] = Case(i_src, j_src);
                     cases[i_dst][j_dst] = Case(i_dst, j_dst);
                     return 1;
                 }else if(cases[i_dst][j_dst].getPion().getColor() != cases[i_src][j_src].getPion().getColor()){
                     std::cout << "Battu par: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                     //revelerUnePiece(i_dst, j_dst);
                     if(joueur){ // si c'est le joueur 1 qui joue
                         joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                     }else{
                         joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                     }
                     cases[i_src][j_src] = Case(i_src, j_src);
                     return 1;
                 }else return 0;
            }


        }else if (j_dst == j_src){
            if(i_dst > i_src) {
                min = i_src + 1;
                max = i_dst;
            }else {
                min = i_dst + 1;
                max = i_src;
            }
            for(int i = min; i < max; i++){
                if(!cases[i][j_src].isEmpty() ||  ((i == 4 || i == 5) && (j_src == 2 || j_src == 3 || j_src == 6 || j_src == 7))){
                    if(ordi && joueur) std::cout << "Mouvement impossible. Case non vide sur le chemin";
                    return 0;
                }
            }
            if(cases[i_dst][j_dst].isEmpty()){
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src, j_src);
                return 1;
            }else if(estPlusFortQue(cases[i_src][j_src].getPion(), cases[i_dst][j_dst].getPion()) ){
                if(joueur){
                    joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }else{
                    joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }
                std:: cout << "Pièce mangée: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src, j_src);
                return 1;
            }else if(cases[i_dst][j_dst].getPion().getColor() != cases[i_src][j_src].getPion().getColor()){
                if(cases[i_src][j_src].getPion().getNom().compare(cases[i_dst][j_dst].getPion().getNom()) == 0){
                    std::cout << "Battu par: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                    if(joueur){
                        joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                        joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                    }else{
                        joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                        joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }
                    cases[i_src][j_src] = Case(i_src, j_src);
                    cases[i_dst][j_dst] = Case(i_dst, j_dst);
                    return 1;
                }else {
                    std::cout << "Battu par: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                    //revelerUnePiece(i_dst, j_dst);
                    if(joueur){ // si c'est le joueur 1 qui joue
                        joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }else{
                        joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }
                    cases[i_src][j_src] = Case(i_src, j_src);
                }
                return 1;
            }else return 0;
        }else{
            if(ordi && joueur) std::cout << "mouvement impossible";
            return 0;
        }
    }else{
        if(ordi && joueur) std::cout << "Out of Bounds" << std::endl;
        return 0;
    }
}

bool PlateauStratego::mouvement_autre(int i_src, int j_src, int i_dst, int j_dst, bool joueur, bool ordi) {
    if( i_dst < 10 && j_dst < 10){
        if((i_dst == i_src -1 && j_dst == j_src) || (i_dst == i_src +1 && j_dst == j_src) || (i_dst == i_src && j_dst == j_src -1) || (i_dst == i_src && j_dst == j_src + 1)){
            if(cases[i_dst][j_dst].isEmpty()){
                move(i_src, j_src, i_dst, j_dst);

            }else if(estPlusFortQue(cases[i_src][j_src].getPion(), cases[i_dst][j_dst].getPion())){
                if(joueur){
                    joueur2[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }else{
                    joueur1[renvoiePionsNbr(cases[i_dst][j_dst].getPion().getNom())] --;
                }
                std:: cout << "Pièce mangée: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                cases[i_dst][j_dst] = cases[i_src][j_src];
                cases[i_src][j_src] = Case(i_src, j_src);

            }else{
                if(cases[i_src][j_src].getPion().getNom().compare(cases[i_dst][j_dst].getPion().getNom()) == 0){
                    std::cout << "Battu par: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
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
                    std::cout << "Battu par: " << cases[i_dst][j_dst].getPion().getNom() << std::endl;
                    if(joueur){ // si c'est le joueur 1 qui joue
                        joueur1[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }else{
                        joueur2[renvoiePionsNbr(cases[i_src][j_src].getPion().getNom())] --;
                    }
                    cases[i_src][j_src] = Case(i_src, j_src);
                }
            }
        }else{
            if(ordi && joueur) std::cout << "mouvement impossible";
            return 0;
        }
        return 1;
    }else{
        if(ordi && joueur) std::cout << "Out of Bounds" << std::endl;
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

bool PlateauStratego::mettrePionJoueurSurPlateau(bool joueur) {
    if(joueur) cacherPieceJoueur(false);
    else cacherPieceJoueur(true);
    std::string piece= "";
    std::string ii = "";
    std::string jj = "";
    int j = 0;
    std::string delimiter = " ";
    for(int h = 0; h < 40; h++){ // valeur h a changer
        std::cout << *(this) << std::endl;
        std::cout << "\nEspion (" << getNbrEspion(joueur) << ") Drapeau (" << getNbrDrapeau(joueur) << ") Eclaireur (" << getNbrEclaireur(joueur) << ") Demineur (" << getNbrDemineur(joueur) << ") Sergent (" << getNbrSergent(joueur) << ") Lieutenant (" << getNbrLieutenant(joueur) << ") Capitaine (" << getNbrCapitaine(joueur) << ") Commandant (" << getNbrCommandant(joueur) << ") Colonnel (" << getNbrColonnel(joueur) << ") General (" << getNbrGeneral(joueur) << ") Marechal (" << getNbrMarechal(joueur) << ") Bombe (" << getNbrBombe(joueur) << ")" << std::endl;
        std::cout << "Format: Nom de la piece  cordonnées: x y" << std::endl;
        std::cout << "Par exemple: Demineur 1 1" << std::endl;
        std::cout << "Pour charger des pièces, tapez: charger" << std::endl;
        std::cout << "Pour lancer la lecture du fichier test, tapez: lecture" << std::endl;

        std::cin >> piece;

        if(piece.compare("charger") == 0){
            mettrePionOrdiSurPlateau(joueur);
            cacherPieceJoueur(joueur);
            goto end;
        }
        if(piece.compare("lecture") == 0){
                lectureFichierTest();
                return false;
        }

        std::cin >> ii;
        std::cin >> jj;

        while(ii.size() != 1 || jj.size() != 1){
            std::cout << "Mauvaise entrée. Veuillez recommencer" << std::endl;
            std::cin >> piece;
            if(piece.compare("charger") == 0){
                cacherPieceJoueur(joueur);
                goto end;
            }

            std::cin >> ii;
            std::cin >> jj;

        }


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
                        cases[i][j].setPion(Pion(piece, imag, Couleur::BLANC));
                        joueur1[renvoiePionsNbr(piece)]--;
                    } else {
                        std::cout << "Vous n'avez plus ce genre de pièce." << std::endl;
                        h--;
                    }
                }else{
                    if (joueur2[renvoiePionsNbr(piece)] > 0) {
                        std::string imag = std::get<1>(img[renvoiePionsNbr(piece)]);
                        cases[i][j].setPion(Pion(piece, imag, Couleur::NOIR));
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
    end:
    std::cout << "Let's the game begin!" << std::endl;
    return true;
}

void PlateauStratego::mettrePionOrdiSurPlateau(bool joueur) {
    srand(time(NULL));
    int r = rand() % 6 + 1;
    std::string piece = "";
    int i = 0;
    int j = 0;
    std::string delimiter = " ";
    std::string nom = "";
    std::string path = "";
    if(joueur){
        nom = "joueur" + std::to_string(r) + ".txt";
        path = "../joueur/" + nom;
    }else{
        nom = "ordi" + std::to_string(r) + ".txt";
        path = "../ordi/" + nom;
    }

    std::cout << path << std::endl;
    std::ifstream infile(path);
    std::string line = "";
    while(std::getline(infile, line)){
        piece = line.substr(0, line.find(delimiter));
        i = std::stoi(line.substr(piece.length()+1, 1));
        j = std::stoi(line.substr(piece.length()+3, 1));
        if(joueur) cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::BLANC));
        else cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::NOIR));
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

std::vector< std::tuple<int, int> > PlateauStratego::getLigneColonne() {
    std::vector< std::tuple<int, int> > pieces;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(cases[i][j].getPion().getColor() == Couleur::NOIR) pieces.push_back({i, j});
        }
    }
    return pieces;
}

void PlateauStratego::revelerUnePiece(int i, int j) {
    std::string nom = cases[i][j].getPion().getNom();
    int n = renvoiePionsNbr(nom);
    cases[i][j].setPionImg(std::get<1>(img[n]));
}


bool PlateauStratego::queBombeEtDrapeau(bool joueur) {
    if(joueur){
        return (joueur1[1] == 0 && joueur1[2] == 0 && joueur1[3] == 0 && joueur1[4] == 0 && joueur1[5] == 0 && joueur1[6] == 0 && joueur1[7] == 0 && joueur1[8] == 0 && joueur1[9] == 0 && joueur1[10] == 0);
    }else{
        return (joueur2[1] == 0 && joueur2[2] == 0 && joueur2[3] == 0 && joueur2[4] == 0 && joueur2[5] == 0 && joueur2[6] == 0 && joueur2[7] == 0 && joueur2[8] == 0 && joueur2[9] == 0 && joueur2[10] == 0);
    }
}

void PlateauStratego::launchStratego(bool ordi) {

   bool lecture = mettrePionJoueurSurPlateau(true);
   if(!lecture){
       lectureFichierTest();
       scoreFinPartie();
       return;
   }

    if(ordi) mettrePionOrdiSurPlateau(false);
    else mettrePionJoueurSurPlateau(false);


    bool quiJoue = true; //joueur 1

    joueur1[0] = 1; joueur1[1] = 1; joueur1[2] = 8; joueur1[3] = 5; joueur1[4] = 4; joueur1[5] = 4; joueur1[6] = 4; joueur1[7] = 3; joueur1[8] = 2; joueur1[9] = 1; joueur1[10] = 1; joueur1[11] = 6;
    joueur2[0] = 1; joueur2[1] = 1; joueur2[2] = 8; joueur2[3] = 5; joueur2[4] = 4; joueur2[5] = 4; joueur2[6] = 4; joueur2[7] = 3; joueur2[8] = 2; joueur2[9] = 1; joueur2[10] = 1; joueur2[11] = 6;


    std::string ii = "";
    std::string jj = "";
    srand(time(NULL));
    while(joueur1[0] != 0 && joueur2[0] != 0){
        cacherPieceJoueur(!quiJoue);
        next_loop:

        if(quiJoue && ordi) std::cout << *(this) << std::endl;
        else if(!ordi) std::cout << *(this) << std::endl;

        if(quiJoue) std::cout << "Tour joueur 1: " << std::endl;
        else if(!ordi) std::cout << "Tour joueur 2: " << std::endl;

        int i_src = 0;
        int j_src = 0;
        int i_dst = 0;
        int j_dst = 0;
        if(!quiJoue && ordi){ // tour ordi
            std::vector< std::tuple<int, int> > coup = getLigneColonne();
            int r = rand() % coup.size();

            i_src = std::get<0>(coup[r]);
            j_src = std::get<1>(coup[r]);

            if(cases[i_src][j_src].getPion().getNom().compare("Eclaireur") == 0){
                again:
                i_dst = rand() % 10;
                j_dst = rand() % 10;
                if((i_dst != i_src && j_dst != j_src) || (i_dst == i_src && j_dst == j_src)) goto again;

            }else {
                int set_i_dst[2] = {i_src + 1, i_src + 1};
                int set_j_dst[2] = {j_src + 1, j_src + 1};
                i_dst = set_i_dst[rand() % 2];
                j_dst = set_j_dst[rand() % 2];
            }

        }else {
            std::cin >> ii;
            if(ii.compare("help") == 0){
                std::cout << help(quiJoue) << std::endl;
                goto next_loop;
            }
            std::cin >> jj;

            while(ii.size() != 1 || jj.size() != 1){
                std::cout << "Mauvaise entrée. Veuillez recommencer" << std::endl;
                goto next_loop;
            }


            i_src = std::stoi(ii);
            j_src = std::stoi(jj);

            std::cin >> ii;
            std::cin >> jj;

            while(ii.size() != 1 || jj.size() != 1){
                std::cout << "Mauvaise entrée. Veuillez recommencer" << std::endl;
                goto next_loop;
            }

            i_dst = std::stoi(ii);
            j_dst = std::stoi(jj);
        }


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
            if(ordi && quiJoue) std::cout << "Case invalide" << std::endl;
            if(ordi && quiJoue) std::cout << "Veuillez entrer de nouvelles valeurs" << std::endl;
            goto next_loop;
        }


        if (cases[i_src][j_src].getPion().getNom().compare("Bombe") == 0 || cases[i_src][j_src].getPion().getNom().compare("Drapeau") == 0 || cases[i_src][j_src].getPion().getNom().compare("") == 0){
            if(ordi && quiJoue) std::cout << "Mouvement impossible\n" << std::endl;
            goto next_loop;
        }else if (cases[i_src][j_src].getPion().getNom().compare("Eclaireur") == 0){
            if(!mouvement_eclaireur(i_src, j_src, i_dst, j_dst, quiJoue, ordi)) goto next_loop;
        }
        else{
            if(!mouvement_autre(i_src, j_src, i_dst, j_dst, quiJoue, ordi)) goto next_loop;
        }
        quiJoue = !quiJoue;
        if(queBombeEtDrapeau(quiJoue)) quiJoue = !quiJoue;
        if(queBombeEtDrapeau(quiJoue) && queBombeEtDrapeau(!quiJoue)){
            std::cout << "Plus personne ne peut bouger de pions. Match nul!";
            break;
        }
    }
    scoreFinPartie();
}

void PlateauStratego::scoreFinPartie() {
    if(joueur1[0] < 0) std::cout << "C'est le joueur 2 qui gagne!" << std::endl;
    else if(joueur2[0] < 0) std::cout << "C'est le joueur 1 qui gagne!" << std::endl;
}

bool PlateauStratego::pieceEstdeplacable(int i, int j) {
    if(i == 0 && j == 0){
        return (cases[i+1][j].isEmpty() || cases[i+1][j+1].isEmpty() || cases[i][j+1].isEmpty());
    }else if(i == 9 && j == 0){
        return (cases[i][j+1].isEmpty() || cases[i-1][j].isEmpty() ||  cases[i-1][j+1].isEmpty());
    }else if(i == 9 && j == 9){
        return (cases[i][j-1].isEmpty() || cases[i-1][j].isEmpty() || cases[i-1][j-1].isEmpty());
    }else if(i == 0 && j == 9){
        return (cases[i+1][j].isEmpty() || cases[i+1][j-1].isEmpty() || cases[i][j-1].isEmpty());
    }else if(i == 0){
        return (cases[i+1][j].isEmpty() || cases[i+1][j+1].isEmpty() || cases[i+1][j-1].isEmpty() || cases[i][j+1].isEmpty() || cases[i][j-1].isEmpty());
    }else if(i == 9){
        return (cases[i][j+1].isEmpty() || cases[i][j-1].isEmpty() || cases[i-1][j].isEmpty() || cases[i-1][j-1].isEmpty() || cases[i-1][j+1].isEmpty());
    }else if(j == 0){
        return (cases[i+1][j].isEmpty() || cases[i+1][j+1].isEmpty() || cases[i][j+1].isEmpty() || cases[i-1][j].isEmpty() || cases[i-1][j+1].isEmpty());
    }else if(j == 9){
        return (cases[i+1][j].isEmpty() || cases[i+1][j-1].isEmpty() || cases[i][j-1].isEmpty() || cases[i-1][j].isEmpty() || cases[i-1][j-1].isEmpty());
    }else
    return (cases[i+1][j].isEmpty() || cases[i+1][j+1].isEmpty() || cases[i+1][j-1].isEmpty() || cases[i][j+1].isEmpty() || cases[i][j-1].isEmpty() || cases[i-1][j].isEmpty() || cases[i-1][j-1].isEmpty() || cases[i-1][j+1].isEmpty());
}

std::string PlateauStratego::help(bool joueur) {
    std::string res = "";
    Couleur c;
    if(joueur) c = Couleur::BLANC;
    else c = Couleur::NOIR;

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++) {
            if (pieceEstdeplacable(i, j)) {
                if (cases[i][j].getPion().getColor() == c && cases[i][j].getPion().getNom().compare("Drapeau") != 0 &&
                    cases[i][j].getPion().getNom().compare("Bombe") != 0) {
                    if (cases[i][j].getPion().getNom().compare("Eclaireur") == 0) {
                        int h = i + 1;
                        while (h < 10 && cases[h][j].isEmpty()) {
                            h++;
                        }
                        if(h-1 != i) {
                            res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " + std::to_string(j) +
                                   " -> ";
                            res += std::to_string(h - 1) + " " + std::to_string(j) + "\n";
                        }

                        h = i - 1;
                        while (h >= 0 && cases[h][j].isEmpty()) {
                            h--;
                        }
                        if(h+1 != i) {
                            res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " + std::to_string(j) +
                                   " -> ";
                            res += std::to_string(h + 1) + " " + std::to_string(j) + "\n";
                        }

                        h = j + 1;
                        while (h < 10 && cases[i][h].isEmpty()) {
                            h++;
                        }
                        if(h-1 != j){
                            res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " + std::to_string(j) +
                                   " -> ";
                            res += std::to_string(i) + " " + std::to_string(h - 1) + "\n";
                        }

                        h = j - 1;
                        while (h >= 0 && cases[i][h].isEmpty()) {
                            h--;
                        }
                        if(h+1 != j) {
                            res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " + std::to_string(j) +
                                   " -> ";
                            res += std::to_string(i) + " " + std::to_string(h + 1) + "\n";
                        }

                    } else {
                        if (i + 1 < 10 && j + 1 < 10 && i - 1 >= 0 && j - 1 >= 0) {
                            if (cases[i - 1][j].isEmpty()) {
                                res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " +
                                       std::to_string(j) + " -> ";
                                res += std::to_string(i - 1) + " " + std::to_string(j) + "\n";

                            }
                            if (cases[i + 1][j].isEmpty()) {
                                res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " +
                                       std::to_string(j) + " -> ";
                                res += std::to_string(i + 1) + " " + std::to_string(j) + "\n";

                            }
                            if (cases[i][j - 1].isEmpty()) {
                                res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " +
                                       std::to_string(j) + " -> ";
                                res += std::to_string(i) + " " + std::to_string(j - 1) + "\n";

                            }
                            if (cases[i][j + 1].isEmpty()) {
                                res += cases[i][j].getPion().getNom() + " " + std::to_string(i) + " " +
                                       std::to_string(j) + " -> ";
                                res += std::to_string(i) + " " + std::to_string(j + 1) + "\n";
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

const void PlateauStratego::lectureFichierTest() {
    std::string delimiter = " ";
    std::string nom = "";
    std::string path = "";
    std::string piece = "";
    int i = 0;
    int j = 0;
    bool joueur = true;
    nom = "joueur" + std::to_string(1)+ ".txt";
    path = "../joueur/" + nom;

    std::cout << path << std::endl;
    std::ifstream infile(path);
    std::string line = "";
    while(std::getline(infile, line)){
        piece = line.substr(0, line.find(delimiter));
        i = std::stoi(line.substr(piece.length()+1, 1));
        j = std::stoi(line.substr(piece.length()+3, 1));
        if(joueur) cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::BLANC));
        else cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::NOIR));
    }

    i = 0;
    j = 0;
    joueur = false;
    nom = "ordi" + std::to_string(1) + ".txt";
    path = "../ordi/" + nom;

    std::cout << path << std::endl;
    std::ifstream infile2(path);
    line = "";
    while(std::getline(infile2, line)){
        piece = line.substr(0, line.find(delimiter));
        i = std::stoi(line.substr(piece.length()+1, 1));
        j = std::stoi(line.substr(piece.length()+3, 1));
        if(joueur) cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::BLANC));
        else cases[i][j].setPion(Pion(piece, std::get<1>(img[renvoiePionsNbr(piece)]), Couleur::NOIR));
    }





std::string file = "../stratego/test1.txt";
    std::ifstream infile3(file);
    line = "";
    delimiter = " ";
    int i_src = -1;
    int j_src = -1;
    int i_dst = -1;
    int j_dst = -1;
    std::cout << *(this) << std::endl;
    joueur = true;
    while(std::getline(infile3, line)){
        cacherPieceJoueur(joueur);
        i_src = std::stoi(line.substr(0, line.find(delimiter)));
        j_src = std::stoi(line.substr(std::to_string(i_src).length()+1, 1));
        i_dst = std::stoi(line.substr(std::to_string(j_src).length()+3, 1));
        j_dst = std::stoi(line.substr(std::to_string(i_dst).length()+5, 1));
        if(cases[i_src][j_src].getPion().getNom() == "Eclaireur") mouvement_eclaireur(i_src,j_src,i_dst,j_dst,joueur,false);
        else mouvement_autre(i_src,j_src,i_dst,j_dst,joueur,false);
        joueur = !joueur;

        std::cout << i_src << " " << j_src << " " << i_dst << " " << j_dst <<std::endl;
        //TODO lancer mouvement
        usleep(1);//5000000);
        std::cout << *(this) << std::endl;

    }
}