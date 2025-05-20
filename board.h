/***********************************************************************
 * Header File:
 *    BOARD
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#pragma once

#include <stack>
#include <cassert>
#include "move.h"   // Because we return a set of Move
#include "pieceSpace.h"

class ogstream;
class TestPawn;
class TestKnight;
class TestBishop;
class TestRook;
class TestQueen;
class TestKing;
class TestBoard;
class Position;
class Piece;


/***************************************************
 * BOARD
 * The game board
 **************************************************/
class Board
{
   friend TestPawn;
   friend TestKnight;
   friend TestBishop;
   friend TestRook;
   friend TestQueen;
   friend TestKing;
   friend TestBoard;
public:

   // create and destroy the board
   Board(ogstream* pgout = nullptr, bool noreset = false);
   virtual ~Board() {}

   // getters
   virtual int  getCurrentMove() const { return numMoves; }
   virtual bool whiteTurn()      const { return numMoves % 2 == 0 ? true : false; }
   virtual void display(const Position& posHover, const Position& posSelect) const;
   virtual const Piece& operator [] (const Position& pos) const;

   // setters
   virtual void free();
   virtual void reset(bool fFree = true);
   virtual void move(const Move& move);
   virtual Piece& operator [] (const Position& pos);

protected:
   void  assertBoard();

   Piece* board[8][8];    // the board of chess pieces
   int numMoves;

   ogstream* pgout;
};


/***************************************************
 * BOARD DUMMY BOARD
 * A board double that does nothing but assert. Will need this for unit tests.
 **************************************************/
class BoardDummy : public Board
{
   friend TestBoard;
public:
   BoardDummy()
   {
      numMoves = 0;
      for (int row = 0; row < 8; ++row)
      {
         for (int col = 0; col < 8; ++col)
            board[col][row] = nullptr;
      }
   }

   ~BoardDummy() {}

   void display(const Position& posHover,
      const Position& posSelect) const {
      assert(false);
   }
   void move(const Move& move) { assert(false); }
   int  getCurrentMove() const { assert(false); return 0; }
   bool whiteTurn()      const { assert(false); return false; }
   Piece& operator [] (const Position& pos)
   {
      assert(false);
      throw true;
   }
   const Piece& operator [] (const Position& pos) const
   {
      assert(false);
      throw true;
   }
};

/***************************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 **************************************************/
class BoardEmpty : public BoardDummy
{
   friend TestBoard;
public:
   Piece* pSpace;
   int moveNumber;

   BoardEmpty();
   ~BoardEmpty();
   const Piece& operator [] (const Position& pos) const
   {
      assert(pos.isValid());
      if (board[pos.getCol()][pos.getRow()])
         return *(board[pos.getCol()][pos.getRow()]);
      else
         return *pSpace;
   }
   int  getCurrentMove() const { return moveNumber; }
};

