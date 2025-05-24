/***********************************************************************
 * Source File:
 *    TEST KNIGHT
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The unit tests for the knight
 ************************************************************************/

#include "testKnight.h"
#include "pieceKnight.h"
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
  * 3             p   .   3
  * 2           P         2
  * 1              (n)    1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKnight::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false);
   knight.fWhite = true;
   knight.position.colRow = 0x60;
   board.board[6][0] = &knight;

   Black black(PAWN);
   board.board[4][1] = &black;
   White white(PAWN);
   board.board[5][2] = &white;

   set <Move> moves;
   Move g1e2p, g1h3;
   g1e2p.source.colRow = g1h3.source.colRow = 0x60;
   g1e2p.dest.colRow = 0x41; g1h3.dest.colRow = 0x72;
   g1e2p.capture = PAWN; g1h3.capture = SPACE;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);
   assertUnit(moves.find(g1e2p) != moves.end());
   assertUnit(moves.find(g1h3) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false);
   knight.fWhite = true;
   knight.position.colRow = 0x34; // d5
   board.board[3][4] = &knight;

   White white(PAWN);
   white.fWhite = true;

   board.board[2][6] = &white; // c7
   board.board[4][6] = &white; // e7
   board.board[1][5] = &white; // b6
   board.board[5][5] = &white; // f6
   board.board[1][3] = &white; // b4
   board.board[5][3] = &white; // f4
   board.board[2][2] = &white; // c3
   board.board[4][2] = &white; // e3

   set<Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves == set<Move>());
   assertUnit(moves.size() == 0);

   // TEARDOWN
   board.board[3][4] = nullptr;
   board.board[2][6] = nullptr;
   board.board[4][6] = nullptr;
   board.board[1][5] = nullptr;
   board.board[5][5] = nullptr;
   board.board[1][3] = nullptr;
   board.board[5][3] = nullptr;
   board.board[2][2] = nullptr;
   board.board[4][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       p   p         7
 * 6     p       p       6
 * 5        (n)          5
 * 4     p       p       4
 * 3       p   p         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false);
   knight.fWhite = true;
   knight.position.colRow = 0x34; // d5
   board.board[3][4] = &knight;

   Black black(PAWN);
   black.fWhite = false;

   board.board[2][6] = &black; // c7
   board.board[4][6] = &black; // e7
   board.board[1][5] = &black; // b6
   board.board[5][5] = &black; // f6
   board.board[1][3] = &black; // b4
   board.board[5][3] = &black; // f4
   board.board[2][2] = &black; // c3
   board.board[4][2] = &black; // e3

   Move captureC7, captureE7, captureB6, captureF6, captureB4, captureF4, captureC3, captureE3;
   captureC7.source.colRow = captureE7.source.colRow = captureB6.source.colRow = captureF6.source.colRow =
      captureB4.source.colRow = captureF4.source.colRow = captureC3.source.colRow = captureE3.source.colRow = 0x34;

   captureC7.dest.colRow = 0x26; captureE7.dest.colRow = 0x46; captureB6.dest.colRow = 0x15; captureF6.dest.colRow = 0x55;
   captureB4.dest.colRow = 0x13; captureF4.dest.colRow = 0x53; captureC3.dest.colRow = 0x22; captureE3.dest.colRow = 0x42;

   set<Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(captureC7) != moves.end());
   assertUnit(moves.find(captureE7) != moves.end());
   assertUnit(moves.find(captureB6) != moves.end());
   assertUnit(moves.find(captureF6) != moves.end());
   assertUnit(moves.find(captureB4) != moves.end());
   assertUnit(moves.find(captureF4) != moves.end());
   assertUnit(moves.find(captureC3) != moves.end());
   assertUnit(moves.find(captureE3) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr;
   board.board[2][6] = nullptr;
   board.board[4][6] = nullptr;
   board.board[1][5] = nullptr;
   board.board[5][5] = nullptr;
   board.board[1][3] = nullptr;
   board.board[5][3] = nullptr;
   board.board[2][2] = nullptr;
   board.board[4][2] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7       .   .         7
 * 6     .       .       6
 * 5        (n)          5
 * 4     .       .       4
 * 3       .   .         3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKnight::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   Knight knight(7, 7, false);
   knight.fWhite = true;
   knight.position.colRow = 0x34; // d5
   board.board[3][4] = &knight;

   Move moveToC7, moveToE7, moveToB6, moveToF6, moveToB4, moveToF4, moveToC3, moveToE3;
   moveToC7.source.colRow = moveToE7.source.colRow = moveToB6.source.colRow = moveToF6.source.colRow =
      moveToB4.source.colRow = moveToF4.source.colRow = moveToC3.source.colRow = moveToE3.source.colRow = 0x34;

   moveToC7.dest.colRow = 0x26; moveToE7.dest.colRow = 0x46; moveToB6.dest.colRow = 0x15; moveToF6.dest.colRow = 0x55;
   moveToB4.dest.colRow = 0x13; moveToF4.dest.colRow = 0x53; moveToC3.dest.colRow = 0x22; moveToE3.dest.colRow = 0x42;

   set<Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(moveToC7) != moves.end());
   assertUnit(moves.find(moveToE7) != moves.end());
   assertUnit(moves.find(moveToB6) != moves.end());
   assertUnit(moves.find(moveToF6) != moves.end());
   assertUnit(moves.find(moveToB4) != moves.end());
   assertUnit(moves.find(moveToF4) != moves.end());
   assertUnit(moves.find(moveToC3) != moves.end());
   assertUnit(moves.find(moveToE3) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr;
}

/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
   // SETUP
   const Knight knight(7, 7, false);
   PieceType pt = SPACE;

   // EXERCISE
   pt = knight.getType();

   // VERIFY
   assertUnit(pt == KNIGHT);

}  // TEARDOWN
