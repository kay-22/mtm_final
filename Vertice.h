#ifndef VERTICE_H
#define VERTICE_H

#include <string>

class Vertice {
private:
    std::string name;
    bool isValidName(std::string name);

public:
    Vertice() : name(std::string("")) {}
    Vertice(std::string name);
    //Vertice(const Vertice&) = default ?
    //operator=() = default ?
    bool operator<(const Vertice&);
    //~Vertice() = default ?
};

#endif 