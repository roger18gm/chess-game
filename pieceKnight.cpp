/***********************************************************************
 * Source File:
 *    KNIGHT
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The KNIGHT class
 ************************************************************************/

#include "pieceKnight.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Knight::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawKnight(position, !isWhite());
   }
}


/**********************************************
 * KNIGHT : GET POSITIONS
 *********************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   // Knight moves in L-shape
   const int moveOffsets[8][2] = {
      {-2, -1}, {-2, 1},  // 2 left, 1 down/up
      {-1, -2}, {-1, 2},  // 1 left, 2 down/up
      {1, -2},  {1, 2},   // 1 right, 2 down/up
      {2, -1},  {2, 1}    // 2 right, 1 down/up
   };

   // Get current position
   int col = position.getCol();
   int row = position.getRow();

   // Check each possible move
   for (int i = 0; i < 8; i++)
   {
      int newCol = col + moveOffsets[i][0];
      int newRow = row + moveOffsets[i][1];

      // Check if new position is on the board
      Position posNew(newCol, newRow);
      if (posNew.isValid())
      {
         // Create the move
         Move move;
         move.setSrc(position);
         move.setDest(posNew);

         // Check what's at the destination position
         const Piece& pieceDestination = board[posNew];
         move.setCapture(pieceDestination.getType());

         // If destination is empty (SPACE) or has an enemy piece, it's a valid move
         if (move.getCapture() == SPACE ||
            pieceDestination.isWhite() != isWhite())
         {
            moves.insert(move);
         }
      }
   }
}