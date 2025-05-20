/***********************************************************************
 * Source File:
 *    PIECE 
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#include "position.h"  // for POSITION
#include "piece.h"     // for all the PIECE class definitions
#include "pieceSpace.h"
#include "pieceKnight.h"
#include "board.h"     // for BOARD
#include "uiDraw.h"    // for draw*()
#include <cassert>     // because we are paranoid
using namespace std;


/************************************************
 * PIECE : ASSIGN
 ***********************************************/
const Piece & Piece::operator = (const Piece & rhs)
{
   // Check for self-assignment
   if (this == &rhs)
      return *this;

   // Copy the values
   this->position = rhs.position;
   this->fWhite = rhs.fWhite;
   this->nMoves = rhs.nMoves;
   this->lastMove = rhs.lastMove;

   // Return a reference to the current object
   return *this;
}

/************************************************
 * PIECE : GET MOVES
 * Iterate through the moves decorator to allow a piece to move
 ***********************************************/
void Piece::getMoves(set <Move> & movesSet, const Board & board) const
{
}

