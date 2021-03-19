#include <cstdio>
#include "chess_header.h"

bool Chess_Board::update_board()
{
  printf("   A B C D E F G H I J K L M N O P\n");//prints out the top of the board
  for(int i =0; i< 16; i++)
  {
  if( (i+1) < 10 ) // doing the numbers on the side
    {
      printf(" %i", (i+1) );
    }
    else
    {
      printf("%i", (i+1) );
    }
    
    for(int k =0; k < 16; k++)
    {
      printf(" %c", board[i][k].character);
      //board[i][k].retrieve_name(board[i][k].character);
      //printf(" %i", board[i][k].ID);
      //printf("%s",board[i][k].retrieve_name(board[i][k].character)); // so this is really messy, kind of an L tho not going to lie. prints out name of piece next to the piece
    }
    printf("\n");
  }
  
  
   
  return false; // this returns false so that the code will only go through one cycle, if the rest of the code is working change this to true unless error.
}

void Chess_Board::populate_board(int a, int b)// fills up the board based on the specifications of play in board.txt
{
  FILE* fp = fopen("board.txt", "r"); // opens the file in reading mode
  if (fp == NULL) // if there isnt L errors
  {
    printf("shucks");
  }
  char *line = NULL; // amount of characters in line 16+ newline
  size_t len = 16; // sixteen we dont want the newline
  
  int iterator =0;
  int iterator2 =0;
  while ((getline(&line, &len, fp)) != -1) 
  {  
    for( int i =0; i<b; i++)
    {
      if(iterator>= (a))
      {
        break;
      }
      board[iterator][i].character = line[i]; //This no longer is a global variablewe are good my thadd. 
      if(line[i] != '.')
      {
        if(iterator2 < 64)
	{
	  board[iterator][i].g_ID = iterator2; // we are declaring each of the peices to their sides now, Im sure that for switching white and black we can just make the sides of the array they are stored to change.
	  board[iterator][i].pos = {i,iterator};
	  sides[0][iterator2] = board[iterator][i];
	}
	else
	{
          board[iterator][i].g_ID = iterator2;
	  board[iterator][i].pos = {i,iterator};
          sides[1][iterator2-64] = board[iterator][i];
	}
        iterator2++;
      }
    
    }
    iterator++;
  }
  fclose(fp);
  
}
// this is going to be a big momma milker of a function... so the groundwork is laid out now, need to actually write the restrictions now.
bool Chess_Board::move_piece(int g_ID, pos future)
{
  bool side;
  // first pin down the piece
  side = (g_ID < 64) ? 0 : 1;
  pos current = sides[side][g_ID - (side*64)].pos; 
  // check if the move is possible.... not doing that yet
  // add character to where it wants to go
  board[future.y][future.x] = sides[side][g_ID - (side*64)];
  // change character in old position to an empty one.	
  board[current.y][current.x].character = '.'; // resets the character to an empty one
  board[current.y][current.x].g_ID = 404; // resets the g_ID so that it does not error on finding the proper position.
  sides[side][g_ID - (side*64)].pos = future; 
  return side;
}

int Chess_Board::get_gID(pos check_pos)
{
  return board[check_pos.y][check_pos.x].g_ID;
}

//so I think that for the rest of this movment code how it will work is that for each piece it will calculate all of the possible moves that can be made when a move is requested, and if the move falls within one of those it will execute the move.
/*
 *
 *potential squares are labed with a pound sign and take squares are with a % sign
 *
 *	
 * . . . . . . . . . . 	
 * . . . . . i . . . . 
 * . . . . % # % . . . 
 * . . . . . # . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * checks, #1 line 4 can move 2 down or up, first have to detrmine way of movement. 
 *
 *so if the thing is positive then we normally go negative and then multiply with a negative. 
 *that means we can determine which way something moves (vertically with) n += 1 + (side* (-2));
 *
 *tries to move to 
bool move_pawn(int g_ID, pos current, pos future, bool side)
{
  int v_it += 1 + (side* (-2)); // the vertical iterator    
  if(get_gID(future) != 404) // aka if this is a piece
  {
    if(({current.x + 1,current.y + v_it} || {current.x - 1, current.y + v_it}) == future)
    {
      return true; // will eventually have to check for check, but I really dont know how to do that in this moment, will be implemented when i figure this out more.
    }
    else
    {
      return false;
    }
  }
  else
  {
    int pawn_line = (side == 0) ? 3 : 12;
    bool pawn_line_bool = 0;
    if( pawn_line == current.y){pawn_line_bool = 1;}
    if((current.x == future.x) && (current.y == (future.y - v_it)|| ((pawn_line_bool == 1) && (current.y == future.y - (2*v_it)))))
    {
      return true;
    }
    else
    {
      return false;
    }
  }


}
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 *
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 *
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 *
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 *
 *
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 *
 *
 * . . . . . . . . . . 	
 * . . . . . . . . . . 
 * . . . . . . . . . . 
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 * . . . . . . . . . .
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * /
