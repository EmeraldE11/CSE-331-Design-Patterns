/***********************************************************************
 * Source File:
 *    VISITOR
 * Summary:
 *    Implementation of the drawing and movement visitors.
 ************************************************************************/

#include "visitor.h"
#include "bird.h"
#include "bullet.h"
#include "effect.h"

/***********************************************************************
* VISIT DRAW :: VISIT
* Draw a bird.
***********************************************************************/
void VisitDraw::visit(Bird& bird)
{
   bird.draw();
}

/***********************************************************************
* VISIT DRAW :: VISIT
* Draw a bullet.
***********************************************************************/
void VisitDraw::visit(Bullet& bullet)
{
   bullet.output();
}

/***********************************************************************
* VISIT DRAW :: VISIT
* Draw an effect.
***********************************************************************/
void VisitDraw::visit(Effect& effect)
{
   effect.render();
}

/***********************************************************************
* VISIT MOVE :: VISIT
* Move a bird.
***********************************************************************/
void VisitMove::visit(Bird& bird)
{
   bird.advance();
}

/***********************************************************************
* VISIT MOVE :: VISIT
* Move a bullet.
***********************************************************************/
void VisitMove::visit(Bullet& bullet)
{
   bullet.move(effects);
}

/***********************************************************************
* VISIT MOVE :: VISIT
* Move an effect.
***********************************************************************/
void VisitMove::visit(Effect& effect)
{
   effect.fly();
}