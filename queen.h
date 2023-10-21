#include "piece.h"
#include <string>
#ifndef QUEEN_H
#define QUEEN_H

class Queen : public Piece {
public:
    Queen(std::string n, std::string color){
        this->coordinate = n;
        this->name = "Q";
        this->color = color;
    }
    std::string getType()override{
        return "q";
    }
    bool isEmpty()override{
        return false;
    }
    void dangerZone(Piece* table[8][8])override{
    }
};

#endif