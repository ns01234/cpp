#include <iostream>
#include <string>
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "empty.h"
#include <iomanip>

using namespace std;

bool checkMove(Piece* table[8][8], string src, string dest){
    char a = src[1] - '1';
    char b = src[0] - 'a';
    char i = dest[1] - '1';
    char j = dest[0] - 'a';
    bool empty = true;

    if((table[a][b]->getType() == "k") && (table[a][b]->color == "white") && (table[i][j]->dangerb)){
        cout << "you can not play your king here" << '\n';
        return false;
    }
    
    if((table[a][b]->getType() == "k") && (table[a][b]->color == "black") && (table[i][j]->dangerw)){
        cout << "you can not play your king here" << '\n';
        return false;
    }

    if((table[a][b]->getType() == "p") && (table[a][b]->color == "white")){    // white pawn
        if((i-a == 2) && (table[a+1][b]->isEmpty() && table[a+2][b]->isEmpty())){
            return true;
        }else if(((i-a == 1) && j == b) && (table[a+1][b]->isEmpty())){
            return true;
        }else if(((i-a == 1) && abs(j-b) == 1) && (table[i][j]->color == "black")){
            return true;
        }
    };
    
    if((table[a][b]->getType() == "p") && (table[a][b]->color == "black")){    // black pawn
        if((a-i == 2) && (table[a-1][b]->isEmpty() && table[a-2][b]->isEmpty())){
            return true;
        }else if(((a-i == 1) && j == b) && (table[a-1][b]->isEmpty())){
            return true;
        }else if(((a-i == 1) && abs(j-b) == 1) && (table[i][j]->color == "white")){
            return true;
        }
    };

    if(table[a][b]->getType() == "r"){    // rook
        if((i > a) && j-b == 0){    // up
            for(int x = a+1; x <= i; x++){
                if(((x != i) && !table[x][b]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && j-b == 0){    // down
            for(int x = a-1; x >= i; x--){
                if(((x != i) && !table[x][b]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((j > b) && a-i == 0){    // right
            for(int x = b+1; x <= j; x++){
                if(((x != j) && !table[a][x]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((b > j) && a-i == 0){    // left
            for(int x = b-1; x >= j; x--){
                if(((x != j) && !table[a][x]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
    }
    if(table[a][b]->getType() == "b"){    // bishop

        if(abs(i-a) != abs(j-b)){
            return false;
        }
        if((i > a) && (j > b)){    // up + right
            for(int x = a+1, y = b+1; x <= i; x++, y++){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((i > a) && (b > j)){    // up + left
            for(int x = a+1, y = b-1; x <= i; x++, y--){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (j > b)){    // down + right
            for(int x = a-1, y = b+1; x >= i; x--, y++){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (b > j)){    // down + left
            for(int x = a-1, y = b-1; x >= i; x--, y--){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }

    }
    if(table[a][b]->getType() == "n"){    // knight
        if(((table[i][j]->isEmpty()) || table[a][b]->color != table[i][j]->color) && ((abs(i-a) == 2 && abs(j-b) == 1) || (abs(i-a) == 1 && abs(j-b) == 2))){
            return true;
        }
        else{
            return false;
        }
    }
    if(table[a][b]->getType() == "q"){    // queen
        if((abs(i-a) != abs(j-b)) && !((abs(i-a) == 0) || abs(j-b) == 0)){
            return false;
        }
        if((i > a) && j-b == 0){    // up
            for(int x = a+1; x <= i; x++){
                if(((x != i) && !table[x][b]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && j-b == 0){    // down
            for(int x = a-1; x >= i; x--){
                if(((x != i) && !table[x][b]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((j > b) && a-i == 0){    // right
            for(int x = b+1; x <= j; x++){
                if(((x != j) && !table[a][x]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((b > j) && a-i == 0){    // left
            for(int x = b-1; x >= j; x--){
                if(((x != j) && !table[a][x]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((i > a) && (j > b)){    // up + right
            for(int x = a+1, y = b+1; x <= i; x++, y++){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((i > a) && (b > j)){    // up + left
            for(int x = a+1, y = b-1; x <= i; x++, y--){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (j > b)){    // down + right
            for(int x = a-1, y = b+1; x >= i; x--, y++){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (b > j)){    // down + left
            for(int x = a-1, y = b-1; x >= i; x--, y--){
                if(((x != i) && !table[x][y]->isEmpty()) || ((table[i][j]->color == table[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
    }
    if(table[a][b]->getType() == "k"){    // king
        if((abs(a-i) < 2) && (abs(j-b) < 2)){
            if(table[i][j]->color == table[a][b]->color){
                return false;
            }
            else{
                return true;
            }
        }
    }
    return false;
}

void resetZone(Piece* table[8][8]){
    for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                if(table[x][y]->isEmpty() || table[x][y]->getType() == "k"){
                    table[x][y]->dangerw = false;
                    table[x][y]->dangerb = false;
                }
            }
        }
}

void printTable(Piece* table[8][8]){
    cout << '\n';
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            cout << setw(1) << table[i][j]->name << " ";
        }
        cout << '\n';
    } 
    cout << '\n';
}

void zoneCreater(Piece* table[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(!table[i][j]->isEmpty()){
                table[i][j]->dangerZone(table);
            }
        }
    }
}

void move(Piece* table[8][8], string src, string dest, Piece* wkingptr, Piece* bkingptr){

    char a = src[1] - '1';
    char b = src[0] - 'a';
    char i = dest[1] - '1';
    char j = dest[0] - 'a';
    
    table[i][j] = table[a][b];
    table[a][b] = new Empty();
    table[i][j]->coordinate[0] = dest[0];
    table[i][j]->coordinate[1] = dest[1];
    
    char k = wkingptr->coordinate[1] - '1';
    char l = wkingptr->coordinate[0] - 'a';
    char m = bkingptr->coordinate[1] - '1';
    char n = bkingptr->coordinate[0] - 'a';

    resetZone(table);
    zoneCreater(table);

    if(table[i][j]->color == "white" && table[k][l]->dangerb){
        table[a][b] = table[i][j];
        table[i][j] = new Empty();
        table[a][b]->coordinate[0] = src[0];
        table[a][b]->coordinate[1] = src[1];
        cout << "which piece: ";
        cin >> src;
        cout << "to where: ";
        cin >> dest;
        if(checkMove(table, src, dest)){
            move(table, src, dest, wkingptr, bkingptr);
        }
    }

    if(table[i][j]->color == "black" && table[m][n]->dangerw){
        table[a][b] = table[i][j];
        table[i][j] = new Empty();
        table[a][b]->coordinate[0] = src[0];
        table[a][b]->coordinate[1] = src[1];
        cout << "which piece: ";
        cin >> src;
        cout << "to where: ";
        cin >> dest;
        if(checkMove(table, src, dest)){
            move(table, src, dest, wkingptr, bkingptr);
        }
    }
}

int main() {

    Piece* table[8][8];
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            table[i][j] = new Empty();
        }
    }
    table[0][0] = new Rook("a1","white");
    table[0][1] = new Knight("b1","white");
    table[0][2] = new Bishop("c1","white");
    table[0][3] = new Queen("d1","white");
    table[0][4] = new King("e1","white");
    table[0][5] = new Bishop("f1","white");
    table[0][6] = new Knight("g1","white");
    table[0][7] = new Rook("h1","white");

    table[1][0] = new Pawn("a2","white");
    table[1][1] = new Pawn("b2","white");
    table[1][2] = new Pawn("c2","white");
    table[1][3] = new Pawn("d2","white");
    table[1][4] = new Pawn("e2","white");
    table[1][5] = new Pawn("f2","white");
    table[1][6] = new Pawn("g2","white");
    table[1][7] = new Pawn("h2","white");
    
    table[7][0] = new Rook("a8","black");
    table[7][1] = new Knight("b8","black");
    table[7][2] = new Bishop("c8","black");
    table[7][3] = new Queen("d8","black");
    table[7][4] = new King("e8","black");
    table[7][5] = new Bishop("f8","black");
    table[7][6] = new Knight("g8","black");
    table[7][7] = new Rook("h8","black");

    table[6][0] = new Pawn("a7","black");
    table[6][1] = new Pawn("b7","black");
    table[6][2] = new Pawn("c7","black");
    table[6][3] = new Pawn("d7","black");
    table[6][4] = new Pawn("e7","black");
    table[6][5] = new Pawn("f7","black");
    table[6][6] = new Pawn("g7","black");
    table[6][7] = new Pawn("h7","black");

    Piece* wkingptr = table[0][4];
    Piece* bkingptr = table[7][4];
    int turn = 0;
    string src;
    string dest;
    
    while(src != "x"){

        string side[] = {"white","black"};
        
        cout << "which piece: ";
        cin >> src;

        char a = src[1] - '1';
        char b = src[0] - 'a';

        if(table[a][b]->color == side[(turn+ 1) % 2]){
            cout << "its not your turn" << '\n';
            continue;
        }

        if(table[a][b]->isEmpty()){
            cout << "there is no piece" << '\n';
            continue;
        }  
        
        cout << "to where: ";
        cin >> dest;

        char i = dest[1] - '1';
        char j = dest[0] - 'a';

        if (checkMove(table, src, dest)){ 
            move(table, src, dest, wkingptr, bkingptr);
            resetZone(table);
            zoneCreater(table);
        }
        else{
            cout << "you can not play this move" << '\n';
            continue;
        }
        turn += 1;
        printTable(table);
        
    }

    return 0;
}