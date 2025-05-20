/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    <Jessen Forbush, Roger Galan>
 * Summary:
 *    The position of a piece, the cursor, or a possible move on a chess board
 ************************************************************************/

#include "position.h"
#include <iostream>

 /******************************************
  * POSITION COPY CONSTRUCTOR WITH DELTA
  ******************************************/
Position::Position(const Position& rhs, const Delta& delta)
{
   int newRow = rhs.getRow() + delta.dRow;
   int newCol = rhs.getCol() + delta.dCol;
   set(newCol, newRow);
}

/******************************************
 * POSITION INSERTION OPERATOR
 ******************************************/
ostream& operator << (ostream& out, const Position& pos)
{
   if (!pos.isValid())            //
      return out << "??";         //

   char col = 'a' + pos.getCol(); //
   char row = '8' - pos.getRow(); //
   return out << col << row;
}

/*************************************
 * POSITION EXTRACTION OPERATOR
 **************************************/
istream& operator >> (istream& in, Position& pos)
{
   string s; //
   in >> s; //
   pos = s; //
   return in;
}


/*************************************
 * IS INVALID
 **************************************/
bool Position::isInvalid() const
{
   // Check if the position is completely invalid (0xff)
   if (colRow == 0xff)
      return true;

   // Extract the row and column values
   int row = colRow & 0x0F;
   int col = (colRow >> 4) & 0x0F;

   // Position is invalid if either row or column is outside range 0-7
   return (row > 7 || col > 7);
}

/*************************************
 * IS VALID
 **************************************/
bool Position::isValid() const
{
   // Check if this is a completely invalid position (0xff)
   if (colRow == 0xff)
      return false;

   // Extract the row and column values
   int row = colRow & 0x0F;
   int col = (colRow >> 4) & 0x0F;

   // Position is valid only if both row and column are in range 0-7
   return (row <= 7 && col <= 7);
}

/*************************************
 * OPERATOR: =
 **************************************/
const Position& Position::operator=(const Position& rhs)
{
   // Check for self-assignment
   if (this == &rhs)
      return *this;

   // Copy the colRow value
   this->colRow = rhs.colRow;

   // Return a reference to the current object
   return *this;
}

/*************************************
 * GET LOCATION
 **************************************/
int Position::getLocation() const
{
   // Extract column from upper 4 bits
   int col = (colRow >> 4) & 0x0F;

   // Extract row from lower 4 bits
   int row = colRow & 0x0F;

   // Convert to location (0-63)
   return row * 8 + col;
}

/*************************************
 * GET COLUMN
 **************************************/
int Position::getCol() const
{
   // Check if this is an invalid position (0xff)
   if (colRow == 0xff)
      return -1;

   // Extract the col and row values
   int col = (colRow >> 4) & 0x0F;
   int row = colRow & 0x0F;

   // Check if either col or row is invalid (0-7)
   return (col > 7 || row > 7) ? -1 : col;
}

/*************************************
 * GET ROW
 **************************************/
int Position::getRow() const
{
   // Check if the position is invalid
   if (colRow == 0xff)
      return -1;

   // Extract the row and col values
   int row = colRow & 0x0F;
   int col = (colRow >> 4) & 0x0F;

   // Check if row is valid (0-7)
   return (row > 7 || col > 7) ? -1 : row;
}

/*************************************
 * SET ROW
 **************************************/
void Position::setRow(int r)
{
   // Check if we're setting an invalid row
   if (r < 0 || r > 7)
   {
      colRow = 0xff; // Mark as invalid position
      return;
   }

   // Keep the column bits (upper 4 bits) and set the row bits (lower 4 bits)
   colRow = (colRow & 0xF0) | (r & 0x0F);
}

/*************************************
 * SET COLUMN
 **************************************/
void Position::setCol(int c)
{
   // Check if we're setting an invalid column
   if (c < 0 || c > 7)
   {
      colRow = 0xff; // Mark as invalid position
      return;
   }

   // Keep the row bits (lower 4 bits) and set the column bits (upper 4 bits)
   colRow = (colRow & 0x0F) | ((c & 0x0F) << 4);
}

