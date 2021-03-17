/* Libraries */
#include <cstdio> // pretty much everything, input and output only actually thinking about it now
//think about including termcolor library to do color if thats a thing that is wanted. 

/* Struct Definitions */
struct chess_piece
{
  char character; // the thing that gets put onto the board
  int ID; // id that represents the character
  int x; // the position on the board the x
  int y; // the position on the board the y
  
const char * retrieve_name(char input) // retrieves the name and also like fills up the id. dont worry about it I guess.
 {
   switch (input)
   {
     case '.' :
      return "Empty";
      break;
     case 'Y' :
      return "Antelope";
      break;
     case 'i' :
      return "Pawn";
      break;
     case '0' :
      return "Elephant";
      break;
     case 'M' :
      return "Machine";
      break;
     case 'I' :
      return "Rook";
      break;
     case 'K' :
      return "Knight";
      break;
     case '!' :
      return "Bishop";
      break;
     case 'u' :
      return "Ship";
      break;
     case '=' :
      return "Buffoon";
      break;
     case '+' :
      return "King";
      break;
     case '?' :
      return "Queen";
      break;
     case 'j' :
      return "Centurion";
      break;
     case '%' :
      return "Lion";
      break;
     case '@' :
      return "Gryphon";
      break;
     case 'C' :
      return "Camel";
      break;
     case ')' :
      return "Bow";
      break;
     case '<' :
      return "Bull";
      break;
     case '/' :
      return "Cannon";
      break;
     case ':' :
      return "Buffalo";
      break;
     case '1' :
      return "Rhinoceros";
      break;
     case '*' :
      return "Star";
      break;
     case '#' :
      return "Unicorn";
      break;
     case '$' :
      return "Dragon Woman";
      break;
     case '&' :
      return "Diablo";
      break;
   }
 };

};

/*Global Variables*/
chess_piece board[16][16]; // our board

/* Class Definitions */

class Chess_Board
{
  public:
    /* Function Definitions */
    bool update_board(chess_piece board[16][16]);
    void populate_board(int a, int b);  
};  
   
/* Class Methods */
//chess board  
bool Chess_Board::update_board(chess_piece board[16][16])
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
      //printf("%s",board[i][k].retrieve_name(board[i][k].character)); // so this is really messy, kind of an L tho not going to lie. prints out name of piece next to the piece
    }
    printf("\n");
  }
  
  
   
  return false;
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

/* Methods */


int main()
{
  Chess_Board new_board;
  new_board.populate_board(16,16);
  
  while( true ) 
  {
    if( new_board.update_board(board) != true)
    {
     break;
    }
  }
  
  return 0;
}

