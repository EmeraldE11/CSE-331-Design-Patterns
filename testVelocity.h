/***********************************************************************
 * Header File:
 *    Test Velocity : Unit test the Velocity class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for `Velocity` mutators. Tests set members explicitly
 *    and verify members directly.
 ************************************************************************/

#pragma once

#define DEBUG

#include "unitTest.h"
#include "position.h" // defines Velocity
#include <string>

 /***************************************************
  * TEST VELOCITY
  * Unit tests for the Velocity class. Tests set members explicitly
  ***************************************************/
class TestVelocity : public UnitTest
{
public:
   void run()
   {
      reset();

      // addDx tests
      test_addDx_stationary0();
      test_addDx_moving0();
      test_addDx_stationary22();
      test_addDx_moving22();

      // addDy tests
      test_addDy_stationary0();
      test_addDy_moving0();
      test_addDy_stationary22();
      test_addDy_moving22();

      // operator+= tests
      test_plusEquals_stationary();
      test_plusEquals_rhsStationary();
      test_plusEquals_lhsStationary();
      test_plusEquals_bothMove();

      // operator*= tests (multiply)
      test_multiply_stationary0();
      test_multiply_stationary1();
      test_multiply_stationary5();
      test_multiply_moving0();
      test_multiply_moving1();
      test_multiply_moving5();

      // Velocity::set(angle, speed) tests
      test_set_nospeed();
      test_set_up();
      test_set_right();
      test_set_down();
      test_set_left();

      report("Velocity");
   }

   // addDx: initial dx == 0, change == 0
   void test_addDx_stationary0()
   {  // SETUP
      Velocity v;
      v.dx = 0.0;
      v.dy = 5.5;    // explicitly set dy as well
      // EXERCISE
      v.addDx(0.0);
      // VERIFY
      assertUnit(v.dx == 0.0);
      assertUnit(v.dy == 5.5);
   }  // TEARDOWN

   // addDx: initial dx == 11, change == 0
   void test_addDx_moving0()
   {  // SETUP
      Velocity v;
      v.dx = 11.0;
      v.dy = -3.3;
      // EXERCISE
      v.addDx(0.0);
      // VERIFY
      assertUnit(v.dx == 11.0);
      assertUnit(v.dy == -3.3);
   }  // TEARDOWN

   // addDx: initial dx == 0, change == 22
   void test_addDx_stationary22()
   {  // SETUP
      Velocity v;
      v.dx = 0.0;
      v.dy = 7.7;
      // EXERCISE
      v.addDx(22.0);
      // VERIFY
      assertUnit(v.dx == 22.0);
      assertUnit(v.dy == 7.7);
   }  // TEARDOWN

   // addDx: initial dx == 11, change == 22
   void test_addDx_moving22()
   {  // SETUP
      Velocity v;
      v.dx = 11.0;
      v.dy = 0.0;
      // EXERCISE
      v.addDx(22.0);
      // VERIFY
      assertUnit(v.dx == 33.0);
      assertUnit(v.dy == 0.0);
   }  // TEARDOWN

   // addDy: initial dy == 0, change == 0
   void test_addDy_stationary0()
   {  // SETUP
      Velocity v;
      v.dx = -2.2;   // explicitly set dx as well
      v.dy = 0.0;
      // EXERCISE
      v.addDy(0.0);
      // VERIFY
      assertUnit(v.dy == 0.0);
      assertUnit(v.dx == -2.2);
   }  // TEARDOWN

   // addDy: initial dy == 11, change == 0
   void test_addDy_moving0()
   {  // SETUP
      Velocity v;
      v.dx = 4.4;
      v.dy = 11.0;
      // EXERCISE
      v.addDy(0.0);
      // VERIFY
      assertUnit(v.dy == 11.0);
      assertUnit(v.dx == 4.4);
   }  // TEARDOWN

   // addDy: initial dy == 0, change == 22
   void test_addDy_stationary22()
   {  // SETUP
      Velocity v;
      v.dx = 1.1;
      v.dy = 0.0;
      // EXERCISE
      v.addDy(22.0);
      // VERIFY
      assertUnit(v.dy == 22.0);
      assertUnit(v.dx == 1.1);
   }  // TEARDOWN

