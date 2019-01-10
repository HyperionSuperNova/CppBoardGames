#include "PlateauDamierInternational.h"

PlateauDamierInternational::PlateauDamierInternational() : PlateauDamier(10) {
    setDimension(10);
}



const bool PlateauDamierInternational::kingMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    int lambda = 1;
        if (i_dst < i_src) {
            i_dst++;
            if (j_dst < j_src) {
                j_dst++;

                while ((i_dst + lambda) != i_src && j_dst + lambda != j_src) {
                    if (!getCase((i_dst + lambda)*getDimension()+j_dst + lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst--;
                if(getCase((i_dst-1)*getDimension()+j_dst-1).isEmpty()){
                    i_dst--;
                    setCase(i_dst*getDimension()+j_dst, new Pion());
                    setCase((i_dst-1)*getDimension()+j_dst-1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, new Pion());
                    if(c == Couleur::BLANC) scoreJ1++;
                    else scoreJ2++;
                    return true;
                }else return false;

            } else if (j_dst > j_src) {
                j_dst--;
                while ((i_dst + lambda) != i_src && (j_dst - lambda) != j_src) {
                    if (!getCase((i_dst + lambda)*getDimension()+j_dst - lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst++;
                if(getCase((i_dst-1)*getDimension()+j_dst+1).isEmpty()){
                    i_dst--;
                    setCase(i_dst*getDimension()+j_dst, new Pion());
                    setCase((i_dst-1)*getDimension()+j_dst+1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, new Pion());
                    if(c == Couleur::BLANC) scoreJ1++;
                    else scoreJ2++;
                    return true;
                }else return false;
            }
            i_dst--;
        } else if (i_dst > i_src) {
            i_dst--;
            if (j_dst < j_src) {
                j_dst++;
                while ((i_dst - lambda) != i_src && j_dst + lambda != j_src) {
                    if (!getCase((i_dst - lambda)*getDimension()+j_dst + lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst--;
                if(getCase((i_dst+1)*getDimension()+j_dst-1).isEmpty()){
                    i_dst++;
                    setCase(i_dst*getDimension()+j_dst, new Pion());
                    setCase((i_dst+1)*getDimension()+j_dst-1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, new Pion());
                    if(c == Couleur::BLANC) scoreJ1++;
                    else scoreJ2++;
                    return true;
                }else return false;

            } else if (j_dst > j_src) {
                j_dst--;
                while ((i_dst - lambda) != i_src && (j_dst - lambda) != j_src) {
                    if (!getCase((i_dst - lambda)*getDimension()+j_dst - lambda).isEmpty()) return false;
                    lambda++;
                }
                j_dst++;
                if(getCase((i_dst+1)*getDimension()+j_dst+1).isEmpty()){
                    i_dst++;
                    setCase(i_dst*getDimension()+j_dst, new Pion());
                    setCase((i_dst+1)*getDimension()+j_dst+1, getCase(i_src*getDimension()+j_src).getPion());
                    setCase(i_src*getDimension()+j_src, new Pion());
                    if(c == Couleur::BLANC) scoreJ1++;
                    else scoreJ2++;
                    return true;
                }else return false;
            }
            i_dst++;
        }
        return false;
}












