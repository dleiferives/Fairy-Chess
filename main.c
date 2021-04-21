#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) ((a >b) ? b : a)


//lets start with the board render


// ## Defining Types ##
typedef struct piece piece, *s_ptrp; // declaring our structs
typedef struct board board, *s_ptrb; 

struct piece // defining piece
{
  int x;
  int y;
  char type;
  // might replace with a bit field, not sure yet though
  int g_id;
  s_ptrp ptr; // self referencing pointer
  // using a bit field to more effectively manage memory, it will do nothing special, but it is good practice 
  unsigned int slide_diagonal : 1;
  unsigned int slide_ortho : 1;
  unsigned int jump : 1;
  
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

int check_move(s_ptrb board, piece p, int p2x, int p2y)
{
 if(p.slide_diagonal == 1)
 {
   // generate all diagonal positions, 
   //diagonal up left
   int tl = MIN(p.x, p.y); // top left 
   int tr = MIN(board->width - p.x, p.y); // top right
   int br = MIN(board->width - p.x, (board->height) - p.y); // bottom right
   int bl = MIN(p.x, board->height -p.y); // bottom left
    

   printf("x:%i  y:%i  bl:%i  tl:%i  tr:%i  br:%i\n width:%i  height:%i", p.x, p.y, bl, tl, tr, br, board->width, board->height);
   if(0 < ((p2y-p.y)*(p2x - p.x)))
   {
    for(int i =0; i <tl; i++) // down left
    {
      //testing
      board->tiles[((p.y - (i+1))*board->width) +p.x -(i+1)].type = '#';
      //testing end
      if( (p2x == (p.x - (i+1))) && ( p2y == (p.y -(i+1))) )
      {
      //  return 1;
      }
    }
    for(int i =0; i < br; i++)
    {
      board->tiles[((p.y + (i+1))*board->width) +p.x +(i+1)].type = '#';

      if( (p2x == (p.x + (i+1))) && (p2y == (p.y + (i+1))) )
      {
        //return 1;
      }
    }
   //}
  // else
   //{

    for(int i =0; i <bl; i++) // down left
    {
      //testing
      board->tiles[((p.y + (i+1))*board->width) +p.x -(i+1)].type = '#';
      //testing end
      if( (p2x == (p.x - (i+1))) && ( p2y == (p.y +(i+1))) )
      {
      //  return 1;
      }
    }
    for(int i =0; i < tr; i++)
    {
      board->tiles[((p.y - (i+1))*board->width) +p.x +(i+1)].type = '#';

      if( (p2x == (p.x + (i+1))) && (p2y == (p.y - (i+1))) )
      {
        //return 1;
      }
    }
   }




 }
 return 0;
}

int move_piece()
{

}

// ## Main Function ##

int main()
{
  board board = {10, 10};
  init_board(&board);
  board.tiles[11].type = 'n';
  board.tiles[11].g_id = 1;
  board.tiles[11].slide_diagonal = 1;
  printf(" %i \n", check_move(&board, board.tiles[11], 4, 4));

  put_board(board.tiles, board.width, board.height);

  return 0;
}
