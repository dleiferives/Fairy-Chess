#include <stdio.h>
#include <stdlib.h>

//lets start with the board render


// ## Defining Types ##
typedef struct piece piece, *s_ptrp; // declaring our structs
typedef struct board board, *s_ptrb; 

struct piece // defining piece
{
  int x;
  int y;
  char type;
  int g_id;
  s_ptrp ptr; // self referencing pointer
};

struct board // defining board
{
  int width;
  int height;
  piece *tiles;
  s_ptrb ptr;// self referencing pointer
};


// ## Function Definitions ##
//prints out the board
int put_board(piece *tiles, int bx,int by)
{
  for(int y =0; y<by; y++)
  {
    for(int x =0; x < bx; x++)
    {
      putchar(tiles[(bx*y) + x].type);
    }

    putchar(10);
  }
}


int init_board(s_ptrb board_p) // from passed board input loads it with default values
{
 // allocating memory for the board's tiles
 piece *aloc_tiles = (piece *) malloc((board_p->width * board_p->height) * sizeof(piece));
 

 // doing the actual initilization, and filling all of the pieces in the board
 for(int x =0; x < board_p->width; x++)
 {
   for(int y =0; y < board_p->height; y++)
   {
     piece temp_piece = {x, y, '.', 0}; // '.'and 0 are the values with nothing at said location
     aloc_tiles[(board_p->width * y) + x] = temp_piece;
   }
 }

 // setting the passed in board's tiles to the allocated pieces done above
 board_p->tiles = aloc_tiles; 
 return 0;
}



// ## Main Function ##

int main()
{
  board board = { 10, 10};
  init_board(&board);
  put_board(board.tiles, board.width, board.height);
  return 0;
}
