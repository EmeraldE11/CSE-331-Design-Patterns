/***********************************************************************
 * Header File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include "position.h"

/******************************************************************************
 * BirdLogic - Logic of each bird type
 *****************************************************************************/
class BirdStorage
{
      friend class TestBird;
      friend class TestSkeet;

   private:
      static Position dimensions;
      int points;
      bool dead;
      Position pt;
      Velocity v;
      double radius;

   public:
      BirdStorage(double radius) : radius(radius), dead(false), points(0) {}

      // getters and setters for points
      int &getPoints() { return points; }
      void setPoints(int points) { this->points = points; }

      // getters and setters for dead
      bool isDead() const { return dead; }
      void kill() { this->dead = true; }

      // getters and setters for position
      Position &getPosition() { return pt; }
      void operator=(const Position &rhs) { this->pt = rhs; }

      // getters and setters for velocity
      Velocity &getVelocity() { return v; }
      void operator=(const Velocity &rhs) { this->v = rhs; }

      // getter for bird radius
      double getRadius() const { return radius; }
      // getter for screen dimensions
      Position getDimensions() const { return dimensions; }
};

/******************************************************************************
 * BirdLogic - Logic of each bird type
 *****************************************************************************/
class BirdLogic
{
      friend class TestBird;
      friend class TestSkeet;

   protected:
      BirdStorage storage;

   public:
      BirdLogic(double radius) : storage(radius) {}
      virtual ~BirdLogic() = default;
      virtual void advance() = 0;

      // getters and setters for points
      int &getPoints() { return storage.getPoints(); }
      void setPoints(int points) { storage.setPoints(points); }

      // getters and setters for dead
      bool isDead() const { return storage.isDead(); }
      void kill() { storage.kill(); }

      // getters and setters for position
      Position &getPosition() { return storage.getPosition(); }
      void operator=(const Position &rhs) { storage = rhs; }

      // getters and setters for velocity
      Velocity &getVelocity() { return storage.getVelocity(); }
      void operator=(const Velocity &rhs) { storage = rhs; }

      // getter for bird radius
      double getRadius() const { return storage.getRadius(); }
      // getter for screen dimensions
      Position getDimensions() const { return storage.getDimensions(); }

      // helper function: determine if bird is out of bounds
      bool isOutOfBounds()
      {
         const Position pt = getPosition();
         const double radius = getRadius();
         const Position dimensions = storage.getDimensions();

         return (
            pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
            pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius
         );
      }
};

/******************************************************************************
 * Standard bird logic
 *****************************************************************************/
class StandardLogic : public BirdLogic
{
   public:
      StandardLogic(double radius) : BirdLogic(radius) {}
      void advance();
};

/******************************************************************************
 * Floater bird logic
 *****************************************************************************/
class FloaterLogic : public BirdLogic
{
   public:
      FloaterLogic(double radius) : BirdLogic(radius) {}
      void advance();
};

/******************************************************************************
 * Sinker bird logic
 *****************************************************************************/
class SinkerLogic : public BirdLogic
{
   public:
      SinkerLogic(double radius) : BirdLogic(radius) {}
      void advance();
};

/******************************************************************************
 * Crazy bird logic
 *****************************************************************************/
class CrazyLogic : public BirdLogic
{
   public:
      CrazyLogic(double radius) : BirdLogic(radius) {}
      void advance();
};

/******************************************************************************
 * Bird - Everything that can be shot
 *****************************************************************************/
class Bird
{
      friend class TestBird;
      friend class TestSkeet;

   protected:
      BirdLogic *logic;

   public:
      Bird() : logic(nullptr) {}
      virtual ~Bird() { delete logic; }

      // setters
      void operator=(const Position &rhs) { *logic = rhs; }
      void operator=(const Velocity &rhs) { *logic = rhs; }
      void setPoints(int pts) { logic->setPoints(pts); }
      void kill() { logic->kill(); }

      // getters
      Position getPosition() const { return logic->getPosition(); }
      Velocity getVelocity() const { return logic->getVelocity(); }
      bool isOutOfBounds() const { return logic->isOutOfBounds(); }
      double getRadius() const { return logic->getRadius(); }
      int getPoints() const { return logic->getPoints(); }
      bool isDead() const { return logic->isDead(); }

      // special functions
      virtual void draw() = 0;
      virtual void advance() { logic->advance(); }
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public Bird
{
      friend class TestSkeet;

   public:
      Standard(double radius = 25.0, double speed = 5.0, int points = 10);
      void draw();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public Bird
{
      friend class TestSkeet;

   public:
      Floater(double radius = 30.0, double speed = 5.0, int points = 15);
      void draw();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public Bird
{
      friend class TestSkeet;

   public:
      Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
      void draw();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public Bird
{
   public:
      Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
      void draw();
};

/*********************************************
 * BIRD FAKE
 * A simple fake Bird used in tests. Its `draw()` and `advance()` must never be
 * called during tests; if either is called the test will fail via
 * assert(false).
 *********************************************/
class BirdLogicFake : public BirdLogic
{
   public:
      BirdLogicFake(double radius = 0.0) : BirdLogic(radius) {}
      void advance() { assert(false); }
};

class BirdFake : public Bird
{
   public:
      BirdFake() : Bird() { logic = new BirdLogicFake; }
      void draw() override { assert(false); }
      void advance() override { assert(false); }
};
