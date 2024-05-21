#include <iostream>
#include <string>
#include <iomanip>
#include "piece.h"
#include "pawn.h"
#include "knight.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "empty.h"
#include <cmath>

using namespace std;

bool abs_pin_checker(Piece* [8][8], string, string &, Piece* , Piece* );
bool checkMove(Piece* [8][8], string, string &, Piece* , Piece* );
void resetZone(Piece* [8][8]);
void printboard(Piece* [8][8]);
void zoneCreater(Piece* [8][8]);
bool check_checker(Piece* [8][8], string, Piece* , Piece* , string );
void move(Piece* [8][8], string, string &, Piece* , Piece* );

int main() {

    Piece* board[8][8];
    char empty_coor[3];
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < 8; j++){
            empty_coor[1] = static_cast<char>(i + '1');
            empty_coor[0] = static_cast<char>(j + 'a');
            empty_coor[2] = '\0';
            board[i][j] = new Empty(empty_coor);
        }
    }
    board[0][0] = new Rook("a1","white");
    board[0][1] = new Knight("b1","white");
    board[0][2] = new Bishop("c1","white");
    board[0][3] = new Queen("d1","white");
    board[0][4] = new King("e1","white");
    board[0][5] = new Bishop("f1","white");
    board[0][6] = new Knight("g1","white");
    board[0][7] = new Rook("h1","white");

    board[1][0] = new Pawn("a2","white");
    board[1][1] = new Pawn("b2","white");
    board[1][2] = new Pawn("c2","white");
    board[1][3] = new Pawn("d2","white");
    board[1][4] = new Pawn("e2","white");
    board[1][5] = new Pawn("f2","white");
    board[1][6] = new Pawn("g2","white");
    board[1][7] = new Pawn("h2","white");
    
    board[7][0] = new Rook("a8","black");
    board[7][1] = new Knight("b8","black");
    board[7][2] = new Bishop("c8","black");
    board[7][3] = new Queen("d8","black");
    board[7][4] = new King("e8","black");
    board[7][5] = new Bishop("f8","black");
    board[7][6] = new Knight("g8","black");
    board[7][7] = new Rook("h8","black");

    board[6][0] = new Pawn("a7","black");
    board[6][1] = new Pawn("b7","black");
    board[6][2] = new Pawn("c7","black");
    board[6][3] = new Pawn("d7","black");
    board[6][4] = new Pawn("e7","black");
    board[6][5] = new Pawn("f7","black");
    board[6][6] = new Pawn("g7","black");
    board[6][7] = new Pawn("h7","black");

    Piece* wkingptr = board[0][4];
    Piece* bkingptr = board[7][4];
    int turn = 0;
    string src;
    string dest;

    zoneCreater(board);

    while(src != "x"){

        string side[] = {"white","black"};
        
        cout << "which piece: ";
        cin >> src;

        char a = src[1] - '1';
        char b = src[0] - 'a';

        for ( string str : board[a][b]->view(board)) {
            cout << str << " ";
        }
        cout << '\n';

        if(board[a][b]->isEmpty()){
            cout << "there is no piece" << '\n';
            continue;
        }  

        if(board[a][b]->color != side[turn % 2]){
            cout << "its not your turn" << '\n';
            continue;
        }
        
        cout << "to where: ";
        cin >> dest;

        char i = dest[1] - '1';
        char j = dest[0] - 'a';

        if (checkMove(board, src, dest, wkingptr, bkingptr)){
            move(board, src, dest, wkingptr, bkingptr);
            // if(board[a][b]->getType() == "r" || board[a][b]->getType() == "k")
            //     board[a][b]->is_played = true;
        }
        else{
            cout << "you can not play this move" << '\n';
            continue;
        }

        if(check_checker(board, side[turn % 2], wkingptr, bkingptr, dest)){
            cout << "checkmate!";
            break;
        }
        printboard(board);
        turn += 1;
    }
    return 0;
}

