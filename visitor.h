/***********************************************************************
 * Header File:
 *    VISITOR
 * Summary:
 *    Abstract and concrete visitors for the Skeet game.
 ************************************************************************/

#pragma once

#include <list> // for list

// Forward declarations of bird, bullet and effect classes
class Bird;
class Bullet;
class Effect;

/***********************************************************************
* VISITOR
* Abstract visitor for all flying objects.
***********************************************************************/
class Visitor
{
public:
   // destructor
   virtual ~Visitor() = default;

   // pure virtual methods to be overridden by child classes
   virtual void visit(Bird& bird) = 0;
   virtual void visit(Bullet& bullet) = 0;
   virtual void visit(Effect& effect) = 0;
};

/***********************************************************************
* VISIT DRAW
* Concrete visitor for drawing game objects.
***********************************************************************/
class VisitDraw : public Visitor
{
public:
   // draw each type of game object
   void visit(Bird& bird) override;
   void visit(Bullet& bullet) override;
   void visit(Effect& effect) override;
};

/***********************************************************************
* VISIT MOVE
* Concrete visitor for moving game objects.
***********************************************************************/
class VisitMove : public Visitor
{
public:
   // constructor
   explicit VisitMove(std::list<Effect*>& effects) 
      : effects(effects) {}

   // move each type of game object
   void visit(Bird& bird) override;
   void visit(Bullet& bullet) override;
   void visit(Effect& effect) override;

private:
   // reference to the effects collection
   std::list<Effect*>& effects;
};