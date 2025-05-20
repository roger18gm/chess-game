/***********************************************************************
 * Source File:
 *    TEST PIECE
 * Author:
 *   Jessen Forbush and Roger Galan
 * Summary:
 *    The unit tests for a piece base class
 ************************************************************************/


#include "testPiece.h"
#include "piece.h"     
#include "board.h"
#include "uiDraw.h"
#include <cassert>      


 /*************************************
  * ASSIGNMENT
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 
  *        rhs.fWhite=true  .lastMove=3 .nMoves=1
  * output:lhs.fWhite=true  .lastMove=3 .nMoves=1
  **************************************/
void TestPiece::assignment()
{  // setup
   PieceDerived lhs(0,0,true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   PieceDerived rhs(3, 3, true);
   rhs.fWhite = true;
   rhs.lastMove = 3;
   rhs.nMoves = 1;
   // exercise
   lhs = rhs;
   // verify
   assertUnit(lhs.fWhite == true);
   assertUnit(lhs.lastMove == 3);
   assertUnit(lhs.nMoves == 1);
   assertUnit(rhs.fWhite == true);
   assertUnit(rhs.lastMove == 3);
   assertUnit(rhs.nMoves == 1);
}  // teardown

 /*************************************
  * EQUALS : space equals space
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=space
  * output:true
  **************************************/
void TestPiece::equals_same()
{  // setup
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = false;
   PieceType rhs = SPACE;
   // exercise
   isSame = lhs == rhs;
   // verify
   assertUnit(isSame == true);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // teardown

 /*************************************
  * EQUALS : space not equals rook
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=rook
  * output:true
  **************************************/
void TestPiece::equals_different()
{  // setup
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = true;
   PieceType rhs = ROOK;
   // exercise
   isSame = lhs == rhs;
   // verify
   assertUnit(isSame == false);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // teardown

 /*************************************
  * NOT EQUALS : space equals space
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=space
  * output:false
  **************************************/
void TestPiece::notEquals_same()
{  // setup
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = true;
   PieceType rhs = SPACE;
   // exercise
   isSame = lhs != rhs;
   // verify
   assertUnit(isSame == false);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // teardown

 /*************************************
  * NOT EQUALS : space not equals rook
  * input: lhs.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  *        rhs=rook
  * output:true
  **************************************/
void TestPiece::notEquals_different()
{  // setup
   PieceDerived lhs(0, 0, true);
   lhs.fWhite = false;
   lhs.lastMove = 6;
   lhs.nMoves = 2;
   lhs.position = Position(2, 3);
   bool isSame = false;
   PieceType rhs = ROOK;
   // exercise
   isSame = lhs != rhs;
   // verify
   assertUnit(isSame == true);
   assertUnit(lhs.fWhite == false);
   assertUnit(lhs.lastMove == 6);
   assertUnit(lhs.nMoves == 2);
}  // teardown

 /*************************************
  * IS WHITE : white
  * input: piece.fWhite=true .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  * output:true
  **************************************/
void TestPiece::isWhite_white()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = true;
   piece.lastMove = 6;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   bool isWhite = false;
   // exercise
   isWhite = piece.isWhite();
   // verify
   assertUnit(isWhite == true);
   assertUnit(piece.fWhite == true);
   assertUnit(piece.lastMove == 6);
   assertUnit(piece.nMoves == 2);
}  // teardown

 /*************************************
  * IS WHITE : black
  * input: piece.fWhite=false .lastMove=6 .nMoves=2 .pos(2,3) .type=space
  * output:false
  **************************************/
void TestPiece::isWhite_black()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 6;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   bool isWhite = true;
   // exercise
   isWhite = piece.isWhite();
   // verify
   assertUnit(isWhite == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 6);
   assertUnit(piece.nMoves == 2);
}  // teardown

 /*************************************
  * IS MOVED : inital when not moved
  * input: piece.fWhite=false .lastMove=0 .nMoves=0 .pos(2,3) .type=space
  * output:false
  **************************************/
void TestPiece::isMoved_initial()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 0;
   piece.nMoves = 0;
   piece.position = Position(2, 3);
   bool isMoved = true;
   // exercise
   isMoved = piece.isMoved();
   // verify
   assertUnit(isMoved == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 0);
   assertUnit(piece.nMoves == 0);
}  // teardown

 /*************************************
  * IS MOVED : has moved twice
  * input: piece.fWhite=false .lastMove=1 .nMoves=2 .pos(2,3) .type=space
  * output:true
  **************************************/
void TestPiece::isMoved_hasMoved()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 1;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   bool isMoved = false;
   // exercise
   isMoved = piece.isMoved();
   // verify
   assertUnit(isMoved == true);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 1);
   assertUnit(piece.nMoves == 2);
}  // teardown

 /*************************************
  * GET NUMBER MOVES : inital when not moved
  * input: piece.fWhite=false .lastMove=0 .nMoves=0 .pos(2,3) .type=space
  * output:0
  **************************************/
