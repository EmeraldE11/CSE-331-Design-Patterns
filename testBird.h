/***********************************************************************
 * Header File:
 *    Test Bird : Unit test the Bird class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for Bird::isOutOfBounds(). Uses BirdFake test double.
 ************************************************************************/

#pragma once

#define DEBUG

#include "unitTest.h"
#include "bird.h"
#include <string>

 /***************************************************
  * TEST BIRD
  * Unit tests for the Bird class. Tests set members explicitly
  ***************************************************/
class TestBird : public UnitTest
{
public:
   void run()
   {
      reset();

      // isOutOfBounds tests
      test_isOutOfBounds_rightNear();
      test_isOutOfBounds_rightOver();
      test_isOutOfBounds_leftNear();
      test_isOutOfBounds_leftOver();
      test_isOutOfBounds_topNear();
      test_isOutOfBounds_topOver();
      test_isOutOfBounds_bottomNear();
      test_isOutOfBounds_bottomOver();

      // advance tests
      test_advance_standardAlive();
      test_advance_standardDead();
      test_advance_sinkerAlive();
      test_advance_sinkerDead();
      test_advance_floaterAlive();
      test_advance_floaterDead();
      test_advance_crazyAlive();
      test_advance_crazyDead();

      report("Bird");
   }

   // right side - just inside (pt.x < dimensions.x + radius)
   void test_isOutOfBounds_rightNear()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = 204.0;            // 204 < 200 + 5 => inside
      b.pt.y = 50.0;
      b.v.dx = 0.0;
      b.v.dy = 0.0;
      b.radius = 5.0;
      b.dead = false;
      b.points = 7;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(204.0, b.pt.x, tolerance);
      assertEqualsTolerance(50.0, b.pt.y, tolerance);
      assertEqualsTolerance(0.0, b.v.dx, tolerance);
      assertEqualsTolerance(0.0, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == false);
      assertUnit(b.points == 7);
      assertUnit(out == false);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // right side - exactly at dimensions + radius => out
   void test_isOutOfBounds_rightOver()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = 205.0;            // 205 >= 200 + 5 => out
      b.pt.y = 60.0;
      b.v.dx = 1.0;
      b.v.dy = 2.0;
      b.radius = 5.0;
      b.dead = true;
      b.points = 3;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(205.0, b.pt.x, tolerance);
      assertEqualsTolerance(60.0, b.pt.y, tolerance);
      assertEqualsTolerance(1.0, b.v.dx, tolerance);
      assertEqualsTolerance(2.0, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == true);
      assertUnit(b.points == 3);
      assertUnit(out == true);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // left side - just inside (pt.x > -radius)
   void test_isOutOfBounds_leftNear()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = -4.0;             // -4 > -5 => inside
      b.pt.y = 100.0;
      b.v.dx = -1.0;
      b.v.dy = 0.0;
      b.radius = 5.0;
      b.dead = false;
      b.points = 11;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(-4.0, b.pt.x, tolerance);
      assertEqualsTolerance(100.0, b.pt.y, tolerance);
      assertEqualsTolerance(-1.0, b.v.dx, tolerance);
      assertEqualsTolerance(0.0, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == false);
      assertUnit(b.points == 11);
      assertUnit(out == false);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // left side - just outside (pt.x < -radius)
   void test_isOutOfBounds_leftOver()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = -6.0;             // -6 < -5 => out
      b.pt.y = 100.0;
      b.v.dx = -2.0;
      b.v.dy = 1.0;
      b.radius = 5.0;
      b.dead = true;
      b.points = 5;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(-6.0, b.pt.x, tolerance);
      assertEqualsTolerance(100.0, b.pt.y, tolerance);
      assertEqualsTolerance(-2.0, b.v.dx, tolerance);
      assertEqualsTolerance(1.0, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == true);
      assertUnit(b.points == 5);
      assertUnit(out == true);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // top side - just inside (pt.y < dimensions.y + radius)
   void test_isOutOfBounds_topNear()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = 120.0;
      b.pt.y = 204.0;            // 204 < 200 + 5 => inside
      b.v.dx = 0.5;
      b.v.dy = 0.5;
      b.radius = 5.0;
      b.dead = false;
      b.points = 2;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(120.0, b.pt.x, tolerance);
      assertEqualsTolerance(204.0, b.pt.y, tolerance);
      assertEqualsTolerance(0.5, b.v.dx, tolerance);
      assertEqualsTolerance(0.5, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == false);
      assertUnit(b.points == 2);
      assertUnit(out == false);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // top side - just outside (pt.y >= dimensions.y + radius)
   void test_isOutOfBounds_topOver()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = 120.0;
      b.pt.y = 205.0;            // 205 >= 200 + 5 => out
      b.v.dx = 0.0;
      b.v.dy = 3.0;
      b.radius = 5.0;
      b.dead = true;
      b.points = 9;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(120.0, b.pt.x, tolerance);
      assertEqualsTolerance(205.0, b.pt.y, tolerance);
      assertEqualsTolerance(0.0, b.v.dx, tolerance);
      assertEqualsTolerance(3.0, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == true);
      assertUnit(b.points == 9);
      assertUnit(out == true);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // bottom side - just inside (pt.y > -radius)
   void test_isOutOfBounds_bottomNear()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = 80.0;
      b.pt.y = -4.0;             // -4 > -5 => inside
      b.v.dx = 0.0;
      b.v.dy = -1.5;
      b.radius = 5.0;
      b.dead = false;
      b.points = 12;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(80.0, b.pt.x, tolerance);
      assertEqualsTolerance(-4.0, b.pt.y, tolerance);
      assertEqualsTolerance(0.0, b.v.dx, tolerance);
      assertEqualsTolerance(-1.5, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == false);
      assertUnit(b.points == 12);
      assertUnit(out == false);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // bottom side - just outside (pt.y < -radius)
   void test_isOutOfBounds_bottomOver()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      BirdFake b;
      b.pt.x = 80.0;
      b.pt.y = -6.0;             // -6 < -5 => out
      b.v.dx = 1.0;
      b.v.dy = -2.0;
      b.radius = 5.0;
      b.dead = true;
      b.points = 4;
      // EXERCISE
      bool out = b.isOutOfBounds();
      // VERIFY
      assertEqualsTolerance(80.0, b.pt.x, tolerance);
      assertEqualsTolerance(-6.0, b.pt.y, tolerance);
      assertEqualsTolerance(1.0, b.v.dx, tolerance);
      assertEqualsTolerance(-2.0, b.v.dy, tolerance);
      assertEqualsTolerance(5.0, b.radius, tolerance);
      assertUnit(b.dead == true);
      assertUnit(b.points == 4);
      assertUnit(out == true);
      // TEARDOWN
      Bird::dimensions = oldDimensions;
   
   }

   // Advance: Standard stays alive after advance (within boundary)
   void test_advance_standardAlive()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Standard s(5.0, 10.0, 10); // will be overwritten explicitly
      s.pt.x = 194.0;
      s.pt.y = 50.0;
      s.v.dx = 10.0;
      s.v.dy = 0.0;
      s.radius = 5.0;
      s.dead = false;
      s.points = 10;

      // EXERCISE
      s.advance();
      // capture results for VERIFY
      double expectedDx = 10.0 * 0.995;
      double expectedX  = 194.0 + expectedDx;

      // VERIFY
      assertEqualsTolerance(194.0, 194.0, tolerance); // explicit check of initial expectation (sanity)
      assertEqualsTolerance(50.0, s.pt.y, tolerance);
      assertEqualsTolerance(expectedDx, s.v.dx, tolerance);
      assertEqualsTolerance(expectedX, s.pt.x, tolerance);
      assertEqualsTolerance(5.0, s.radius, tolerance);
      assertUnit(s.dead == false);
      assertUnit(s.points == 10);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Standard moves out of bounds and becomes dead
   void test_advance_standardDead()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Standard s(5.0, 10.0, 10); // will be overwritten explicitly
      s.pt.x = 196.0;
      s.pt.y = 60.0;
      s.v.dx = 10.0;
      s.v.dy = 0.0;
      s.radius = 5.0;
      s.dead = false;
      s.points = 10;

      // EXERCISE
      s.advance();
      // capture results for VERIFY
      double expectedDx = 10.0 * 0.995;
      double expectedX  = 196.0 + expectedDx;

      // VERIFY
      assertEqualsTolerance(196.0, 196.0, tolerance); // explicit check of initial expectation (sanity)
      assertEqualsTolerance(60.0, s.pt.y, tolerance);
      assertEqualsTolerance(expectedDx, s.v.dx, tolerance);
      assertEqualsTolerance(expectedX, s.pt.x, tolerance);
      assertEqualsTolerance(5.0, s.radius, tolerance);
      // moved out of bounds => dead true and points negated
      assertUnit(s.dead == true);
      assertUnit(s.points == -10);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Sinker stays alive after advance (within boundary)
   void test_advance_sinkerAlive()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Sinker s(5.0, 10.0, 10); // will be overwritten explicitly
      s.pt.x = 194.0;
      s.pt.y = 50.0;
      s.v.dx = 10.0;
      s.v.dy = 0.0;
      s.radius = 5.0;
      s.dead = false;
      s.points = 10;

      // EXERCISE
      s.advance();
      // expected velocity and position after advance:
      double expectedDy = 0.0 - 0.07;        // v.addDy(-0.07)
      double expectedX  = 194.0 + 10.0;      // pt.add(v) uses original dx (no drag)
      double expectedY  = 50.0 + expectedDy; // pt.add(v) uses updated dy

      // VERIFY
      assertEqualsTolerance(194.0, 194.0, tolerance); // explicit check of initial expectation
      assertEqualsTolerance(50.0, 50.0, tolerance);
      assertEqualsTolerance(10.0, s.v.dx, tolerance);
      assertEqualsTolerance(expectedDy, s.v.dy, tolerance);
      assertEqualsTolerance(expectedX, s.pt.x, tolerance);
      assertEqualsTolerance(expectedY, s.pt.y, tolerance);
      assertEqualsTolerance(5.0, s.radius, tolerance);
      assertUnit(s.dead == false);
      assertUnit(s.points == 10);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Sinker moves out of bounds and becomes dead
   void test_advance_sinkerDead()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Sinker s(5.0, 10.0, 10); // will be overwritten explicitly
      s.pt.x = 196.0;
      s.pt.y = 60.0;
      s.v.dx = 10.0;
      s.v.dy = 0.0;
      s.radius = 5.0;
      s.dead = false;
      s.points = 10;

      // EXERCISE
      s.advance();
      // expected velocity and position after advance:
      double expectedDy = 0.0 - 0.07;        // v.addDy(-0.07)
      double expectedX  = 196.0 + 10.0;      // pt.add(v)
      double expectedY  = 60.0 + expectedDy;

      // VERIFY
      assertEqualsTolerance(196.0, 196.0, tolerance);
      assertEqualsTolerance(60.0, 60.0, tolerance);
      assertEqualsTolerance(10.0, s.v.dx, tolerance);
      assertEqualsTolerance(expectedDy, s.v.dy, tolerance);
      assertEqualsTolerance(expectedX, s.pt.x, tolerance);
      assertEqualsTolerance(expectedY, s.pt.y, tolerance);
      assertEqualsTolerance(5.0, s.radius, tolerance);
      // moved out of bounds => dead true and points negated
      assertUnit(s.dead == true);
      assertUnit(s.points == -10);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Floater stays alive after advance (within boundary)
   void test_advance_floaterAlive()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Floater f(5.0, 10.0, 15); // will be overwritten explicitly
      f.pt.x = 194.0;
      f.pt.y = 50.0;
      f.v.dx = 10.0;
      f.v.dy = 0.0;
      f.radius = 5.0;
      f.dead = false;
      f.points = 15;

      // EXERCISE
      f.advance();
      // expected: v *= 0.99, pt += v(using multiplied values), then v.addDy(0.05)
      double expectedDxBeforeAdd = 10.0 * 0.99;
      double expectedDyBeforeAdd = 0.0 * 0.99;
      double expectedX  = 194.0 + expectedDxBeforeAdd;
      double expectedY  = 50.0 + expectedDyBeforeAdd;
      double expectedFinalDy = expectedDyBeforeAdd + 0.05; // after v.addDy(0.05)

      // VERIFY
      assertEqualsTolerance(194.0, 194.0, tolerance);
      assertEqualsTolerance(50.0, 50.0, tolerance);
      assertEqualsTolerance(expectedDxBeforeAdd, f.v.dx, tolerance);
      assertEqualsTolerance(expectedFinalDy, f.v.dy, tolerance);
      assertEqualsTolerance(expectedX, f.pt.x, tolerance);
      assertEqualsTolerance(expectedY, f.pt.y, tolerance);
      assertEqualsTolerance(5.0, f.radius, tolerance);
      assertUnit(f.dead == false);
      assertUnit(f.points == 15);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Floater moves out of bounds and becomes dead
   void test_advance_floaterDead()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Floater f(5.0, 10.0, 15); // will be overwritten explicitly
      f.pt.x = 196.0;
      f.pt.y = 60.0;
      f.v.dx = 10.0;
      f.v.dy = 0.0;
      f.radius = 5.0;
      f.dead = false;
      f.points = 15;

      // EXERCISE
      f.advance();
      // expected after v *= 0.99
      double expectedDxBeforeAdd = 10.0 * 0.99;
      double expectedDyBeforeAdd = 0.0 * 0.99;
      double expectedX  = 196.0 + expectedDxBeforeAdd;
      double expectedY  = 60.0 + expectedDyBeforeAdd;
      double expectedFinalDy = expectedDyBeforeAdd + 0.05;

      // VERIFY
      assertEqualsTolerance(196.0, 196.0, tolerance);
      assertEqualsTolerance(60.0, 60.0, tolerance);
      assertEqualsTolerance(expectedDxBeforeAdd, f.v.dx, tolerance);
      assertEqualsTolerance(expectedFinalDy, f.v.dy, tolerance);
      assertEqualsTolerance(expectedX, f.pt.x, tolerance);
      assertEqualsTolerance(expectedY, f.pt.y, tolerance);
      assertEqualsTolerance(5.0, f.radius, tolerance);
      // moved out of bounds => dead true and points negated
      assertUnit(f.dead == true);
      assertUnit(f.points == -15);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Crazy changes direction (random min) and remains alive
   void test_advance_crazyAlive()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Crazy c(5.0, 4.5, 30); // values will be overridden explicitly
      c.pt.x = 50.0;
      c.pt.y = 50.0;
      c.v.dx = 2.0;
      c.v.dy = 1.0;
      c.radius = 5.0;
      c.dead = false;
      c.points = 30;

      // EXERCISE
      c.advance();

      // VERIFY
      // randomInt(0,15) returns 0 so v.addDx(randomDouble(-1.5,1.5)) adds -1.5
      assertEqualsTolerance(2.0 - 1.5, c.v.dx, tolerance);
      assertEqualsTolerance(1.0 - 1.5, c.v.dy, tolerance);

      // position updated by the new velocity
      assertEqualsTolerance(50.0 + (2.0 - 1.5), c.pt.x, tolerance);
      assertEqualsTolerance(50.0 + (1.0 - 1.5), c.pt.y, tolerance);

      // explicit checks of other members
      assertEqualsTolerance(5.0, c.radius, tolerance);
      assertUnit(c.dead == false);
      assertUnit(c.points == 30);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }

   // Advance: Crazy changes direction (random min) and moves out of bounds -> dead
   void test_advance_crazyDead()
   {  // SETUP
      Position oldDimensions = Bird::dimensions;
      Bird::dimensions.x = 200.0;
      Bird::dimensions.y = 200.0;

      Crazy c(5.0, 4.5, 30); // values will be overridden explicitly
      c.pt.x = 197.0;
      c.pt.y = 60.0;
      c.v.dx = 10.0;
      c.v.dy = 0.0;
      c.radius = 5.0;
      c.dead = false;
      c.points = 30;

      // EXERCISE
      c.advance();

      // VERIFY
      // velocity changed by randomDouble(-1.5,1.5) => -1.5
      assertEqualsTolerance(10.0 - 1.5, c.v.dx, tolerance);
      assertEqualsTolerance(0.0 - 1.5, c.v.dy, tolerance);

      // position updated by the new velocity
      assertEqualsTolerance(197.0 + (10.0 - 1.5), c.pt.x, tolerance);
      assertEqualsTolerance(60.0 + (0.0 - 1.5), c.pt.y, tolerance);

      // moved out of bounds (x >= dimensions.x + radius) => dead true and points negated
      assertUnit(c.dead == true);
      assertUnit(c.points == -30);
      assertEqualsTolerance(5.0, c.radius, tolerance);

      // TEARDOWN
      Bird::dimensions = oldDimensions;
   }
};