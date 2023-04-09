#include "chess.hpp"
#include<cmath>
#include<iostream>
#include<string>
#include<vector>
#include<ctype.h>

using namespace std;

//Types of pieces: P-pawn, B-bishop, Q-queen, K-king, H-horse; R-rook

//Function to get a move from a user
Move move_input() {
    Move wanted_move;
    bool valid_coordinates = false;
    
    while (!valid_coordinates) {
        cout << "Enter starting coordinates (y, x): ";
        cin >> wanted_move.y_coordinate_starting >> wanted_move.x_coordinate_starting;

        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input, please enter an integer: "<<endl;
        }

        cout << "Enter target coordinates (y, x): ";
        cin >> wanted_move.y_coordinate_target >> wanted_move.x_coordinate_target;
        
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Invalid input, please enter an integer: "<<endl;
        }
        if (wanted_move.y_coordinate_starting < 0 || wanted_move.y_coordinate_starting > 8 ||
            wanted_move.x_coordinate_starting < 0 || wanted_move.x_coordinate_starting > 8 ||
            wanted_move.y_coordinate_target < 0 || wanted_move.y_coordinate_target > 8 ||
            wanted_move.x_coordinate_target < 0 || wanted_move.x_coordinate_target > 8) {
            cout << "Invalid coordinates. Please try again." << endl;
        }
        else {
            valid_coordinates = true;
        }
    }
    
    return wanted_move;
}


