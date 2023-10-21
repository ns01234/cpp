#include <string>
#include <vector>
#ifndef PIECE_H
#define PIECE_H
using namespace std;

class Piece {
public:
    string coordinate;
    string name;
    string color;
    bool dangerw;
    bool dangerb;
    virtual string getType(){
        return "";
    }
    virtual bool isEmpty(){
        return true;
    }
    virtual void dangerZone(Piece* table[8][8]){

    }
    virtual vector<string> view(Piece* table[8][8]){
        vector<string> a;
        return a;
    }
};

#endif