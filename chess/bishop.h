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
     vector<string> view(Piece* table[8][8])override{

        vector<string> views;
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        char chessCoordinate[3];

        while((a+x < 8 && b+x < 8) && (table[a+x][b+x]->isEmpty() || (table[a][b]->color != table[a+x][b+x]->color))){    // up + right
            
            chessCoordinate[1] = static_cast<char>(a + x + '1');
            chessCoordinate[0] = static_cast<char>(b + x + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a+x][b+x]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while((a+x < 8 && b-x >= 0) && (table[a+x][b-x]->isEmpty() || (table[a][b]->color != table[a+x][b-x]->color))){    // up + left

            chessCoordinate[1] = static_cast<char>(a + x + '1');
            chessCoordinate[0] = static_cast<char>(b - x + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a+x][b-x]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while((a-x >= 0 && b+x < 8) && (table[a-x][b+x]->isEmpty() || (table[a][b]->color != table[a-x][b+x]->color))){    // down + right

            chessCoordinate[1] = static_cast<char>(a - x + '1');
            chessCoordinate[0] = static_cast<char>(b + x + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a-x][b+x]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while((a-x >= 0 && b-x >= 0) && (table[a-x][b-x]->isEmpty() || (table[a][b]->color != table[a-x][b-x]->color))){    // down + left

            chessCoordinate[1] = static_cast<char>(a - x + '1');
            chessCoordinate[0] = static_cast<char>(b - x + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a-x][b-x]->isEmpty()){
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
    
            while((a+x < 8 && b+x < 8) && (table[a+x][b+x]->isEmpty() || (table[a+x][b+x]->getType() == "k" && table[a+x][b+x]->color == "black"))){    // up + right
                table[a+x][b+x]->dangerw = true;
                x += 1;
            }
            x = 1;
            while((a+x < 8 && b-x >= 0) && (table[a+x][b-x]->isEmpty() || (table[a+x][b-x]->getType() == "k" && table[a+x][b-x]->color == "black"))){    // up + left
                table[a+x][b-x]->dangerw = true;
                x += 1;
            }
            x = 1;
            while((a-x >= 0 && b+x < 8) && (table[a-x][b+x]->isEmpty() || (table[a-x][b+x]->getType() == "k" && table[a-x][b+x]->color == "black"))){    // down + right 
                table[a-x][b+x]->dangerw = true;
                x += 1;
            }
            x = 1;
            while((a-x >= 0 & b-x >= 0) && (table[a-x][b-x]->isEmpty() || (table[a-x][b-x]->getType() == "k" && table[a-x][b-x]->color == "black"))){    // down + left
                table[a-x][b-x]->dangerw = true;
                x += 1;
            }
        }

        if(table[a][b]->color == "black"){
    
            while((a+x < 8 && b+x < 8) && (table[a+x][b+x]->isEmpty() || (table[a+x][b+x]->getType() == "k" && table[a+x][b+x]->color == "white"))){    // up + right
                table[a+x][b+x]->dangerb = true;
                x += 1;
            }
            x = 1;
            while((a+x < 8 && b-x >= 0) && (table[a+x][b-x]->isEmpty() || (table[a+x][b-x]->getType() == "k" && table[a+x][b-x]->color == "white"))){    // up + left
                table[a+x][b-x]->dangerb = true;
                x += 1;
            }
            x = 1;
            while((a-x >= 0 && b+x < 8) && (table[a-x][b+x]->isEmpty() || (table[a-x][b+x]->getType() == "k" && table[a-x][b+x]->color == "white"))){    // down + right 
                table[a-x][b+x]->dangerb = true;
                x += 1;
            }
            x = 1;
            while((a-x >= 0 & b-x >= 0) && (table[a-x][b-x]->isEmpty() || (table[a-x][b-x]->getType() == "k" && table[a-x][b-x]->color == "white"))){    // down + left
                table[a-x][b-x]->dangerb = true;
                x += 1;
            }
        }
    }
};

#endif
