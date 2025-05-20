/***********************************************************************
 * Header File:
 *    TEST BOARD
 * Author:
 *    <your name here>
 * Summary:
 *    The unit tests for Board
 ************************************************************************/

#pragma once

#include "unitTest.h"

class Board;

/***************************************************
 * BOARD TEST
 * Test the Board class
 ***************************************************/
class TestBoard : public UnitTest
{
public:
   void run()
   {
      // construct
      construct_default();
      construct_dummyBoard();
      construct_emptyBoard();

      // move
      move_pawnSimple();
      move_pawnCapture();
      move_pawnDouble();
      move_pawnEnpassant();
      move_pawnPromotion();
      move_rookSlide();
      move_rookAttack();
      move_bishopSlide();
      move_bishopAttack();
      move_knightMove();
      move_knightAttack();
      move_queenSlide();
      move_queenAttack();
      move_kingMove();
      move_kingAttack();
      move_kingShortCastle();
      move_kingLongCastle();

      // Get Current Move
      getCurrentMove_initial();
      getCurrentMove_second();
      getCurrentMove_middleWhite();
      getCurrentMove_middleBlack();

      // Whites Turn?
      whiteTurn_initial();
      whiteTurn_second();
      whiteTurn_middleWhite();
      whiteTurn_middleBlack();

      // fetch and get
      fetch_a1();
      fetch_h8();
      fetch_a8();
      set_a1();
      set_h8();
      set_a8();

      report("Board");
   }
private:

   void createDummyBoard(Board& board);
   void construct_default();
   void construct_dummyBoard();
   void construct_emptyBoard();
   void getCurrentMove_initial();
   void getCurrentMove_second();
   void getCurrentMove_middleWhite();
   void getCurrentMove_middleBlack();

   void whiteTurn_initial();
   void whiteTurn_second();
   void whiteTurn_middleWhite();
   void whiteTurn_middleBlack();

   void move_pawnSimple();
   void move_pawnCapture();
   void move_pawnDouble();
   void move_pawnEnpassant();
   void move_pawnPromotion();
   void move_rookSlide();
   void move_rookAttack();
   void move_bishopSlide();
   void move_bishopAttack();
   void move_knightMove();
   void move_knightAttack();
   void move_queenSlide();
   void move_queenAttack();
   void move_kingMove();
   void move_kingAttack();
   void move_kingShortCastle();
   void move_kingLongCastle();

   void fetch_a1();
   void fetch_h8();
   void fetch_a8();
   void set_a1();
   void set_h8();
   void set_a8();

};

