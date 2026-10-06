/***********************************************************************
 * Header File:
 *    Fragment : Pieces that fly off a dead bird
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Pieces that fly off a dead bird
 ************************************************************************/

#pragma once
#include "position.h"

/**********************
 * Effect: stuff that is not interactive
 **********************/
class Effect
{
      // allow unit tests direct access to private/protected members
      friend class TestEffect;
      friend class TestSkeet;

   protected:
      Position pt; // location of the effect
      double age;  // 1.0 = new, 0.0 = dead
   public:
      // create a fragment based on the velocity and position of the bullet
      Effect(const Position &pt) : pt(pt), age(0.5) {}

      // draw it
      virtual void render() const = 0;

      // move it forward with regards to inertia. Let it age
      virtual void fly() = 0;

      // it is dead when age goes to 0.0
      virtual bool isDead() const { return age <= 0.0; }
};

/**********************
 * FRAGMENT
 * Pieces that fly off a dead bird
 **********************/
class Fragment : public Effect
{
      // allow unit tests direct access to private members of Fragment
      friend class TestEffect;

   private:
      Velocity v;  // direction the fragment is flying
      double size; // size of the fragment
   public:
      // create a fragment based on the velocity and position of the bullet
      Fragment(const Position &pt, const Velocity &v);

      // draw it
      void render() const;

      // move it forward with regards to inertia. Let it age
      void fly();
};

/**********************
 * STREEK
 * Stuff that trails off the back of shrapnel
 **********************/
class Streek : public Effect
{
      // allow unit tests direct access to private members of Streek
      friend class TestEffect;

   private:
      Position ptEnd;

   public:
      // create a fragment based on the velocity and position of the bullet
      Streek(const Position &pt, Velocity v);

      // draw it
      void render() const;

      // move it forward with regards to inertia. Let it age
      void fly();
};

/**********************
 * EXHAUST
 * Stuff that comes out the back of a missile when in flight
 **********************/
class Exhaust : public Effect
{
      // allow unit tests direct access to private members of Exhaust
      friend class TestEffect;

   private:
      Position ptEnd;

   public:
      // create a fragment based on the velocity and position of the bullet
      Exhaust(const Position &pt, Velocity v);

      // draw it
      void render() const;

      // move it forward with regards to inertia. Let it age
      void fly();
};

/**********************
 * EFFECT DUMMY
 * A deterministic dummy effect used by unit tests.  render/fly do nothing,
 * and isDead always returns false.
 **********************/
class EffectDummy : public Effect
{
   public:
      EffectDummy() : Effect(Position()) {}

      // render and fly are required by the interface; do nothing here.
      void render() const override { assert(false); }
      void fly() override { assert(false); }

      // for tests, always report not dead
      bool isDead() const override
      {
         assert(false);
         return false;
      }
};
