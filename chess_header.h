#include <cstdio>
#pragma once


template <class T>
class pair
{
  public:
    T obs[2];
    pair(T first, T second) {obs[0] = first; obs[1] = second;}
};

struct Point
{
  int x;
  int y;
};


class Piece
{
  public:
    // Variables
    Point pos; // the location of the piece
    int g_Id = 0; // the global identifier for the piece ( - = black, + = white)
    char character = '.'; // the character that represents the piece
    float value; // not sure if this will be usefull, however for AI?


    //Functions

    //to get the side of a piece just do the following bitwise operation (n >> 32) & 1;   
};


class Board
{
  public:
   Piece * pieces; // the pointer that holds all the pieces
   Piece * tiles; // the pointer that is the board, but is called tiles for readability 
   int num_pieces; // the number of pieces that are on the board
   int width =0;//to be overwritten
   int height =0; //to be overwritten
   pair<Piece*> import_board(char* file_name, int length);
   bool update_board();
};

int c_str_to_int ( char * string , int length );

int sign(int x);
