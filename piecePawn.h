/***********************************************************************
 * Header File:
 *    PAWN
 * Author:
*    Roger Galan & Jessen Forbush
 * Summary:
 *    The PAWN class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * PAWN
  * The Pawn, aka the ""
  ***************************************************/
class Pawn : public Piece
{
public:
   Pawn(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
   Pawn(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
   ~Pawn() {}
   PieceType getType()            const { return PAWN; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
};