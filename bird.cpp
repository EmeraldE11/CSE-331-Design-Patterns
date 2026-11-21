/***********************************************************************
 * Source File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#include <cassert>
#include "bird.h"
#include "random.h"
#include <vector>
#include <string>

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


/***************************************************************/
/***************************************************************/
/*                         CONSTRUCTORS                         */
/***************************************************************/
/***************************************************************/

/******************************************************************
 * STANDARD constructor
 ******************************************************************/
Standard::Standard(double radius, double speed, int points) : Bird()
{
   // set the position: standard birds start from the middle
   pt.setY(randomDouble(dimensions.getY() * 0.25, dimensions.getY() * 0.75));
   pt.setX(0.0);

   // set the velocity
   v.setDx(randomDouble(speed - 0.5, speed + 0.5));
   v.setDy(randomDouble(-speed / 5.0, speed / 5.0));

   // set the points
   this->points = points;

   // set the size
   this->radius = radius;
}

/******************************************************************
 * FLOATER constructor
 ******************************************************************/
Floater::Floater(double radius, double speed, int points) : Bird()
{
   // floaters start on the lower part of the screen because they go up with time
   pt.setY(randomDouble(dimensions.getY() * 0.01, dimensions.getY() * 0.5));
   pt.setX(0.0);

   // set the velocity
   v.setDx(randomDouble(speed - 0.5, speed + 0.5));
   v.setDy(randomDouble(0.0, speed / 3.0));

   // set the points value
   this->points = points;

   // set the size
   this->radius = radius;
}

/******************************************************************
 * SINKER constructor
 ******************************************************************/
Sinker::Sinker(double radius, double speed, int points) : Bird()
{
   // sinkers start on the upper part of the screen because they go down with time
   pt.setY(randomDouble(dimensions.getY() * 0.50, dimensions.getY() * 0.95));
   pt.setX(0.0);

   // set the velocity
   v.setDx(randomDouble(speed - 0.5, speed + 0.5));
   v.setDy(randomDouble(-speed / 3.0, 0.0));

   // set the points value
   this->points = points;

   // set the size
   this->radius = radius;
}

/******************************************************************
 * CRAZY constructor
 ******************************************************************/
Crazy::Crazy(double radius, double speed, int points) : Bird()
{
   // crazy birds start in the middle and can go any which way
   pt.setY(randomDouble(dimensions.getY() * 0.25, dimensions.getY() * 0.75));
   pt.setX(0.0);

   // set the velocity
   v.setDx(randomDouble(speed - 0.5, speed + 0.5));
   v.setDy(randomDouble(-speed / 5.0, speed / 5.0));

   // set the points value
   this->points = points;

   // set the size
   this->radius = radius;
}

 /***************************************************************/
 /***************************************************************/
 /*                            ADVANCE                          */
 /***************************************************************/
 /***************************************************************/

/*********************************************
 * STANDARD ADVANCE
 * How the standard bird moves - inertia and drag
 *********************************************/
void Standard::advance()
{
   // small amount of drag
   v *= 0.995;

   // inertia
   pt.add(v);

   // out of bounds checker
   if (isOutOfBounds())
   {
      kill();
      points *= -1; // points go negative when it is missed!
   }
}

/*********************************************
 * FLOATER ADVANCE
 * How the floating bird moves: strong drag and anti-gravity
 *********************************************/
void Floater::advance()
{
   // large amount of drag
   v *= 0.990;

   // inertia
   pt.add(v);

   // anti-gravity
   v.addDy(0.05);

   // out of bounds checker
   if (isOutOfBounds())
   {
      kill();
      points *= -1; // points go negative when it is missed!
   }
}

/*********************************************
 * CRAZY ADVANCE
 * How the crazy bird moves, every half a second it changes direciton
 *********************************************/
void Crazy::advance()
{
   // erratic turns eery half a second or so
   if (randomInt(0, 15) == 0)
   {
      v.addDy(randomDouble(-1.5, 1.5));
      v.addDx(randomDouble(-1.5, 1.5));
   }

   // inertia
   pt.add(v);

   // out of bounds checker
   if (isOutOfBounds())
   {
      kill();
      points *= -1; // points go negative when it is missed!
   }
}

