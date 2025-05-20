/***********************************************************************
 * Header File:
 *    TEST PIECE
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The unit tests for the piece base class
 ************************************************************************/

#pragma once

#include "unitTest.h"

/***************************************************
 * TEST PIECE 
 * Test the PIECE base class
 ***************************************************/
class TestPiece : public UnitTest
{
public:

   void run()
   {
      assignment();

      equals_same();
      equals_different();
      notEquals_same();
      notEquals_different();

      isWhite_white();
      isWhite_black();
      isMoved_initial();
      isMoved_hasMoved();
      getNMoves_initial();
      getNMoves_hasMoved();

      getPosition();
      justMoved_initial();
      justMoved_hasMoved();
      justMoved_justMoved();

      setLastMove();

      report("Piece");
   }
private:
   void assignment();

   void equals_same();
   void equals_different();
   void notEquals_same();
   void notEquals_different();

   void isWhite_white();
   void isWhite_black();
   void isMoved_initial();
   void isMoved_hasMoved();
   void getNMoves_initial();
   void getNMoves_hasMoved();

   void getPosition();
   void justMoved_initial();
   void justMoved_hasMoved();
   void justMoved_justMoved();

   void setLastMove();


};

