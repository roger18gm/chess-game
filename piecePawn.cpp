/***********************************************************************
 * Source File:
 *    PAWN
 * Author:
 *    Jessen Forbush and Roger Galan
 * Summary:
 *    The PAWN class
 ************************************************************************/

#include "piecePawn.h"
#include "board.h"
#include "uiDraw.h"    // for draw*()
#include <iostream>

 /***************************************************
 * PIECE DRAW
 * Draw all the pieces.
 ***************************************************/
void Pawn::display(ogstream* pgout) const
{
   if (pgout != nullptr)
   {
      pgout->drawPawn(position, !isWhite());
   }
}

/***************************************************
* PAWN : GET POSITIONS
***************************************************/
void Pawn::getMoves(set <Move>& moves, const Board& board) const
{
   // Determine forward direction based on color
   int forwardRowDelta = fWhite ? 1 : -1;

   // Check if we can move forward one
   Position posOneStep(position.getCol(), position.getRow() + forwardRowDelta);
   if (posOneStep.isValid() && board[posOneStep].getType() == SPACE)
   {
      Move move;
      move.setSrc(position);
      move.setDest(posOneStep);
      move.setWhiteMove(isWhite());
      move.setCapture(SPACE); 
      moves.insert(move);

      // Check if we can move forward by two
      if (nMoves == 0) 
      {
         Position posTwoSteps(position.getCol(), position.getRow() + (forwardRowDelta * 2));
         if (posTwoSteps.isValid() && board[posTwoSteps].getType() == SPACE)
         {
            Move moveTwoSteps;
            moveTwoSteps.setSrc(position);
            moveTwoSteps.setDest(posTwoSteps);
            moveTwoSteps.setWhiteMove(isWhite());
            moveTwoSteps.setCapture(SPACE); 
            moves.insert(moveTwoSteps);
         }
      }
   }

   // Check for diagonal captures
   int captureColDeltaLeft = -1; // Column change for left capture
   int captureColDeltaRight = 1; // Column change for right capture

   // Check left diagonal capture
   Position posCaptureLeft(position.getCol() + captureColDeltaLeft, position.getRow() + forwardRowDelta);
   if (posCaptureLeft.isValid())
   {
      PieceType pieceAtCaptureLeft = board[posCaptureLeft].getType();
      if (pieceAtCaptureLeft != SPACE && board[posCaptureLeft].isWhite() != fWhite)
      {
         Move move;
         move.setSrc(position);
         move.setDest(posCaptureLeft);
         move.setWhiteMove(isWhite());
         move.setCapture(pieceAtCaptureLeft); 
         moves.insert(move);
      }
   }

   // Check right diagonal capture
   Position posCaptureRight(position.getCol() + captureColDeltaRight, position.getRow() + forwardRowDelta);
   if (posCaptureRight.isValid())
   {
      PieceType pieceAtCaptureRight = board[posCaptureRight].getType();
      if (pieceAtCaptureRight != SPACE && board[posCaptureRight].isWhite() != fWhite)
      {
         Move move;
         move.setSrc(position);
         move.setDest(posCaptureRight);
         move.setWhiteMove(isWhite());
         move.setCapture(pieceAtCaptureRight); 
         moves.insert(move);
      }
   }

   // Check for en passant on the left
   Position posAdjacentLeft(position.getCol() + captureColDeltaLeft, position.getRow()); // Piece left of pawn
   Position posEnPassantLeftTarget(position.getCol() + captureColDeltaLeft, position.getRow() + forwardRowDelta); // The left diagonal square
   if (posAdjacentLeft.isValid() && board[posAdjacentLeft].getType() == PAWN &&
      board[posAdjacentLeft].isWhite() != fWhite &&
      board[posAdjacentLeft].getNMoves() == 1 && 
      board[posAdjacentLeft].justMoved(board.getCurrentMove()) &&
      posEnPassantLeftTarget.isValid() && board[posEnPassantLeftTarget].getType() == SPACE)
   {
      Move move;
      move.setSrc(position);
      move.setDest(posEnPassantLeftTarget);
      move.setWhiteMove(isWhite());
      move.setCapture(PAWN); 
      move.setEnPassant();
      moves.insert(move);
   }

   // Check for en passant on the right
   Position posAdjacentRight(position.getCol() + captureColDeltaRight, position.getRow()); // Piece right of pawn
   Position posEnPassantRightTarget(position.getCol() + captureColDeltaRight, position.getRow() + forwardRowDelta); // The right diagonal square
   if (posAdjacentRight.isValid() && board[posAdjacentRight].getType() == PAWN &&
      board[posAdjacentRight].isWhite() != fWhite &&
      board[posAdjacentRight].getNMoves() == 1 && 
      board[posAdjacentRight].justMoved(board.getCurrentMove()) &&
      posEnPassantRightTarget.isValid() && board[posEnPassantRightTarget].getType() == SPACE)
   {
      Move move;
      move.setSrc(position);
      move.setDest(posEnPassantRightTarget);
      move.setWhiteMove(isWhite());
      move.setCapture(PAWN); 
      move.setEnPassant();
      moves.insert(move);
   }
}