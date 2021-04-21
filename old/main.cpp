#include <cstdio>
#include "chess_header.h"

int main()
{
  Board new_board;
  new_board.import_board("board.txt",9);
  new_board.update_board();
  return 0;
}
