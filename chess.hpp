#include<string>
#include<iostream>
#include<vector>

using namespace std;

struct Move{
    int y_coordinate_starting;
    int x_coordinate_starting;
    int y_coordinate_target;
    int x_coordinate_target;
};

class Piece{

    public:
        int y_coordinate;
        int x_coordinate;
        char type;
        bool color;

        Piece(int y, int x, bool side, char t){
            y_coordinate = y;
            x_coordinate = x;
            type = t;
            color = side;
        }
        Piece(){
            y_coordinate=-1;
            x_coordinate=-1;
            type=' ';
            color=false;
        }
        char get_type();
        Move get_all_possible_moves(Piece board[8][8], Piece element);
};


void print_board(Piece board[8][8]);
bool is_move_possible(Piece board[8][8], Move destination, bool side, vector<Move> previous_moves);
bool is_checked(Piece board[8][8], Piece king, vector<Move> previous_moves);
bool is_promotion(Piece board[8][8], vector<Move> previous_moves);
void promotion(Piece (&board)[8][8], vector<Move> previous_moves);
bool is_en_passant_possible(Piece board[8][8], vector<Move> previous_moves, Move pawn_move);
Move move_input();
void make_move(Piece (&board)[8][8], Move desired_move, vector<Move> &list_of_moves);
void undo_move(Piece (&board)[8][8], vector<Move> &previous_moves);
bool is_move_killing_king(Piece board[8][8], Move destination);
bool is_king_threating_king(Piece board[8][8], bool side, Move destination);
bool game_won(Piece (&board)[8][8], Piece king, vector<Move> previous_moves);
Piece if_beaten(Piece board[8][8], Move move);
bool is_king_moving_to_check(Piece board[8][8], Move destination, vector<Move> previous_moves);