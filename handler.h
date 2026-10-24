/***********************************************************************
 * Header File:
 *    HANDLER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The Chain of Responsibility for user input. Each handler gets a
 *    chance to act on the request. If a handler returns TRUE, it has
 *    consumed the request and the rest of the chain is skipped. If it
 *    returns FALSE, the request continues down the chain.
 *
 *    The handlers never see the keyboard or the level. Skeet translates
 *    the keyboard into a Request (which key means which bullet) and
 *    decides which handlers are in the chain for each level.
 ************************************************************************/

#pragma once

class Skeet;

/*********************************************
 * BULLET TYPE
 * Which kind of bullet the player asked to fire
 *********************************************/
enum class BulletType { NONE, PELLET, MISSILE, BOMB };

/*********************************************
 * REQUEST
 * What the player asked for this frame, without any
 * knowledge of which keys were pressed
 *********************************************/
struct Request
{
   Request() : restart(false), fire(BulletType::NONE),
      clockwise(0), counterclockwise(0) {
   }

   bool       restart;           // start a new game (only means something at game over)
   BulletType fire;              // which bullet to fire, if any
   int        clockwise;         // how hard to turn the gun / missiles clockwise
   int        counterclockwise;  // how hard to turn the gun / missiles counterclockwise
};

/*********************************************
 * HANDLER
 * The abstract handler in the chain of responsibility
 *********************************************/
class Handler
{
public:
   virtual ~Handler() {}

   // act on the request. Return TRUE if the rest of the chain is skipped
   virtual bool handleRequest(const Request& request, Skeet& skeet) = 0;
};

/*********************************************
 * HANDLER GAME OVER
 * When the game is over, a restart request starts a new game
 *********************************************/
class HandlerGameOver : public Handler
{
public:
   bool handleRequest(const Request& request, Skeet& skeet) override;
};

/*********************************************
 * HANDLER MOVE GUN
 * Turn the gun. Never consumes the request.
 *********************************************/
class HandlerMoveGun : public Handler
{
public:
   bool handleRequest(const Request& request, Skeet& skeet) override;
};

/*********************************************
 * HANDLER GUIDE MISSILE
 * Steer the missiles in flight. Never consumes the request.
 *********************************************/
class HandlerGuideMissile : public Handler
{
public:
   bool handleRequest(const Request& request, Skeet& skeet) override;
};

/*********************************************
 * HANDLER PELLET
 * Fires a pellet when a pellet is requested
 *********************************************/
class HandlerPellet : public Handler
{
public:
   bool handleRequest(const Request& request, Skeet& skeet) override;
};

/*********************************************
 * HANDLER MISSILE
 * Fires a missile when a missile is requested
 *********************************************/
class HandlerMissile : public Handler
{
public:
   bool handleRequest(const Request& request, Skeet& skeet) override;
};

/*********************************************
 * HANDLER BOMB
 * Fires a bomb when a bomb is requested
 *********************************************/
class HandlerBomb : public Handler
{
public:
   bool handleRequest(const Request& request, Skeet& skeet) override;
};