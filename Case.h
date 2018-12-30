#ifndef CPLUSPROJ_CASE_H
#define CPLUSPROJ_CASE_H


#include "Pion.h"

class Case {
private:
    int x;
    int y;
    Pion pion;
public:
    Case();
    Case(int ii, int jj);
    Pion getPion();
    int getX();
    int getY();
    void setPionImg(std::string);
    void setPionBis(Pion& p);
    void setPion(Pion);
    bool isEmpty();
    friend std:: ostream&operator<<(std:: ostream&, const Case &);

};


#endif //CPLUSPROJ_CASE_H