void TestPiece::getNMoves_initial()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 0;
   piece.nMoves = 0;
   piece.position = Position(2, 3);
   int nMoves = 9;
   // exercise
   nMoves = piece.getNMoves();
   // verify
   assertUnit(nMoves == 0);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 0);
   assertUnit(piece.nMoves == 0);
}  // teardown

 /*************************************
  * GET NUMBER MOVES : has moved twice
  * input: piece.fWhite=false .lastMove=1 .nMoves=2 .pos(2,3) .type=space
  * output:2
  **************************************/
void TestPiece::getNMoves_hasMoved()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 1;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int nMoves = 9;
   // exercise
   nMoves = piece.getNMoves();
   // verify
   assertUnit(nMoves == 2);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 1);
   assertUnit(piece.nMoves == 2);
}  // teardown


 /*************************************
  * GET POSITION
  * input: piece.fWhite=false .lastMove=1 .nMoves=2 .pos(2,3) .type=space
  * output:pos(2,3)
  **************************************/
void TestPiece::getPosition()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 1;
   piece.nMoves = 2;
   piece.position = Position(2,3);
   Position pos;
   // exercise
   pos = piece.getPosition();
   // verify
   assertUnit(pos == Position(2,3));
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 1);
   assertUnit(piece.nMoves == 2);
}  // teardown

 /*************************************
  * JUST MOVED : initial position of the piece
  * input: piece.fWhite=false .lastMove=0 .nMoves=0 .pos(2,3) .type=space
  *        currentMove=7
  * output:false
  **************************************/
void TestPiece::justMoved_initial()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 0;
   piece.nMoves = 0;
   piece.position = Position(2, 3);
   int currentMove = 7;
   bool justMoved = true;
   // exercise
   justMoved = piece.justMoved(currentMove);
   // verify
   assertUnit(justMoved == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 0);
   assertUnit(piece.nMoves == 0);
}  // teardown

 /*************************************
  * JUST MOVED : moved a few times
  * input: piece.fWhite=false .lastMove=4 .nMoves=2 .pos(2,3) .type=space
  *        currentMove=7
  * output:false
  **************************************/
void TestPiece::justMoved_hasMoved()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 4;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int currentMove = 7;
   bool justMoved = true;
   // exercise
   justMoved = piece.justMoved(currentMove);
   // verify
   assertUnit(justMoved == false);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 4);
   assertUnit(piece.nMoves == 2);
}  // teardown

 /*************************************
  * JUST MOVED : just moved
  * input: piece.fWhite=false .lastMove=4 .nMoves=2 .pos(2,3) .type=space
  *        currentMove=5
  * output:true
  **************************************/
void TestPiece::justMoved_justMoved()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 4;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int currentMove = 5;
   bool justMoved = false;
   // exercise
   justMoved = piece.justMoved(currentMove);
   // verify
   assertUnit(justMoved == true);
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 4);
   assertUnit(piece.nMoves == 2);
}  // teardown

 /*************************************
  * SET LAST MOVE
  * input:  piece.fWhite=false .lastMove=4 .nMoves=2 .pos(2,3) .type=space
  *         currentMove=6
  * output: piece.fWhite=false .lastMove=6 .nMoves=3 .pos(2,3) .type=space
  **************************************/
void TestPiece::setLastMove()
{  // setup
   PieceDerived piece(0, 0, true);
   piece.fWhite = false;
   piece.lastMove = 4;
   piece.nMoves = 2;
   piece.position = Position(2, 3);
   int currentMove = 6;
   // exercise
   piece.setLastMove(currentMove);
   // verify
   assertUnit(piece.fWhite == false);
   assertUnit(piece.lastMove == 6);
   assertUnit(piece.nMoves == 3);
}  // teardown

