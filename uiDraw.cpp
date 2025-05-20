/***********************************************************************
 * Source File:
 *    USER INTERFACE DRAW
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/


#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock

#include "position.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32


#include "uiDraw.h"
#include "uiInteract.h"

using namespace std;

// pieces: black and white
const int RGB_WHITE[] = { 255, 255, 255 };
const int RGB_BLACK[] = { 0, 0, 0 };

// normal squares: tan and brown
const int RGB_WHITE_SQUARE[] = { 210, 180, 140 };
const int RGB_BLACK_SQUARE[] = { 165, 42, 42 };

// the color of a selected square
const int RGB_SELECTED[] = { 255, 0, 0 };
//const int RGB_SELECTED[] = { 115, 88, 70 };

// color of the coordinates
const int RGB_LETTERS[] = { 128, 128, 128 };

// color of the square around the board
const int RGB_SQUARE[] = { 64, 64, 64 };

/*************************************************************************
 * DISPLAY the text in the buffer on the screen
 *************************************************************************/
void ogstream::flush()
{
   string sOut;
   string sIn = str();

   // copy everything but the newlines
   for (string::iterator it = sIn.begin(); it != sIn.end(); ++it)
      // newline triggers an buffer flush and a move down
      if (*it == '\n')
      {
         drawText(position, sOut.c_str());
         sOut.clear();
         position.adjustRow(-1);
      }
      // othewise append
      else
         sOut += *it;

   // put the text on the screen
   if (!sOut.empty())
   {
      drawText(position, sOut.c_str());
      position.adjustRow(-1);
   }

   // reset the buffer
   str("");
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text, in absolute coordinates
 *          text      The text to be displayed
 ************************************************************************/
void ogstream::drawText(const Position& topLeft, const char* text) const
{
    void* pFont = GLUT_TEXT;

    // prepare to draw the text from the top-left corner
    glRasterPos2f((GLfloat)topLeft.getX(), (GLfloat)topLeft.getY());

    // loop through the text
    for (const char* p = text; *p; p++)
        glutBitmapCharacter(pFont, *p);
}

/*************************************************************************
 * DRAW LETTER
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text, in absolute coordiantes
 *          letter    The letter to be displayed
 ************************************************************************/
void ogstream::drawLetter(const Position& topLeft, char letter) const
{
    void* pFont = GLUT_TEXT;

    // prepare to draw the text from the top-left corner
    glRasterPos2f((GLfloat)topLeft.getX(), (GLfloat)topLeft.getY());

    // loop through the text
    glutBitmapCharacter(pFont, letter);
}


/************************************************************************
* GL COLOR
* Set the color on the board
*   INPUT  rgb  RGB color in integers (0...255)
*************************************************************************/
void glColor(const int * rgb)
{
   glColor3f((GLfloat)(rgb[0] / 256.0), 
             (GLfloat)(rgb[1] / 256.0),
             (GLfloat)(rgb[2] / 256.0));
}

/************************************************************************
* DRAW Piece
* Draw a piece at a certain location on the board, in ortho coordinates
*   INPUT  location   The location of the piece
*          black      Whether the piece is black
*          rectangles The rectangles of the piece
*************************************************************************/
void ogstream::drawPiece(bool black, Rect rectangle[], int num) const
{
   assert(position.isValid());
   GLint x   = (GLint)((position.getCol() + 0.5) * 
                        SIZE_SQUARE + SIZE_SQUARE);
   GLint y   = (GLint)((position.getRow() + 0.5) *
                        SIZE_SQUARE + SIZE_SQUARE);

   // get ready to draw
   glBegin(GL_QUADS);
   glColor(black ? RGB_BLACK : RGB_WHITE);

   // iterate through the rectangles
   for (int i = 0; i < num; i++)
   { 
      glVertex2i(x + rectangle[i].x0, y + rectangle[i].y0);
      glVertex2i(x + rectangle[i].x1, y + rectangle[i].y1);
      glVertex2i(x + rectangle[i].x2, y + rectangle[i].y2);
      glVertex2i(x + rectangle[i].x3, y + rectangle[i].y3);
   }

   // finish the drawing
   glEnd();
}

/************************************************************************
* DRAW King
* Draw a king at a certain location on the board
*   INPUT  location  The location of the king
*          black     Whether the king is black
*************************************************************************/
void ogstream::drawKing(const Position& pos, bool black)
{
   Rect rectangles[] =
   {
      { 1,8,  -1,8,  -1,1,   1,1},     // cross vertical
      {-3,6,   3,6,   3,4,  -3,4},     // cross horizontal
      {-8,3,  -8,-3, -3,-3, -3,3},     // bug bump left
      { 8,3,   8,-3,  3,-3,  3,3},     // bug bump right
      { 5,1,   5,-5, -5,-5, -5,1},     // center column
      { 8,-4, -8,-4, -8,-5,  8,-5},    // base center
      { 8,-6, -8,-6, -8,-8,  8,-8}     // base
   };
   
   position = pos;
   drawPiece(black, rectangles, 7);
}

/************************************************************************
* DRAW Queen
* Draw a queen at a certain location on the board
*   INPUT  location  The location of the queen
*          black     Whether the queen is black
*************************************************************************/
void ogstream::drawQueen(const Position& pos, bool black)
{
   Rect rectangles[] =
   {
      { 8,8,   5,8,   5,5,   8,5 },     // right crown jewel
      {-8,8,  -5,8,  -5,5,  -8,5 },     // left crown jewel
      { 2,8,  -2,8,  -2,5,   2,5 },     // center crown jewel
      { 7,5,   5,5,   1,0,   5,0 },     // right crown holder
      {-7,5,  -5,5,  -1,0,  -5,0 },     // left crown holder
      { 1,5,   1,0,  -1,0,  -1,5 },     // center crown holder
      { 4,0,  -4,0,  -4,-2,  4,-2},     // upper base
      { 6,-3, -6,-3, -6,-5,  6,-5},     // middel base
      { 8,-6, -8,-6, -8,-8,  8,-8}      // base
   };

   position = pos;
   drawPiece(black, rectangles, 9);
}

/************************************************************************
* DRAW Rook
* Draw a Rook at a certain location on the board
*   INPUT  location  The location of the Rook
*          black     Whether the knight is castle
*************************************************************************/
void ogstream::drawRook(const Position& pos, bool black)
{
   Rect rectangles[] =
   {
      {-8,7,  -8,4,  -4,4,  -4,7},   // left battlement
      { 8,7,   8,4,   4,4,   4,7},   // right battlement
      { 2,7,   2,4,  -2,4,  -2,7},   // center battlement
      { 4,3,   4,-5, -4,-5, -4,3},   // wall
      { 6,-6, -6,-6, -6,-8,  6,-8}   // base
   };

   position = pos;
   drawPiece(black, rectangles, 5);
}

/************************************************************************
* DRAW Knight
* Draw a knight at a certain location on the board
*   INPUT  location  The location of the knight
*          black     Whether the knight is black
*************************************************************************/
void ogstream::drawKnight(const Position& pos, bool black)
{
   Rect rectangles[] =
   {
      {-7,3,  -3,6,  -1,3,  -5,0},  // muzzle
      {-2,6,  -2,8,   0,8,   0,3},  // head
      {-3,6,   3,6,   6,1,   1,1},  // main
      { 6,1,   1,1,  -5,-5,  5,-5}, // body
      { 6,-6, -6,-6, -6,-8,  6,-8}  // base
   
   };

   position = pos;
   drawPiece(black, rectangles, 5);
}

/************************************************************************
* DRAW Bishop
* Draw a Bishop at a certain location on the board
*   INPUT  location  The location of the Bishop
*          black     Whether the knight is Bishop
*************************************************************************/
void ogstream::drawBishop(const Position& pos, bool black)
{
   Rect rectangles[] =
   {
      {-1,8,  -1,2,   1,2,   1,8 },   // center of head
      { 1,8,   1,2,   5,2,   5,5 },   // right part of head
      {-4,5,  -4,2,  -2,2,  -2, 6},   // left of head
      {-5,3,  -5,2,   5,2,   5,3 },   // base of head
      {-2,2,  -4,-5,  4,-5,  2,2 },   // neck
      { 6,-6, -6,-6, -6,-8,  6,-8}    // base
   };

   position = pos;
   drawPiece(black, rectangles, 6);
}

/************************************************************************
* DRAW PAWN
* Draw a pawn at a certain location on the board
*   INPUT  location  The location of the pawn
*          black     Whether the pawn is black
*************************************************************************/
void ogstream::drawPawn(const Position& pos, bool black)
{
   Rect rectangles[] =
   {
      { 1,7,  -1,7,  -2,5,  2,5 }, // top of head
      { 3,5,  -3,5,  -3,3,  3,3 }, // bottom of head
      { 1,3,  -1,3,  -2,-3, 2,-3}, // neck
      { 4,-3, -4,-3, -4,-5, 4,-5}  // base
   };

   position = pos;
   drawPiece(black, rectangles, 4);
}

/************************************************************************
* DRAW BOARD
* Draw the chess board. Note that all coordinates are in the origional
* dimensions (SQUARE_SIZE + SQUARE_SIZE * 8 + SQUARE_SIZE), 
* not taking into account any scaling or resizing (non-ortho coordinates)
************************************************************************/
void ogstream::drawBoard()
{
   // draw the squares of the board
   glBegin(GL_QUADS);
   for (int row = 0; row < 8; row++)
      for (int col = 0; col < 8; col++)
      {
         // set the checker-board color
         if ((row + col) % 2 == 0)
            glColor(RGB_BLACK_SQUARE);
         else
            glColor(RGB_WHITE_SQUARE);

         // draw the square
         Position pos;
         GLint x0 = (GLint)((col + 0) * SIZE_SQUARE + 1 + SIZE_SQUARE);
         GLint x1 = (GLint)((col + 1) * SIZE_SQUARE - 1 + SIZE_SQUARE);
         GLint y0 = (GLint)((row + 0) * SIZE_SQUARE + 1 + SIZE_SQUARE);
         GLint y1 = (GLint)((row + 1) * SIZE_SQUARE - 1 + SIZE_SQUARE);
         glVertex2i(x0, y0);
         glVertex2i(x1, y0);
         glVertex2i(x1, y1);
         glVertex2i(x0, y1);
      }
   glEnd();

   // draw a box around the coordinates
   glBegin(GL_LINE_STRIP);
   glColor(RGB_SQUARE);
   GLint inner = SIZE_SQUARE / 2;
   GLint outter = 8 * SIZE_SQUARE + SIZE_SQUARE + SIZE_SQUARE / 2;
   glVertex2i(inner, inner);
   glVertex2i(inner, outter);
   glVertex2i(outter, outter);
   glVertex2i(outter, inner);
   glVertex2i(inner, inner);
   glEnd();
   
   // draw a box around the edge
   inner = SIZE_SQUARE - 2;
   outter = SIZE_SQUARE + 8 * SIZE_SQUARE + 2;
   glBegin(GL_LINE_STRIP);
   glVertex2i(inner, inner);
   glVertex2i(inner, outter);
   glVertex2i(outter, outter);
   glVertex2i(outter, inner);
   glVertex2i(inner, inner);
   glEnd();

   
   // draw the letters along the bottom and the top
   glColor(RGB_LETTERS);
   const GLfloat WIDTH_LETTER  = 4.0;  // width of one letter
   const GLfloat HEIGHT_LETTER = 14.0; // height of one letter
   const GLfloat TEXT_MARGIN   = 2.0;  // how close a letter can get to the edge
   for (int col = 0; col < 8; col++)
   {
      void* pFont = GLUT_TEXT;

      // Bottom row
      GLfloat xPos = (GLfloat)SIZE_SQUARE +          // indent by the board margin
                     (GLfloat)(col * SIZE_SQUARE) +  // tab over by the number of columns
                     (GLfloat)(SIZE_SQUARE / 2) +    // center on the column
                     -WIDTH_LETTER;                  // back up by the width of a letter
      GLfloat yPos = TEXT_MARGIN;                    // just a bit from the bottom
      glRasterPos2f(xPos, yPos);
      glutBitmapCharacter(pFont, (char)('a' + col));

      // top row
      yPos = (GLfloat)(SIZE_SQUARE * 2) +            // add the margins and...
             (GLfloat)(8 * SIZE_SQUARE) +            // add the size of the squares
             -HEIGHT_LETTER +                        // subtract the size of a letter
             -TEXT_MARGIN;                           // just a bit from the bottom
      glRasterPos2f(xPos, yPos);
      glutBitmapCharacter(pFont, (char)('a' + col));
   }

   // draw the numbers along the side
   for (int row = 0; row < 8; row++)
   {
      void* pFont = GLUT_TEXT;
      
      // left column
      GLfloat xPos = TEXT_MARGIN;                    // just a bit from the side
      GLfloat yPos = (GLfloat)SIZE_SQUARE +          // indent by the board margin
                     (GLfloat)(row * SIZE_SQUARE) +  // tab over by the number of rows
                     (GLfloat)(SIZE_SQUARE / 2) +    // center on the row
                     -HEIGHT_LETTER/2;               // back up by the height of a letter
      glRasterPos2f(xPos, yPos);
      glutBitmapCharacter(pFont, (char)('1' + row));
      
      // right column
      xPos = (GLfloat)(SIZE_SQUARE * 2) +            // add the margins and...
             (GLfloat)(8 * SIZE_SQUARE) +            // add the size of the squares
             -HEIGHT_LETTER +                        // subtract the size of a letter
             -TEXT_MARGIN;                           // just a bit from the bottom
      glRasterPos2f(xPos, yPos);
      glutBitmapCharacter(pFont, (char)('1' + row));
   }
}

/************************************************************************
* DRAW SELECTED
* Highlight a chess square:
*   INPUT  location  The location of the selected square, in ortho coordinates
************************************************************************/
void ogstream::drawSelected(const Position& pos)
{
   // do nothing if there is nothing to do
   if (pos.isInvalid())
      return;

   // find the row and column
   int row = pos.getRow();
   int col = pos.getCol();


   // set the color and drawing style
   glBegin(GL_QUADS);
   glColor(RGB_SELECTED);

   // draw the square
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + 3 + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + 3 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE - 3 + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + 3 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE - 3 + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE - 3 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + 3 + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE - 3 + SIZE_SQUARE));

   // indicate we are finished
   glEnd();

}

