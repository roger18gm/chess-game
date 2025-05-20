/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The PAWN class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawPawn(position, !isWhite());
   }
}


/**********************************************
 * BISHOP : GET POSITIONS
 *********************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{


}