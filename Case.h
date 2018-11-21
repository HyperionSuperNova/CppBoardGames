//
// Created by merat on 15/11/18.
//

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
    void setPion(Pion);

    bool isEmpty();
    friend std:: ostream&operator<<(std:: ostream&, const Case &);

};


#endif //CPLUSPROJ_CASE_H
