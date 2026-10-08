#include "advance.h"
#include "bird.h"
#include "random.h"

// ----------------------------------------------------------------------------
// Advance strategy for the standard bird
// How the standard bird moves - inertia and drag
// ----------------------------------------------------------------------------
void StandardAdvance::execute(Bird *context)
{
   // small amount of drag
   context->v *= 0.995;

   // inertia
   context->pt.add(context->v);

   // out of bounds checker
   if (context->isOutOfBounds())
   {
      context->kill();
      context->points *= -1; // points go negative when it is missed!
   }
}

// ----------------------------------------------------------------------------
// Advance strategy for the crazy bird
// How the crazy bird moves, every half a second it changes direciton
// ----------------------------------------------------------------------------
void CrazyAdvance::execute(Bird *context)
{
   // erratic turns eery half a second or so
   if (randomInt(0, 15) == 0)
   {
      context->v.addDy(randomDouble(-1.5, 1.5));
      context->v.addDx(randomDouble(-1.5, 1.5));
   }

   // inertia
   context->pt.add(context->v);

   // out of bounds checker
   if (context->isOutOfBounds())
   {
      context->kill();
      context->points *= -1; // points go negative when it is missed!
   }
}

// ----------------------------------------------------------------------------
// Advance strategy for the sinker bird
// How the sinker bird moves, no drag but gravity
// ----------------------------------------------------------------------------
void SinkerAdvance::execute(Bird *context)
{
   // gravity
   context->v.addDy(-0.07);

   // inertia
   context->pt.add(context->v);

   // out of bounds checker
   if (context->isOutOfBounds())
   {
      context->kill();
      context->points *= -1; // points go negative when it is missed!
   }
}

// ----------------------------------------------------------------------------
// Advance strategy for the floater bird
// ----------------------------------------------------------------------------
void FloaterAdvance::execute(Bird *context)
{
   // large amount of drag
   context->v *= 0.990;

   // inertia
   context->pt.add(context->v);

   // anti-gravity
   context->v.addDy(0.05);

   // out of bounds checker
   if (context->isOutOfBounds())
   {
      context->kill();
      context->points *= -1; // points go negative when it is missed!
   }
}
