/***********************************************************************
 * Header File:
 *    MOVE
 * Author:
 *    <Jessen Forbush, Roger Galan>
 * Summary:
 *    Everything we need to know about a single chess move
 ***********************************************************************/

#pragma once

#include <string>
#include "position.h"  // Every move has two Positions as attributes
#include "pieceType.h" // A piece type

using std::string;
using std::ostream;
using std::istream;

class TestMove;
class TestBoard;
class TestKnight;
class TestBishop;
class TestRook;
class TestQueen;
class TestKing;
class TestPawn;

/***************************************************
 * MOVE
 * One move across the board
 ***************************************************/
class Move
{
public:
   enum MoveType { MOVE, ENPASSANT, CASTLE_KING, CASTLE_QUEEN, MOVE_ERROR };

   friend class TestMove;
   friend class TestBoard;
   friend class TestKnight;
   friend class TestBishop;
   friend class TestRook;
   friend class TestQueen;
   friend class TestKing;
   friend class TestPawn;

   // Constructors
   Move();
   Move(const string& str);

   // Methods related to move text and parsing
   void read(const string& str);
   string getText() const { return text; }
   void assign(string str) { read(str); }

   // Position getters
   Position getSrc() const { return source; }
   Position getDest() const { return dest; }

   void setSrc(Position pos) { source = pos; }
   void setDest(Position pos) { dest = pos; }

   // Piece information getters
   PieceType getPromotion() const { return promote; }
   PieceType getCapture() const { return capture; }

   void setCapture(PieceType pt) { capture = pt; }

   // Special move type getters
   bool getEnPassant() const { return enpassant; }
   bool getCastleK() const { return castleK; }
   bool getCastleQ() const { return castleQ; }
   bool getWhiteMove() const { return isWhite; }

   // Special move type setters
   void setEnPassant()
   {
      enpassant = true;
      moveType = ENPASSANT;
   }

   void setCastle(bool isKing);
   void setCastleQ()
   {
      castleQ = true;
      moveType = CASTLE_QUEEN;
   }

   void setWhiteMove(bool whiteOrBlack) { isWhite = whiteOrBlack; }

   // Move assignment
   void assign(Move& move);

   // Operators
   bool operator==(const Move& rhs) const { return dest == rhs.dest && source == rhs.source && dest.getLocation() == rhs.dest.getLocation() && source.getLocation() == rhs.source.getLocation(); }
   bool operator!=(const Move& rhs) const { return !(*this == rhs); }
   bool operator<(const Move& rhs) const { return dest < rhs.dest; }

private:
   // Helper methods
   char letterFromPieceType(PieceType pt) const;
   PieceType pieceTypeFromLetter(char letter) const;
   void processSpecialMoveChar(char specialChar);

   // Move attributes
   Position  source;    // where the move originated from
   Position  dest;      // where the move finished
   PieceType promote;   // piece to be promoted to
   PieceType capture;   // did a capture happen this move?
   MoveType  moveType;  // what type of move is this?
   bool      isWhite;   // whose turn is it anyway?
   string    text;      // what is the textual version of the move?

   // Special move flags
   bool      enpassant; // is this an en passant capture?
   bool      castleK;   // is this a king-side castle?
   bool      castleQ;   // is this a queen-side castle?
   string    error;     // any error message
};

// Stream operators
ostream& operator << (ostream& out, const Move& move);
istream& operator >> (istream& in, Move& move);
