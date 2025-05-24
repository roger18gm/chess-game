/***********************************************************************
 * Source File:
 *    TEST KING
 * Author:
 *    Jessen Forbush & Roger Galan
 * Summary:
 *    The unit tests for the King
 ************************************************************************/

#include "testKing.h"
#include "pieceRook.h"
#include "pieceKing.h"
#include "board.h"
#include "uiDraw.h"
#include <cassert>

 /*************************************
  * +---a-b-c-d-e-f-g-h---+
  * |                     |
  * 8                     8
  * 7                     7
  * 6       p p p         6
  * 5       p(k)p         5
  * 4       p p p         4
  * 3                     3
  * 2                     2
  * 1                     1
  * |                     |
  * +---a-b-c-d-e-f-g-h---+
  **************************************/
void TestKing::getMoves_blocked()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false);
   king.fWhite = true;
   king.position.colRow = 0x24; // c5
   board.board[2][4] = &king;

   White white(PAWN);
   white.fWhite = true;

   board.board[1][3] = &white; // b4
   board.board[1][4] = &white; // b5
   board.board[1][5] = &white; // b6
   board.board[2][3] = &white; // c4
   board.board[2][5] = &white; // c6
   board.board[3][3] = &white; // d4
   board.board[3][4] = &white; // d5
   board.board[3][5] = &white; // d6

   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves == set<Move>());
   assertUnit(moves.size() == 0);

   // TEARDOWN

   board.board[2][4] = nullptr;
   board.board[1][3] = nullptr;
   board.board[1][4] = nullptr;
   board.board[1][5] = nullptr;
   board.board[2][3] = nullptr;
   board.board[2][5] = nullptr;
   board.board[3][3] = nullptr;
   board.board[3][4] = nullptr;
   board.board[3][5] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       P P P         6
 * 5       P(k)P         5
 * 4       P P P         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_capture()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false);
   king.fWhite = true;
   king.position.colRow = 0x24; // c5
   board.board[2][4] = &king;

   Black black(PAWN);
   black.fWhite = false;

   board.board[1][3] = &black; // b4
   board.board[1][4] = &black; // b5
   board.board[1][5] = &black; // b6
   board.board[2][3] = &black; // c4
   board.board[2][5] = &black; // c6
   board.board[3][3] = &black; // d4
   board.board[3][4] = &black; // d5
   board.board[3][5] = &black; // d6

   Move captureB4, captureB5, captureB6, captureC4, captureC6, captureD4, captureD5, captureD6;
   captureB4.source.colRow = captureB5.source.colRow = captureB6.source.colRow =
      captureC4.source.colRow = captureC6.source.colRow = captureD4.source.colRow =
      captureD5.source.colRow = captureD6.source.colRow = 0x24;

   captureB4.dest.colRow = 0x13; captureB5.dest.colRow = 0x14; captureB6.dest.colRow = 0x15;
   captureC4.dest.colRow = 0x23; captureC6.dest.colRow = 0x25; captureD4.dest.colRow = 0x33;
   captureD5.dest.colRow = 0x34; captureD6.dest.colRow = 0x35;

   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(captureB4) != moves.end());
   assertUnit(moves.find(captureB5) != moves.end());
   assertUnit(moves.find(captureB6) != moves.end());
   assertUnit(moves.find(captureC4) != moves.end());
   assertUnit(moves.find(captureC6) != moves.end());
   assertUnit(moves.find(captureD4) != moves.end());
   assertUnit(moves.find(captureD5) != moves.end());
   assertUnit(moves.find(captureD6) != moves.end());

   // TEARDOWN

   board.board[2][4] = nullptr;
   board.board[1][3] = nullptr;
   board.board[1][4] = nullptr;
   board.board[1][5] = nullptr;
   board.board[2][3] = nullptr;
   board.board[2][5] = nullptr;
   board.board[3][3] = nullptr;
   board.board[3][4] = nullptr;
   board.board[3][5] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6       . . .         6
 * 5       .(k).         5
 * 4       . . .         4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_free()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false);
   king.fWhite = true;
   king.position.colRow = 0x24; // c5
   board.board[2][4] = &king;

   Move moveToB4, moveToB5, moveToB6, moveToC4, moveToC6, moveToD4, moveToD5, moveToD6;
   moveToB4.source.colRow = moveToB5.source.colRow = moveToB6.source.colRow =
      moveToC4.source.colRow = moveToC6.source.colRow = moveToD4.source.colRow =
      moveToD5.source.colRow = moveToD6.source.colRow = 0x24;

   moveToB4.dest.colRow = 0x13; moveToB5.dest.colRow = 0x14; moveToB6.dest.colRow = 0x15;
   moveToC4.dest.colRow = 0x23; moveToC6.dest.colRow = 0x25; moveToD4.dest.colRow = 0x33;
   moveToD5.dest.colRow = 0x34; moveToD6.dest.colRow = 0x35;

   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 8);
   assertUnit(moves.find(moveToB4) != moves.end());
   assertUnit(moves.find(moveToB5) != moves.end());
   assertUnit(moves.find(moveToB6) != moves.end());
   assertUnit(moves.find(moveToC4) != moves.end());
   assertUnit(moves.find(moveToC6) != moves.end());
   assertUnit(moves.find(moveToD4) != moves.end());
   assertUnit(moves.find(moveToD5) != moves.end());
   assertUnit(moves.find(moveToD6) != moves.end());

   // TEARDOWN
   board.board[2][4] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2   . .               2
 * 1  (k).               1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_end()
{
   // SETUP
   BoardEmpty board;
   King king(7, 7, false);
   king.fWhite = true;
   king.position.colRow = 0x00; // a1
   board.board[0][0] = &king;

   Move moveToA2, moveToB1, moveToB2;
   moveToA2.source.colRow = moveToB1.source.colRow = moveToB2.source.colRow = 0x00;
   moveToA2.dest.colRow = 0x01; moveToB1.dest.colRow = 0x10; moveToB2.dest.colRow = 0x11;

   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   assertUnit(moves.size() == 3);
   assertUnit(moves.find(moveToA2) != moves.end());
   assertUnit(moves.find(moveToB1) != moves.end());
   assertUnit(moves.find(moveToB2) != moves.end());

   // TEARDOWN
   board.board[0][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r   . .(k). . r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastle()
{
   // SETUP
   BoardEmpty board;
   King king(4, 0, true); // e1
   king.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = 0;
   board.board[4][0] = &king;

   Rook rookKingSide(7, 0, true); // h1
   rookKingSide.fWhite = true;
   rookKingSide.nMoves = 0;
   board.board[7][0] = &rookKingSide;

   Rook rookQueenSide(0, 0, true); // a1
   rookQueenSide.fWhite = true;
   rookQueenSide.nMoves = 0;
   board.board[0][0] = &rookQueenSide;

   White pawn1(PAWN);
   White pawn2(PAWN);
   White pawn3(PAWN);
   pawn1.fWhite = true;
   pawn2.fWhite = true;
   pawn3.fWhite = true;
   board.board[3][1] = &pawn1; // d2
   board.board[4][1] = &pawn2; // e2
   board.board[5][1] = &pawn3; // f2

   set<Move> moves;

   // EXERCISE
   king.getMoves(moves, board);

   // VERIFY
   bool foundKingSideCastle = false;
   bool foundQueenSideCastle = false;

   for (const Move& move : moves)
   {
      if (move.getCastleK())
         foundKingSideCastle = true;
      if (move.getCastleQ())
         foundQueenSideCastle = true;
   }

   assertUnit(foundKingSideCastle == true);
   assertUnit(foundQueenSideCastle == true);
   assertUnit(moves.size() >= 2);

   // TEARDOWN

   board.board[4][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[0][0] = nullptr;
   board.board[3][1] = nullptr;
   board.board[4][1] = nullptr;
   board.board[5][1] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8   R   . .(K). . R   8
 * 7         P P P       7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2                     2
 * 1                     1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_blackCastle()
{
   BoardEmpty board;
   King king(4, 7, false); // e8
   king.fWhite = false;
   king.position.colRow = 0x47;
   king.nMoves = 0;
   board.board[4][7] = &king;

   Rook rookKingSide(7, 7, false); // h8
   rookKingSide.fWhite = false;
   rookKingSide.nMoves = 0;
   board.board[7][7] = &rookKingSide;

   Rook rookQueenSide(0, 7, false); // a8
   rookQueenSide.fWhite = false;
   rookQueenSide.nMoves = 0;
   board.board[0][7] = &rookQueenSide;

   Black pawn1(PAWN);
   Black pawn2(PAWN);
   Black pawn3(PAWN);
   pawn1.fWhite = false;
   pawn2.fWhite = false;
   pawn3.fWhite = false;
   board.board[3][6] = &pawn1; // d7
   board.board[4][6] = &pawn2; // e7
   board.board[5][6] = &pawn3; // f7

   set<Move> moves;
   king.getMoves(moves, board);

   bool foundKingSideCastle = false;
   bool foundQueenSideCastle = false;

   for (const Move& move : moves)
   {
      if (move.getCastleK())
         foundKingSideCastle = true;
      if (move.getCastleQ())
         foundQueenSideCastle = true;
   }

   assertUnit(foundKingSideCastle == true);
   assertUnit(foundQueenSideCastle == true);
   assertUnit(moves.size() >= 2);

   board.board[4][7] = nullptr;
   board.board[7][7] = nullptr;
   board.board[0][7] = nullptr;
   board.board[3][6] = nullptr;
   board.board[4][6] = nullptr;
   board.board[5][6] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleKingMoved()
{
   BoardEmpty board;
   King king(4, 0, true); // e1
   king.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = 1; // King HAS moved
   board.board[4][0] = &king;

   Rook rookKingSide(7, 0, true); // h1
   rookKingSide.fWhite = true;
   rookKingSide.nMoves = 0;
   board.board[7][0] = &rookKingSide;

   Rook rookQueenSide(0, 0, true); // a1
   rookQueenSide.fWhite = true;
   rookQueenSide.nMoves = 0;
   board.board[0][0] = &rookQueenSide;

   set<Move> moves;
   king.getMoves(moves, board);

   bool foundKingSideCastle = false;
   bool foundQueenSideCastle = false;

   for (const Move& move : moves)
   {
      if (move.getCastleK())
         foundKingSideCastle = true;
      if (move.getCastleQ())
         foundQueenSideCastle = true;
   }

   assertUnit(foundKingSideCastle == false);
   assertUnit(foundQueenSideCastle == false);

   board.board[4][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[0][0] = nullptr;
}

/*************************************
 * +---a-b-c-d-e-f-g-h---+
 * |                     |
 * 8                     8
 * 7                     7
 * 6                     6
 * 5                     5
 * 4                     4
 * 3                     3
 * 2         p p p       2
 * 1   r     .(k).   r   1
 * |                     |
 * +---a-b-c-d-e-f-g-h---+
 **************************************/
void TestKing::getMoves_whiteCastleRookMoved()
{
   BoardEmpty board;
   King king(4, 0, true); // e1
   king.fWhite = true;
   king.position.colRow = 0x40;
   king.nMoves = 0;
   board.board[4][0] = &king;

   Rook rookKingSide(7, 0, true); // h1
   rookKingSide.fWhite = true;
   rookKingSide.nMoves = 1; // Rook HAS moved
   board.board[7][0] = &rookKingSide;

   Rook rookQueenSide(0, 0, true); // a1
   rookQueenSide.fWhite = true;
   rookQueenSide.nMoves = 1; // Rook HAS moved
   board.board[0][0] = &rookQueenSide;

   set<Move> moves;
   king.getMoves(moves, board);

   bool foundKingSideCastle = false;
   bool foundQueenSideCastle = false;

   for (const Move& move : moves)
   {
      if (move.getCastleK())
         foundKingSideCastle = true;
      if (move.getCastleQ())
         foundQueenSideCastle = true;
   }

   assertUnit(foundKingSideCastle == false);
   assertUnit(foundQueenSideCastle == false);

   board.board[4][0] = nullptr;
   board.board[7][0] = nullptr;
   board.board[0][0] = nullptr;
}

/*************************************
 * GET TYPE : king
 * Input:
 * Output: KING
 **************************************/
void TestKing::getType()
{
   const King king(7, 7, false);
   PieceType pt = SPACE;

   pt = king.getType();

   assertUnit(pt == KING);
}
