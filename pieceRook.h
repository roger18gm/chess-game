/***********************************************************************
 * Header File:
 *    ROOK
 * Author:
*    Roger Galan & Jessen Forbush
 * Summary:
 *    The ROOK class
 ************************************************************************/

#pragma once

#include "piece.h"

 /***************************************************
  * ROOK
  * The Rook, aka the ""
  ***************************************************/
class Rook : public Piece
{
public:
   Rook(const Position& pos, bool isWhite) : Piece(pos, isWhite) {}
   Rook(int c, int r, bool isWhite) : Piece(c, r, isWhite) {}
   ~Rook() {}
   PieceType getType()            const { return ROOK; }
   void getMoves(set <Move>& moves, const Board& board) const;
   void display(ogstream* pgout)  const;
};