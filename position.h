/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <Jessen Forbush, Roger Galan>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#pragma once

#include <string>
#include <cstdint>
using std::string;
using std::ostream;
using std::istream;

const int SIZE_SQUARE = 32;   // number of pixels in a square by default

/***********************************************
 * DELTA
 * Movement in a direction (dRow and dCol)
 **********************************************/
struct Delta
{
   int dRow;
   int dCol;
};

const Delta ADD_R = { 1,  0 };
const Delta ADD_C = { 0,  1 };
const Delta SUB_R = { -1,  0 };
const Delta SUB_C = { 0, -1 };


class PositionTest;
class TestMove;
class TestKnight;
class TestBishop;
class TestRook;
class TestQueen;
class TestKing;
class TestPawn;
class TestBoard;

/***************************************************
 * POSITION
 * The location of a piece on the board
 ***************************************************/
class Position
{
   friend class PositionTest;
   friend class TestMove;
   friend class TestKnight;
   friend class TestBishop;
   friend class TestRook;
   friend class TestQueen;
   friend class TestKing;
   friend class TestPawn;
   friend class TestBoard;
public:

   // Position :    The Position class can work with other positions,
   //               Allowing for comparisions, copying, etc.
   Position(const Position& rhs) : colRow(rhs.colRow) {}
   Position() : colRow(0xff) {}

   bool isInvalid() const;
   bool isValid()   const;
   void setValid() {} // dont know if we need these...
   void setInvalid() {}
   bool operator <  (const Position& rhs) const { return this->colRow < rhs.colRow; }
   bool operator == (const Position& rhs) const { return this->colRow == rhs.colRow; }
   bool operator != (const Position& rhs) const { return this->colRow != rhs.colRow; }
   const Position& operator=(const Position& rhs);

   // Location : The Position class can work with locations, which
   //            are 0...63 where we start in row 0, then row 1, etc.
   Position(int location) { setLocation(location); }
   int getLocation() const;
   void setLocation(int location);

   // Row/Col : The position class can work with row/column,
   //           which are 0..7 and 0...7
   Position(int c, int r) { set(c, r); }
   virtual int getCol() const;
   virtual int getRow() const;
   void setRow(int r);
   void setCol(int c);
   void set(int c, int r);

   // Text:    The Position class can work with textual coordinates,
   //          such as "d4"

   Position(const char* s);
   const Position& operator=(const char* rhs);
   const Position& operator=(const string& rhs)
   {
      *this = Position(rhs.c_str());
      return *this;
   }
   string getText() const;
   // Pixels:    The Position class can work with screen coordinates,
   //            a.k.a. Pixels, these are X and Y coordinates. Note that
   //            we need to scale them according to the size of the board.
   int getX()   const
   {
      return (int)((double)getCol() * getSquareWidth() + getSquareWidth());
   }
   int getY()   const
   {
      return (int)((double)getRow() * getSquareHeight() + getSquareHeight());
   }
   void setXY(double x, double y);

   double getSquareWidth()  const { return squareWidth; }
   double getSquareHeight() const { return squareHeight; }
   void setBoardWidthHeight(int widthBoard, int heightBoard);

   // Delta:    The Position class can work with deltas, which are
   //           offsets from a given location. This helps pieces move
   //           on the chess board.
   Position(const Position& rhs, const Delta& delta);
   void adjustRow(int dRow) { setRow(getRow() + dRow); }
   void adjustCol(int dCol) { setCol(getCol() + dCol); }
   const Position& operator += (const Delta& rhs) {
      set(getCol() + rhs.dCol, getRow() + rhs.dRow);
      return *this;
   }
   Position operator + (const Delta& rhs) const { return Position(rhs.dCol, rhs.dRow); }

private:
   void set(uint8_t colRowNew) { colRow = colRowNew; }

   uint8_t colRow;
   static double squareWidth;
   static double squareHeight;
};

ostream& operator << (ostream& out, const Position& pos);
istream& operator >> (istream& in, Position& pos);
