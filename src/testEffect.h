/***********************************************************************
 * Header File:
 *    Test Effect : Unit test the Effect class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for the Effect/Fragment/Streek/Exhaust classes. Tests set
 *    inputs explicitly and verify internals via friendship with Effect
 *    subclasses.
 ************************************************************************/

#pragma once

#define DEBUG

#include "effect.h"
#include "unitTest.h"
#include <string>

/***************************************************
 * TEST EFFECTS
 * Unit tests for the Effect/Fragment/Streek/Exhaust classes. Tests set members
 * explicitly
 ***************************************************/
class TestEffect : public UnitTest
{
   private:
      const double tolerance = 1e-7;

   public:
      void run()
      {
         reset();

         // Fragment tests
         test_fly_fragmentStationary();
         test_fly_fragmentLeft();
         test_fly_fragmentUp();
         test_fly_fragmentDiagonal();

         // Streek tests
         test_fly_streekStationary();
         test_fly_streekLeft();
         test_fly_streekUp();
         test_fly_streekDiagonal();

         // Exhaust tests
         test_fly_exhaustStationary();
         test_fly_exhaustLeft();
         test_fly_exhaustUp();
         test_fly_exhaustDiagonal();

         report("Effect");
      }

      // Fragment::fly test - stationary
      void test_fly_fragmentStationary()
      { // SETUP
         Position p;
         Velocity v;
         Fragment f(p, v);
         f.pt.x = 0.0;
         f.pt.y = 0.0;
         f.v.dx = 0.0;
         f.v.dy = 0.0;
         f.size = 10.0;
         f.age = 0.5;

         // EXERCISE
         f.fly();

         // VERIFY
         assertUnit(f.pt.x == 0.0);
         assertUnit(
            f.pt.y ==
            0.0); // with zero velocity the position should remain unchanged
         assertEqualsTolerance(0.50 - 0.02, f.age, tolerance);
         assertEqualsTolerance(10 * 0.95, f.size, tolerance);
      } // TEARDOWN

      void test_fly_fragmentLeft()
      { // SETUP
         Position p;
         Velocity v;
         Fragment f(p, v);
         f.pt.x = 11.1;
         f.pt.y = 22.2;
         f.v.dx = -2.0;
         f.v.dy = 0.0;
         f.size = 10.0;
         f.age = 0.5;

         // EXERCISE
         f.fly();

         // VERIFY
         assertEqualsTolerance(11.1 + (-2.0), f.pt.x, tolerance);
         assertEqualsTolerance(22.2, f.pt.y, tolerance);
         assertEqualsTolerance(0.5 - 0.02, f.age, tolerance);
         assertEqualsTolerance(10.0 * 0.95, f.size, tolerance);
         assertEqualsTolerance(-2.0, f.v.dx, tolerance);
         assertEqualsTolerance(0.0, f.v.dy, tolerance);
      } // TEARDOWN

      void test_fly_fragmentUp()
      { // SETUP
         Position p;
         Velocity v;
         Fragment f(p, v);
         f.pt.x = 3.3;
         f.pt.y = 4.4;
         f.v.dx = 0.0;
         f.v.dy = 2.0;
         f.size = 10.0;
         f.age = 0.5;

         // EXERCISE
         f.fly();

         // VERIFY
         assertEqualsTolerance(3.3 + 0.0, f.pt.x, tolerance);
         assertEqualsTolerance(4.4 + 2.0, f.pt.y, tolerance);
         assertEqualsTolerance(0.5 - 0.02, f.age, tolerance);
         assertEqualsTolerance(10.0 * 0.95, f.size, tolerance);
         assertEqualsTolerance(0.0, f.v.dx, tolerance);
         assertEqualsTolerance(2.0, f.v.dy, tolerance);
      } // TEARDOWN

      // Fragment::fly test - diagonal movement
      void test_fly_fragmentDiagonal()
      { // SETUP
         Position p;
         Velocity v;
         Fragment f(p, v);
         f.pt.x = 7.7;
         f.pt.y = 8.8;
         f.v.dx = -1.5;
         f.v.dy = 2.5;
         f.size = 10.0;
         f.age = 0.5;

         // EXERCISE
         f.fly();

         // VERIFY
         assertEqualsTolerance(7.7 + (-1.5), f.pt.x, tolerance);
         assertEqualsTolerance(8.8 + 2.5, f.pt.y, tolerance);
         assertEqualsTolerance(0.5 - 0.02, f.age, tolerance);
         assertEqualsTolerance(10.0 * 0.95, f.size, tolerance);
         assertEqualsTolerance(-1.5, f.v.dx, tolerance);
         assertEqualsTolerance(2.5, f.v.dy, tolerance);
      } // TEARDOWN

      // Streek::fly test - stationary
      void test_fly_streekStationary()
      { // SETUP
         Position p;
         Velocity v;
         Streek s(p, v);
         s.pt.x = 0.0;
         s.pt.y = 0.0;
         s.ptEnd.x = 0.0;
         s.ptEnd.y = 0.0;
         s.age = 0.5;

         // EXERCISE
         s.fly();

         // VERIFY
         // Streek does not move pt in fly(); it only ages by 0.10
         assertEqualsTolerance(0.0, s.pt.x, tolerance);
         assertEqualsTolerance(0.0, s.pt.y, tolerance);
         assertEqualsTolerance(0.0, s.ptEnd.x, tolerance);
         assertEqualsTolerance(0.0, s.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.10, s.age, tolerance);
      } // TEARDOWN

