/* Libraries */
#include <cstdio> // pretty much everything, input and output only actually thinking about it now
#include <stdlib.h> // i think this will let there be background coloring, i will have to check now, this could be poggers
/*Global Variables*/
char board[16][16]; // our board

/* Function Definitions */
bool update_board(char board[16][16]);
void populate_board(int a, int b);
int main()
{
	system("Color E4");
	populate_board(16,16);
	while( true ) 
	{
		if( update_board(board) != true)
		{
		 break;
		}
	}
	
	return 0;
}


bool update_board(char board[16][16])
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
			printf(" %c", board[i][k]);
		
		}
		printf("\n");
	}
	
	
 	
	return false;
}

void populate_board(int a, int b)// fills up the board based on the specifications of play in board.txt
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
			board[iterator][i] = line[i]; // so this calls the golbal variable board, its messy but it works
		
		}
		iterator++;
	}
	fclose(fp);
	
}
