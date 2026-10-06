/***********************************************************************
 * Source File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#include "bird.h"
#include "random.h"
#include <cassert>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h> // Second OpenGL library
#include <openGL/gl.h> // Main OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>   // Main OpenGL library
#include <GL/glut.h> // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <GL/glut.h> // OpenGL library we copied
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

/***************************************************************/
/***************************************************************/
/*                         CONSTRUCTORS                         */
/***************************************************************/
/***************************************************************/

/******************************************************************************
 * Factory for different common varieties of birds
 *****************************************************************************/
Bird *Bird::factory(BirdType type)
{
   switch (type)
   {
      case BIRD_STANDARD_LEVEL_1:
         return new Standard(30.0, 7.0, 10);
      case BIRD_STANDARD_LEVEL_2:
         return new Standard(25.0, 5.0, 12);
      case BIRD_STANDARD_LEVEL_3:
         return new Standard(20.0, 5.0, 15);
      case BIRD_STANDARD_LEVEL_4:
         return new Standard(15.0, 4.0, 18);
      case BIRD_SINKER_LEVEL_2:
         return new Sinker(25.0, 4.5, 20);
      case BIRD_SINKER_LEVEL_3:
         return new Sinker(20.0, 4.0, 22);
      case BIRD_SINKER_LEVEL_4:
         return new Sinker(15.0, 3.5, 25);
      case BIRD_FLOATER_LEVEL_3:
         return new Floater(20.0, 5.0, 15);
      case BIRD_FLOATER_LEVEL_4:
         return new Floater(15.0, 4.0, 25);
      case BIRD_CRAZY_LEVEL_4:
         return new Crazy(15.0, 4.5, 30);
      default:
         // If another bird type is added, then a new case
         // constructing the type should be inserted above
         assert(!"unknown bird type");
   }
}

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
   // floaters start on the lower part of the screen because they go up with
   // time
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
   // sinkers start on the upper part of the screen because they go down with
   // time
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
static void drawDisk(const Position &center, double radius, double red,
                     double green, double blue)
{
   assert(radius > 1.0);
   const double increment =
      M_PI / radius; // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */,
             (GLfloat)green /* green % */,
             (GLfloat)blue /* blue % */);

   // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);

   // go around the circle
   for (double radians = increment; radians <= M_PI * 2.0 + .5;
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

/*********************************************
 * STANDARD DRAW
 * Draw a standard bird: blue center and white outline
 *********************************************/
void Standard::draw()
{
   if (!isDead())
   {
      drawDisk(pt, radius - 0.0, 1.0, 1.0, 1.0); // white outline
      drawDisk(pt, radius - 3.0, 0.0, 0.0, 1.0); // blue center
   }
}

/*********************************************
 * FLOATER DRAW
 * Draw a floating bird: white center and blue outline
 *********************************************/
void Floater::draw()
{
   if (!isDead())
   {
      drawDisk(pt, radius - 0.0, 0.0, 0.0, 1.0); // blue outline
      drawDisk(pt, radius - 4.0, 1.0, 1.0, 1.0); // white center
   }
}

/*********************************************
 * CRAZY DRAW
 * Draw a crazy bird: concentric circles in a course gradient
 *********************************************/
void Crazy::draw()
{
   if (!isDead())
   {
      drawDisk(pt, radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
      drawDisk(pt, radius * 0.8, 0.2, 0.2, 1.0);
      drawDisk(pt, radius * 0.6, 0.4, 0.4, 1.0);
      drawDisk(pt, radius * 0.4, 0.6, 0.6, 1.0);
      drawDisk(pt, radius * 0.2, 0.8, 0.8, 1.0); // almost white inside
   }
}

/*********************************************
 * SINKER DRAW
 * Draw a sinker bird: black center and dark blue outline
 *********************************************/
void Sinker::draw()
{
   if (!isDead())
   {
      drawDisk(pt, radius - 0.0, 0.0, 0.0, 0.8);
      drawDisk(pt, radius - 4.0, 0.0, 0.0, 0.0);
   }
}
