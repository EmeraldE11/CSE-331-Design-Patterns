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
#include "bullet.h"

 /************************
  * HANDLER GAME OVER : HANDLE REQUEST
  * Start a new game
  ************************/
bool HandlerGameOver::handleRequest(const Request& request, Skeet& skeet)
{
   if (request.restart)
   {
      skeet.restart();
      return true;
   }
   return false;
}

/************************
 * HANDLER MOVE GUN : HANDLE REQUEST
 * Turn the gun. Returns FALSE so the gun can move while
 * something else happens.
 ************************/
bool HandlerMoveGun::handleRequest(const Request& request, Skeet& skeet)
{
   skeet.moveGun(request.clockwise, request.counterclockwise);
   return false;
}

/************************
 * HANDLER GUIDE MISSILE : HANDLE REQUEST
 * Steer the missiles in flight. Returns FALSE so the missiles
 * can be steered while something else happens.
 ************************/
bool HandlerGuideMissile::handleRequest(const Request& request, Skeet& skeet)
{
   skeet.moveMissile(request.clockwise, request.counterclockwise);
   return false;
}

/************************
 * HANDLER PELLET : HANDLE REQUEST
 * Fire a pellet. This handler can only ever create a Pellet.
 ************************/
bool HandlerPellet::handleRequest(const Request& request, Skeet& skeet)
{
   if (request.fire == BulletType::PELLET)
   {
      skeet.addBullet(new Pellet(skeet.getGunAngle()));
      return true;
   }
   return false;
}

/************************
 * HANDLER MISSILE : HANDLE REQUEST
 * Fire a missile. This handler can only ever create a Missile.
 ************************/
bool HandlerMissile::handleRequest(const Request& request, Skeet& skeet)
{
   if (request.fire == BulletType::MISSILE)
   {
      Missile* p = new Missile(skeet.getGunAngle());
      skeet.addBullet(p);

      // HandlerGuideMissile already ran before this missile existed, so
      // give the new missile the same steering the others got this frame
      p->input(request.clockwise != 0, request.counterclockwise != 0, false);
      return true;
   }
   return false;
}

/************************
 * HANDLER BOMB : HANDLE REQUEST
 * Fire a bomb. This handler can only ever create a Bomb.
 ************************/
bool HandlerBomb::handleRequest(const Request& request, Skeet& skeet)
{
   if (request.fire == BulletType::BOMB)
   {
      skeet.addBullet(new Bomb(skeet.getGunAngle()));
      return true;
   }
   return false;
}