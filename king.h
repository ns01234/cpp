#include "piece.h"
#include <string>
#ifndef KING_H
#define KING_H

class King : public Piece {
public:
    King(std:: string n, std::string color){
        this->coordinate = n;
        this->name = "K";
        this->color = color;
    }
    std::string getType()override{
        return "k";
    }
    bool isEmpty()override{
        return false;
    }
    void dangerZone(Piece* table[8][8])override{
    }
};

#endif