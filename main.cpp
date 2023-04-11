#include "chess.hpp"


int main(){
    
    bool white = true;
    bool black = false;
    bool mate = false;

    Move first_element_of_list = {0,0,0,0};
    vector<Move> previous_moves;
    previous_moves.push_back(first_element_of_list);
    Move move_user;
    Piece beaten_piece;

    //white pieces
    Piece king_white = Piece(7, 4, white, 'K');
    Piece queen_white = Piece(7, 3, white, 'Q');
    Piece bishop_white_first = Piece(7, 2, white, 'B');
    Piece knight_white_first = Piece(7, 1, white, 'H');
    Piece rook_white_first = Piece(7, 0, white, 'R');
    Piece rook_white_second = Piece(7, 7, white, 'R');
    Piece knight_white_second = Piece(7, 6, white, 'H');
    Piece bishop_white_second = Piece(7, 5, white, 'B');
    //white pawns
    Piece pawn_white_first = Piece(6, 0, white, 'P');
    Piece pawn_white_second = Piece(6, 1, white, 'P');
    Piece pawn_white_third = Piece(6, 2, white, 'P');
    Piece pawn_white_fourth = Piece(6, 3, white, 'P');
    Piece pawn_white_fifth = Piece(6, 4, white, 'P');
    Piece pawn_white_sixth = Piece(6, 5, white, 'P');
    Piece pawn_white_seventh = Piece(6, 6, white, 'P');
    Piece pawn_white_eight = Piece(6, 7, white, 'P');

    //black pieces
    Piece king_black = Piece(0, 4, black, 'K');
    Piece queen_black = Piece(0, 3, black, 'Q');
    Piece bishop_black_first = Piece(0, 2, black, 'B');
    Piece knight_black_first = Piece(0, 1, black, 'H');
    Piece rook_black_first = Piece(0, 0, black, 'R');
    Piece rook_black_second = Piece(0, 7, black, 'R');
    Piece knight_black_second = Piece(0, 6, black, 'H');
    Piece bishop_black_second = Piece(0, 5, black, 'B');
    //black pawns
    Piece pawn_black_first = Piece(1, 0, black, 'P');
    Piece pawn_black_second = Piece(1, 1, black, 'P');
    Piece pawn_black_third = Piece(1, 2, black, 'P');
    Piece pawn_black_fourth = Piece(1, 3, black, 'P');
    Piece pawn_black_fifth = Piece(1, 4, black, 'P');
    Piece pawn_black_sixth = Piece(1, 5, black, 'P');
    Piece pawn_black_seventh = Piece(1, 6, black, 'P');
    Piece pawn_black_eight = Piece(1, 7, black, 'P');

    Piece board[8][8] = {{rook_black_first,knight_black_first,bishop_black_first,queen_black,king_black,bishop_black_second,knight_black_second,rook_black_second},{pawn_black_first,pawn_black_second,pawn_black_third,pawn_black_fourth,pawn_black_fifth,pawn_black_sixth,pawn_black_seventh,pawn_black_eight},{Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece()},{Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece()},{Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece()},{Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece(),Piece()},{pawn_white_first,pawn_white_second,pawn_white_third,pawn_white_fourth,pawn_white_fifth,pawn_white_sixth,pawn_white_seventh,pawn_white_eight},{rook_white_first,knight_white_first,bishop_white_first,queen_white,king_white,bishop_white_second,knight_white_second,rook_white_second}};
    print_board(board);

    while(!mate){
        bool not_proper_move = true;
        //bool is_move_possible(Piece board[8][8], Move target, bool side, vector<Move> previous_moves);
        while(not_proper_move){
            move_user = move_input();
            if(is_move_possible(board, move_user, white, previous_moves) && !is_move_killing_king(board,move_user)){
                not_proper_move = false;
                beaten_piece = if_beaten(board, move_user);    
                make_move(board,move_user,previous_moves);
                if(is_checked(board, king_white, previous_moves)){
                    undo_move(board, previous_moves);
                    board[move_user.y_coordinate_target][move_user.x_coordinate_target] = beaten_piece;
                    cout<<"Cant move like this because of check. Try again."<<endl;
                    not_proper_move = true;
                }
                promotion(board, previous_moves);     
            }
            else{
                cout<<"Move is not possible, try again:"<<endl;
            }
        }
        not_proper_move = true;
        print_board(board);
        if(game_won(board, king_black, previous_moves)){
            cout<<"White won, good job!";
            system("PAUSE");
            return 0;
        }
        
        //void make_move(Piece (&board)[8][8], Move desired_move, vector<Move> list_of_moves, bool side)
        while(not_proper_move){
            move_user = move_input();
            if(is_move_possible(board, move_user, black , previous_moves) && !is_move_killing_king(board,move_user)){
                not_proper_move = false;
                beaten_piece = if_beaten(board, move_user);
                make_move(board,move_user,previous_moves);
                if(is_checked(board, king_black, previous_moves)){
                    undo_move(board, previous_moves);
                    board[move_user.y_coordinate_target][move_user.x_coordinate_target] = beaten_piece;
                    cout<<"Cant move like this because of check. Try again."<<endl;
                    not_proper_move = true;
                }
                promotion(board, previous_moves);   
            }
            else{
                cout<<"Move is not possible, try again:"<<endl;
            }
        }
        print_board(board);
        if(game_won(board, king_black, previous_moves)){
            cout<<"White won, good job!";
            system("PAUSE");
            return 0;
        }   
    }
    return 0;
}