/************************************************************************
* DRAW HOVER
* Highlight a chess square:
*   INPUT  location  The location of the selected square, in ortho coordinates
************************************************************************/
void ogstream::drawHover(const Position& pos)
{
   // do nothing if there is nothing to do
   if (pos.isInvalid())
      return;

   // find the row and column
   int row = pos.getRow();
   int col = pos.getCol();

   // set the color and drawing style
   glBegin(GL_QUADS);
   glColor(RGB_SELECTED);

   // draw the square
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE + SIZE_SQUARE));
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE + SIZE_SQUARE));

   // set the checker-board color
   if ((row + col) % 2 == 0)
      glColor(RGB_BLACK_SQUARE);
   else
      glColor(RGB_WHITE_SQUARE);

   // draw the square
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + 2 + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + 2 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE - 2 + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + 2 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE - 2 + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE - 2 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + 2 + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE - 2 + SIZE_SQUARE));


   // finish the drawing
   glEnd();
}

/************************************************************************
* DRAW POSSIBLE
* Highlight a chess square:
*   INPUT  location  The location of the selected square, in ortho coordinates
************************************************************************/
void ogstream::drawPossible(const Position& pos)
{
   // do nothing if there is nothing to do
   if (pos.isInvalid())
      return;

   // find the row and column
   int row = pos.getRow();
   int col = pos.getCol();

   // set the color and drawing style
   glBegin(GL_QUADS);
   glColor(RGB_SELECTED);

   // draw the square
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + 7 + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + 7 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE - 7 + SIZE_SQUARE),
              (GLint)((row + 0) * SIZE_SQUARE + 7 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 1) * SIZE_SQUARE - 7 + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE - 7 + SIZE_SQUARE));
   glVertex2i((GLint)((col + 0) * SIZE_SQUARE + 7 + SIZE_SQUARE),
              (GLint)((row + 1) * SIZE_SQUARE - 7 + SIZE_SQUARE));

   // finish the drawing
   glEnd();
}