/*************************************
 * SET
 **************************************/
void Position::set(int c, int r)
{
   // Check if we're setting an invalid row or column
   if (r < 0 || r > 7 || c < 0 || c > 7)
   {
      colRow = 0xff; // Mark as invalid position
      return;
   }

   // Combine the column and row values into a single byte
   colRow = ((c & 0x0F) << 4) | (r & 0x0F);
}

/*************************************
 * SET LOCATION
 **************************************/
void Position::setLocation(int location)
{  // example location: 57
   if (location < 0 || location >= 64)
   {
      colRow = 0xff;
      return;
   }
   int row = location / 8;
   int col = location % 8;
   set(col, row);
}

/*************************************
 * SET: XY
 **************************************/
void Position::setXY(double x, double y)
{
   // Calculate the column and row
   int col = (int)(x / getSquareWidth()) - 1;
   int row = 8 - (int)(y / getSquareHeight());

   // Check if X coordinate is invalid (out of bounds)
   if (col < 0 || col > 7)
   {
      colRow = 0xff; // Set to 0xff for invalid X position
      return;
   }

   // Check if Y coordinate is invalid (out of bounds)
   if (row < 0 || row > 7)
   {
      colRow = 0x3f; // Set to 0x3f for invalid Y position
      return;
   }

   // Set the row and column
   set(col, row);
}

/*************************************
 * SET BOARD WIDTH AND HEIGHT
 **************************************/
void Position::setBoardWidthHeight(int widthBoard, int heightBoard)
{
   if (widthBoard < 0 || heightBoard < 0)
      return;
   squareWidth = (double)widthBoard / 10.0; // 8 squares + 2 spaces
   squareHeight = (double)heightBoard / 10.0;
}

/*************************************
 * CHARACTER STRING: CONSTRUCTOR
 **************************************/
Position::Position(const char* s)
{
   // Skip empty string
   if (s == nullptr || *s == '\0')
   {
      colRow = 0xff;  // Invalid position
      return;
   }

   // Extract column and row from the text (e.g., "d4")
   char colChar = s[0];
   char rowChar = s[1];

   // Validate the input format
   if (!isalpha(colChar) || !isdigit(rowChar))
   {
      colRow = 0xff;  // Invalid position
      return;
   }

   // Convert column letter to 0-7 (a-h -> 0-7)
   int col = tolower(colChar) - 'a';

   // Convert row digit to 0-7 (1-8 -> 0-7)
   int row = rowChar - '1';

   // Validate ranges
   if (col < 0 || col > 7 || row < 0 || row > 7)
   {
      colRow = 0xff;  // Invalid position
      return;
   }

   // Set the position
   set(col, row);
}

/**********************
 CHARACTER STRING: ASSIGNMENT OPERATOR
 *********************************/
const Position& Position::operator=(const char* rhs)
{
   // Handle null pointer
   if (rhs == nullptr)
   {
      colRow = 0xff;  // Invalid position
      return *this;
   }

   // Extract column and row from the text
   char colChar = rhs[0];
   char rowChar = rhs[1];

   // Validate the input format
   if (!isalpha(colChar) || !isdigit(rowChar))
   {
      colRow = 0xff;  // Invalid position
      return *this;
   }

   // Convert column letter to 0-7 (a-h -> 0-7)
   int col = tolower(colChar) - 'a';

   // Convert row digit to 0-7 (1-8 -> 0-7)
   int row = rowChar - '1';

   // Validate ranges
   if (col < 0 || col > 7 || row < 0 || row > 7)
   {
      colRow = 0xff;  // Invalid position
      return *this;
   }

   // Set the position
   set(col, row);

   return *this;
}

/*************************************
 * GET TEXT
 * Convert the internal row and column to a text coordinate (e.g., "g3")
 *************************************/
string Position::getText() const
{
   if (!isValid())
      return "??";

   char colChar = 'a' + getCol();
   char rowChar = '8' - getRow();
   string text = "";
   text += colChar;
   text += rowChar;
   return text;
}