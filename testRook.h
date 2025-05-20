/***********************************************************************
 * Header File:
 *    TEST ROOK
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the Rook
 ************************************************************************/

#pragma once

#include "unitTest.h"

 /***************************************************
  * ROOK TEST
  * Test the Rook class
  ***************************************************/
class TestRook : public UnitTest
{
public:

   void run()
   {
      getMoves_blocked();
      getMoves_slideToEnd();
      getMoves_slideToBlock();
      getMoves_slideToCapture();

      getType();

      report("Rook");
   }
private:
   void getMoves_blocked();
   void getMoves_slideToEnd();
   void getMoves_slideToBlock();
   void getMoves_slideToCapture();
   void getType();
};
