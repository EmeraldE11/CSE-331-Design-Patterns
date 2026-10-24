/***********************************************************************
 * Header File:
 *    HANDLER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The Chain of Responsibility for user input. Each handler gets a
 *    chance to act on the user input. If a handler returns TRUE, it has
 *    consumed the input and the rest of the chain is skipped. If it
 *    returns FALSE, the input continues down the chain.
 ************************************************************************/

#pragma once

class UserInput;
class Skeet;

/*********************************************
 * HANDLER
 * The abstract handler in the chain of responsibility
 *********************************************/
class Handler
{
public:
   virtual ~Handler() {}

   // act on the user input. Return TRUE if the rest of the chain is skipped
   virtual bool handleRequest(const UserInput & ui, Skeet & skeet) = 0;
};

/*********************************************
 * HANDLER GAME OVER
 * When the game is over, the space bar restarts the game
 *********************************************/
class HandlerGameOver : public Handler
{
public:
   bool handleRequest(const UserInput & ui, Skeet & skeet) override;
};

/*********************************************
 * HANDLER MOVE GUN
 * Turn the gun. Never consumes the input.
 *********************************************/
class HandlerMoveGun : public Handler
{
public:
   bool handleRequest(const UserInput & ui, Skeet & skeet) override;
};

/*********************************************
 * HANDLER GUIDE MISSILE
 * Steer the missiles in flight. Never consumes the input.
 *********************************************/
class HandlerGuideMissile : public Handler
{
public:
   bool handleRequest(const UserInput & ui, Skeet & skeet) override;
};

/*********************************************
 * HANDLER PELLET
 * The space bar fires a pellet
 *********************************************/
class HandlerPellet : public Handler
{
public:
   bool handleRequest(const UserInput & ui, Skeet & skeet) override;
};

/*********************************************
 * HANDLER MISSILE
 * The M key fires a missile
 *********************************************/
class HandlerMissile : public Handler
{
public:
   bool handleRequest(const UserInput & ui, Skeet & skeet) override;
};

/*********************************************
 * HANDLER BOMB
 * The B key fires a bomb
 *********************************************/
class HandlerBomb : public Handler
{
public:
   bool handleRequest(const UserInput & ui, Skeet & skeet) override;
};
