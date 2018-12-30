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
    virtual const void move(int i_src, int j_src, int i_dst, int j_dst) const;
    friend std::ostream &operator<<(std::ostream &, const Plateau &);
};



#endif //CPLUSPROJ_PLATEAU_H