      // Streek::fly test - left
      // name: streekLeft
      // position: 11.1,22.2
      // ptEnd: (set)
      // age: 0.5
      void test_fly_streekLeft()
      { // SETUP
         Position p;
         Velocity v;
         Streek s(p, v);
         s.pt.x = 11.1;
         s.pt.y = 22.2;
         s.ptEnd.x = 9.1; // arbitrary end point for test
         s.ptEnd.y = 22.2;
         s.age = 0.5;

         // EXERCISE
         s.fly();

         // VERIFY
         // Streek does not change location; only ages
         assertEqualsTolerance(11.1, s.pt.x, tolerance);
         assertEqualsTolerance(22.2, s.pt.y, tolerance);
         assertEqualsTolerance(9.1, s.ptEnd.x, tolerance);
         assertEqualsTolerance(22.2, s.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.10, s.age, tolerance);
      } // TEARDOWN

      // Streek::fly test - up
      void test_fly_streekUp()
      { // SETUP
         Position p;
         Velocity v;
         Streek s(p, v);
         s.pt.x = 3.3;
         s.pt.y = 4.4;
         s.ptEnd.x = 3.3;
         s.ptEnd.y = 6.4; // arbitrary end point
         s.age = 0.5;

         // EXERCISE
         s.fly();

         // VERIFY
         assertEqualsTolerance(3.3, s.pt.x, tolerance);
         assertEqualsTolerance(4.4, s.pt.y, tolerance);
         assertEqualsTolerance(3.3, s.ptEnd.x, tolerance);
         assertEqualsTolerance(6.4, s.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.10, s.age, tolerance);
      } // TEARDOWN

      // Streek::fly test - diagonal
      void test_fly_streekDiagonal()
      { // SETUP
         Position p;
         Velocity v;
         Streek s(p, v);
         s.pt.x = 7.7;
         s.pt.y = 8.8;
         s.ptEnd.x = 6.2;
         s.ptEnd.y = 11.3;
         s.age = 0.5;

         // EXERCISE
         s.fly();

         // VERIFY
         assertEqualsTolerance(7.7, s.pt.x, tolerance);
         assertEqualsTolerance(8.8, s.pt.y, tolerance);
         assertEqualsTolerance(6.2, s.ptEnd.x, tolerance);
         assertEqualsTolerance(11.3, s.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.10, s.age, tolerance);
      } // TEARDOWN

      // Exhaust::fly test - stationary
      void test_fly_exhaustStationary()
      { // SETUP
         Position p;
         Velocity v;
         Exhaust e(p, v);
         e.pt.x = 0.0;
         e.pt.y = 0.0;
         e.ptEnd.x = 0.0;
         e.ptEnd.y = 0.0;
         e.age = 0.5;

         // EXERCISE
         e.fly();

         // VERIFY
         // Exhaust only ages by 0.025
         assertEqualsTolerance(0.0, e.pt.x, tolerance);
         assertEqualsTolerance(0.0, e.pt.y, tolerance);
         assertEqualsTolerance(0.0, e.ptEnd.x, tolerance);
         assertEqualsTolerance(0.0, e.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.025, e.age, tolerance);
      } // TEARDOWN

      // Exhaust::fly test - left
      void test_fly_exhaustLeft()
      { // SETUP
         Position p;
         Velocity v;
         Exhaust e(p, v);
         e.pt.x = 11.1;
         e.pt.y = 22.2;
         e.ptEnd.x = 9.1;
         e.ptEnd.y = 22.2;
         e.age = 0.5;

         // EXERCISE
         e.fly();

         // VERIFY
         assertEqualsTolerance(11.1, e.pt.x, tolerance);
         assertEqualsTolerance(22.2, e.pt.y, tolerance);
         assertEqualsTolerance(9.1, e.ptEnd.x, tolerance);
         assertEqualsTolerance(22.2, e.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.025, e.age, tolerance);
      } // TEARDOWN

      // Exhaust::fly test - up
      void test_fly_exhaustUp()
      { // SETUP
         Position p;
         Velocity v;
         Exhaust e(p, v);
         e.pt.x = 3.3;
         e.pt.y = 4.4;
         e.ptEnd.x = 3.3;
         e.ptEnd.y = 6.4;
         e.age = 0.5;

         // EXERCISE
         e.fly();

         // VERIFY
         assertEqualsTolerance(3.3, e.pt.x, tolerance);
         assertEqualsTolerance(4.4, e.pt.y, tolerance);
         assertEqualsTolerance(3.3, e.ptEnd.x, tolerance);
         assertEqualsTolerance(6.4, e.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.025, e.age, tolerance);
      } // TEARDOWN

      // Exhaust::fly test - diagonal
      void test_fly_exhaustDiagonal()
      { // SETUP
         Position p;
         Velocity v;
         Exhaust e(p, v);
         e.pt.x = 7.7;
         e.pt.y = 8.8;
         e.ptEnd.x = 6.2;
         e.ptEnd.y = 11.3;
         e.age = 0.5;

         // EXERCISE
         e.fly();

         // VERIFY
         assertEqualsTolerance(7.7, e.pt.x, tolerance);
         assertEqualsTolerance(8.8, e.pt.y, tolerance);
         assertEqualsTolerance(6.2, e.ptEnd.x, tolerance);
         assertEqualsTolerance(11.3, e.ptEnd.y, tolerance);
         assertEqualsTolerance(0.5 - 0.025, e.age, tolerance);
      } // TEARDOWN
};