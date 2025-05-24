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
const Piece& Piece::operator = (const Piece& rhs)
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

/***************************************************
* PIECE : GEN MOVES SLIDE
***************************************************/
set<Move> Piece::getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const
{
   set <Move> moves;
   for (int i = 0; i < numDelta; i++)
   {
      Position posMove(position, deltas[i]);
      while (posMove.isValid() && board[posMove] == SPACE)
      {
         Move move;
         move.setSrc(position);
         move.setDest(posMove);
         move.setWhiteMove(isWhite());
         moves.insert(move);

         posMove += deltas[i];
      }

      if (posMove.isValid() && board[posMove].isWhite() != fWhite)
      {
         Move move;
         move.setSrc(position);
         move.setDest(posMove);
         move.setWhiteMove(isWhite());
         if (board[posMove] != SPACE)
            move.setCapture(board[posMove].getType());
         moves.insert(move);
      }
   }

   return moves;
}


/***************************************************
* PIECE : GEN MOVES NO SLIDE
*               From a list of deltas, find all the
*               possible moves
***************************************************/
set <Move> Piece::getMovesNoSlide(const Board& board,
   const Delta deltas[],
   int numDelta) const
{
   set<Move> moves;
   for (int i = 0; i < numDelta; i++)
   {
      Position posMove(position, deltas[i]);
      if (posMove.isValid())
      {
         const Piece& targetPiece = board[posMove];

         // Can move to empty space or capture enemy piece
         if (targetPiece == SPACE || targetPiece.isWhite() != fWhite)
         {
            Move move;
            move.setSrc(getPosition());
            move.setDest(posMove);
            move.setWhiteMove(isWhite());
            if (targetPiece != SPACE)
               move.setCapture(targetPiece.getType());
            moves.insert(move);
         }
      }

   }
   return moves;
}
