/*********************************************
 * Header file:
 *    USER INTERFACE INTERACTION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This module will create an OpenGL window,
 *    enter the OpenGL main loop, and accept events.
 *    The main methods are:
 *    1. Constructors - Create the window
 *    2. run()        - Run the main loop
 *    3. callback     - Specified in Run, this user-provided
 *                      function will get called with every frame
 *    4. isDown()     - Is a given key pressed on this loop?
 **********************************************/

#pragma once

#include "position.h"

/********************************************
 * INTERFACE
 * All the data necessary to keep our graphics
 * state in memory
 ********************************************/
class Interface
{
public:
   Interface() {}
   // Constructor if you want to set up the window with anything but
   // the default parameters
   Interface(const char* title)
   {
      initialize(title);
   }

   // This will set the game in motion
   void run(void (*callBack)(Interface*, void*), void* p);

   // Is it time to redraw the screen
   bool isTimeToDraw();

   // Set the next draw time based on current time and time period
   void setNextDrawTime();

   // Retrieve the next tick time... the time of the next draw.
   unsigned long getNextTick() { return nextTick; };

   char getKey()         const { return key;     }
   
   void keyEvent(int key, bool fDown);
   void resetKey();
   
   // How many frames per second are we configured for?
   void setFramesPerSecond(double value);

   // Current frame rate
   double frameRate() const { return timePeriod; };

   Position  getSelectPosition()   const { return posSelect; }
   Position  getHoverPosition()    const { return posHover; }
   Position  getPreviousPosition() const { return posSelectPrevious; }

   void setSelectPosition(const Position& pos)
   {
      if (pos != posSelect)
         posSelectPrevious = posSelect;
      posSelect = pos;
   }
   void clearSelectPosition()
   {
      posSelectPrevious.setInvalid();
      posSelect.setInvalid();
   }
   void clearPreviousPosition()
   {
      posSelectPrevious.setInvalid();
   }

   void setHoverPosition(const Position & pos)
   {
      posHover = pos;
   }

   static void* p;                   // for client
   static void (*callBack)(Interface*, void*);

private:
   void initialize(const char* title);

   static bool         initialized;    // only run the constructor once!
   static double       timePeriod;     // interval between frame draws
   static unsigned long nextTick;      // time (from clock()) of our next draw

   static Position  posHover;          // mouse hover position in chess coordinates
   static Position  posSelect;         // mouse clicked position in chess coordinates
   static Position  posSelectPrevious; // previous clicked position
   
   static char key;                    // key pressed
};

/***************************************************************
 * KEYBOARD CALLBACK
 * Generic callback to a regular ascii keyboard event, such as
 * the space bar or the letter 'q'
 ***************************************************************/
void keyboardCallback(unsigned char key, int x, int y);

/************************************************************************
 * RUN
 * Set the game in action.  We will get control back in our drawCallback
 *************************************************************************/
void run();
