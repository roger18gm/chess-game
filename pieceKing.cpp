/***********************************************************************
 * Source File:
 *    KING
 * Author:
 *    Jessen Forbush & Roger Galan
 * Summary:
 *    The KING class
 ************************************************************************/

#include "pieceKing.h"
#include "pieceRook.h"
#include "board.h"
#include "uiDraw.h"
#include <iostream>

 /***************************************************
  * PIECE DRAW
  * Draw the king piece
  ***************************************************/
void King::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawKing(position, !isWhite());
   }
}

/**********************************************
 * KING : GET MOVES
 * Get all possible king moves including castling
 *********************************************/
void King::getMoves(set <Move>& moves, const Board& board) const
{
   const Delta delta[] =
   {
      { -1,  1 }, { 0,  1 }, { 1,  1 },
      { -1,  0 },            { 1,  0 },
      { -1, -1 }, { 0, -1 }, { 1, -1 }
   };

   // Get basic king moves (one square in any direction)
   moves = getMovesNoSlide(board, delta, sizeof(delta) / sizeof(delta[0]));

   // Add castling moves if conditions are met
   addCastlingMoves(moves, board);
}

/**********************************************
 * KING : ADD CASTLING MOVES
 * Check if king can castle and add those moves
 *********************************************/
void King::addCastlingMoves(set<Move>& moves, const Board& board) const
{
   // Can't castle if king has moved
   if (isMoved())
      return;

   // Try king-side castle (short castle)
   if (canCastleKingSide(board))
   {
      Move castleMove;
      castleMove.setSrc(position);
      castleMove.setDest(Position(position.getCol() + 2, position.getRow()));
      castleMove.setCastle(true); // true = king side
      castleMove.setWhiteMove(isWhite());
      moves.insert(castleMove);
   }

   // Try queen-side castle (long castle)
   if (canCastleQueenSide(board))
   {
      Move castleMove;
      castleMove.setSrc(position);
      castleMove.setDest(Position(position.getCol() - 2, position.getRow()));
      castleMove.setCastleQ(); // Queen side castle
      castleMove.setWhiteMove(isWhite());
      moves.insert(castleMove);
   }
}

/**********************************************
 * KING : CAN CASTLE KING SIDE
 * Check if king-side castling is possible
 *********************************************/
bool King::canCastleKingSide(const Board& board) const
{
   int row = position.getRow();
   int col = position.getCol();

   // Check if king is in starting position
   if ((isWhite() && (col != 4 || row != 0)) ||
      (!isWhite() && (col != 4 || row != 7)))
      return false;

   // Check if rook is in correct position and hasn't moved
   Position rookPos(7, row); // h1 for white, h8 for black
   if (!rookPos.isValid())
      return false;

   const Piece& rook = board[rookPos];
   if (rook.getType() != ROOK || rook.isWhite() != isWhite() || rook.isMoved())
      return false;

   // Check if squares between king and rook are empty
   for (int c = col + 1; c < 7; c++)
   {
      Position checkPos(c, row);
      if (board[checkPos].getType() != SPACE)
         return false;
   }

   return true;
}

/**********************************************
 * KING : CAN CASTLE QUEEN SIDE
 * Check if queen-side castling is possible
 *********************************************/
bool King::canCastleQueenSide(const Board& board) const
{
   int row = position.getRow();
   int col = position.getCol();

   // Check if king is in starting position
   if ((isWhite() && (col != 4 || row != 0)) ||
      (!isWhite() && (col != 4 || row != 7)))
      return false;

   // Check if rook is in correct position and hasn't moved
   Position rookPos(0, row); // a1 for white, a8 for black
   if (!rookPos.isValid())
      return false;

   const Piece& rook = board[rookPos];
   if (rook.getType() != ROOK || rook.isWhite() != isWhite() || rook.isMoved())
      return false;

   // Check if squares between king and rook are empty
   for (int c = col - 1; c > 0; c--)
   {
      Position checkPos(c, row);
      if (board[checkPos].getType() != SPACE)
         return false;
   }

   return true;
}
