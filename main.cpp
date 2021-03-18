//Notes, return in Chess_Board::update_board should be eventually changed to true and not false, only false on error, in this moment it is true so that testing is easier.

/* Libraries */
#include <cstdio> // pretty much everything, input and output only actually thinking about it now
#include "chess_header.h" // this includes the classes/Structs/ Cpp files Chess_Board and Chess_Piece
//think about including termcolor library to do color if thats a thing that is wanted. 

int main()
{
  Chess_Board new_board;
  new_board.populate_board(16,16);
  
  while( true ) 
  {
    new_board.move_piece(0,{8,8});
    if( new_board.update_board() != true)
    {
     break;
    }
  }
  
  return 0;
}

