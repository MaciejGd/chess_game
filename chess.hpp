#include<string>
#include<iostream>
#include<vector>

using namespace std;

//struct of move, it stores starting (y, x) coordinates and coordinates of target field (x, y)
struct Move{
    int y_coordinate_starting;
    int x_coordinate_starting;
    int y_coordinate_target;
    int x_coordinate_target;
};

//piece representing pieces, for empty fields there is an empty constructor
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

//functions to print board and taking input from user
int translating_chars_to_ints(char first_coordinate);
void print_board(Piece board[8][8]);
Move move_input();

//functions used to modify board status
void make_move(Piece (&board)[8][8], Move desired_move, vector<Move> &list_of_moves);
void undo_move(Piece (&board)[8][8], vector<Move> &previous_moves);
void promotion(Piece (&board)[8][8], vector<Move> previous_moves);

//function returning beaten piece, necessary to bring piece back to live if undoing move is needed
Piece if_beaten(Piece board[8][8], Move move);

//bool functions implementing chess rules
bool is_move_possible(Piece board[8][8], Move destination, bool side, vector<Move> previous_moves);
bool game_won(Piece board[8][8], Piece king, vector<Move> previous_moves);

//bool functions implementing chess rules - king related
bool is_checked(Piece board[8][8], Piece king, vector<Move> previous_moves);
bool is_move_killing_king(Piece board[8][8], Move destination);
bool is_king_moving_to_check(Piece board[8][8], Move destination, vector<Move> previous_moves);
bool is_castle_possible(Piece board[8][8], bool side, vector<Move> previous_moves, Move castle);

//bool functions implementing chess rules - pawn related
bool is_promotion(Piece board[8][8], vector<Move> previous_moves);
bool is_en_passant_possible(Piece board[8][8], vector<Move> previous_moves, Move pawn_move);





