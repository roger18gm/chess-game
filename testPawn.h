/***********************************************************************
 * Header File:
 *    TEST PAWN
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for Pawn
 ************************************************************************/

#pragma once

#include "unitTest.h"

 /***************************************************
  * PAWN TEST
  * Test the Pawn class
  ***************************************************/
class TestPawn : public UnitTest
{
public:

   void run()
   {
      getMoves_simpleWhite();
      getMoves_simpleBlack();
      getMoves_initialAdvanceWhite();
      getMoves_initialAdvanceBlack();
      getMoves_captureWhite();
      getMoves_captureBlack();
      getMoves_enpassantWhite();
      getMoves_enpassantBlack();
      getMoves_promotionWhite();
      getMoves_promotionBlack();

      getType();

      report("Pawn");
   }
private:
   void getMoves_simpleWhite();
   void getMoves_simpleBlack();
   void getMoves_initialAdvanceWhite();
   void getMoves_initialAdvanceBlack();
   void getMoves_captureWhite();
   void getMoves_captureBlack();
   void getMoves_enpassantWhite();
   void getMoves_enpassantBlack();
   void getMoves_promotionWhite();
   void getMoves_promotionBlack();
   void getType();

};

