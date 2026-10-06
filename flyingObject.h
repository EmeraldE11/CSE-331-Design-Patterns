/***********************************************************************
 * Header File:
 *    FLYING OBJECT
 * Summary:
 *    Abstract element for the Visitor design pattern.
 ************************************************************************/

#pragma once

// Forward declaring Visitor
class Visitor;

/***********************************************************************
* FLYING OBJECT
* Common interface for all visited game objects.
***********************************************************************/
class FlyingObject
{
public:
   // destructor
   virtual ~FlyingObject() = default;
   // pure virtual accept method to be overridden by child classes
   virtual void accept(Visitor& visitor) = 0;
};