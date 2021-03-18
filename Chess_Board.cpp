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
  while ((getline(&line, &len, fp)) != -1) 
  {  
    for( int i =0; i<b; i++)
    {
      if(iterator>= (a))
      {
        break;
      }
      board[iterator][i].character = line[i]; // so this calls the golbal variable board, its messy but it works
    
    }
    iterator++;
  }
  fclose(fp);
  
}
