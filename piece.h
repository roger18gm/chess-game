/***********************************************************************
 * Header File:
 *    PIECE 
 * Author:
*    Jessen Forbush and Roger Galan
 * Summary:
 *    The Piece base class and all the derived classes:
 *       SPACE, KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN
 ************************************************************************/

#pragma once

#include <set>         // for SET to return a set of possible moves
#include <list>        // for the move-type,list
#include <cassert>
#include "position.h"  // Because Position is a member variable
#include "move.h"      // Because we return a set of Move
#include "pieceType.h" // A piece type.
using std::set;

// forward declaration because one of the Piece methods takes a Board
// as a parameter, and the Board has an array of Pieces
class ogstream;
class Board;
class MoveType;

class TestPiece;
class TestKing;
class TestPawn;
class TestQueen;
class TestRook;
class TestBishop;
class TestKnight;
class TestBoard;


/***************************************************
 * PIECE
 * The abstract piece type
 ***************************************************/
class Piece
{
public:
   friend TestPiece;
   friend TestKing;
   friend TestQueen;
   friend TestRook;
   friend TestBishop;
   friend TestKnight;
   friend TestPawn;
   friend TestBoard;
   
   // constructors and stuff
   Piece(const Position & pos, bool isWhite = true) : position(pos), fWhite(isWhite), nMoves(0), lastMove(0)    {}
   Piece(int c, int r, bool isWhite = true) : position(c,r), fWhite(isWhite), nMoves(0), lastMove(0) {}
   Piece(const Piece& piece) { *this = piece; }
   virtual ~Piece()                                   {}
   virtual const Piece& operator = (const Piece& rhs);

   // getters
   virtual bool operator == (PieceType pt) const { return getType() == pt; }
   virtual bool operator != (PieceType pt) const { return getType() != pt; }
   virtual bool isWhite()                  const { return fWhite;         }
   virtual bool isMoved()                  const { return getNMoves() != 0;         }
   virtual int  getNMoves()                const { return nMoves;         }
   virtual void decrementNMoves() { nMoves-= (nMoves > 1) ? 2 : 0; }
   virtual const Position & getPosition()  const { return position;   }
   virtual bool justMoved(int currentMove) const { return currentMove - 1 == lastMove; }

   // setter
   virtual void setLastMove(int currentMove) 
   { 
      lastMove = currentMove; 
      nMoves++; 
   }

   // overwritten by the various pieces
   virtual PieceType getType()                                    const = 0;
   virtual void display(ogstream * pgout)                         const = 0;
   void getMoves(set <Move>& moves, const Board& board) const {};

protected:

   int  nMoves;                    // how many times have you moved?
   bool fWhite;                    // which team are you on?
   Position position;              // current position of this piece
   int  lastMove;                  // last time this piece moved
   set <Move> getMovesSlide(const Board& board, const Delta deltas[], int numDelta) const;
   set <Move> getMovesNoSlide(const Board& board, const Delta deltas[], int numDelta) const;
};



/***************************************************
 * PIECE DERIVED
 * A simple derived class so we can test Piece. This is a Space
 ***************************************************/
class PieceDerived : public Piece
{
public:
   PieceDerived(const Position& pos, bool isWhite) : Piece(pos, isWhite) { }
   PieceDerived(int c, int r, bool isWhite) : Piece(c, r, isWhite)        { }
   ~PieceDerived()                                                       { }
   PieceType getType()            const     { return SPACE;                }
   void display(ogstream* pgout)  const     { assert(false);               }
};



/***************************************************
 * PIECE DUMMY
 * The dummy double! - Everything returns FALSE
 ***************************************************/
class PieceDummy : public Piece
{
public:

   // constructors and stuff
   PieceDummy()                                          : Piece(0, 0, true   ) {}
   PieceDummy(const Position & pos, bool isWhite = true) : Piece(pos,  isWhite) {}
   PieceDummy(int c, int r, bool isWhite = true)         : Piece(c, r, isWhite) {}
   PieceDummy(const Piece & piece)                       : Piece(0, 0, true   ) {}
   ~PieceDummy()                                                                {}
   const Piece& operator = (const Piece& rhs)
   {
      assert(false);
      return *this;
   }
   const Piece& operator = (const Position& rhs)
   {
      assert(false);
      return *this;
   }

   // getters
   bool operator == (char letter)  const { assert(false); return true;  }
   bool operator != (char letter)  const { assert(false); return true;  }
   bool isWhite()                  const { assert(false); return true;  }
   bool isMoved()                  const { assert(false); return true;  }
   int  getNMoves()                const { assert(false); return 0;     }
   void decrementNMoves()                { assert(false);               }
   const Position & getPosition()  const { assert(false); return position; }
   bool justMoved(int currentMove) const { assert(false); return true;  }

   // setter
   void setLastMove(int currentMove)     { assert(false);               }

   // overwritten by the various pieces
   PieceType getType()             const { assert(false); return SPACE; }
   void display(ogstream * pgout)  const { assert(false);               }
};

/***************************************************
 * PIECE SPY
 * A piece that is only counted.
 **************************************************/
class PieceSpy : public PieceDummy
{
public:
   PieceSpy(int c, int r, bool f = true, PieceType pt = SPACE) 
      : PieceDummy(c, r, f), pt(pt)
   {
      numConstruct++;
   }
   PieceSpy(const PieceSpy& piece) : PieceDummy(piece), pt(SPACE)
   {
      numCopy++;
   }
   ~PieceSpy()
   {
      numDelete++;
   }
   const PieceSpy& operator = (const PieceSpy& rhs)
   {
      numAssign++;
      return *this;
   }
   const Piece& operator = (const Position& rhs)
   {
      numMove++;
      nMoves++;                    // it moved one more time
      position = rhs;              // actually change the position
      return *this;                // return self
   }
   void setLastMove(int currentMove) { lastMove = currentMove; }
   const Position& getPosition()  const { return position; }
   PieceType getType()            const { return pt;       }
   bool isWhite()                 const { return fWhite;   }


   static int numConstruct;
   static int numCopy;
   static int numDelete;
   static int numAssign;
   static int numMove;

   static void reset()
   {
      numConstruct = numCopy = numDelete = numAssign = numMove = 0;
   }
private:
   PieceType pt;
};


/***************************************************
 * WHITE PIECE
 * Generic piece whose only allowable property is the color
 **************************************************/
class White : public PieceDummy
{
   PieceType pt;
public:
   White() : PieceDummy(), pt(ROOK) {}
   White(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const { return true; }
   PieceType getType() const { return pt; }
   int  getNMoves()                const { return nMoves; }
   void getMoves(set <Move>& moves, const Board& board) const { }
   virtual bool justMoved(int currentMove) const { return currentMove - 1 == lastMove; }
};

class Black : public PieceDummy
{
   PieceType pt;
public:
   Black() : PieceDummy(), pt(ROOK) {}
   Black(PieceType pt) : PieceDummy(), pt(pt) {}
   bool isWhite() const { return false; }
   PieceType getType() const { return pt; }
   int  getNMoves()                const { return nMoves; }
   void getMoves(set <Move>& moves, const Board& board) const { }
   virtual bool justMoved(int currentMove) const { return currentMove - 1 == lastMove; }
};



