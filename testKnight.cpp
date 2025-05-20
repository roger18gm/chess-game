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
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x60;
   board.board[6][0] = &knight;
   Black black(PAWN);
   board.board[4][1] = &black;
   White white(PAWN);
   board.board[5][2] = &white;
   set <Move> moves;
   Move g1e2p;
   g1e2p.source.colRow = 0x60;
   g1e2p.dest.colRow = 0x41;
   g1e2p.capture = PAWN;
   Move g1h3;
   g1h3.source.colRow = 0x60;
   g1h3.dest.colRow = 0x72;
   g1h3.capture = SPACE;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 2);  // many possible moves
   assertUnit(moves.find(g1e2p) != moves.end());
   assertUnit(moves.find(g1h3) != moves.end());

   // TEARDOWN
   board.board[6][0] = nullptr; // white knight
   board.board[4][1] = nullptr; // black pawn
   board.board[5][2] = nullptr; // white pawn
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
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x34; // d5 position (column 3, row 4)
   board.board[3][4] = &knight;

   // Create friendly pawns (white) at all 8 potential knight move positions
   White pawnC7(PAWN);
   White pawnE7(PAWN);
   White pawnB6(PAWN);
   White pawnF6(PAWN);
   White pawnB4(PAWN);
   White pawnF4(PAWN);
   White pawnC3(PAWN);
   White pawnE3(PAWN);

   // Make sure all pawns are white (same as the knight)
   pawnC7.fWhite = true;
   pawnE7.fWhite = true;
   pawnB6.fWhite = true;
   pawnF6.fWhite = true;
   pawnB4.fWhite = true;
   pawnF4.fWhite = true;
   pawnC3.fWhite = true;
   pawnE3.fWhite = true;

   // Place pawns on the board at all the knight's potential move locations
   board.board[2][6] = &pawnC7; // c7
   board.board[4][6] = &pawnE7; // e7
   board.board[1][5] = &pawnB6; // b6
   board.board[5][5] = &pawnF6; // f6
   board.board[1][3] = &pawnB4; // b4
   board.board[5][3] = &pawnF4; // f4
   board.board[2][2] = &pawnC3; // c3
   board.board[4][2] = &pawnE3; // e3

   // Create set to hold results
   set<Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY
   // Since all potential moves should be blocked, the set should be empty
   assertUnit(moves == set<Move>());
   assertUnit(moves.size() == 0);  // no possible moves


   // TEARDOWN
   board.board[3][4] = nullptr; // knight
   board.board[2][6] = nullptr; // c7 pawn
   board.board[4][6] = nullptr; // e7 pawn
   board.board[1][5] = nullptr; // b6 pawn
   board.board[5][5] = nullptr; // f6 pawn
   board.board[1][3] = nullptr; // b4 pawn
   board.board[5][3] = nullptr; // f4 pawn
   board.board[2][2] = nullptr; // c3 pawn
   board.board[4][2] = nullptr; // e3 pawn
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
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x34; // d5 position (column 3, row 4)
   board.board[3][4] = &knight;

   // Create opposing pawns (black) at knight's move positions
   Black pawnC7(PAWN);
   Black pawnE7(PAWN);
   Black pawnB6(PAWN);
   Black pawnF6(PAWN);
   Black pawnB4(PAWN);
   Black pawnF4(PAWN);
   Black pawnC3(PAWN);
   Black pawnE3(PAWN);

   // Make sure all pawns are black (opposite of the knight)
   pawnC7.fWhite = false;
   pawnE7.fWhite = false;
   pawnB6.fWhite = false;
   pawnF6.fWhite = false;
   pawnB4.fWhite = false;
   pawnF4.fWhite = false;
   pawnC3.fWhite = false;
   pawnE3.fWhite = false;

   // Place pawns on the board at all the knight's possible move locations
   board.board[2][6] = &pawnC7; // c7
   board.board[4][6] = &pawnE7; // e7
   board.board[1][5] = &pawnB6; // b6
   board.board[5][5] = &pawnF6; // f6
   board.board[1][3] = &pawnB4; // b4
   board.board[5][3] = &pawnF4; // f4
   board.board[2][2] = &pawnC3; // c3
   board.board[4][2] = &pawnE3; // e3

   // Create expected moves with captures
   Move captureC7;
   captureC7.source.colRow = 0x34; // d5
   captureC7.dest.colRow = 0x26;   // c7

   Move captureE7;
   captureE7.source.colRow = 0x34; // d5
   captureE7.dest.colRow = 0x46;   // e7

   Move captureB6;
   captureB6.source.colRow = 0x34; // d5
   captureB6.dest.colRow = 0x15;   // b6

   Move captureF6;
   captureF6.source.colRow = 0x34; // d5
   captureF6.dest.colRow = 0x55;   // f6

   Move captureB4;
   captureB4.source.colRow = 0x34; // d5
   captureB4.dest.colRow = 0x13;   // b4

   Move captureF4;
   captureF4.source.colRow = 0x34; // d5
   captureF4.dest.colRow = 0x53;   // f4

   Move captureC3;
   captureC3.source.colRow = 0x34; // d5
   captureC3.dest.colRow = 0x22;   // c3

   Move captureE3;
   captureE3.source.colRow = 0x34; // d5
   captureE3.dest.colRow = 0x42;   // e3

   // Create a collection of all expected moves
   set<Move> expectedMoves;
   expectedMoves.insert(captureC7);
   expectedMoves.insert(captureE7);
   expectedMoves.insert(captureB6);
   expectedMoves.insert(captureF6);
   expectedMoves.insert(captureB4);
   expectedMoves.insert(captureF4);
   expectedMoves.insert(captureC3);
   expectedMoves.insert(captureE3);

   set<Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY - the moves set should exactly match our expected moves
   assertUnit(moves == expectedMoves);
   assertUnit(moves.size() == 8);  // many possible moves
   assertUnit(moves.find(captureC7) != moves.end());
   assertUnit(moves.find(captureE7) != moves.end());
   assertUnit(moves.find(captureB6) != moves.end());
   assertUnit(moves.find(captureF6) != moves.end());
   assertUnit(moves.find(captureB4) != moves.end());
   assertUnit(moves.find(captureF4) != moves.end());
   assertUnit(moves.find(captureC3) != moves.end());
   assertUnit(moves.find(captureE3) != moves.end());


   // TEARDOWN
   board.board[3][4] = nullptr; // knight
   board.board[2][6] = nullptr; // c7 pawn
   board.board[4][6] = nullptr; // e7 pawn
   board.board[1][5] = nullptr; // b6 pawn
   board.board[5][5] = nullptr; // f6 pawn
   board.board[1][3] = nullptr; // b4 pawn
   board.board[5][3] = nullptr; // f4 pawn
   board.board[2][2] = nullptr; // c3 pawn
   board.board[4][2] = nullptr; // e3 pawn
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
   Knight knight(7, 7, false /*white*/); // we will reset all this.
   knight.fWhite = true;
   knight.position.colRow = 0x34; // d5 position (column 3, row 4)
   board.board[3][4] = &knight;

   // Create expected moves on an empty board
   Move moveToC7;
   moveToC7.source.colRow = 0x34; // d5
   moveToC7.dest.colRow = 0x26;   // c7

   Move moveToE7;
   moveToE7.source.colRow = 0x34; // d5
   moveToE7.dest.colRow = 0x46;   // e7

   Move moveToB6;
   moveToB6.source.colRow = 0x34; // d5
   moveToB6.dest.colRow = 0x15;   // b6

   Move moveToF6;
   moveToF6.source.colRow = 0x34; // d5
   moveToF6.dest.colRow = 0x55;   // f6

   Move moveToB4;
   moveToB4.source.colRow = 0x34; // d5
   moveToB4.dest.colRow = 0x13;   // b4

   Move moveToF4;
   moveToF4.source.colRow = 0x34; // d5
   moveToF4.dest.colRow = 0x53;   // f4

   Move moveToC3;
   moveToC3.source.colRow = 0x34; // d5
   moveToC3.dest.colRow = 0x22;   // c3

   Move moveToE3;
   moveToE3.source.colRow = 0x34; // d5
   moveToE3.dest.colRow = 0x42;   // e3

   // Create a collection of all expected moves
   set<Move> expectedMoves;
   expectedMoves.insert(moveToC7);
   expectedMoves.insert(moveToE7);
   expectedMoves.insert(moveToB6);
   expectedMoves.insert(moveToF6);
   expectedMoves.insert(moveToB4);
   expectedMoves.insert(moveToF4);
   expectedMoves.insert(moveToC3);
   expectedMoves.insert(moveToE3);

   set<Move> moves;

   // EXERCISE
   knight.getMoves(moves, board);

   // VERIFY - the moves set should exactly match our expected moves
   assertUnit(moves == expectedMoves);
   assertUnit(moves.size() == 8);  // many possible moves
   assertUnit(moves.find(moveToC7) != moves.end());
   assertUnit(moves.find(moveToE7) != moves.end());
   assertUnit(moves.find(moveToB6) != moves.end());
   assertUnit(moves.find(moveToF6) != moves.end());
   assertUnit(moves.find(moveToB4) != moves.end());
   assertUnit(moves.find(moveToF4) != moves.end());
   assertUnit(moves.find(moveToC3) != moves.end());
   assertUnit(moves.find(moveToE3) != moves.end());

   // TEARDOWN
   board.board[3][4] = nullptr; // knight
}



/*************************************
 * GET TYPE : knight
 * Input:
 * Output: KNIGHT
 **************************************/
void TestKnight::getType()
{
   // SETUP  
   const Knight knight(7, 7, false /*white*/);
   PieceType pt = SPACE;

   // EXERCISE
   pt = knight.getType();

   // VERIFY
   assertUnit(pt == KNIGHT);
}  // TEARDOWN
