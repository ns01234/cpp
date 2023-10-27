#include <iostream>
#include "piece.h"
#include <string>
#ifndef KNIGHT_H
#define KNIGHT_H
using namespace std;

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

        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';

        if(table[a][b]->color == "white"){
    
            if((a+2 < 8 && b+1 < 8) && (table[a+2][b+1]->isEmpty() || (table[a+2][b+1]->getType() == "k" && table[a+2][b+1]->color == "black"))){
                table[a+2][b+1]->dangerw = true;
            }

            if((a+1 < 8 && b+2 < 8) && (table[a+1][b+2]->isEmpty() || (table[a+1][b+2]->getType() == "k" && table[a+1][b+2]->color == "black"))){
                table[a+1][b+2]->dangerw = true;
            }

            if((a-1 >= 0 && b+2 < 8) && (table[a-1][b+2]->isEmpty() || (table[a-1][b+2]->getType() == "k" && table[a-1][b+2]->color == "black"))){
                table[a-1][b+2]->dangerw = true;
            }

            if((a-2 >= 0 && b+1 < 8) && (table[a-2][b+1]->isEmpty() || (table[a-2][b+1]->getType() == "k" && table[a-2][b+1]->color == "black"))){
                table[a-2][b+1]->dangerw = true;
            }
            if((a-2 >= 0 && b-1 >= 0) && (table[a-2][b-1]->isEmpty() || (table[a-2][b-1]->getType() == "k" && table[a-2][b-1]->color == "black"))){
                table[a-2][b-1]->dangerw = true;
            }

            if((a-1 >= 0 && b-2 >= 0) && (table[a-1][b-2]->isEmpty() || (table[a-1][b-2]->getType() == "k" && table[a-1][b-2]->color == "black"))){
                table[a-1][b-2]->dangerw = true;
            }

            if((a+1 < 8 && b-2 >= 0) && (table[a+1][b-2]->isEmpty() || (table[a+1][b-2]->getType() == "k" && table[a+1][b-2]->color == "black"))){
                table[a+1][b-2]->dangerw = true;
            }

            if((a+2 < 8 && b-1 >= 0) && (table[a+2][b-1]->isEmpty() || (table[a+2][b-1]->getType() == "k" && table[a+2][b-1]->color == "black"))){
                table[a+2][b-1]->dangerw = true;
            }
        }

        if(table[a][b]->color == "black"){

            if((a+2 < 8 && b+1 < 8) && (table[a+2][b+1]->isEmpty() || (table[a+2][b+1]->getType() == "k" && table[a+2][b+1]->color == "white"))){
                table[a+2][b+1]->dangerb = true;
            }

            if((a+1 < 8 && b+2 < 8) && (table[a+1][b+2]->isEmpty() || (table[a+1][b+2]->getType() == "k" && table[a+1][b+2]->color == "white"))){
                table[a+1][b+2]->dangerb = true;
            }

            if((a-1 >= 0 && b+2 < 8) && (table[a-1][b+2]->isEmpty() || (table[a-1][b+2]->getType() == "k" && table[a-1][b+2]->color == "white"))){
                table[a-1][b+2]->dangerb = true;
            }

            if((a-2 >= 0 && b+1 < 8) && (table[a-2][b+1]->isEmpty() || (table[a-2][b+1]->getType() == "k" && table[a-2][b+1]->color == "white"))){
                table[a-2][b+1]->dangerb = true;
            }
            if((a-2 >= 0 && b-1 >= 0) && (table[a-2][b-1]->isEmpty() || (table[a-2][b-1]->getType() == "k" && table[a-2][b-1]->color == "white"))){
                table[a-2][b-1]->dangerb = true;
            }

            if((a-1 >= 0 && b-2 >= 0) && (table[a-1][b-2]->isEmpty() || (table[a-1][b-2]->getType() == "k" && table[a-1][b-2]->color == "white"))){
                table[a-1][b-2]->dangerb = true;
            }

            if((a+1 < 8 && b-2 >= 0) && (table[a+1][b-2]->isEmpty() || (table[a+1][b-2]->getType() == "k" && table[a+1][b-2]->color == "white"))){
                table[a+1][b-2]->dangerb = true;
            }

            if((a+2 < 8 && b-1 >= 0) && (table[a+2][b-1]->isEmpty() || (table[a+2][b-1]->getType() == "k" && table[a+2][b-1]->color == "white"))){
                table[a+2][b-1]->dangerb = true;
            }            
        }       
    }
    vector<string> view(Piece* table[8][8])override{

        vector<string> views;
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        char coor[3];
        int rel_coor[8][2] = {{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2}};

        for(int i = 0; i < 8; i++){
            int new_row = a + rel_coor[i][0];
            int new_col = b + rel_coor[i][1];
            if(new_row < 8 && new_row >= 0 && new_col < 8 && new_col >= 0){
                if(table[new_row][new_col]->isEmpty() || (table[a][b]->color != table[new_row][new_col]->color)){

                    coor[1] = static_cast<char>(new_row + '1');
                    coor[0] = static_cast<char>(new_col + 'a');
                    coor[2] = '\0';
                    views.push_back(coor);
                }
            }
        }
        return views;
    }
};

#endif
