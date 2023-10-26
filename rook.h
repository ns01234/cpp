#include "piece.h"
#include <string>
#include <vector>
#ifndef ROOK_H
#define ROOK_H
using namespace std;

class Rook : public Piece {
public:
    bool is_played = false;
    Rook(string n, string color){
        this->coordinate = n;
        this->name = "R";
        this->color = color;
    }
    string getType()override{
        return "r";
    }
    bool isEmpty()override{
        return false;
    }
    vector<string> view(Piece* table[8][8])override{
        vector<string> views;
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        char coor[3];
    
        while(a+x < 8 && (table[a+x][b]->isEmpty() || (table[a][b]->color != table[a+x][b]->color))){    // up
            
            coor[1] = static_cast<char>(a + x + '1');
            coor[0] = static_cast<char>(b + 'a');
            coor[2] = '\0';
            views.push_back(coor);
            if(!table[a+x][b]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while(a-x >= 0 && (table[a-x][b]->isEmpty() || (table[a][b]->color != table[a-x][b]->color))){    // down

            coor[1] = static_cast<char>(a - x + '1');
            coor[0] = static_cast<char>(b + 'a');
            coor[2] = '\0';
            views.push_back(coor);
            if(!table[a-x][b]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while(b+x < 8 && (table[a][b+x]->isEmpty() || (table[a][b]->color != table[a][b+x]->color))){    // right

            coor[1] = static_cast<char>(a  + '1');
            coor[0] = static_cast<char>(b + x + 'a');
            coor[2] = '\0';
            views.push_back(coor);
            if(!table[a][b+x]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while(b-x >= 0 && (table[a][b-x]->isEmpty() || (table[a][b]->color != table[a][b-x]->color))){    // left

            coor[1] = static_cast<char>(a + '1');
            coor[0] = static_cast<char>(b - x + 'a');
            coor[2] = '\0';
            views.push_back(coor);
            if(!table[a][b-x]->isEmpty()){
                break;
            }
            x += 1;
        }
        return views;
    }
    void dangerZone(Piece* table[8][8])override{

        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        
        if(table[a][b]->color == "white"){
    
            while(a+x < 8 && (table[a+x][b]->isEmpty() || (table[a+x][b]->getType() == "k" && table[a+x][b]->color == "black"))){    // up
                table[a+x][b]->dangerw = true;
                x += 1;
            }
            x = 1;
            while(a-x >= 0 && (table[a-x][b]->isEmpty() || (table[a-x][b]->getType() == "k" && table[a-x][b]->color == "black"))){    // down
                table[a-x][b]->dangerw = true;
                x += 1;
            }
            x = 1;
            while(b+x < 8 && (table[a][b+x]->isEmpty() || (table[a][b+x]->getType() == "k" && table[a][b+x]->color == "black"))){    // right
                table[a][b+x]->dangerw = true;
                x += 1;
            }
            x = 1;
            while(b-x >= 0 && (table[a][b-x]->isEmpty() || (table[a][b-x]->getType() == "k" && table[a][b-x]->color == "black"))){    // left
                table[a][b-x]->dangerw = true;
                x += 1;
            }
        }

        if(table[a][b]->color == "black"){
    
            while(a+x < 8 && (table[a+x][b]->isEmpty() || (table[a+x][b]->getType() == "k" && table[a+x][b]->color == "white"))){    // up
                table[a+x][b]->dangerb = true;
                x += 1;
            }
            x = 1;
            while(a-x >= 0 && (table[a-x][b]->isEmpty() || (table[a-x][b]->getType() == "k" && table[a-x][b]->color == "white"))){    // down
                table[a-x][b]->dangerb = true;
                x += 1;
            }
            x = 1;
            while(b+x < 8 && (table[a][b+x]->isEmpty() || (table[a][b+x]->getType() == "k" && table[a][b+x]->color == "white"))){    // right
                table[a][b+x]->dangerb = true;
                x += 1;
            }
            x = 1;
            while(b-x >= 0 && (table[a][b-x]->isEmpty() || (table[a][b-x]->getType() == "k" && table[a][b-x]->color == "white"))){    // left
                table[a][b-x]->dangerb = true;
                x += 1;
            }
        }
    }
};

#endif