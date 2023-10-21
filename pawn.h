#include "piece.h"
#include <string>
#ifndef PAWN_H
#define PAWN_H

class Pawn : public Piece {
public:
    Pawn(std::string n, std:: string color){
        this->coordinate = n;
        this->name = "p";
        this->color = color;
    }
    std::string getType()override{
        return "p";
    }
    bool isEmpty()override{
        return false;
    }
    void dangerZone(Piece* table[8][8])override{

    }
};
#endif