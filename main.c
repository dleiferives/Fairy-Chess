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
 len[0] = (take_last == 1) ? 4 : (up+down+left+right);
 len[0] += (j_no_take == 0) ? 0 : 16;
 
 int pointer_pos =0;

 int *result = (int *) malloc(len[0] * sizeof(int));

 if( (direction == 1) || (direction == 0))
 {
   for(int i =1; i <= up; i++)
   {
     puts("up");
     if(take_last ==1)
     {
       puts("test");
       if(board->tiles[(board->width * (y-(i))) + (x+0)].g_id == 0) continue;
       if(board->tiles[(board->width * (y-(i))) + (x+0)].side != side)
       {
        result[pointer_pos] = ((board->width *(y-(i) )) + (x+0)) + 1;
          printf("\ntake last %i %i %i %i", (x+0), y-(i), board->width*(y-(i)) + (x+0), result[pointer_pos]);
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
      if(board->tiles[(board->width * y-(i)) + (x+0)].g_id == 0)// if empty add to possible moves
      {
        result[pointer_pos] = ((board->width *(y-(i))) + (x+0)) + 1;
          printf("\nempty: %i %i %i %i", (x+0), y-(i), board->width*(y-(i)) + (x+0), result[pointer_pos]);
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
               copy_array = slide_ortho(board, (x+0) , y-(i), side , 1, 0, 1, &meta_len); 
             for(int j =0; j < meta_len; j++)
             {
               result[pointer_pos+j] = copy_array[j];
               printf("\ncopy_array: %i", copy_array[j]);

             }
          printf("\ndsfds %i %i %i %i %i", (x+0), y-(i), board->width*(y-(i)) + (x+0), result[pointer_pos], meta_len);
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
           if(board->tiles[(board->width * y-(i)) + (x+0)].side != side)
           {
             result[pointer_pos] = ((board->width *(y-(i))) + (x+0)) + 1;
             printf("\ntaking: %i %i %i %i", (x+0), y-(i), board->width*(y-(i)) + (x+0), result[pointer_pos]);
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

 if( (direction == 2) || (direction == 0))
 {
   for(int i =1; i < right; i++)
   {
     puts("right");
     if(take_last ==1)
     {
       puts("test");
       if(board->tiles[(board->width * (y )) + (x+i)].g_id == 0) continue;
       if(board->tiles[(board->width * (y )) + (x+i)].side != side)
       {
        result[pointer_pos] = ((board->width *(y )) + (x+i)) + 1;
          printf("\n %i %i %i %i", (x+i), y, board->width*(y) + (x+i), result[pointer_pos]);
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
      if(board->tiles[(board->width * y) + (x+i)].g_id == 0)// if empty add to possible moves
      {
        result[pointer_pos] = ((board->width *(y)) + (x+i)) + 1;
          printf("\n %i %i %i %i", (x+i), y, board->width*(y) + (x+i), result[pointer_pos]);
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
               copy_array = slide_ortho(board, (x+i) , y, side , 1, 0, 2, &meta_len); 
             for(int j =0; j < meta_len; j++)
             {
               result[pointer_pos+j] = copy_array[j];
               printf("\ncopy_array: %i", copy_array[j]);

             }
          printf("\ndsfds %i %i %i %i %i", (x+i), y, board->width*(y) + (x+i), result[pointer_pos], meta_len);
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
           if(board->tiles[(board->width * y) + (x+i)].side != side)
           {
             result[pointer_pos] = ((board->width *(y)) + (x+i)) + 1;
             printf("\n %i %i %i %i", (x+i), y, board->width*(y) + (x+i), result[pointer_pos]);
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


 if( (direction == 4) || (direction == 0))// going left
 {
   printf("LEFT %i", left);
   for(int i =1; i <= left; i++)
   {
     puts("left");
     if(take_last ==1)
     {
       puts("test");
       if(board->tiles[(board->width * (y )) + (x-i)].g_id == 0) continue;
       if(board->tiles[(board->width * (y )) + (x-i)].side != side)
       {
        result[pointer_pos] = ((board->width *(y )) + (x-i)) + 1;
          printf("\n %i %i %i %i", (x-i), y, board->width*(y) + (x-i), result[pointer_pos]);
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
      if(board->tiles[(board->width * y) + (x-i)].g_id == 0)// if empty add to possible moves
      {
        result[pointer_pos] = ((board->width *(y)) + (x-i)) + 1;
          printf("\n %i %i %i %i", (x-i), y, board->width*(y) + (x-i), result[pointer_pos]);
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
               copy_array = slide_ortho(board, (x-i) , y, side , 1, 0, 4, &meta_len); 
             for(int j =0; j < meta_len; j++)
             {
               result[pointer_pos+j] = copy_array[j];
               printf("\ncopy_array: %i", copy_array[j]);

             }
          printf("\ndsfds %i %i %i %i %i", (x-i), y, board->width*(y) + (x-i), result[pointer_pos], meta_len);
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
           if(board->tiles[(board->width * y) + (x-i)].side != side)
           {
             result[pointer_pos] = ((board->width *(y)) + (x-i)) + 1;
             printf("\n %i %i %i %i", (x-i), y, board->width*(y) + (x-i), result[pointer_pos]);
             pointer_pos++;
             break;
           }
           else // don't take same sides peice
           {
            // result[pointer_pos] = 0;
            // printf("\n %i %i %i %i", (x+i), y, board->width*(y) + (x+i), result[pointer_pos]);
            // pointer_pos++;
            // break;
           }
         }
       }
     }
   }
 }



 if( (direction == 3) || (direction == 0))
 {

   for(int i =1; i <= down; i++)
   {
     puts("down");
     printf("\nDOWN %i %i %i", down, take_last, board->tiles[40].g_id);
     if(take_last ==1)
     {
       puts("test");
       if(board->tiles[(board->width * (y+(i))) + (x+0)].g_id == 0) continue;
       if(board->tiles[(board->width * (y+(i))) + (x+0)].side != side)
       {
        result[pointer_pos] = ((board->width *(y+(i) )) + (x+0)) + 1;
          printf("\ntake last %i %i %i %i", (x+0), y+(i), board->width*(y+(i)) + (x+0), result[pointer_pos]);
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
          printf("\nnot jumping: %i %i %i %i %i", (x+0), y+(i), board->width*(y+(i)) + (x+0), result[pointer_pos], board->tiles[(board->width * y+(i)) + (x+0)].g_id );
      if(board->tiles[(board->width * (y+(i))) + (x+0)].g_id == 0)// if empty add to possible moves
      {
        result[pointer_pos] = ((board->width *(y+(i))) + (x+0)) + 1;
          printf("\nempty: %i %i %i %i", (x+0), y+(i), board->width*(y+(i)) + (x+0), result[pointer_pos]);
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
               copy_array = slide_ortho(board, (x+0) , y+(i), side , 1, 0, 1, &meta_len); 
             for(int j =0; j < meta_len; j++)
             {
               result[pointer_pos+j] = copy_array[j];
               printf("\ncopy_array: %i", copy_array[j]);

             }
          printf("\ndown dsfds %i %i %i %i %i", (x+0), y+(i), board->width*(y+(i)) + (x+0), result[pointer_pos], meta_len);
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
           if(board->tiles[(board->width * y+(i)) + (x+0)].side != side)
           {
             result[pointer_pos] = ((board->width *(y+(i))) + (x+0)) + 1;
             printf("\ntaking: %i %i %i %i", (x+0), y+(i), board->width*(y+(i)) + (x+0), result[pointer_pos]);
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



int check_move(s_ptrb board, piece p, int pos)
{
 if(p.slide_ortho == 1)
 {
  int len =0;
  int *array = slide_ortho(board, p.x, p.y, p.side, 0, p.shooter_ortho, 0, &len);
  for( int i =0; i < len; i++)
  {
    if(array[i] == 0) continue;
    printf("\n %i %i", array[i]-1, i);
    board->tiles[array[i]-1].type = '#';
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

  printf(" %i \n", check_move(&board, board.tiles[21], 21));

  put_board(board.tiles, board.width, board.height);

  return 0;
}
