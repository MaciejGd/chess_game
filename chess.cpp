#include "chess.hpp"
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
#include<ctype.h>

using namespace std;

//function to read a char as integer we want
int translating_chars_to_ints(char first_coordinate){
    int result;
    switch(first_coordinate){
        case 'a':
            result = 0;
            break;
        case 'b':
            result = 1;
            break;
        case 'c':
            result = 2;
            break;
        case 'd':
            result = 3;
            break;
        case 'e':
            result = 4;
            break;
        case 'f':
            result = 5;
            break;
        case 'g':
            result = 6;
            break;
        case 'h':
            result = 7;
            break;
        default:
            result = -1;
            break;
    }
    return result;
}

//Function to get a move from a user
Move move_input() {
    Move wanted_move;
    bool valid_coordinates = false;
    char starting_char;
    char ending_char;
    int starting_int;
    int ending_int;

    while (!valid_coordinates) {
        cout << "Enter starting coordinates (y, x): ";
        cin >> starting_char >> starting_int;
        wanted_move.y_coordinate_starting = 8 - starting_int;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input, please enter proper coordinates: "<<endl;
        }

        cout << "Enter target coordinates (y, x): ";
        cin >> ending_char >> ending_int;
        wanted_move.y_coordinate_target = 8 - ending_int; 
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input, please enter proper coordinates: "<<endl;
        }

        wanted_move.x_coordinate_starting = translating_chars_to_ints(starting_char);
        wanted_move.x_coordinate_target = translating_chars_to_ints(ending_char);
        
        if (wanted_move.y_coordinate_starting < 0 || wanted_move.y_coordinate_starting > 7 ||
            wanted_move.x_coordinate_starting < 0 || wanted_move.x_coordinate_starting > 7 ||
            wanted_move.y_coordinate_target < 0 || wanted_move.y_coordinate_target > 7 ||
            wanted_move.x_coordinate_target < 0 || wanted_move.x_coordinate_target > 7) {
            cout << "Invalid coordinates. Please try again." << endl;
        }
        else {
            valid_coordinates = true;
        }
    }
    
    return wanted_move;
}


void print_board(Piece board[8][8]){
    cout<<"    a   b   c   d   e   f   g   h\n";
    cout<<"  +---+---+---+---+---+---+---+---+\n";
    int x = 8;
    for(int i = 0; i<8; i++, x--){
        cout<<x<<" |";
        for(int j = 0; j<8; j++){
            if(board[i][j].get_color()==true){
                cout<<" "<<board[i][j].get_type()<<" |";
            }
            else{
                char ch = board[i][j].get_type();
                cout<<" "<<(char)tolower(ch)<<" |";
            }
            
        }
        cout<<endl;
        cout<<"  +---+---+---+---+---+---+---+---+\n";
    }
}

//functions to check or manipulate class properties
char Piece::get_type(){
    return type;
}

void Piece::change_type(char desired_type){
    type = desired_type;
}

int Piece::get_y(){
    return y_coordinate; 
}

int Piece::get_x(){
    return x_coordinate; 
}

void Piece::change_coordinates(int y, int x){
    y_coordinate = y;
    x_coordinate = x;
}

bool Piece::get_color(){
    return color;
}