   // addDy: initial dy == 11, change == 22
   void test_addDy_moving22()
   {  // SETUP
      Velocity v;
      v.dx = 0.0;
      v.dy = 11.0;
      // EXERCISE
      v.addDy(22.0);
      // VERIFY
      assertUnit(v.dy == 33.0);
      assertUnit(v.dx == 0.0);
   }  // TEARDOWN

   // operator+=: LHS (0,0), RHS (0,0)
   void test_plusEquals_stationary()
   {  // SETUP
      Velocity lhs;
      Velocity rhs;
      lhs.dx = 0.0; 
      lhs.dy = 0.0;
      rhs.dx = 0.0; 
      rhs.dy = 0.0;
      // EXERCISE
      lhs += rhs;
      // VERIFY
      assertUnit(lhs.dx == 0.0);
      assertUnit(lhs.dy == 0.0);
      // RHS should remain unchanged
      assertUnit(rhs.dx == 0.0);
      assertUnit(rhs.dy == 0.0);
   }  // TEARDOWN

   // operator+=: LHS (11,22), RHS (0,0)
   void test_plusEquals_rhsStationary()
   {  // SETUP
      Velocity lhs;
      Velocity rhs;
      lhs.dx = 11.0; 
      lhs.dy = 22.0;
      rhs.dx = 0.0;  
      rhs.dy = 0.0;
      // EXERCISE
      lhs += rhs;
      // VERIFY
      assertUnit(lhs.dx == 11.0);
      assertUnit(lhs.dy == 22.0);
      // RHS should remain unchanged
      assertUnit(rhs.dx == 0.0);
      assertUnit(rhs.dy == 0.0);
   }  // TEARDOWN

   // operator+=: LHS (0,0), RHS (33,44)
   void test_plusEquals_lhsStationary()
   {  // SETUP
      Velocity lhs;
      Velocity rhs;
      lhs.dx = 0.0;  
      lhs.dy = 0.0;
      rhs.dx = 33.0; 
      rhs.dy = 44.0;
      // EXERCISE
      lhs += rhs;
      // VERIFY
      assertUnit(lhs.dx == 33.0);
      assertUnit(lhs.dy == 44.0);
      // RHS should remain unchanged
      assertUnit(rhs.dx == 33.0);
      assertUnit(rhs.dy == 44.0);
   }  // TEARDOWN

   // operator+=: LHS (11,22), RHS (33,44)
   void test_plusEquals_bothMove()
   {  // SETUP
      Velocity lhs;
      Velocity rhs;
      lhs.dx = 11.0; 
      lhs.dy = 22.0;
      rhs.dx = 33.0; 
      rhs.dy = 44.0;
      // EXERCISE
      lhs += rhs;
      // VERIFY
      assertUnit(lhs.dx == 44.0); // 11 + 33
      assertUnit(lhs.dy == 66.0); // 22 + 44
      // RHS should remain unchanged
      assertUnit(rhs.dx == 33.0);
      assertUnit(rhs.dy == 44.0);
   }  // TEARDOWN

   // multiply: v = 0.0, m = 0
   void test_multiply_stationary0()
   {  // SETUP
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // EXERCISE
      v *= 0.0;
      // VERIFY
      assertUnit(v.dx == 0.0);
      assertUnit(v.dy == 0.0);
   }  // TEARDOWN

   // multiply: v = 0.0, m = 1
   void test_multiply_stationary1()
   {  // SETUP
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // EXERCISE
      v *= 1.0;
      // VERIFY
      assertUnit(v.dx == 0.0);
      assertUnit(v.dy == 0.0);
   }  // TEARDOWN

   // multiply: v = 0.0, m = 5
   void test_multiply_stationary5()
   {  // SETUP
      Velocity v;
      v.dx = 0.0;
      v.dy = 0.0;
      // EXERCISE
      v *= 5.0;
      // VERIFY
      assertUnit(v.dx == 0.0);
      assertUnit(v.dy == 0.0);
   }  // TEARDOWN

   // multiply: v = 11,22, m = 0
   void test_multiply_moving0()
   {  // SETUP
      Velocity v;
      v.dx = 11.0;
      v.dy = 22.0;
      // EXERCISE
      v *= 0.0;
      // VERIFY
      assertUnit(v.dx == 0.0);
      assertUnit(v.dy == 0.0);
   }  // TEARDOWN

