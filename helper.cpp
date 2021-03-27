#include "chess_header.h"
#include <cstdio>

int c_str_to_int ( char * string , int length ) // reads a string into an integer
{
  int temp=0;
  for(int i =0; i < length; i++)
  {
    if(string[i] == 10) break;
    temp *= 10;
    temp += (string[i]-48);
  }
  return temp;
}

int sign(int x)
{
  return ((x>0) - (x<0));
}
