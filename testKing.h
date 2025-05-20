/***********************************************************************
 * Header File:
 *    TEST KING
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for King
 ************************************************************************/

#pragma once

#include "unitTest.h"




 /***************************************************
  * KING TEST
  * Test the King class
  ***************************************************/
class TestKing : public UnitTest
{
public:

   void run()
   {
      getMoves_blocked();
      getMoves_capture();
      getMoves_free();
      getMoves_end();
      getMoves_whiteCastle();
      getMoves_blackCastle();
      getMoves_whiteCastleKingMoved();
      getMoves_whiteCastleRookMoved();

      getType();

      report("King");
   }
private:
   void getMoves_blocked();
   void getMoves_capture();
   void getMoves_free();
   void getMoves_end();
   void getMoves_whiteCastle();
   void getMoves_blackCastle();
   void getMoves_whiteCastleKingMoved();
   void getMoves_whiteCastleRookMoved();
   void getType();
};
