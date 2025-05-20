/***********************************************************************
 * Header File:
 *    TEST BISHOP
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for the bishop
 ************************************************************************/

#pragma once


#include "unitTest.h"

 /***************************************************
  * BISHOP TEST
  * Test the BISHOP class
  ***************************************************/
class TestBishop : public UnitTest
{
public:

   void run()
   {
      getMoves_blocked();
      getMoves_slideToEnd();
      getMoves_slideToBlock();
      getMoves_slideToCapture();

      getType();

      report("Bishop");
   }
private:
   void getMoves_blocked();
   void getMoves_slideToEnd();
   void getMoves_slideToBlock();
   void getMoves_slideToCapture();
   void getType();
};

