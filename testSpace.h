/***********************************************************************
 * Header File:
 *    TEST SPACE
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The unit tests for the space
 ************************************************************************/

#pragma once


#include "unitTest.h"
#include "pieceSpace.h"

 /***************************************************
  * BISHOP TEST
  * Test the BISHOP class
  ***************************************************/
class TestSpace : public UnitTest
{
public:

   void run()
   {
      construct_a1();
      construct_h8();
      construct_a8();
      getType();

      report("Space");
   }
private:

   /*************************************
    * CONSTRUCT : a1
    * Input: 0,0
    * Output: a1
    **************************************/
   void construct_a1()
   {
      // SETUP  
      int row = 0;
      int col = 0;

      // EXERCISE
      Space space(col, row);

      // VERIFY
      assertUnit(space.position == Position("a1"));

   }  // TEARDOWN

   /*************************************
    * CONSTRUCT : h8
    * Input: 7,7
    * Output: a1
    **************************************/
   void construct_h8()
   {
      // SETUP  
      int row = 7;
      int col = 7;

      // EXERCISE
      Space space(col, row);

      // VERIFY
      assertUnit(space.position == Position("h8"));

   }  // TEARDOWN


   /*************************************
    * CONSTRUCT : a8
    * Input:  0,7
    * Output: a8
    **************************************/
   void construct_a8()
   {
      // SETUP  
      int row = 7;
      int col = 0;

      // EXERCISE
      Space space(col, row);

      // VERIFY
      assertUnit(space.position == Position("a8"));
   }

   /*************************************
    * GET TYPE : space
    * Input:
    * Output: SPACE
    **************************************/
   void getType()
   {
      // SETUP  
      const Space space(7, 7);
      PieceType pt = SPACE;

      // EXERCISE
      pt = space.getType();

      // VERIFY
      assertUnit(pt == SPACE);

   }  // TEARDOWN

};

