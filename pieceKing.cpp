/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The KING class
 ************************************************************************/

#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void King::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawKing(position, !isWhite());
   }
}


/**********************************************
 * KING : GET POSITIONS
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{


}