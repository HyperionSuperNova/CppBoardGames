#ifndef CPLUSPROJ_PION_H
#define CPLUSPROJ_PION_H



#include <iostream>
#include <boost/serialization/access.hpp>

enum class Couleur {BLANC, NOIR};

inline std::ostream &operator<<(std::ostream &os, Couleur c){
    switch(c){
        case Couleur::BLANC : os << "B"; break;
        case Couleur::NOIR : os << "N"; break;
    }
    return os;
}
class Pion{
private:
    std::string name;
    std::string img;
    Couleur color;

    public:

    Pion();

    Pion(const std::string &name);
    Pion(const std::string &name, const std::string &img, Couleur c);
    void setNom(std::string);
    void setImg(std::string);
    Couleur getColor();
    std::string getNom();
    std::string getImg();

    friend std::ostream &operator<<(std::ostream &os, const Pion &pion);
};

#endif //CPLUSPROJ_PION_H
