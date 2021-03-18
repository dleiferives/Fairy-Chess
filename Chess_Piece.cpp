#include "chess_header.h"

const char * Chess_Piece::retrieve_name(char input) // retrieves the name and also like fills up the id. dont worry about it I guess.
 {
   switch (input)
   {
      case '.' :
        ID = 0;
        return "Empty";
        break;
      case 'Y' :
        ID = 21;
        return "Antelope";
        break;
      case 'i' :
        ID = 1;
        return "Pawn";
        break;
      case '0' :
        ID = 8;
        return "Elephant";
        break;
      case 'M' :
        ID = 9;
        return "Machine";
        break;
      case 'I' :
        ID = 4;
        return "Rook";
        break;
      case 'K' :
        ID = 2;
        return "Knight";
        break;
      case '!' :
        ID = 3;
        return "Bishop";
        break;
      case 'u' :
        ID = 12;
        return "Ship";
        break;
      case '=' :
        ID = 7;
        return "Buffoon";
        break;
      case '+' :
        ID = 5;
        return "King";
        break;
      case '?' :
        ID = 4;
        return "Queen";
        break;
      case 'j' :
        ID = 6;
        return "Centurion";
        break;
      case '%' :
        ID = 10;
        return "Lion";
        break;
      case '@' :
        ID = 11;
        return "Gryphon";
        break;
      case 'C' :
        ID = 13;
        return "Camel";
        break;
      case ')' :
        ID = 15;
        return "Bow";
        break;
      case '<' :
        ID = 20;
        return "Bull";
        break;
      case '/' :
        ID = 14;
        return "Cannon";
        break;
      case ':' :
        ID = 16;
        return "Buffalo";
        break;
      case '1' :
        ID = 22;
        return "Rhinoceros";
        break;
      case '*' :
        ID = 23;
        return "Star";
        break;
      case '#' :
        ID = 19;
        return "Unicorn";
        break;
      case '$' :
        ID = 17;
        return "Dragon Woman";
        break;
      case '&' :
        ID = 18;
        return "Diablo";
        break;
    }
  };
