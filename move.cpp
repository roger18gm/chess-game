/***********************************************************************
 * Source File:
 *    MOVE
 * Author:
 *    <Jessen Forbush, Roger Galan>
 * Summary:
 *    Everything we need to know about a single chess move
 ***********************************************************************/

#include "move.h"
#include "pieceType.h"
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

/***************************************************
 * MOVE : DEFAULT CONSTRUCTOR
 * Initialize a move to be invalid
 ***************************************************/
Move::Move() : promote(SPACE), capture(SPACE), moveType(MOVE_ERROR),
isWhite(false), text(""), enpassant(false), castleK(false),
castleQ(false), error("")
{
   // Make sure the positions are invalid
   source.setInvalid();
   dest.setInvalid();
}

/***************************************************
 * MOVE : STRING CONSTRUCTOR
 * Initialize a move from a text string (e.g., "e5e6")
 ***************************************************/
Move::Move(const string& str) : text(str)
{
   // Use the read method to parse the string
   read(str);
}

/***************************************************
 * MOVE : READ
 * Parse a move string and update this Move object
 ***************************************************/
void Move::read(const string& str)
{
   // Store the original text
   text = str;

   // Check if string is long enough to contain a move
   if (str.length() < 4)
      return;

   // Parse positions
   source = Position(str.substr(0, 2).c_str());
   dest = Position(str.substr(2, 2).c_str());

   // If positions are invalid, return
   if (!source.isValid() || !dest.isValid())
      return;

   // Default to a simple move
   moveType = MOVE;

   // Process special move indicators (5th character, if present)
   if (str.length() >= 5)
      processSpecialMoveChar(str[4]);
}

/***************************************************
 * MOVE : PROCESS SPECIAL MOVE CHAR
 * Helper method to process the special character
 * indicating move type
 ***************************************************/
void Move::processSpecialMoveChar(char specialChar)
{
   switch (specialChar)
   {
   case 'c':  // King-side castle
      setCastle(true);
      break;

   case 'C':  // Queen-side castle
      setCastle(false);
      break;

   case 'E':  // En passant
      setEnPassant();
      capture = PAWN;
      break;
   default:   // Must be a capture or other indicator
      if (islower(specialChar) || specialChar == ' ')
         capture = pieceTypeFromLetter(specialChar);
      break;
   }
}

/***************************************************
 * MOVE : LETTER FROM PIECE TYPE
 * Convert a piece type to the corresponding character
 ***************************************************/
char Move::letterFromPieceType(PieceType pt) const
{
   switch (pt)
   {
   case SPACE:  return ' ';
   case PAWN:   return 'p';
   case KNIGHT: return 'n';
   case BISHOP: return 'b';
   case ROOK:   return 'r';
   case QUEEN:  return 'q';
   case KING:   return 'k';
   default:     return '?';
   }
}

/***************************************************
 * MOVE : PIECE TYPE FROM LETTER
 * Convert a character to the corresponding piece type
 ***************************************************/
PieceType Move::pieceTypeFromLetter(char letter) const
{
   switch (tolower(letter))
   {
   case 'p': return PAWN;
   case 'n': return KNIGHT;
   case 'b': return BISHOP;
   case 'r': return ROOK;
   case 'q': return QUEEN;
   case 'k': return KING;
   case ' ': return SPACE;
   default:  return SPACE;
   }
}

/***************************************************
 * MOVE : SET CASTLE
 * Set this move as a castle move, either king-side
 * or queen-side based on the isKing parameter
 ***************************************************/
void Move::setCastle(bool isKing)
{
   if (isKing)
   {
      castleK = true;
      moveType = CASTLE_KING;
   }
   else
   {
      castleQ = true;
      moveType = CASTLE_QUEEN;
   }
}

/***************************************************
 * MOVE : ASSIGN (MOVE)
 * Copy all properties from another move
 ***************************************************/
void Move::assign(Move& move)
{
   source = move.source;
   dest = move.dest;
   promote = move.promote;
   capture = move.capture;
   moveType = move.moveType;
   isWhite = move.isWhite;
   text = move.text;
   enpassant = move.enpassant;
   castleK = move.castleK;
   castleQ = move.castleQ;
   error = move.error;
}
