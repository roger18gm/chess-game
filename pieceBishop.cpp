/***********************************************************************
 * Source File:
 *    BISHOP
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The BISHOP class
 ************************************************************************/

#include "pieceBishop.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Bishop::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawBishop(position, !isWhite());
   }
}

/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Bishop::getMoves(set <Move>& moves, const Board& board) const
{
   const Delta delta[] =
   {
      {-1,  1},   {1,  1},

      {-1, -1},   {1, -1}
   };

   moves = getMovesSlide(board, delta, sizeof(delta) / sizeof(delta[0]));
}
