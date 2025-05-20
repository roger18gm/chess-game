/***********************************************************************
 * Header File:
 *    USER INTERFACE DRAW
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#pragma once

#include "position.h"
#include <sstream>    // for OSTRINGSTRING
using std::string;

 /*************************************************************************
  * GRAPHICS STREAM
  * A graphics stream that behaves much like COUT except on a drawn screen.
  * Special methods are added to facilitate drawing simulator elements.
  *************************************************************************/
class ogstream : public std::ostringstream
{
public:
    ogstream() : position()                                 {          }
    ogstream(const Position& position) : position(position) {          }
    ~ogstream()                                             { flush(); }

    // Methods specific to drawing text on the screen
    virtual void flush();
    void setPosition(const Position& position) { flush(); this->position = position; }
    ogstream& operator = (const Position& position)
    {
        setPosition(position);
        return *this;
    }

    // Methods to draw the chess pieces on the screen
    virtual void drawKing(  const Position& pos, bool black);
    virtual void drawQueen( const Position& pos, bool black);
    virtual void drawRook(  const Position& pos, bool black);
    virtual void drawPawn(  const Position& pos, bool black);
    virtual void drawBishop(const Position& pos, bool black);
    virtual void drawKnight(const Position& pos, bool black);

    // Methods to draw the board 
    virtual void drawBoard();
    virtual void drawSelected(const Position& pos);
    virtual void drawHover(   const Position& pos);
    virtual void drawPossible(const Position& pos);

protected:
    Position position;

private:

    /************************************************************************
    * RECT
    * One rectangle
    *************************************************************************/
    struct Rect
    {
        int x0;
        int y0;
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
    };

    void drawPiece(bool black, Rect rectangle[], int num) const;
    void drawText(const Position& topLeft, const char* text) const;
    void drawLetter(const Position& topLeft, char letter) const;
};
