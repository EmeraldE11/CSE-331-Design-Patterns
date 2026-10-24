/***********************************************************************
 * Source File:
 *    HANDLER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The concrete handlers in the Chain of Responsibility for user input
 ************************************************************************/

#include "handler.h"
#include "skeet.h"
#include "uiInteract.h"
#include "bullet.h"

/************************
 * HANDLER GAME OVER : HANDLE REQUEST
 * The space bar resets the game
 ************************/
bool HandlerGameOver::handleRequest(const UserInput & ui, Skeet & skeet)
{
   if (ui.isSpace())
   {
      skeet.time.reset();
      skeet.score.reset();
      skeet.hitRatio.reset();
      return true;
   }
   return false;
}

/************************
 * HANDLER MOVE GUN : HANDLE REQUEST
 * Up and right turn the gun one way, down and left the other way.
 * Returns FALSE so the gun can move while something else happens.
 ************************/
bool HandlerMoveGun::handleRequest(const UserInput & ui, Skeet & skeet)
{
   skeet.moveGun(ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft());
   return false;
}

/************************
 * HANDLER GUIDE MISSILE : HANDLE REQUEST
 * Send the movement information to all the bullets. Only missiles care.
 * Returns FALSE so the missiles can be steered while something else happens.
 ************************/
bool HandlerGuideMissile::handleRequest(const UserInput & ui, Skeet & skeet)
{
   skeet.moveMissile(ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft(), ui.isB());
   return false;
}

/************************
 * HANDLER PELLET : HANDLE REQUEST
 * The space bar fires a pellet
 ************************/
bool HandlerPellet::handleRequest(const UserInput & ui, Skeet & skeet)
{
   if (ui.isSpace())
   {
      skeet.bullets.push_back(new Pellet(skeet.gun.getAngle()));
      return true;
   }
   return false;
}

/************************
 * HANDLER MISSILE : HANDLE REQUEST
 * The M key fires a missile
 ************************/
bool HandlerMissile::handleRequest(const UserInput & ui, Skeet & skeet)
{
   if (ui.isM())
   {
      Missile * p = new Missile(skeet.gun.getAngle());
      skeet.bullets.push_back(p);

      // HandlerGuideMissile already ran before this missile existed, so
      // give the new missile the same steering the others got this frame
      p->input(ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft(), ui.isB());
      return true;
   }
   return false;
}

/************************
 * HANDLER BOMB : HANDLE REQUEST
 * The B key fires a bomb
 ************************/
bool HandlerBomb::handleRequest(const UserInput & ui, Skeet & skeet)
{
   if (ui.isB())
   {
      skeet.bullets.push_back(new Bomb(skeet.gun.getAngle()));
      return true;
   }
   return false;
}
