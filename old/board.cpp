#include "chess_header.h"
#include <cstdio>

pair<Piece*> Board::import_board(char * file_name, int length)//string that is board name, length of said string.??
{
  file_name = "board.txt";
  //here we will be reading in the specifications of the board that will be read in
  FILE * file_pointer;
  char s_width[10];//string width
  char s_height[10];//string height
  file_pointer = fopen(file_name,"r");
  
  if(file_pointer == NULL) printf("you messed up bud"); 
  
  if ( fgets(s_width,10,file_pointer) != NULL)
    {width = c_str_to_int(s_width , 10);}
  
  if( fgets(s_height,10,file_pointer) != NULL)
    {height = c_str_to_int(s_height, 10);}
  
  Piece * quick = new Piece[width*height];
  tiles = quick;

  delete [] quick;

  //reading white
  printf("Reading White\n");
  char * buffer_width = new char[width+1];
  for(int y =0; y < height; y++ )
  {
    if(fgets(buffer_width,width+2,file_pointer) != NULL)
    { 
      for(int x =0; x < width; x++ )
      {
        printf(" %c",buffer_width[x]); 
      }
    }
    printf("\n");  
  }

  //reading black
  printf("Reading Black\n");
  for(int y =0; y < height; y++ )
  {
    if(fgets(buffer_width,width+2,file_pointer) != NULL)
    { 
      for(int x =0; x < width; x++ )
      {
        printf(" %c",buffer_width[x]);
        tiles[(y*height)+x].character = buffer_width[x];	
      }
    }
    printf("\n");   
  }

  fclose(file_pointer);
  delete[] buffer_width;

  
}

bool Board::update_board()
{
  char * s_board = new char[(width+1)*height];
  for(int i =0; i < height; i++)
  {
    for(int j =0; j<width; j++)
    {
      s_board[(i*height)+j] = tiles[i].character;
    }
    s_board[(i*height)+width] = 10;
  }
  puts(s_board);
  return true;
}
