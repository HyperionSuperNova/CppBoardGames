#ifndef CPLUSPROJ_PLATEAU_H
#define CPLUSPROJ_PLATEAU_H


#include "Case.h"

class Plateau {
private:
    int dimension;
    Case * cases;
public:
    Plateau(int dimension);

    virtual ~Plateau();

    int getDimension() const;
    void setDimension(int);
    virtual Case getCase(int) const;
    virtual void setCase(int, Pion*);
    virtual const void move(int i_src, int j_src, int i_dst, int j_dst);
    void setCases(int, Pion&);
    friend std::ostream &operator<<(std::ostream &, const Plateau &);
};



#endif //CPLUSPROJ_PLATEAU_H