//function for checking if move is possible
bool is_move_possible(Piece board[8][8],Move destination, bool side, vector<Move> previous_moves){

    //checking general rules for move to be possible
    if(board[destination.y_coordinate_starting][destination.x_coordinate_starting].get_color()!=side){
        return false;
    }
    else if(board[destination.y_coordinate_starting][destination.x_coordinate_starting].get_type()==' '){
        return false;
    }
    //to edit
    else if(board[destination.y_coordinate_target][destination.x_coordinate_target].get_color()==side && board[destination.y_coordinate_target][destination.x_coordinate_target].get_type()!=' '){
        return false;
    }
    else if(destination.x_coordinate_starting==destination.x_coordinate_target && destination.y_coordinate_starting==destination.y_coordinate_target){
        return false;
    }

    switch(board[destination.y_coordinate_starting][destination.x_coordinate_starting].get_type()){
        //checking if given move is possible if at starting field there is a Rook
        case 'R':
            if(destination.y_coordinate_starting==destination.y_coordinate_target){
                if(destination.x_coordinate_target-destination.x_coordinate_starting>0){
                    for(int i = destination.x_coordinate_starting+1; i<destination.x_coordinate_target; i++){
                        if(board[destination.y_coordinate_starting][i].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target-destination.x_coordinate_starting<0){
                    for(int i = destination.x_coordinate_starting-1; i>destination.x_coordinate_target; i--){
                        if(board[destination.y_coordinate_starting][i].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
            }
            else if(destination.x_coordinate_starting==destination.x_coordinate_target){
                if(destination.y_coordinate_target-destination.y_coordinate_starting>0){
                    for(int i = destination.y_coordinate_starting+1; i<destination.y_coordinate_target; i++){
                        if(board[i][destination.x_coordinate_starting].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
                else if(destination.y_coordinate_target-destination.y_coordinate_starting<0){
                    for(int i = destination.y_coordinate_target-1; i>destination.y_coordinate_target; i--){
                        if(board[i][destination.x_coordinate_starting].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
            }
            return false;
            break;

        case 'B':
            //checking if move is possible for bishop
            if(abs(destination.x_coordinate_target-destination.x_coordinate_starting)==abs(destination.y_coordinate_target-destination.y_coordinate_starting)){
                if(destination.x_coordinate_target>destination.x_coordinate_starting && destination.y_coordinate_target>destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting+1; i<destination.y_coordinate_target;){
                        for(int j = destination.x_coordinate_starting+1; j<destination.x_coordinate_target; j++, i++){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target<destination.x_coordinate_starting && destination.y_coordinate_target>destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting+1; i<destination.y_coordinate_target;){
                        for(int j = destination.x_coordinate_starting-1; j>destination.x_coordinate_target; j--, i++){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target<destination.x_coordinate_starting && destination.y_coordinate_target<destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting-1; i>destination.y_coordinate_target; ){
                        for(int j = destination.x_coordinate_starting-1; j>destination.x_coordinate_target; j--,i--){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target>destination.x_coordinate_starting && destination.y_coordinate_target<destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting-1; i>destination.y_coordinate_target;){
                        for(int j = destination.x_coordinate_starting+1; j<destination.x_coordinate_target; j++, i--){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
            }
            else{
                return false;
            }
            break;
        //checking if move is possible for knight
        case 'H':
            if(abs(destination.y_coordinate_target-destination.y_coordinate_starting)==2){
                if(abs(destination.x_coordinate_target-destination.x_coordinate_starting)==1){
                    return true;
                }
            }
            else if(abs(destination.y_coordinate_target-destination.y_coordinate_starting)==1){
                if(abs(destination.x_coordinate_target-destination.x_coordinate_starting)==2){
                    return true;
                }
            }
            else{
                return false;
            }
            break;
        //checking if move is possible for queen
        case 'Q':
            if(abs(destination.x_coordinate_target-destination.x_coordinate_starting)==abs(destination.y_coordinate_target-destination.y_coordinate_starting)){
                if(destination.x_coordinate_target>destination.x_coordinate_starting && destination.y_coordinate_target>destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting+1; i<destination.y_coordinate_target;){
                        for(int j = destination.x_coordinate_starting+1; j<destination.x_coordinate_target; j++, i++){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target<destination.x_coordinate_starting && destination.y_coordinate_target>destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting+1; i<destination.y_coordinate_target;){
                        for(int j = destination.x_coordinate_starting-1; j>destination.x_coordinate_target; j--, i++){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target<destination.x_coordinate_starting && destination.y_coordinate_target<destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting-1; i>destination.y_coordinate_target; ){
                        for(int j = destination.x_coordinate_starting-1; j>destination.x_coordinate_target; j--,i--){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target>destination.x_coordinate_starting && destination.y_coordinate_target<destination.y_coordinate_starting){
                    for(int i = destination.y_coordinate_starting-1; i>destination.y_coordinate_target;){
                        for(int j = destination.x_coordinate_starting+1; j<destination.x_coordinate_target; j++, i--){
                            if(board[i][j].get_type()==' '){
                                continue;
                            }
                            else{
                                return false;
                            }
                        }
                    }
                    return true;
                }
            }
            else if(destination.y_coordinate_starting==destination.y_coordinate_target){
                if(destination.x_coordinate_target-destination.x_coordinate_starting>0){
                    for(int i = destination.x_coordinate_starting+1; i<destination.x_coordinate_target; i++){
                        if(board[destination.y_coordinate_starting][i].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
                else if(destination.x_coordinate_target-destination.x_coordinate_starting<0){
                    for(int i = destination.x_coordinate_starting-1; i>destination.x_coordinate_target; i--){
                        if(board[destination.y_coordinate_starting][i].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
            }
            else if(destination.x_coordinate_starting==destination.x_coordinate_target){
                if(destination.y_coordinate_target-destination.y_coordinate_starting>0){
                    for(int i = destination.y_coordinate_starting+1; i<destination.y_coordinate_target; i++){
                        if(board[i][destination.x_coordinate_starting].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
                else if(destination.y_coordinate_target-destination.y_coordinate_starting<0){
                    for(int i = destination.y_coordinate_starting-1; i>destination.y_coordinate_target; i--){
                        if(board[i][destination.x_coordinate_starting].get_type()==' '){
                            continue;
                        }
                        else{
                            return false;
                        }
                    }
                    return true;
                }
            }
            else{
                return false;
            }
            break;
        //checking if move is possible for King
        case 'K':
            if(is_king_moving_to_check(board,destination, previous_moves)){
                return false;
            }
            if(abs(destination.x_coordinate_target-destination.x_coordinate_starting)==1 && abs(destination.y_coordinate_target-destination.y_coordinate_starting)==1){
                return true;
            }
            else if(abs(destination.y_coordinate_target-destination.y_coordinate_starting)==1 && destination.x_coordinate_target-destination.x_coordinate_starting==0){
                return true;
            }
            else if(destination.x_coordinate_target-destination.x_coordinate_starting==0 && abs(destination.y_coordinate_target-destination.y_coordinate_starting)==1){
                return true;
            }
            else if(is_castle_possible(board, side, previous_moves, destination)){
                return true;            
            }
            else{
                return false;
            }
            break;
        case 'P':
            if(destination.x_coordinate_starting==destination.x_coordinate_target && board[destination.y_coordinate_target][destination.x_coordinate_target].get_type() == ' '){
                if(!side){
                    if(destination.y_coordinate_target-destination.y_coordinate_starting==1){
                        return true;
                    }
                    else if(destination.y_coordinate_starting==1 && destination.y_coordinate_target-destination.y_coordinate_starting==2){
                        return true;
                    }
                }
                else{
                    if(destination.y_coordinate_starting-destination.y_coordinate_target==1){
                        return true;
                    }
                    else if(destination.y_coordinate_starting==6 && destination.y_coordinate_starting-destination.y_coordinate_target==2){
                        return true;
                    }
                }
            }
            else if(abs(destination.x_coordinate_target-destination.x_coordinate_starting)==1){
                if(is_en_passant_possible(board, previous_moves, destination)){
                   if(side==false){
                        if(destination.y_coordinate_target-destination.y_coordinate_starting==1){
                            return true;
                        }
                    }
                    else{
                        if(destination.y_coordinate_starting-destination.y_coordinate_target==1){
                            return true;
                        }
                    } 
                }
                else{
                    if(side==false){
                        if(destination.y_coordinate_target-destination.y_coordinate_starting==1 && board[destination.y_coordinate_target][destination.x_coordinate_target].get_type()!=' '){
                            return true;
                        }
                    }
                    else{
                        if(destination.y_coordinate_starting-destination.y_coordinate_target==1 && board[destination.y_coordinate_target][destination.x_coordinate_target].get_type()!=' '){
                            return true;
                        }
                    }
                }
            }
            return false;
            break;
        default:
            return false;
            break;
    }
    return false;
}

//checking if castle is possible
bool is_castle_possible(Piece board[8][8], bool side, vector<Move> previous_moves, Move castle){
    //checking if good move coordinates has been given and if king is not checked 
    if(is_checked(board, board[castle.y_coordinate_starting][castle.x_coordinate_starting], previous_moves)){
        return false;
    }
    if(side){
        if(castle.y_coordinate_target != 7){
            return false;
        }
        else if(castle.x_coordinate_target != 6 && castle.x_coordinate_target != 2){
            return false;
        }
    }
    else {
        if(castle.y_coordinate_target != 0){
            return false;
        }
        else if(castle.x_coordinate_target != 6 && castle.x_coordinate_target != 2){
            return false;
        }
    }

    //checking if there is no piece between rook and king in special environment
    if(castle.x_coordinate_target == 2 && board[castle.y_coordinate_target][1].get_type() != ' ')
        return false;

    //checking if king or rook was moved or if rook was taken
    for(Move i : previous_moves){
        if(side){
            if(i.y_coordinate_starting == 7 && i.x_coordinate_starting == 4){
                return false;
            }
            if(castle.x_coordinate_target == 2 && ((i.y_coordinate_starting == 7 && i.x_coordinate_starting == 0) ||(i.y_coordinate_target == 7 && i.x_coordinate_target == 0))){
                return false;
            }
            else if(castle.x_coordinate_target == 6 && ((i.y_coordinate_starting == 7 && i.x_coordinate_starting == 7) || (i.y_coordinate_target == 7 && i.x_coordinate_target == 7))){
                return false;
            }
            else if(castle.x_coordinate_target == 2 && board[7][1].get_type()!=' '){
                return false;
            }
        }
        else{
            if(i.y_coordinate_starting == 0 && i.x_coordinate_starting == 4){
                return false;
            }
            if(castle.x_coordinate_target == 2 && ((i.y_coordinate_starting == 0 && i.x_coordinate_starting == 0) || (i.y_coordinate_target == 0 && i.x_coordinate_target == 0))){
                return false;
            }
            else if(castle.x_coordinate_target == 6 && ((i.y_coordinate_starting == 0 && i.x_coordinate_starting == 7) || (i.y_coordinate_target == 7 && i.x_coordinate_target == 7))){
                return false;
            }
        }
    }
    return true;
}

//checking if king is checked
bool is_checked(Piece board[8][8], Piece king, vector<Move> previous_moves){
    Move checking_move;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].get_color()!=king.get_color() && board[i][j].get_type()!=' '&& board[i][j].get_type()!='K'){ 
                checking_move.y_coordinate_starting = i;
                checking_move.x_coordinate_starting = j;
                checking_move.y_coordinate_target = king.get_y();
                checking_move.x_coordinate_target = king.get_x();
                if(is_move_possible(board, checking_move,board[i][j].get_color(),previous_moves)){
                    return true;
                } 
            }
            
        }
    }
    return false;
}

//checking if king is moving to check
bool is_king_moving_to_check(Piece board[8][8], Move destination , vector<Move> previous_moves){
    
    Piece beaten_piece = Piece();
    if(board[destination.y_coordinate_target][destination.x_coordinate_target].get_type() == 'K'){
        return false;
    }

    beaten_piece = if_beaten(board, destination);

    board[destination.y_coordinate_target][destination.x_coordinate_target] = board[destination.y_coordinate_starting][destination.x_coordinate_starting];
    board[destination.y_coordinate_starting][destination.x_coordinate_starting] = Piece();
    Move checking_move;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].get_color()!=board[destination.y_coordinate_target][destination.x_coordinate_target].get_color() && board[i][j].get_type()!=' '&& board[i][j].get_type()!='K'){ 
                checking_move.y_coordinate_starting = i;
                checking_move.x_coordinate_starting = j;
                checking_move.y_coordinate_target = destination.y_coordinate_target;
                checking_move.x_coordinate_target = destination.x_coordinate_target;
                if(is_move_possible(board, checking_move,board[i][j].get_color(),previous_moves)){
                    board[destination.y_coordinate_starting][destination.x_coordinate_starting] = board[destination.y_coordinate_target][destination.x_coordinate_target];
                    board[destination.y_coordinate_target][destination.x_coordinate_target] = beaten_piece;
                    return true;
                } 
            }
        }
    }
    board[destination.y_coordinate_starting][destination.x_coordinate_starting] = board[destination.y_coordinate_target][destination.x_coordinate_target];
    board[destination.y_coordinate_target][destination.x_coordinate_target] = beaten_piece;
    return false;
}


//checking if there is poromotion
bool is_promotion(Piece board[8][8], vector<Move> previous_moves){
    Move last_move = previous_moves.back();
    if(board[last_move.y_coordinate_target][last_move.x_coordinate_target].get_type() == 'P'){
        if(board[last_move.y_coordinate_target][last_move.x_coordinate_target].get_color() == true){
            if(last_move.y_coordinate_target==0){
                return true;
            }
        }
        else{
            if(last_move.y_coordinate_target==7){
                return true;
            }
        }
    }
    return false;
    
}

//making promotion
void promotion(Piece (&board)[8][8], vector<Move> previous_moves){
    Move last_move = previous_moves.back();
    if(is_promotion(board,previous_moves)){
        char chosen_one;
        bool valid_input = false;
        while(!valid_input){
            cout<<"What piece do you want to change this piece into?: Type: q-Queen, r-Rook, b-Bishop, h-Knight"<<endl;
            try{
                cin>>chosen_one;
                if(chosen_one=='q'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].change_type('Q');
                    valid_input = true;
                }
                else if(chosen_one=='r'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].change_type('R');
                    valid_input = true;
                }
                else if(chosen_one=='b'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].change_type('B');
                    valid_input = true;
                }
                else if(chosen_one=='h'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].change_type('H');
                    valid_input = true;
                }
                else{
                    throw "Invalid input. ";
                }   
            }
            catch(const exception& e){
                cerr<<"Invalid input: "<< e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
            }
            
        }
    }

}

//checking if en passant is possible
bool is_en_passant_possible(Piece board[8][8], vector<Move> previous_moves, Move pawn_move){
    Move last_move = previous_moves.back();
    if(board[last_move.y_coordinate_target][last_move.x_coordinate_target].get_type()!='P')
        return false;
    if(abs(last_move.y_coordinate_target-last_move.y_coordinate_starting)!=2 && abs(pawn_move.x_coordinate_starting-last_move.x_coordinate_target)!=1)   
        return false;
    if(last_move.y_coordinate_target!=pawn_move.y_coordinate_starting)
        return false;
    return true;
}

//making move on a board
void make_move(Piece (&board)[8][8], Move desired_move, vector<Move> &list_of_moves){
    //statement to erase pawn beaten with en passant
    if(board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting].get_type()=='P' && board[desired_move.y_coordinate_target][desired_move.x_coordinate_target].get_type() == ' ' && desired_move.x_coordinate_target!=desired_move.x_coordinate_starting){
        if(board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting].get_color()){
            board[desired_move.y_coordinate_target+1][desired_move.x_coordinate_target].change_type(' ');
        }
        else{
            board[desired_move.y_coordinate_target-1][desired_move.x_coordinate_target].change_type(' ');
        }
    }
    //checking if king is moving (had to implement castle)
    //here i stopped writing changes to my code becaouse it was too late

    if(board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting].get_type() == 'K' && desired_move.y_coordinate_starting == desired_move.y_coordinate_target){
        if(desired_move.x_coordinate_starting == 4 && desired_move.x_coordinate_target == 2){
            board[desired_move.y_coordinate_target][desired_move.x_coordinate_target] = board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting];
            board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting] = Piece();
            board[desired_move.y_coordinate_target][3] = board[desired_move.y_coordinate_target][0];
            board[desired_move.y_coordinate_target][0] = Piece();
            list_of_moves.push_back(desired_move);
        }
        else if(desired_move.x_coordinate_starting == 4 && desired_move.x_coordinate_target == 6){
            board[desired_move.y_coordinate_target][desired_move.x_coordinate_target] = board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting];
            board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting] = Piece();
            board[desired_move.y_coordinate_target][5] = board[desired_move.y_coordinate_target][7];
            board[desired_move.y_coordinate_target][7] = Piece();
            list_of_moves.push_back(desired_move);
        }
        else{
            board[desired_move.y_coordinate_target][desired_move.x_coordinate_target]=board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting];
            board[desired_move.y_coordinate_target][desired_move.x_coordinate_target].change_coordinates(desired_move.y_coordinate_target, desired_move.x_coordinate_target);
            board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting] = Piece();
            list_of_moves.push_back(desired_move);
        }
    }
    else{
        board[desired_move.y_coordinate_target][desired_move.x_coordinate_target]=board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting];
        board[desired_move.y_coordinate_target][desired_move.x_coordinate_target].change_coordinates(desired_move.y_coordinate_target, desired_move.x_coordinate_target);
        board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting] = Piece();
        list_of_moves.push_back(desired_move);
    }    
}
//if enemy was beaten it will return the piece it beaten so the undo move would bring this piece back to life
Piece if_beaten(Piece board[8][8], Move move){
    if(board[move.y_coordinate_target][move.x_coordinate_target].get_type()!=' '){
        return board[move.y_coordinate_target][move.x_coordinate_target]; 
    }
    //returning piece beaten with en passant
    else if(board[move.y_coordinate_target][move.x_coordinate_target].get_type() ==' ' && board[move.y_coordinate_starting][move.x_coordinate_starting].get_type() == 'P' && move.x_coordinate_target!=move.x_coordinate_starting){
        if(board[move.y_coordinate_starting][move.x_coordinate_starting].get_color()){
            return board[move.y_coordinate_target+1][move.x_coordinate_target];
        }
        else{
            return board[move.y_coordinate_target-1][move.x_coordinate_target];
        }
    } 
    return Piece();
}

//undoing not proper move
void undo_move(Piece (&board)[8][8], vector<Move> &previous_moves){
    Move re_move = previous_moves.back();
    previous_moves.pop_back(); 
    int target_x = re_move.x_coordinate_starting;
    int starting_x = re_move.x_coordinate_target;
    int target_y = re_move.y_coordinate_starting;
    int starting_y = re_move.y_coordinate_target;
    Move undo = {starting_y, starting_x, target_y, target_x};
    make_move(board, undo, previous_moves);
    previous_moves.pop_back(); 
}

//had to extract this piece of code from function is_move_possible because it causes problems with function is_checked
bool is_move_killing_king(Piece board[8][8], Move destination){
    if(board[destination.y_coordinate_target][destination.x_coordinate_target].get_type() == 'K'){
        return true;
    }
    return false;
}

//checking if there is end of the game
bool game_won(Piece board[8][8], Piece king, vector<Move> previous_moves){
    Piece beaten_piece;
    Move possible_cover;
    if(is_checked(board, king, previous_moves)){
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                if(board[i][j].get_color()==king.get_color()){
                    for(int y = 0; y<8; y++){
                        for(int x = 0; x<8; x++){
                            possible_cover = {i,j,y,x}; 
                            if(is_move_possible(board, possible_cover, king.get_color(), previous_moves)){
                                beaten_piece = if_beaten(board, possible_cover);
                                board[possible_cover.y_coordinate_target][possible_cover.x_coordinate_target] = board[possible_cover.y_coordinate_starting][possible_cover.x_coordinate_starting];
                                board[possible_cover.y_coordinate_starting][possible_cover.x_coordinate_starting] = Piece();
                                if(!is_checked(board, king, previous_moves)){
                                    board[possible_cover.y_coordinate_starting][possible_cover.x_coordinate_starting] = board[possible_cover.y_coordinate_target][possible_cover.x_coordinate_target];
                                    board[possible_cover.y_coordinate_target][possible_cover.x_coordinate_target] = beaten_piece;
                                    return false;
                                }
                                board[possible_cover.y_coordinate_starting][possible_cover.x_coordinate_starting] = board[possible_cover.y_coordinate_target][possible_cover.x_coordinate_target];
                                board[possible_cover.y_coordinate_target][possible_cover.x_coordinate_target] = beaten_piece;
                            }
                        }
                    }
                }  
            }
        }
        return true;
    }
    return false;
}

//stealmate mechanics
bool stealmate(Piece board[8][8], Piece king, vector<Move> previous_moves){
    Move move;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].get_color() == king.get_color()){
                for(int y = 0; y<8; y++){
                    for(int x = 0; x<8; x++){
                        move.y_coordinate_starting = i;
                        move.x_coordinate_starting = j;
                        move.y_coordinate_target = y;
                        move.x_coordinate_target = x;
                        if(is_move_possible(board, move, king.get_color(), previous_moves)){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}