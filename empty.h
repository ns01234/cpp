#include "piece.h"
#include <string>
#ifndef EMPTY_H
#define EMPTY_H

class Empty : public Piece {
public:

    std::string getType(){
        return "empty";
    }
    bool isEmpty()override{
        return true;
    }
    void dangerZone(Piece* table[8][8])override{

    }
};
#endif