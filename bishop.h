#include "piece.h"
#include <string>
#ifndef BISHOP_H
#define BISHOP_H

class Bishop : public Piece {
public:
    Bishop(std::string n, std::string color){
        this->coordinate = n;
        this->name = "B";
        this->color = color;
    }
    std::string getType()override{
        return "b";
    }
    bool isEmpty()override{
        return false;
    }
    void dangerZone(Piece* table[8][8])override{

    }
};

#endif