bool check_checker(Piece* board[8][8], string side, Piece* wkingptr, Piece* bkingptr, string dest){

    char i = dest[1] - '1';
    char j = dest[0] - 'a';
    char k = wkingptr->coordinate[1] - '1';
    char l = wkingptr->coordinate[0] - 'a';
    char m = bkingptr->coordinate[1] - '1';
    char n = bkingptr->coordinate[0] - 'a';

    if(side == "white" && bkingptr->dangerw){
        cout << "black king is under attack\n";
            if(bkingptr->view(board).empty()){
                for(int x = i, y = j; abs(x-m) > 0 ; x+=(m-i)/(abs(m-i)), y+=(n-j)/abs(n-j)){
                    for(int b_i = 0; b_i < 8; b_i++){
                        for(int b_j = 0; b_j < 8; b_j++){
                            if(board[b_i][b_j]->color == "black"){
                                for(string str : board[b_i][b_j]->view(board)){
                                    if(str == board[x][y]->coordinate){
                                        return false;
                                    } 
                                }
                            }
                        }
                    }
                }
                return true;
            }else if(!abs_pin_checker(board, bkingptr->coordinate, dest, wkingptr, bkingptr) && abs(i-m) < 2 && abs(j-n) < 2){
                return true;
            }
    }else if(side == "black" && wkingptr->dangerb){
        cout << "white king is under attack\n";
            if(wkingptr->view(board).empty()){
                for(int x = i, y = j; abs(x-k) > 0 ; x+=(k-i)/(abs(k-i)), y+=(l-j)/abs(l-j)){
                    for(int b_i = 0; b_i < 8; b_i++){
                        for(int b_j = 0; b_j < 8; b_j++){
                            if(board[b_i][b_j]->color == "white"){
                                for(string str : board[b_i][b_j]->view(board)){
                                    if(str == board[x][y]->coordinate){
                                        return false;
                                    }
                                }
                            }
                        }
                    }
                }
                return true;
            }else if(!abs_pin_checker(board, bkingptr->coordinate, dest, wkingptr, bkingptr) && abs(i-k) < 2 && abs(j-l) < 2){
                return true;
            }
    }
    return false;
}

bool abs_pin_checker(Piece* board[8][8], string src, string &dest, Piece* wkingptr, Piece* bkingptr){

    char k = wkingptr->coordinate[1] - '1';
    char l = wkingptr->coordinate[0] - 'a';
    char m = bkingptr->coordinate[1] - '1';
    char n = bkingptr->coordinate[0] - 'a';

    char a = src[1] - '1';
    char b = src[0] - 'a';
    char i = dest[1] - '1';
    char j = dest[0] - 'a';
    char empty_coor[3];
    empty_coor[0] = src[0];
    empty_coor[1] = src[1];
    empty_coor[2] = '\0';

    Piece* hold = board[i][j];
    board[i][j] = board[a][b];
    board[a][b] = new Empty(empty_coor);
    board[i][j]->coordinate[0] = dest[0];
    board[i][j]->coordinate[1] = dest[1];
        
    resetZone(board);
    zoneCreater(board);

    if(board[i][j]->color == "white" && wkingptr->dangerb){

        board[a][b] = board[i][j];  
        board[i][j] = hold;
        board[a][b]->coordinate[0] = src[0];
        board[a][b]->coordinate[1] = src[1];
        resetZone(board);
        zoneCreater(board);
        return false;
    }

    if(board[i][j]->color == "black" && bkingptr->dangerw){
        board[a][b] = board[i][j];
        board[i][j] = hold;
        board[a][b]->coordinate[0] = src[0];
        board[a][b]->coordinate[1] = src[1];
        resetZone(board);
        zoneCreater(board);
        return false;
    }

    board[a][b] = board[i][j];  
    board[i][j] = hold;
    board[a][b]->coordinate[0] = src[0];
    board[a][b]->coordinate[1] = src[1];
    resetZone(board);
    zoneCreater(board);
    return true;
}

void move(Piece* board[8][8], string src, string &dest, Piece* wkingptr, Piece* bkingptr){

    char a = src[1] - '1';
    char b = src[0] - 'a';
    char i = dest[1] - '1';
    char j = dest[0] - 'a';
    char empty_coor[3];
    empty_coor[0] = src[0];
    empty_coor[1] = src[1];
    empty_coor[2] = '\0';
    
    board[i][j] = board[a][b];
    board[a][b] = new Empty(empty_coor);
    board[i][j]->coordinate[0] = dest[0];
    board[i][j]->coordinate[1] = dest[1];

    resetZone(board);
    zoneCreater(board);
}

void resetZone(Piece* board[8][8]){
    for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++){
                if(board[x][y]->isEmpty() || board[x][y]->getType() == "k"){
                    board[x][y]->dangerw = false;
                    board[x][y]->dangerb = false;
                }
            }
        }
}

void printboard(Piece* board[8][8]){
    cout << '\n';
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 8; j++) {
            cout << setw(1) << board[i][j]->name << " ";
        }
        cout << '\n';
    } 
    cout << '\n';
}

void zoneCreater(Piece* board[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(!board[i][j]->isEmpty()){
                board[i][j]->dangerZone(board);
            }
        }
    }
}