void print_board(Piece board[8][8]){
    cout<<"    0   1   2   3   4   5   6   7\n";
    cout<<"  +---+---+---+---+---+---+---+---+\n";
    for(int i = 0; i<8; i++){
        cout<<i<<" |";
        for(int j = 0; j<8; j++){
            if(board[i][j].color==true){
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

char Piece::get_type(){
    return type;
}

bool is_move_possible(Piece board[8][8],Move destination, bool side, vector<Move> previous_moves){

    //checking general rules for move to be possible
    if(board[destination.y_coordinate_starting][destination.x_coordinate_starting].color!=side){
        return false;
    }
    else if(board[destination.y_coordinate_starting][destination.x_coordinate_starting].type==' '){
        return false;
    }
    //to edit
    else if(board[destination.y_coordinate_target][destination.x_coordinate_target].color==side && board[destination.y_coordinate_target][destination.x_coordinate_target].type!=' '){
        return false;
    }
    else if(destination.x_coordinate_starting==destination.x_coordinate_target && destination.y_coordinate_starting==destination.y_coordinate_target){
        return false;
    }

    switch(board[destination.y_coordinate_starting][destination.x_coordinate_starting].type){
        //checking if given move is possible if at starting field there is a Rook
        case 'R':
            if(destination.y_coordinate_starting==destination.y_coordinate_target){
                if(destination.x_coordinate_target-destination.x_coordinate_starting>0){
                    for(int i = destination.x_coordinate_starting+1; i<destination.x_coordinate_target; i++){
                        if(board[destination.y_coordinate_starting][i].type==' '){
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
                        if(board[destination.y_coordinate_starting][i].type==' '){
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
                        if(board[i][destination.x_coordinate_starting].type==' '){
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
                        if(board[i][destination.x_coordinate_starting].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                            if(board[i][j].type==' '){
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
                        if(board[destination.y_coordinate_starting][i].type==' '){
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
                        if(board[destination.y_coordinate_starting][i].type==' '){
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
                        if(board[i][destination.x_coordinate_starting].type==' '){
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
                        if(board[i][destination.x_coordinate_starting].type==' '){
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
            if(is_king_threating_king(board,side,destination)){
                return false;
            }
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
            else{
                return false;
            }
            break;
        case 'P':
            if(destination.x_coordinate_starting==destination.x_coordinate_target && board[destination.y_coordinate_target][destination.x_coordinate_target].type == ' '){
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
                        if(destination.y_coordinate_target-destination.y_coordinate_starting==1 && board[destination.y_coordinate_target][destination.x_coordinate_target].type!=' '){
                            return true;
                        }
                    }
                    else{
                        if(destination.y_coordinate_starting-destination.y_coordinate_target==1 && board[destination.y_coordinate_target][destination.x_coordinate_target].type!=' '){
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

bool is_checked(Piece board[8][8], Piece king, vector<Move> previous_moves){
    Move checking_move;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].color!=king.color && board[i][j].type!=' '&& board[i][j].type!='K'){ 
                checking_move.y_coordinate_starting = i;
                checking_move.x_coordinate_starting = j;
                checking_move.y_coordinate_target = king.y_coordinate;
                checking_move.x_coordinate_target = king.x_coordinate;
                if(is_move_possible(board, checking_move,board[i][j].color,previous_moves)){
                    return true;
                } 
            }
            
        }
    }
    return false;
}


bool is_king_moving_to_check(Piece board[8][8], Move destination , vector<Move> previous_moves){
    
    Piece beaten_piece = Piece();
    if(board[destination.y_coordinate_target][destination.x_coordinate_target].type == 'K'){
        return false;
    }

    beaten_piece = if_beaten(board, destination);

    board[destination.y_coordinate_target][destination.x_coordinate_target] = board[destination.y_coordinate_starting][destination.x_coordinate_starting];
    board[destination.y_coordinate_starting][destination.x_coordinate_starting] = Piece();
    Move checking_move;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if(board[i][j].color!=board[destination.y_coordinate_starting][destination.x_coordinate_starting].color && board[i][j].type!=' '&& board[i][j].type!='K'){ 
                checking_move.y_coordinate_starting = i;
                checking_move.x_coordinate_starting = j;
                checking_move.y_coordinate_target = destination.y_coordinate_target;
                checking_move.x_coordinate_target = destination.x_coordinate_target;
                if(is_move_possible(board, checking_move,board[i][j].color,previous_moves)){
                    return true;
                } 
            }
            
        }
    }
    return false;
}



bool is_promotion(Piece board[8][8], vector<Move> previous_moves){
    Move last_move = previous_moves.back();
    if(board[last_move.y_coordinate_target][last_move.x_coordinate_target].type == 'P'){
        if(board[last_move.y_coordinate_target][last_move.x_coordinate_target].color==true){
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
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].type = 'Q';
                    valid_input = true;
                }
                else if(chosen_one=='r'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].type = 'R';
                    valid_input = true;
                }
                else if(chosen_one=='b'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].type = 'B';
                    valid_input = true;
                }
                else if(chosen_one=='h'){
                    board[last_move.y_coordinate_target][last_move.x_coordinate_target].type = 'H';
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

//if x is same after the move and 

bool is_en_passant_possible(Piece board[8][8], vector<Move> previous_moves, Move pawn_move){
    Move last_move = previous_moves.back();
    if(board[last_move.y_coordinate_target][last_move.x_coordinate_target].type!='P')
        return false;
    if(abs(last_move.y_coordinate_target-last_move.y_coordinate_starting)!=2 && abs(pawn_move.x_coordinate_starting-last_move.x_coordinate_target)!=1)   
        return false;
    if(last_move.y_coordinate_target!=pawn_move.y_coordinate_starting)
        return false;
    return true;
}

void make_move(Piece (&board)[8][8], Move desired_move, vector<Move> &list_of_moves){
    //statement to erase pawn beaten with en passant
    if(board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting].type=='P' && board[desired_move.y_coordinate_target][desired_move.x_coordinate_target].type==' ' && desired_move.x_coordinate_target!=desired_move.x_coordinate_starting){
        if(board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting].color){
            board[desired_move.y_coordinate_target+1][desired_move.x_coordinate_target].type = ' ';
        }
        else{
            board[desired_move.y_coordinate_target-1][desired_move.x_coordinate_target].type = ' ';
        }
    }
    board[desired_move.y_coordinate_target][desired_move.x_coordinate_target]=board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting];
    board[desired_move.y_coordinate_target][desired_move.x_coordinate_target].y_coordinate = desired_move.y_coordinate_target;
    board[desired_move.y_coordinate_target][desired_move.x_coordinate_target].x_coordinate = desired_move.x_coordinate_target;
    board[desired_move.y_coordinate_starting][desired_move.x_coordinate_starting].type=' ';
    list_of_moves.push_back(desired_move);
        
}
//if enemy was beaten it will return the piece it beaten so the undo move would bring this piece back to life
Piece if_beaten(Piece board[8][8], Move move){
    if(board[move.y_coordinate_target][move.x_coordinate_target].type!=' '){
        return board[move.y_coordinate_target][move.x_coordinate_target]; 
    }
    //returning piece beaten with en passant
    else if(board[move.y_coordinate_target][move.x_coordinate_target].type ==' ' && board[move.y_coordinate_starting][move.x_coordinate_starting].type == 'P' && move.x_coordinate_target!=move.x_coordinate_starting){
        if(board[move.y_coordinate_starting][move.x_coordinate_starting].color){
            return board[move.y_coordinate_target+1][move.x_coordinate_target];
        }
        else{
            return board[move.y_coordinate_target-1][move.x_coordinate_target];
        }
    } 
    return Piece();
}

void undo_move(Piece (&board)[8][8], vector<Move> &previous_moves){
    Move re_move = previous_moves.back();
    previous_moves.pop_back(); 
    int target_x = re_move.x_coordinate_starting;
    int starting_x = re_move.x_coordinate_target;
    int target_y = re_move.y_coordinate_starting;
    int starting_y = re_move.y_coordinate_target;
    Move undo = {starting_y, starting_x, target_y, target_x};
    make_move(board, undo, previous_moves);
    //previous_moves.pop_back(); 
}
//had to extract this piece of code from function is_move_possible because it causes problems with function is_checked
bool is_move_killing_king(Piece board[8][8], Move destination){
    if(board[destination.y_coordinate_target][destination.x_coordinate_target].type=='K')
        return true;
    
    return false;
}

bool game_won(Piece (&board)[8][8], Piece king, vector<Move> previous_moves){
    Move possible_cover;
    if(is_checked(board, king, previous_moves)){
        for(int i = 0; i<8; i++){
            for(int j = 0; j<8; j++){
                if(board[i][j].color==king.color){
                    for(int y = 0; y<8; y++){
                        for(int x = 0; x<8; x++){
                            possible_cover = {i,j,y,x}; 
                            if(is_move_possible(board, possible_cover, king.color, previous_moves)){
                                make_move(board, possible_cover, previous_moves);
                                if(!is_checked(board, king, previous_moves)){
                                    undo_move(board,previous_moves);
                                    return false;
                                }
                                undo_move(board,previous_moves);
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

