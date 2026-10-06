/***********************************************************************
 * Header File:
 *    Test Gun : Unit test the Gun class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for the Gun class. Tests set inputs explicitly and
 *    verify Gun's private members via friendship.
 ************************************************************************/

#pragma once

#define DEBUG

#include "unitTest.h"
#include "gun.h"
#include <string>

 /***************************************************
  * TEST GUN
  * Unit tests for the Gun class. Tests set members explicitly
  ***************************************************/
class TestGun : public UnitTest
{
public:
   void run()
   {
      reset();

      test_constructor_origin();
      test_constructor_position();

      test_interact_nothing();
      test_interact_clockSlow();

      // additional interact tests requested
      test_interact_clockFast();
      test_interact_counterSlow();
      test_interact_counterFast();
      test_interact_wrapLow();
      test_interact_wrapHigh();
      test_interact_cancel();

      report("Gun");
   }

   // constructor: gun placed at origin (0.0, 0.0)
   void test_constructor_origin()
   {  // SETUP
      Position p;
      p.x = 0.0;
      p.y = 0.0;
      // EXERCISE
      Gun g(p);
      // VERIFY
      // angle is initialized to 0.78 in the constructor
      assertUnit(g.angle == 0.78);
      // position copied into gun
      assertUnit(g.pt.x == 0.0);
      assertUnit(g.pt.y == 0.0);
   }  // TEARDOWN

   // constructor: gun placed at (10, 20)
   void test_constructor_position()
   {  // SETUP
      Position p;
      p.x = 10.0;
      p.y = 20.0;
      // EXERCISE
      Gun g(p);
      // VERIFY
      assertUnit(g.angle == 0.78);
      assertUnit(g.pt.x == 10.0);
      assertUnit(g.pt.y == 20.0);
   }  // TEARDOWN

   // interact: nothing (clockwise=0, counterclockwise=0) - angle should not change
   void test_interact_nothing()
   {  // SETUP
      Position p;
      p.x = 5.0;
      p.y = 6.0;
      Gun g(p);
      g.angle = 1.234;         // explicitly set angle
      g.pt.x = 5.0; 
      g.pt.y = 6.0; // explicit position
      // EXERCISE
      g.interact(0, 0);
      // VERIFY
      assertEqualsTolerance(1.234, g.angle, 1e-7);
      assertUnit(g.pt.x == 5.0);
      assertUnit(g.pt.y == 6.0);
   }  // TEARDOWN

   // interact: slow clockwise input (clockwise=5) - angle increases by 0.025 (unless capped)
   void test_interact_clockSlow()
   {  // SETUP
      Position p;
      p.x = 2.0;
      p.y = 3.0;
      Gun g(p);
      g.angle = 1.234;           // explicitly set angle
      g.pt.x = 2.0; 
      g.pt.y = 3.0; // explicit position
      // EXERCISE
      g.interact(5, 0); // slow clockwise -> +0.025
      // VERIFY
      assertEqualsTolerance(1.234 + 0.025, g.angle, 1e-7);
      assertUnit(g.pt.x == 2.0);
      assertUnit(g.pt.y == 3.0);
   }  // TEARDOWN

   // interact: fast clockwise (clockwise=11) -> +0.06, capped by M_PI_2 if necessary
   void test_interact_clockFast()
   {  // SETUP
      Position p;
      p.x = 7.0;
      p.y = 8.0;
      Gun g(p);
      g.angle = 1.234;
      g.pt.x = 7.0; 
      g.pt.y = 8.0;
      // EXERCISE
      g.interact(11, 0); // fast clockwise -> +0.06
      // VERIFY
      assertEqualsTolerance(1.234 + 0.06, g.angle, 1e-7);
      assertUnit(g.pt.x == 7.0);
      assertUnit(g.pt.y == 8.0);
   }  // TEARDOWN

   // interact: slow counterclockwise (counterclockwise=5) -> -0.025
   void test_interact_counterSlow()
   {  // SETUP
      Position p;
      p.x = 4.0;
      p.y = 5.0;
      Gun g(p);
      g.angle = 1.234;
      g.pt.x = 4.0; 
      g.pt.y = 5.0;
      // EXERCISE
      g.interact(0, 5); // slow counterclockwise -> -0.025
      // VERIFY
      assertEqualsTolerance(1.234 - 0.025, g.angle, 1e-7);
      assertUnit(g.pt.x == 4.0);
      assertUnit(g.pt.y == 5.0);
   }  // TEARDOWN

   // interact: fast counterclockwise (counterclockwise=11) -> -0.06
   void test_interact_counterFast()
   {  // SETUP
      Position p;
      p.x = 9.0;
      p.y = 10.0;
      Gun g(p);
      g.angle = 1.234;
      g.pt.x = 9.0; 
      g.pt.y = 10.0;
      // EXERCISE
      g.interact(0, 11); // fast counterclockwise -> -0.06
      // VERIFY
      assertEqualsTolerance(1.234 - 0.06, g.angle, 1e-7);
      assertUnit(g.pt.x == 9.0);
      assertUnit(g.pt.y == 10.0);
   }  // TEARDOWN

   // interact: wrapLow: angle starts low and counterclockwise large -> should clamp to 0.0
   void test_interact_wrapLow()
   {  // SETUP
      Position p;
      p.x = 1.0;
      p.y = 2.0;
      Gun g(p);
      g.angle = 0.01;
      g.pt.x = 1.0; 
      g.pt.y = 2.0;
      // EXERCISE
      g.interact(0, 11); // subtract 0.06 => negative => clamp to 0.0
      // VERIFY
      assertEqualsTolerance(0.0, g.angle, 1e-7);
      assertUnit(g.pt.x == 1.0);
      assertUnit(g.pt.y == 2.0);
   }  // TEARDOWN

   // interact: wrapHigh: large angle, fast clockwise -> clamp to M_PI_2
   void test_interact_wrapHigh()
   {  // SETUP
      Position p;
      p.x = 3.0;
      p.y = 4.0;
      Gun g(p);
      g.angle = 6.28; // large angle
      g.pt.x = 3.0; 
      g.pt.y = 4.0;
      static constexpr double HALF_PI = 1.5707963267948966;
      // EXERCISE
      g.interact(11, 0); // would add 0.06 but then clamp to HALF_PI
      // VERIFY
      assertEqualsTolerance(HALF_PI, g.angle, 1e-7);
      assertUnit(g.pt.x == 3.0);
      assertUnit(g.pt.y == 4.0);
   }  // TEARDOWN

   // interact: cancel inputs (clockwise=1, counterclockwise=1) -> net zero change
   void test_interact_cancel()
   {  // SETUP
      Position p;
      p.x = 11.0;
      p.y = 12.0;
      Gun g(p);
      g.angle = 1.234;
      g.pt.x = 11.0; 
      g.pt.y = 12.0;
      // EXERCISE
      g.interact(1, 1); // +0.025 then -0.025 => net 0
      // VERIFY
      assertEqualsTolerance(1.234, g.angle, 1e-7);
      assertUnit(g.pt.x == 11.0);
      assertUnit(g.pt.y == 12.0);
   }  // TEARDOWN

};