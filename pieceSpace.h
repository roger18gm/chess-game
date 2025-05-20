/***********************************************************************
 * Header File:
 *    SPACE
 * Author:
 *   Jessen Forbush and Roger Galan
 * Summary:
 *    The space
 ************************************************************************/

#pragma once

#include "piece.h"

class TestSpace;

 /***************************************************
  * SPACES
  * A space is a trivial piece
  ***************************************************/
class Space : public Piece
{
   friend TestSpace;
public:
   Space(int c, int r) : Piece(c, r)   {               }
   ~Space() { }
   PieceType getType()           const { return SPACE;  }
   void display(ogstream* pgout) const {               }
};