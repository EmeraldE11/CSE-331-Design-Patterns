/***********************************************************************
 * Source File:
 *    Advance : How a bird moves each frame (Template Method pattern)
 * Author:
 *    <your name>
 * Summary:
 *    The template method and the steps of the four concrete templates
 ************************************************************************/

#include "advance.h"
#include "bird.h"
#include "random.h"

/***************************************************************/
/***************************************************************/
/*                    ABSTRACT TEMPLATE                         */
/***************************************************************/
/***************************************************************/

/*********************************************
 * ADVANCE : ADVANCE
 * The template method. Every bird moves through these steps
 * in this order, then is checked for leaving the screen.
 *********************************************/
void Advance::advance(Bird & bird)
{
   drag(bird);
   turn(bird);
   inertia(bird);
   buoyancy(bird);

   // out of bounds checker
   if (bird.isOutOfBounds())
   {
      bird.kill();
      bird.setPoints(-bird.getPoints()); // points go negative when it is missed!
   }
}

/*********************************************
 * ADVANCE : INERTIA
 * Move the bird according to its current velocity.
 * All birds do this exactly the same.
 *********************************************/
void Advance::inertia(Bird & bird)
{
   bird.getPosition().add(bird.getVelocity());
}

/***************************************************************/
/***************************************************************/
/*                    CONCRETE TEMPLATES                        */
/***************************************************************/
/***************************************************************/

/*********************************************
 * STANDARD ADVANCE : DRAG
 * Small amount of drag
 *********************************************/
void StandardAdvance::drag(Bird & bird)
{
   bird.getVelocity() *= 0.995;
}

/*********************************************
 * FLOATER ADVANCE : DRAG
 * Large amount of drag
 *********************************************/
void FloaterAdvance::drag(Bird & bird)
{
   bird.getVelocity() *= 0.990;
}

/*********************************************
 * FLOATER ADVANCE : BUOYANCY
 * Anti-gravity
 *********************************************/
void FloaterAdvance::buoyancy(Bird & bird)
{
   bird.getVelocity().addDy(0.05);
}

/*********************************************
 * SINKER ADVANCE : DRAG
 * Gravity. Applied here (before inertia) rather than in
 * buoyancy() so the sinker moves exactly as it did before.
 *********************************************/
void SinkerAdvance::drag(Bird & bird)
{
   bird.getVelocity().addDy(-0.07);
}

/*********************************************
 * CRAZY ADVANCE : TURN
 * Erratic turns every half a second or so
 *********************************************/
void CrazyAdvance::turn(Bird & bird)
{
   if (randomInt(0, 15) == 0)
   {
      bird.getVelocity().addDy(randomDouble(-1.5, 1.5));
      bird.getVelocity().addDx(randomDouble(-1.5, 1.5));
   }
}
