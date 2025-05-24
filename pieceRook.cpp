/***********************************************************************
 * Source File:
 *    ROOK
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The ROOK class
 ************************************************************************/

#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * ROOK: PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Rook::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawRook(position, !isWhite());
   }
}


/**********************************************
 * ROOK : GET POSITIONS
 *************************************************/
void Rook::getMoves(set <Move>& moves, const Board& board) const
{
   const Delta delta[] =
   {
                { 0,  1 },
      { -1,  0 },            { 1,  0 },
                { 0, -1 }
   };

   moves = getMovesSlide(board, delta, sizeof(delta) / sizeof(delta[0]));
}