bool checkMove(Piece* board[8][8], string src, string &dest, Piece* wkingptr, Piece* bkingptr){

    char a = src[1] - '1';
    char b = src[0] - 'a';
    char i = dest[1] - '1';
    char j = dest[0] - 'a';
    bool empty = true;

    if((board[a][b]->getType() == "k") && (board[a][b]->color == "white") && (board[i][j]->dangerb)){
        cout << "you can not play your king here" << '\n';
        return false;
    }
    
    if((board[a][b]->getType() == "k") && (board[a][b]->color == "black") && (board[i][j]->dangerw)){
        cout << "you can not play your king here" << '\n';
        return false;
    }

    if(!abs_pin_checker(board, src, dest, wkingptr, bkingptr)){
        return false;
    }

    if((board[a][b]->getType() == "p") && (board[a][b]->color == "white")){    // white pawn
        if((i-a == 2) && (board[a+1][b]->isEmpty() && board[a+2][b]->isEmpty())){
            return true;
        }else if(((i-a == 1) && j == b) && (board[a+1][b]->isEmpty())){
            return true;
        }else if(((i-a == 1) && abs(j-b) == 1) && (board[i][j]->color == "black")){
            return true;
        }
    };
    
    if((board[a][b]->getType() == "p") && (board[a][b]->color == "black")){    // black pawn
        if((a-i == 2) && (board[a-1][b]->isEmpty() && board[a-2][b]->isEmpty())){
            return true;
        }else if(((a-i == 1) && j == b) && (board[a-1][b]->isEmpty())){
            return true;
        }else if(((a-i == 1) && abs(j-b) == 1) && (board[i][j]->color == "white")){
            return true;
        }
    };

    if(board[a][b]->getType() == "r"){    // rook
        if((i > a) && j-b == 0){    // up
            for(int x = a+1; x <= i; x++){
                if(((x != i) && !board[x][b]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && j-b == 0){    // down
            for(int x = a-1; x >= i; x--){
                if(((x != i) && !board[x][b]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((j > b) && a-i == 0){    // right
            for(int x = b+1; x <= j; x++){
                if(((x != j) && !board[a][x]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((b > j) && a-i == 0){    // left
            for(int x = b-1; x >= j; x--){
                if(((x != j) && !board[a][x]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
    }
    if(board[a][b]->getType() == "b"){    // bishop

        if(abs(i-a) != abs(j-b)){
            return false;
        }
        if((i > a) && (j > b)){    // up + right
            for(int x = a+1, y = b+1; x <= i; x++, y++){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((i > a) && (b > j)){    // up + left
            for(int x = a+1, y = b-1; x <= i; x++, y--){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (j > b)){    // down + right
            for(int x = a-1, y = b+1; x >= i; x--, y++){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (b > j)){    // down + left
            for(int x = a-1, y = b-1; x >= i; x--, y--){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }

    }
    if(board[a][b]->getType() == "n"){    // knight
        if(((board[i][j]->isEmpty()) || board[a][b]->color != board[i][j]->color) && ((abs(i-a) == 2 && abs(j-b) == 1) || (abs(i-a) == 1 && abs(j-b) == 2))){
            return true;
        }
        else{
            return false;
        }
    }
    if(board[a][b]->getType() == "q"){    // queen
        if((abs(i-a) != abs(j-b)) && !((abs(i-a) == 0) || abs(j-b) == 0)){
            return false;
        }
        if((i > a) && j-b == 0){    // up
            for(int x = a+1; x <= i; x++){
                if(((x != i) && !board[x][b]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && j-b == 0){    // down
            for(int x = a-1; x >= i; x--){
                if(((x != i) && !board[x][b]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((j > b) && a-i == 0){    // right
            for(int x = b+1; x <= j; x++){
                if(((x != j) && !board[a][x]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((b > j) && a-i == 0){    // left
            for(int x = b-1; x >= j; x--){
                if(((x != j) && !board[a][x]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == j))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((i > a) && (j > b)){    // up + right
            for(int x = a+1, y = b+1; x <= i; x++, y++){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((i > a) && (b > j)){    // up + left
            for(int x = a+1, y = b-1; x <= i; x++, y--){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (j > b)){    // down + right
            for(int x = a-1, y = b+1; x >= i; x--, y++){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
        if((a > i) && (b > j)){    // down + left
            for(int x = a-1, y = b-1; x >= i; x--, y--){
                if(((x != i) && !board[x][y]->isEmpty()) || ((board[i][j]->color == board[a][b]->color) && (x == i))){
                    empty = false; 
                }
            }
            return empty;
        }
    }
    if(board[a][b]->getType() == "k"){    // king
        if((abs(a-i) < 2) && (abs(j-b) < 2)){
            if(board[i][j]->color == board[a][b]->color){
                return false;
            }
            else{
                return true;
            }
        }    
    }

    return false;
}
