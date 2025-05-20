/***********************************************************************
 * Header File:
 *    TEST KNIGHT
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for Knight
 ************************************************************************/

#pragma once

#include "unitTest.h"


/***************************************************
 * KNIGHT TEST
 * Test the Knight class
 ***************************************************/
class TestKnight : public UnitTest
{
public:

   void run()
   {
      getMoves_blocked();
      getMoves_capture();
      getMoves_free();
      getMoves_end();

      getType();
      
      report("Knight");
   }
private:
   void getMoves_blocked();
   void getMoves_capture();
   void getMoves_free();
   void getMoves_end();
   void getType();
};
