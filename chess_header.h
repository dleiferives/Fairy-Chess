#include <cstdio> // pretty much everything, input and output only actually thinking about it now
#pragma once // makes it so the fat kid we all love dosent go out and lose all that weight, oh shucks that was a bad thing to write. No idea where that came from. Anywyas, this makes it so that the header cannot be called twice in a file.

// the defitnition for the code that resides in Chess_Piece.cpp
struct pos
{
  int x;
  int y;
};

struct Chess_Piece
{
  char character; // the thing that gets put onto the board
  int ID; // id that represents the character
  int g_ID = 404; // The global 
  pos pos;
  bool state; // if the thing is alive or if it is dead. Dunno if it will be usefull
const char * retrieve_name(char input); // retrieves the name for the character that is at a position in the board, ye and also like fills up the id. dont worry about it I guess.

};


//the defitnition for what resides in Chess_Board.cpp
class Chess_Board
{
  public:
    Chess_Piece board[16][16];
    Chess_Piece sides[2][64];
    /* Function Definitions */
    bool update_board();
    void populate_board(int a, int b); // the parenthisis are done to make the array be passed by reference and not an array of reference ask Dylan for improper clarification  
    bool move_piece(int g_ID, pos future); 
    // global id so we can pin down the piece and the side, the current pos and future pos we can then use to determine if the move is possible as we now know the peice.
    int get_gID(pos check_pos);
};  
   
