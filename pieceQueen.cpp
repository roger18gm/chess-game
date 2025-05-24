/***********************************************************************
 * Source File:
 *    QUEEN
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The QUEEN class
 ************************************************************************/

#include "pieceQueen.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Queen::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawQueen(position, !isWhite());
   }
}

/**********************************************
 * QUEEN : GET POSITIONS
 *********************************************/
void Queen::getMoves(set <Move>& moves, const Board& board) const
{
   const Delta delta[] =
   {
      { -1,  1 }, { 0,  1 }, { 1,  1 },
      { -1,  0 },            { 1,  0 },
      { -1, -1 }, { 0, -1 }, { 1, -1 }
   };

   moves = getMovesSlide(board, delta, sizeof(delta) / sizeof(delta[0]));
}