/***********************************************************************
 * Header File:
 *    Advance : How a bird moves each frame (Template Method pattern)
 * Author:
 *    <your name>
 * Summary:
 *    Advance is the abstract template. Its advance() method is the
 *    template method: it always runs the same steps in the same order.
 *    The four concrete templates fill in only the steps they need.
 ************************************************************************/

#pragma once

class Bird;   // the context: Advance::advance() receives the bird to move

/*********************************************
 * ADVANCE
 * Abstract template class. No member variables.
 *   advance() is public and NOT virtual so every bird runs the
 *   same sequence of steps. The steps are private; all but
 *   inertia() are virtual and do nothing by default.
 *********************************************/
class Advance
{
public:
   virtual ~Advance() {}

   // the template method
   void advance(Bird & bird);

private:
   // the steps, called in this order by advance()
   virtual void drag    (Bird & bird) {}   // default: no drag
   virtual void turn    (Bird & bird) {}   // default: no turning
           void inertia (Bird & bird);     // same for every bird
   virtual void buoyancy(Bird & bird) {}   // default: no buoyancy
};

/*********************************************
 * STANDARD ADVANCE
 * The standard bird slows down a little every frame.
 *********************************************/
class StandardAdvance : public Advance
{
private:
   void drag(Bird & bird) override;
};

/*********************************************
 * FLOATER ADVANCE
 * The floater has strong drag and floats upward.
 *********************************************/
class FloaterAdvance : public Advance
{
private:
   void drag    (Bird & bird) override;
   void buoyancy(Bird & bird) override;
};

/*********************************************
 * SINKER ADVANCE
 * The sinker is pulled down by gravity.
 *   NOTE: The spec places gravity in buoyancy(). It is implemented
 *   in drag() instead because the original game applied gravity
 *   BEFORE inertia, while the floater's anti-gravity is applied
 *   AFTER inertia. Using drag() keeps the sinker's motion
 *   identical to the original game.
 *********************************************/
class SinkerAdvance : public Advance
{
private:
   void drag(Bird & bird) override;
};

/*********************************************
 * CRAZY ADVANCE
 * The crazy bird changes direction about every half second.
 *********************************************/
class CrazyAdvance : public Advance
{
private:
   void turn(Bird & bird) override;
};
