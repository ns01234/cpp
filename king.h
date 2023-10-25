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
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';

        int relativePositions[8][2] = {
        {1, 1}, {1, 0}, {1, -1},
        {0, 1},          {0, -1},
        {-1, 1}, {-1, 0}, {-1, -1}
        };

    for (int i = 0; i < 8; i++) {
        int newRow = a + relativePositions[i][0];
        int newCol = b + relativePositions[i][1];

        if (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {

            if(table[a][b]->color == "white" && (table[newRow][newCol]->isEmpty() || (table[newRow][newCol]->color == "black"))){
                table[newRow][newCol]->dangerw = true;

            }else if(table[a][b]->color == "black" && (table[newRow][newCol]->isEmpty() || (table[newRow][newCol]->color == "white"))){
                table[newRow][newCol]->dangerb = true;
            }
        }
    }
        // if(table[a][b]->color == "white"){
        //     for(int i = 0; i < 3; i++){
        //         for(int j = 0; j < 3; j++){
        //             if((0 <= a+1-i < 8) && (0 <= b+1-j < 8)){
        //                 if(table[a+1-i][b+1-j]->isEmpty() || table[a+1-i][b+1-j]->color == "black"){
        //                     table[a+1-i][b+1-j]->dangerw = true;
        //                 }
        //             }
        //         }
        //     }     
        // }
        // if(table[a][b]->color == "black"){
        //     for(int i = 0; i < 3; i++){
        //         for(int j = 0; j < 3; j++){

        //             if((0 <= a+1-i < 8) && (0 <= b+1-j < 8)){
        //                 if(table[a+1-i][b+1-j]->isEmpty() || table[a+1-i][b+1-j]->color == "white"){
        //                     table[a+1-i][b+1-j]->dangerb = true;
        //                 }
        //             }
        //         }
        //     }     
        // }

    }
    vector<string> view(Piece* t[8][8])override{

        vector<string> views;
        char a = this->coordinate[1] - '1';
        char b = this->coordinate[0] - 'a';
        int x = 1;
        char coor[3];
        int rel_coor[8][2] = {{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1}};

        for(int i = 0; i < 8; i++){
            int r = a + rel_coor[i][0];
            int c = b + rel_coor[i][1];
            if(r < 8 && r >= 0 && c < 8 && c >= 0){
                if((t[a][b]->color != t[r][c]->color) 
                && ((t[a][b]->color == "white" && !t[r][c]->dangerb) 
                || (t[a][b]->color == "black" && !t[r][c]->dangerw))){

                    coor[1] = static_cast<char>(r + '1');
                    coor[0] = static_cast<char>(c + 'a');
                    coor[2] = '\0';
                    views.push_back(coor);
                }
            }
        }
        return views;
    }

};

#endif