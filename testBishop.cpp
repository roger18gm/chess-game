/***********************************************************************
 * Source File:
 *    TEST BISHOP
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The unit tests for a bishop
 ************************************************************************/


#include "testBishop.h"
#include "pieceBishop.h"      
#include "board.h"
#include "uiDraw.h"
#include <cassert>      




 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6                     6
  * 5                     5
  * 4                     4
  * 3     p   p           3
  * 2      (b)            2
  * 1     p   p           1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestBishop::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21; // c2 position (column 3, row 4)
   board.board[2][1] = &bishop;
   White white(PAWN);
   board.board[1][0] = board.board[1][2] = 
   board.board[3][0] = board.board[3][2] = &white; 
   set<Move> moves;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY
   assertUnit(moves == set<Move>());
   assertUnit(moves.size() == 0);  // no possible moves

   // TEARDOWN
   board.board[2][1] = board.board[1][0] = board.board[1][2] = 
   board.board[3][0] = board.board[3][2] = nullptr; 
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 .   7
 * 6               .     6
 * 5             .       5
 * 4   .       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     .   .           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToEnd()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21; // c2 position (column 3, row 2)
   board.board[2][1] = &bishop;
   set<Move> moves; 
   Move c2a4, c2b1, c2b3, c2d1, c2d3, c2e4, c2f5, c2g6, c2h7;
   c2a4.source.colRow = c2b1.source.colRow = c2b3.source.colRow = 
   c2d1.source.colRow = c2d3.source.colRow = c2e4.source.colRow = 
   c2f5.source.colRow = c2g6.source.colRow = c2h7.source.colRow = 0x21;
   c2a4.capture = c2b1.capture = c2b3.capture = 
   c2d1.capture = c2d3.capture = c2e4.capture = 
   c2f5.capture = c2g6.capture = c2h7.capture = SPACE;
   c2a4.dest.colRow = 0x03;
   c2b1.dest.colRow = 0x10;
   c2b3.dest.colRow = 0x12;
   c2d1.dest.colRow = 0x30;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54;
   c2g6.dest.colRow = 0x65;
   c2h7.dest.colRow = 0x76;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY

   assertUnit(moves.size() == 9);  // 9 possible moves
   assertUnit(moves.find(c2a4) != moves.end());
   assertUnit(moves.find(c2b1) != moves.end());
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d1) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());
   assertUnit(moves.find(c2h7) != moves.end());

   // TEARDOWN
   board.board[2][1] = nullptr; // bishop
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 p   7
 * 6               .     6
 * 5             .       5
 * 4   p       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     p   p           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToBlock()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21; // c2 position (column 3, row 2)
   board.board[2][1] = &bishop;
   White white(PAWN);
   board.board[0][3] = board.board[1][0] = 
   board.board[3][0] = board.board[7][6] = &white;
   set<Move> moves;
   Move c2b3, c2d3, c2e4, c2f5, c2g6;
   c2b3.source.colRow = c2d3.source.colRow = c2e4.source.colRow = 
   c2f5.source.colRow = c2g6.source.colRow = 0x21;
   c2b3.capture = c2d3.capture = c2e4.capture = 
   c2f5.capture = c2g6.capture = SPACE;
   c2b3.dest.colRow = 0x12;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54; 
   c2g6.dest.colRow = 0x65;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY

   assertUnit(moves.size() == 5);  // 5 possible moves
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());

   // TEARDOWN
   board.board[2][1] = board.board[0][3] = 
   board.board[1][0] = board.board[3][0] = board.board[7][6] = nullptr;
}


/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                 P   7
 * 6               .     6
 * 5             .       5
 * 4   P       .         4
 * 3     .   .           3
 * 2      (b)            2
 * 1     P   P           1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestBishop::getMoves_slideToCapture()
{
   // SETUP
   BoardEmpty board;
   Bishop bishop(7, 7, false /*white*/); // we will reset all this.
   bishop.fWhite = true;
   bishop.position.colRow = 0x21; // c2 position (column 3, row 2)
   board.board[2][1] = &bishop;
   Black black(PAWN);
   board.board[0][3] = board.board[1][0] = 
   board.board[3][0] = board.board[7][6] = &black;
   set<Move> moves;
   Move c2b3, c2d3, c2e4, c2f5, c2g6;
   c2b3.source.colRow = c2d3.source.colRow = c2e4.source.colRow = 
   c2f5.source.colRow = c2g6.source.colRow = 0x21;
   c2b3.capture = c2d3.capture = c2e4.capture = 
   c2f5.capture = c2g6.capture = SPACE;
   c2b3.dest.colRow = 0x12;
   c2d3.dest.colRow = 0x32;
   c2e4.dest.colRow = 0x43;
   c2f5.dest.colRow = 0x54;
   c2g6.dest.colRow = 0x65;

   // EXERCISE
   bishop.getMoves(moves, board);

   // VERIFY

   assertUnit(moves.size() == 9);  // 9 possible moves
   assertUnit(moves.find(c2b3) != moves.end());
   assertUnit(moves.find(c2d3) != moves.end());
   assertUnit(moves.find(c2e4) != moves.end());
   assertUnit(moves.find(c2f5) != moves.end());
   assertUnit(moves.find(c2g6) != moves.end());

   // TEARDOWN
   board.board[2][1] = board.board[0][3] =
   board.board[1][0] = board.board[3][0] =
   board.board[7][6] = nullptr;
}


/*************************************
 * GET TYPE : bishop
 * Input:
 * Output: BISHOP
 **************************************/
void TestBishop::getType()
{
   // SETUP  
   const Bishop bishop(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = bishop.getType();

   // VERIFY
   assertUnit(pt == BISHOP);
}  // TEARDOWN
