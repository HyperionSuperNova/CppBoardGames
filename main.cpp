#include <iostream>
#include "Plateau.h"
#include "PlateauDamier.h"
#include "PlateauStratego.h"
#include "PlateauEchiquier.h"
#include "PlateauAnglais.h"

int main() {
    //PlateauEchiquier e;
    //e.launchEchiquier(true);
    //PlateauStratego p;
    //p.launchStratego(true);
    PlateauAnglais p(8);
    p.launcher();
}