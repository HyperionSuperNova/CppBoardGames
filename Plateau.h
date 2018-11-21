//
// Created by merat on 15/11/18.
//

#ifndef CPLUSPROJ_PLATEAU_H
#define CPLUSPROJ_PLATEAU_H


#include "Case.h"

class Plateau {
protected:
    const int dimension;
    Case ** cases;
public:
    Plateau(int dimension);

    virtual ~Plateau();

    virtual Case getCase(int, int);
    virtual void setCase(int, int, Pion);

    friend std::ostream &operator<<(std::ostream &, const Plateau &);
};



#endif //CPLUSPROJ_PLATEAU_H
