/***********************************************************************
 * Header File:
 *    Test Points : Unit test the Points class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for the Points class.
 ************************************************************************/

#pragma once

#define DEBUG

#include "unitTest.h"
#include "points.h"
#include <string>

 /***************************************************
  * TEST POINTS
  * Unit tests for the Points class. Tests set members explicitly
  ***************************************************/
class TestPoints : public UnitTest
{
public:
   void run()
   {
      reset();

      test_points_constructor();
      test_points_update_notExpire();
      test_points_update_expire();

      report("Points");
   }

   // constructor: verify deterministic initialization (randomDouble returns min)
   void test_points_constructor()
   {  // SETUP
      Position p(100.0, 50.0);
      // EXERCISE
      Points pts(p, 7);
      // VERIFY
      // position copied
      assertEqualsTolerance(100.0, pts.pt.getX(), tolerance);
      assertEqualsTolerance(50.0,  pts.pt.getY(), tolerance);

      // value and age
      assertUnit(pts.value == 7);
      assertEqualsTolerance(1.0, pts.age, tolerance);

      // randomDouble returns min => v.dx and v.dy set to 1.0 (multiplyFactor positive)
      assertEqualsTolerance(1.0, pts.v.getDx(), tolerance);
      assertEqualsTolerance(1.0, pts.v.getDy(), tolerance);
   }  // TEARDOWN

   // update: age does not expire after update
   void test_points_update_notExpire()
   {  // SETUP
      Position p(10.0, 20.0);
      Points pts(p, 5);

      // explicitly set internals to deterministic values
      pts.pt.setX(10.0);
      pts.pt.setY(20.0);
      pts.v.setDx(2.0);
      pts.v.setDy(3.0);
      pts.value = 5;
      pts.age = 0.50;

      // EXERCISE
      pts.update();

      // VERIFY
      // randomDouble(-0.15,0.15) returns -0.15 => v decreased by 0.15
      assertEqualsTolerance(2.0 - 0.15, pts.v.getDx(), tolerance);
      assertEqualsTolerance(3.0 - 0.15, pts.v.getDy(), tolerance);

      // position updated by new velocity
      assertEqualsTolerance(10.0 + (2.0 - 0.15), pts.pt.getX(), tolerance);
      assertEqualsTolerance(20.0 + (3.0 - 0.15), pts.pt.getY(), tolerance);

      // age decreased by 0.01 and not expired
      assertEqualsTolerance(0.50 - 0.01, pts.age, tolerance);
      assertUnit(pts.isDead() == false);

      // explicit other checks
      assertUnit(pts.value == 5);
   }  // TEARDOWN

   // update: age expires (age reaches 0.0)
   void test_points_update_expire()
   {  // SETUP
      Position p(30.0, 40.0);
      Points pts(p, -3);

      // explicitly set internals to deterministic values
      pts.pt.setX(30.0);
      pts.pt.setY(40.0);
      pts.v.setDx(0.0);
      pts.v.setDy(0.0);
      pts.value = -3;
      pts.age = 0.01; // will go to 0.0 after update

      // EXERCISE
      pts.update();

      // VERIFY
      // velocity changed by randomDouble min (-0.15)
      assertEqualsTolerance(0.0 - 0.15, pts.v.getDx(), tolerance);
      assertEqualsTolerance(0.0 - 0.15, pts.v.getDy(), tolerance);

      // position updated by new velocity
      assertEqualsTolerance(30.0 + (-0.15), pts.pt.getX(), tolerance);
      assertEqualsTolerance(40.0 + (-0.15), pts.pt.getY(), tolerance);

      // age decreased to 0.0 and isDead returns true
      assertEqualsTolerance(0.01 - 0.01, pts.age, tolerance);
      assertUnit(pts.isDead() == true);

      // explicit other checks
      assertUnit(pts.value == -3);
   }  // TEARDOWN

};