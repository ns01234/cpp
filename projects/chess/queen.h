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
    vector<string> view(Piece* table[8][8])override{

        vector<string> views;
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        char chessCoordinate[3];
    
        while(a+x < 8 && (table[a+x][b]->isEmpty() || (table[a][b]->color != table[a+x][b]->color))){    // up
            
            chessCoordinate[1] = static_cast<char>(a + x + '1');
            chessCoordinate[0] = static_cast<char>(b + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a+x][b]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while(a-x >= 0 && (table[a-x][b]->isEmpty() || (table[a][b]->color != table[a-x][b]->color))){    // down

            chessCoordinate[1] = static_cast<char>(a - x + '1');
            chessCoordinate[0] = static_cast<char>(b + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a-x][b]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while(b+x < 8 && (table[a][b+x]->isEmpty() || (table[a][b]->color != table[a][b+x]->color))){    // right

            chessCoordinate[1] = static_cast<char>(a  + '1');
            chessCoordinate[0] = static_cast<char>(b + x + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a][b+x]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
        while(b-x >= 0 && (table[a][b-x]->isEmpty() || (table[a][b]->color != table[a][b-x]->color))){    // left

            chessCoordinate[1] = static_cast<char>(a + '1');
            chessCoordinate[0] = static_cast<char>(b - x + 'a');
            chessCoordinate[2] = '\0';
            views.push_back(chessCoordinate);
            if(!table[a][b-x]->isEmpty()){
                break;
            }
            x += 1;
        }
        x = 1;
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
};

#endif
