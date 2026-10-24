/***********************************************************************
 * Header File:
 *    SKEET
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The game class
 ************************************************************************/

#pragma once

#include "position.h"
#include "uiInteract.h"
#include "bird.h"
#include "bullet.h"
#include "effect.h"
#include "gun.h"
#include "time.h"
#include "score.h"
#include "points.h"
#include "handler.h"

#include <list>
#include <vector>
#include <memory>

 /*************************************************************************
  * Skeet
  * The game class
  *************************************************************************/
class Skeet
{
   // allow unit tests direct access to private members
   friend class TestSkeet;
   friend class TestHandler;

   // the handlers in the chain of responsibility act on the game
   friend class HandlerGameOver;
   friend class HandlerMoveGun;
   friend class HandlerGuideMissile;
   friend class HandlerPellet;
   friend class HandlerMissile;
   friend class HandlerBomb;

public:
   Skeet(Position& dimensions) : dimensions(dimensions),
      gun(Position(800.0, 0.0)), time(), score(), hitRatio(), bullseye(false),
      handlersLevel(-1) {
   }

   // handle all user input
   void interact(const UserInput& ui);

   // move the gameplay by one unit of time
   void animate();

   // output everything on the screen
   void drawLevel()  const;    // output the game
   void drawStatus() const;    // output the status information

   // is the game currently playing right now?
   bool isPlaying() const { return time.isPlaying(); }
private:
   // generate new birds
   void spawn();
   void drawBackground(double redBack, double greenBack, double blueBack) const;
   void drawTimer(double percent,
      double redFore, double greenFore, double blueFore,
      double redBack, double greenBack, double blueBack) const;
   void drawBullseye(double angle) const;

   // build the chain of responsibility for the given level
   void setLevel(int level);

   // used by the handlers
   void moveGun(int clockwise, int counterclockwise)
   {
      gun.interact(clockwise, counterclockwise);
   }
   void moveMissile(bool isUp, bool isDown, bool isB)
   {
      // send movement information to all the bullets. Only the missile cares.
      for (auto bullet : bullets)
         bullet->input(isUp, isDown, isB);
   }

   Gun gun;                       // the gun
   std::list<Bird*> birds;        // all the shootable birds
   std::list<Bullet*> bullets;    // the bullets
   std::list<Effect*> effects;    // the fragments of a dead bird.
   std::list<Points>  points;     // point values;
   Time time;                     // how many frames have transpired since the beginning
   Score score;                   // the player's score
   HitRatio hitRatio;             // the hit ratio for the birds
   Position dimensions;           // size of the screen
   bool bullseye;

   // the chain of responsibility for user input
   std::vector<std::unique_ptr<Handler>> handlers;
   int handlersLevel;             // the level the chain was built for
};