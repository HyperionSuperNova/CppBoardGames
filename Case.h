#ifndef CPLUSPROJ_CASE_H
#define CPLUSPROJ_CASE_H


#include <boost/serialization/access.hpp>
#include "Pion.h"

class Case {
private:
    int x;
    int y;
    Pion pion;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & x;
        ar & y;
        ar & pion;
    }
public:
    Case();
    Case(int ii, int jj);
    Pion getPion();
    int getX();
    int getY();
    void setPionImg(std::string);
    void setPionBis(Pion &p);
    void setPion(Pion &);
    bool isEmpty();
    friend std:: ostream&operator<<(std:: ostream&, const Case &);

};


#endif //CPLUSPROJ_CASE_H
