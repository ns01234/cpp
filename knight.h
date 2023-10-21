#include "piece.h"
#include <string>
#ifndef KNIGHT_H
#define KNIGHT_H

class Knight : public Piece {
public:
    Knight(std::string n, std::string color){
        this->coordinate = n;
        this->name = "N";
        this->color = color;
    }
    std::string getType()override{
        return "n";
    }
    bool isEmpty()override{
        return false;
    }
    void dangerZone(Piece* table[8][8])override{

    }
};

#endif