/*********************************************
 * SINKER ADVANCE
 * How the sinker bird moves, no drag but gravity
 *********************************************/
void Sinker::advance()
{
   // gravity
   v.addDy(-0.07);

   // inertia
   pt.add(v);

   // out of bounds checker
   if (isOutOfBounds())
   {
      kill();
      points *= -1; // points go negative when it is missed!
   }
}

/***************************************************************/
/***************************************************************/
/*                             DRAW                            */
/***************************************************************/
/***************************************************************/

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
static void drawDisk(const Position& center, double radius,
              double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));

      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}


/*
 * Interpret a drawing command and draw the correct bird.
 */
static void drawIt(const std::vector<std::string>& command)
{
   // Make sure the command has enough information
   if (command.size() < 4)
      return;

   // Convert the command strings into numbers
   double x = std::stod(command[1]);
   double y = std::stod(command[2]);
   double r = std::stod(command[3]);

   // Create the bird's position
   Position pt(x, y);

   // Draw a standard bird
   if (command[0] == "STANDARD")
   {
      drawDisk(pt, r, 1.0, 1.0, 1.0);       // White outline
      drawDisk(pt, r - 3.0, 0.0, 0.0, 1.0); // Blue center
   }

   // Draw a floater bird
   else if (command[0] == "FLOATER")
   {
      drawDisk(pt, r, 0.0, 0.0, 1.0);       // Blue outline
      drawDisk(pt, r - 4.0, 1.0, 1.0, 1.0); // White center
   }

   // Draw a sinker bird
   else if (command[0] == "SINKER")
   {
      drawDisk(pt, r, 0.0, 0.0, 0.8);       // Dark blue outline
      drawDisk(pt, r - 4.0, 0.0, 0.0, 0.0); // Black center
   }

   // Draw a crazy bird
   else if (command[0] == "CRAZY")
   {
      drawDisk(pt, r * 1.0, 0.0, 0.0, 1.0);
      drawDisk(pt, r * 0.8, 0.2, 0.2, 1.0);
      drawDisk(pt, r * 0.6, 0.4, 0.4, 1.0);
      drawDisk(pt, r * 0.4, 0.6, 0.6, 1.0);
      drawDisk(pt, r * 0.2, 0.8, 0.8, 1.0);
   }
}



/*********************************************
 * STANDARD DRAW
 * Send standard bird instructions.
 *********************************************/
void Standard::draw()
{
   if (!isDead())
   {
      // Create a command with type, position, and radius
      std::vector<std::string> command;

      command.push_back("STANDARD");
      command.push_back(std::to_string(pt.getX()));
      command.push_back(std::to_string(pt.getY()));
      command.push_back(std::to_string(radius));

      // Send the command to the interpreter
      drawIt(command);
   }
}


/*********************************************
 * FLOATER DRAW
 * Send floater bird instructions.
 *********************************************/
void Floater::draw()
{
   if (!isDead())
   {
      // Create the drawing command
      std::vector<std::string> command;

      command.push_back("FLOATER");
      command.push_back(std::to_string(pt.getX()));
      command.push_back(std::to_string(pt.getY()));
      command.push_back(std::to_string(radius));

      // Send the command to the interpreter
      drawIt(command);
   }
}

/*********************************************
 * CRAZY DRAW
 * Send crazy bird instructions.
 *********************************************/
void Crazy::draw()
{
   if (!isDead())
   {
      // Create the drawing command
      std::vector<std::string> command;

      command.push_back("CRAZY");
      command.push_back(std::to_string(pt.getX()));
      command.push_back(std::to_string(pt.getY()));
      command.push_back(std::to_string(radius));

      // Send the command to the interpreter
      drawIt(command);
   }
}

/*********************************************
 * SINKER DRAW
 * Send sinker bird instructions.
 *********************************************/
void Sinker::draw()
{
   if (!isDead())
   {
      // Create the drawing command
      std::vector<std::string> command;

      command.push_back("SINKER");
      command.push_back(std::to_string(pt.getX()));
      command.push_back(std::to_string(pt.getY()));
      command.push_back(std::to_string(radius));

      // Send the command to the interpreter
      drawIt(command);
   }
}
