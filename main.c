#include <stdio.h>
#include <stdlib.h>
#include <string.h> // memcopy, should probably implement my own version though.

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
  unsigned int g_id: 16; // declaring a sixteen bit int 
  // using a bit field to more effectively manage memory, it will do nothing special, but it is good practice 
  unsigned int side: 1; // 0 for white 1 for black as white goes first
  unsigned int slide_diagonal : 1;
  unsigned int slide_ortho : 1;
  unsigned int jump : 1;
  unsigned int shooter_diagonal : 1;
  unsigned int shooter_ortho : 1;
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
     piece temp_piece = {x, y, '.', 0, 0, 0, 0, 0, 0, 0, 0}; // '.'and 0 are the values with nothing at said location
     aloc_tiles[(board_p->width * y) + x] = temp_piece;
   }
 }

 // setting the passed in board's tiles to the allocated pieces done above
 board_p->tiles = aloc_tiles; 
 return 0;
}

int *slide_ortho(s_ptrb board, int x, int y, int side, int take_last, int j_no_take, int direction, int *len) // len should be accesed by reference, will return via pointer, take means can it move anywhere on its slide, or only on its last position if that is taking.
{
 //direction follows the path, so if it is called from up direction  =1 right =2 down =3 left = 4 0=normal
 //
 //
 //
 int up = y;
 int down = board->height - y;
 int left = x;
 int right = board->width - x;
need to fix the direction array 
 int *direction_arr = {up,down,left,right}; 
 
 len[0] = (take_last == 1) ? 4 : (up+down+left+right);
 len[0] += (j_no_take == 0) ? 0 : 16;
 
 int pointer_pos =0;

 int *result = (int *) malloc(len[0] * sizeof(int));


int start;
int end;
if(direction ==0)
{
  start =1;
  end =4;
}
else
{

}



 for(int v_direction =start; v_direction <= end; v_direction++)
 {
   int v_m = !(v_direction > 2);
   int v_n = !(v_m);
   int v_o = 1-(2*(direction %2));

   for(int i =1; i <= direction_arr[v_direction-1]; i++)
   {
     int m =v_m*i*v_o;
     int n =v_n*i*v_o;
     if(take_last ==1)
     {

       if(board->tiles[(board->width * (y+(m))) + (x+(n))].g_id == 0) continue;
       if(board->tiles[(board->width * (y+(m))) + (x+(n))].side != side)
       {
        result[pointer_pos] = ((board->width *(y+(m) )) + (x+(n))) + 1;
        pointer_pos++;
        break;
       }
       else
       {
         break;
       }
     }
     else // normal piece movment
     {
      if(board->tiles[(board->width * (y+(m))) + (x+(n))].g_id == 0)// if empty add to possible moves
      {
        result[pointer_pos] = ((board->width *(y+(m))) + (x+(n))) + 1;
        pointer_pos++;
        continue;
      
      }
      else
      {
        if((j_no_take !=0) )
        {
           int meta_len =0;
           if(j_no_take == 1)
           {
//             *result[pointer_pos] = slide_ortho(board, x, y-(i+1), side, 1, 0, 1, &meta_len); // getting cannon pos up
             int * copy_array = (int *) malloc(10*sizeof(int));
               copy_array = slide_ortho(board, (x+(n)) , y+(m), side , 1, 0, v_direction, &meta_len); 
             for(int j =0; j < meta_len; j++)
             {
               result[pointer_pos+j] = copy_array[j];

             }
             pointer_pos += meta_len;
           }
           if(j_no_take == 2)
           {
             //for the diagonal checks... i dont think any pieces actually do that, however, if they do, wouldent that be cool.
           }
           break;
 
         }
         else
         {
           // not a cannon or something cannon like
           if(board->tiles[(board->width * y+(m)) + (x+(n))].side != side)
           {
             result[pointer_pos] = ((board->width *(y+(m))) + (x+(n))) + 1;
             pointer_pos++;
             break;
           }
           else // don't take same sides peice
           {
           }
         }
       }
     }
   }
 }


 for(int i=pointer_pos; i< (len[0]); i++)
 {
   result[i] = 0;
 }

 return result;
 
}






int *generate_moves(s_ptrb board, piece p)
{
 int *result;  
 return result;
}



int check_move(s_ptrb board, piece p, int pos, int t_pos)
{
 if(p.slide_ortho == 1)
 {
  int len =0;
  int *array = slide_ortho(board, p.x, p.y, p.side, 0, p.shooter_ortho, 0, &len);
  for( int i =0; i < len; i++)
  {
    if(array[i] == 0) continue;
   // printf("\n %i %i", array[i]-1, i); // can be used to print out the positions stuff tries to move t0
    //board->tiles[array[i]-1].type = '#';
    if(t_pos == array[i]-1)
    {
      move_piece(board, pos, t_pos); 
      puts("pogchamp");
      return 1;
    }
  }
 }
 return 0;
}

int move_piece(s_ptrb board, int pos_init, int pos_final)
{
  piece final = board->tiles[pos_final];
  piece init = board->tiles[pos_init];
  piece empty = {init.x, init.y, '.', 0,0,0,0,0,0,0};

  printf("\n %c,%c,%c", board->tiles[pos_final].type, board->tiles[pos_init].type,empty.type);

  final.type = init.type;
  final.g_id = init.g_id;
  final.side = init.side;
  final.slide_diagonal = init.slide_diagonal;
  final.slide_ortho = init.slide_ortho;
  final.jump = init.jump;
  final.shooter_diagonal = init.shooter_diagonal;
  final.shooter_ortho = init.shooter_ortho;
  
  board->tiles[pos_init] = empty;
  board->tiles[pos_final] = final;

  printf("\n %c,%c,%c", board->tiles[pos_final].type, board->tiles[pos_init].type,empty.type);
  return 1;


}

// ## Main Function ##

int main()
{
  board board = {10, 10};
  init_board(&board);
  board.tiles[21].type = 'n';
  board.tiles[21].g_id = 1;
  board.tiles[21].slide_ortho = 1;
  board.tiles[21].shooter_ortho =1;
  
  //preloading some pieces
  board.tiles[23].type = '@';
  board.tiles[23].g_id =1;
  board.tiles[23].side = 1;

  board.tiles[26].type = 'x';
  board.tiles[26].side = 1;
  board.tiles[26].g_id = 2;

  put_board(board.tiles, board.width, board.height);
  printf(" %i \n", check_move(&board, board.tiles[21], 21, 26));

  put_board(board.tiles, board.width, board.height);

  return 0;
}