   // multiply: v = 11,22, m = 1
   void test_multiply_moving1()
   {  // SETUP
      Velocity v;
      v.dx = 11.0;
      v.dy = 22.0;
      // EXERCISE
      v *= 1.0;
      // VERIFY
      assertUnit(v.dx == 11.0);
      assertUnit(v.dy == 22.0);
   }  // TEARDOWN

   // multiply: v = 11,22, m = 5
   void test_multiply_moving5()
   {  // SETUP
      Velocity v;
      v.dx = 11.0;
      v.dy = 22.0;
      // EXERCISE
      v *= 5.0;
      // VERIFY
      assertUnit(v.dx == 55.0); // 11 * 5
      assertUnit(v.dy == 110.0); // 22 * 5
   }  // TEARDOWN

   // Velocity::set(angle, speed) tests
   static constexpr double EPS = 1e-7;
   const double PI = 3.14159265358979323846;

   // name=nospeed, angle=0, speed=0
   void test_set_nospeed()
   {  // SETUP
      Velocity v;
      v.dx = 9.9;   // sentinel
      v.dy = -9.9;  // sentinel
      // EXERCISE
      v.set(0.0, 0.0);
      // VERIFY (use assertEqualsTolerance for floating comparisons)
      assertEqualsTolerance(0.0, v.getDx(), EPS);
      assertEqualsTolerance(0.0, v.getDy(), EPS);
      assertEqualsTolerance(0.0, v.dx, EPS);
      assertEqualsTolerance(0.0, v.dy, EPS);
   }  // TEARDOWN

   // name=up, angle=0, speed=10
   void test_set_up()
   {  // SETUP
      Velocity v;
      v.dx = 1.1; v.dy = 1.1;
      // EXERCISE
      v.set(0.0, 10.0);
      // VERIFY: sin(0)=0 -> dx=0, cos(0)=1 -> dy=10
      assertEqualsTolerance(0.0, v.getDx(), EPS);
      assertEqualsTolerance(10.0, v.getDy(), EPS);
      assertEqualsTolerance(0.0, v.dx, EPS);
      assertEqualsTolerance(10.0, v.dy, EPS);
   }  // TEARDOWN

   // name=right, angle=pi/2, speed=10
   void test_set_right()
   {  // SETUP
      Velocity v;
      v.dx = -2.2; v.dy = -2.2;
      // EXERCISE
      v.set(PI / 2.0, 10.0);
      // VERIFY: sin(pi/2)=1 -> dx=10, cos(pi/2)=0 -> dy=0
      assertEqualsTolerance(10.0, v.getDx(), EPS);
      assertEqualsTolerance(0.0, v.getDy(), EPS);
      assertEqualsTolerance(10.0, v.dx, EPS);
      assertEqualsTolerance(0.0, v.dy, EPS);
   }  // TEARDOWN

   // name=down, angle=pi, speed=10
   void test_set_down()
   {  // SETUP
      Velocity v;
      v.dx = 3.3; v.dy = 3.3;
      // EXERCISE
      v.set(PI, 10.0);
      // VERIFY: sin(pi)=0 -> dx=0, cos(pi)=-1 -> dy=-10
      assertEqualsTolerance(0.0, v.getDx(), EPS);
      assertEqualsTolerance(-10.0, v.getDy(), EPS);
      assertEqualsTolerance(0.0, v.dx, EPS);
      assertEqualsTolerance(-10.0, v.dy, EPS);
   }  // TEARDOWN

   // name=left, angle=3pi/2, speed=10
   void test_set_left()
   {  // SETUP
      Velocity v;
      v.dx = 4.4; v.dy = -4.4;
      // EXERCISE
      v.set(3.0 * PI / 2.0, 10.0);
      // VERIFY: sin(3pi/2)=-1 -> dx=-10, cos(3pi/2)=0 -> dy=0
      assertEqualsTolerance(-10.0, v.getDx(), EPS);
      assertEqualsTolerance(0.0, v.getDy(), EPS);
      assertEqualsTolerance(-10.0, v.dx, EPS);
      assertEqualsTolerance(0.0, v.dy, EPS);
   }  // TEARDOWN

};