/***********************************************************************
 * Source File:
 *    BOARD
 * Author:
 *    <Roger Galan, Jessen Forbush>
 * Summary:
 *    A collection of pieces and a small amount of game state
 ************************************************************************/

#include "board.h"
#include "uiDraw.h"
#include "position.h"
#include "piece.h"
#include "pieceKnight.h"
#include <cassert>
using namespace std;

/***********************************************
 * BOARD : RESET
 *         Just fill the board with the known pieces
 *   +---a-b-c-d-e-f-g-h---+
 *   |                     |
 *   8     N         N     8
 *   7                     7
 *   6                     6
 *   5                     5
 *   4                     4
 *   3                     3
 *   2                     2
 *   1     n         n     1
 *   |                     |
 *   +---a-b-c-d-e-f-g-h---+
 ***********************************************/
void Board::reset(bool fFree)
{
   // free everything
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;

   // Add white knights at b8 (1,7) and g8 (6,7)
   board[1][7] = new Knight(1, 7, true);
   board[6][7] = new Knight(6, 7, true);

   // Add black knights at b1 (1,0) and g1 (6,0)
   board[1][0] = new Knight(1, 0, false);
   board[6][0] = new Knight(6, 0, false);

   // Fill empty spaces with Space objects
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         if (board[c][r] == nullptr)
            board[c][r] = new Space(c, r);
}


/***********************************************
* BOARD : GET
*         Get a piece from a given position.
***********************************************/
const Piece& Board::operator [] (const Position& pos) const
{
   Piece* p = board[pos.getCol()][pos.getRow()];
   return *p;
}

Piece& Board::operator [] (const Position& pos)
{
   //assert(pos.isValid());
   Piece* p = board[pos.getCol()][pos.getRow()];
   return *p;
}

/***********************************************
* BOARD : DISPLAY
*         Display the board
***********************************************/
void Board::display(const Position& posHover, const Position& posSelect) const
{
   // First draw the board
   if (pgout != nullptr)
   {
      pgout->drawBoard();
      pgout->drawHover(posHover);
      pgout->drawSelected(posSelect);

      // Draw all the pieces on the board
      for (int r = 0; r < 8; r++)
      {
         for (int c = 0; c < 8; c++)
         {
            if (board[c][r] != nullptr && board[c][r]->getType() != SPACE)
            {
               board[c][r]->display(pgout);
            }
         }
      }
   }
}


/************************************************
 * BOARD : CONSTRUCT
 *         Free up all the allocated memory
 ************************************************/
Board::Board(ogstream* pgout, bool noreset) : pgout(pgout), numMoves(0)
{
   // Initialize everything to nullptr
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         board[c][r] = nullptr;

   // Only reset the board if asked
   if (!noreset)
      reset();
}


/************************************************
 * BOARD : FREE
 *         Free up all the allocated memory
 ************************************************/
void Board::free()
{
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         if (board[c][r] != nullptr)
         {
            delete board[c][r];
            board[c][r] = nullptr;
         }
}


/**********************************************
 * BOARD : ASSERT BOARD
 *         Verify the board is well-formed
 *********************************************/
void Board::assertBoard()
{
   // Verify pointers are valid
   for (int r = 0; r < 8; r++)
      for (int c = 0; c < 8; c++)
         assert(board[c][r] != nullptr);
}




/**********************************************
 * BOARD : MOVE
 *         Execute a move according to the contained instructions
 *   INPUT move The instructions of the move
 *********************************************/
void Board::move(const Move& move)
{
   // Get source and destination positions
   int srcCol = move.getSrc().getCol();
   int srcRow = move.getSrc().getRow();
   int destCol = move.getDest().getCol();
   int destRow = move.getDest().getRow();

   // Check if positions are valid
   if (!move.getSrc().isValid() || !move.getDest().isValid())
      return;

   // Get the piece at the source position
   Piece* piece = board[srcCol][srcRow];

   // Check if there's actually a piece at the source
   if (piece == nullptr || piece->getType() == SPACE)
      return;

   // Update the move counter of the piece
   piece->setLastMove(numMoves);

   // Move the piece to the destination
   board[destCol][destRow] = piece;

   // Clear the source position by placing a Space there
   board[srcCol][srcRow] = new Space(srcCol, srcRow);

   // Increment move counter
   numMoves++;
}



/**********************************************
 * BOARD EMPTY
 * The game board that is completely empty.
 * It does not even have spaces though each non-filled
 * spot will report it has a space. This is for unit testing
 *********************************************/
BoardEmpty::BoardEmpty() : BoardDummy(), pSpace(nullptr)
{
   pSpace = new Space(1, 2);
}
BoardEmpty::~BoardEmpty()
{
   delete pSpace;
}


