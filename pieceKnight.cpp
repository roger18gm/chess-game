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

/***************************************************
* KNIGHT: GET POSITIONS
***************************************************/
void Knight::getMoves(set <Move>& moves, const Board& board) const
{
   // possible positions relative to current position
   const Delta delta[] =
   {
            {-1, 2},   { 1,  2},
   {-2,  1},                      { 2,  1},
   {-2, -1},                      { 2, -1},
            { -1, -2}, { 1,  -2}
   };

   moves = getMovesNoSlide(board,
      delta, sizeof(delta) / sizeof(delta[0]));
}