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

        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';

        if(table[a][b]->color == "white" && a < 7 && b < 7){
            if(table[a+1][b+1]->isEmpty() || (table[a+1][b+1]->getType() == "k" && table[a+1][b+1]->color == "black")){
                table[a+1][b+1]->dangerw = true;
            }
            if(table[a+1][b-1]->isEmpty() || (table[a+1][b-1]->getType() == "k" && table[a+1][b-1]->color == "black")){
                table[a+1][b-1]->dangerw = true;
            }
        }

        if(table[a][b]->color == "black" && a > 0 && b > 0){
            if(table[a-1][b+1]->isEmpty() || (table[a-1][b+1]->getType() == "k" && table[a-1][b+1]->color == "white")){
                table[a-1][b+1]->dangerb = true;
            }
            if(table[a-1][b-1]->isEmpty() || (table[a-1][b-1]->getType() == "k" && table[a-1][b-1]->color == "white")){
                table[a-1][b-1]->dangerb = true;
            }
        }
    }
    vector<string> view(Piece* table[8][8])override{

        vector<string> views;
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        char coor[3];
        int side = 0;
        if(table[a][b]->color == "white"){
            side = 1;
        }else if(table[a][b]->color == "black"){
            side = -1;
        }
    
    if(a+side < 8 && a+side >= 0){
        if(table[a+side][b]->isEmpty() && a + side < 8){
            
            coor[1] = static_cast<char>(a + side + '1');
            coor[0] = static_cast<char>(b + 'a');
            coor[2] = '\0';
            views.push_back(coor);
        }
    }
    if(a+(2*side) < 8 && a+(2*side) >= 0 && a == (3.5 - (2.5 * side))){
        if(table[a+(2*side)][b]->isEmpty() && table[a+side][b]->isEmpty() && a+(2*side) < 8){

            coor[1] = static_cast<char>(a + (2*side) + '1');
            coor[0] = static_cast<char>(b + 'a');
            coor[2] = '\0';
            views.push_back(coor);
        }
    }
    if(a+side < 8 && a+side >= 0 && b+1 < 8){
        if(!table[a+side][b+1]->isEmpty() && table[a+side][b-1]->color != this->color){
            
            coor[1] = static_cast<char>(a + side + '1');
            coor[0] = static_cast<char>(b + 1 + 'a');
            coor[2] = '\0';
            views.push_back(coor);
        }
    }
    if(a+side < 8 && a+side >= 0 && b-1 >= 0){
        if(!table[a+side][b-1]->isEmpty() && table[a+side][b-1]->color != this->color){
            
            coor[1] = static_cast<char>(a + side + '1');
            coor[0] = static_cast<char>(b - 1 + 'a');
            coor[2] = '\0';
            views.push_back(coor);
        }
    }
        return views;
    }   
    
};
#endif
