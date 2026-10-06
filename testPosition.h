/***********************************************************************
 * Header File:
 *    Test Position : Unit test the Position class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the unit tests for the Position class.
 ************************************************************************/
 
 #pragma once

 #define DEBUG

 #include "unitTest.h"
 #include "position.h"
 #include <sstream>
 #include <string>


 /***************************************************
 * TEST POSITION
 * Unit tests for the Position class. Tests set members explicitly
 ***************************************************/
class TestPosition : public UnitTest
{
public:
   void run()
   {
      reset();

      // add X,Y (existing tests)
      test_addX_zero(); 
      test_addX_nonzero();
      test_addY_zero();
      test_addY_nonzero();

      // basic constructors / getters / copy
      test_nonDefaultConstructor();
      test_copyConstructor();

      // equality / inequality
      test_equality_same();
      test_equality_xDifferent();
      test_equality_yDifferent();
      test_equality_bothDifferent();

      // setters
      test_setters();

      // add with Velocity and operator +=
      test_add_zero();
      test_add_x();
      test_add_y();
      test_add_xy();

      // assignment operator
      test_assignment_operator();

      // stream operators
      test_stream_insertion();
      test_stream_extraction();

      // free functions
      test_minimumDistance_parallelUp();
      test_minimumDistance_parallelRight();
      test_minimumDistance_Cross();

      report("Position");
   }

   // add X when at origin
   void test_addX_zero()
   {  // SETUP
      Position p;
      p.x = 0.0;
      p.y = 33.33;
      // EXERCISE
      p.addX(2.0);
      // VERIFY
      assertUnit(p.x == 2.0);
      assertUnit(p.y == 33.33);
   }  // TEARDOWN

   // add X at a position
   void test_addX_nonzero()
   {  // SETUP
      Position p;
      p.x = 11.11;
      p.y = 33.33;
      // EXERCISE
      p.addX(2.0);
      // VERIFY
      assertUnit(p.x == 13.11);
      assertUnit(p.y == 33.33);
   }  // TEARDOWN

   // add Y when at origin
   void test_addY_zero()
   {  // SETUP
      Position p;
      p.x = 33.33;
      p.y = 0.0;
      // EXERCISE
      p.addY(3.0);
      // VERIFY
      assertUnit(p.x == 33.33);
      assertUnit(p.y == 3.0);
   }  // TEARDOWN

   // add Y at a position
   void test_addY_nonzero()
   {  // SETUP
      Position p;
      p.x = 33.33;
      p.y = 11.11;
      // EXERCISE
      p.addY(2.0);
      // VERIFY
      assertUnit(p.x == 33.33);
      assertUnit(p.y == 13.11);
   }  // TEARDOWN

   // constructor with parameters and getters
   void test_nonDefaultConstructor()
   {  // SETUP
      // EXERCISE
      Position p(1.1, 2.2);
      // VERIFY
      assertUnit(p.x == 1.1);
      assertUnit(p.y == 2.2);
   }  // TEARDOWN

   // copy constructor
   void test_copyConstructor()
   {  // SETUP
      Position pSrc;
      pSrc.x = 3.3;
      pSrc.y = 4.4;
      // EXERCISE
      Position sDes(pSrc);
      // VERIFY
      assertUnit(sDes.x == 3.3);
      assertUnit(sDes.y == 4.4);
      assertUnit(pSrc.x == 3.3);
      assertUnit(pSrc.y == 4.4);
   }  // TEARDOWN

   // operator== and operator!= - same
   void test_equality_same()
   {  // SETUP
      Position pLHS;
      Position pRHS;
      pLHS.x = 1.1;
      pLHS.y = 2.2;
      pRHS.x = 1.1;
      pRHS.y = 2.2;
      bool isSame = false;
      // EXERCISE
      isSame = (pLHS == pRHS);
      // VERIFY
      assertUnit(isSame);        
      assertUnit(pLHS.x == 1.1);
      assertUnit(pLHS.y == 2.2);
      assertUnit(pRHS.x == 1.1);
      assertUnit(pRHS.y == 2.2);
   }  // TEARDOWN

   // operator== and operator!= - x different
   void test_equality_xDifferent()
   {  // SETUP
      Position pLHS;
      Position pRHS;
      pLHS.x = 1.1;
      pLHS.y = 2.2;
      pRHS.x = 9.9;   // different x
      pRHS.y = 2.2;   // same y
      bool isSame = true;
      // EXERCISE
      isSame = (pLHS == pRHS);
      // VERIFY
      assertUnit(!isSame);
      assertUnit(pLHS.x == 1.1);
      assertUnit(pLHS.y == 2.2);
      assertUnit(pRHS.x == 9.9);
      assertUnit(pRHS.y == 2.2);
   }  // TEARDOWN

   // operator== and operator!= - y different
   void test_equality_yDifferent()
   {  // SETUP
      Position pLHS;
      Position pRHS;
      pLHS.x = 1.1;
      pLHS.y = 2.2;
      pRHS.x = 1.1;   // same x
      pRHS.y = 8.8;   // different y
      bool isSame = true;
      // EXERCISE
      isSame = (pLHS == pRHS);
      // VERIFY
      assertUnit(!isSame);
      assertUnit(pLHS.x == 1.1);
      assertUnit(pLHS.y == 2.2);
      assertUnit(pRHS.x == 1.1);
      assertUnit(pRHS.y == 8.8);
   }  // TEARDOWN

   // operator== and operator!= - both different
   void test_equality_bothDifferent()
   {  // SETUP
      Position pLHS;
      Position pRHS;
      pLHS.x = 1.1;
      pLHS.y = 2.2;
      pRHS.x = 7.7;   // different x
      pRHS.y = 8.8;   // different y
      bool isSame = true;
      // EXERCISE
      isSame = (pLHS == pRHS);
      // VERIFY
      assertUnit(!isSame);
      assertUnit(pLHS.x == 1.1);
      assertUnit(pLHS.y == 2.2);
      assertUnit(pRHS.x == 7.7);
      assertUnit(pRHS.y == 8.8);
   }  // TEARDOWN

   // setX / setY
   void test_setters()
   {  // SETUP
      Position p;
      p.x = 0.0; 
      p.y = 0.0;
      // EXERCISE
      p.setX(9.9);
      p.setY(8.8);
      // VERIFY
      assertUnit(p.x == 9.9);
      assertUnit(p.y == 8.8);
   }  // TEARDOWN

   // add(const Velocity&) and operator +=
   void test_add_zero()
   {  // SETUP
      Position p;
      p.x = 1.0; 
      p.y = 1.0;
      Velocity0 v;
      // EXERCISE
      p.add(v);
      // VERIFY
      assertUnit(p.x == 1.0);
      assertUnit(p.y == 1.0);
   }  // TEARDOWN

  // add(const Velocity&) and operator +=
   void test_add_x()
   {  // SETUP
      Position p;
      p.x = 1.0;
      p.y = 1.0;
      VelocityR v;
      // EXERCISE
      p.add(v);
      // VERIFY
      assertUnit(p.x == 12.11);
      assertUnit(p.y == 1.0);
   }  // TEARDOWN

   // add(const Velocity&) and operator +=
   void test_add_y()
   {  // SETUP
      Position p;
      p.x = 1.0;
      p.y = 1.0;
      VelocityU v;
      // EXERCISE
      p.add(v);
      // VERIFY
      assertUnit(p.x == 1.0);
      assertUnit(p.y == 23.22);
   }  // TEARDOWN

     // add(const Velocity&) and operator +=
   void test_add_xy()
   {  // SETUP
      Position p;
      p.x = 1.0;
      p.y = 1.0;
      VelocityRU v;
      // EXERCISE
      p.add(v);
      // VERIFY
      assertUnit(p.x == 12.11);
      assertUnit(p.y == 23.22);
   }  // TEARDOWN

   // assignment operator
   void test_assignment_operator()
   {  // SETUP
      Position a;
      a.x = 5.5; 
      a.y = 6.6;
      Position b;
      b.x = 0.0; 
      b.y = 0.0;
      // EXERCISE
      b = a;
      // VERIFY
      assertUnit(a.x == 5.5);
      assertUnit(a.y == 6.6);
      assertUnit(b.x == 5.5);
      assertUnit(b.y == 6.6);
   }  // TEARDOWN

   // operator<< basic check (formatting presence)
   void test_stream_insertion()
   {  // SETUP
      Position p;
      p.x = 1.23;
      p.y = 4.56;
      std::ostringstream out;
      // EXERCISE
      out << p;
      // VERIFY
      std::string s = out.str();
      assertUnit(s == "(1.23, 4.56)");
      assertUnit(p.x == 1.23);
      assertUnit(p.y == 4.56);
   }  // TEARDOWN

   // operator>> extraction
   void test_stream_extraction()
   {  // SETUP
      Position p;
      p.x = 99.9;
      p.y = 99.9;
      std::istringstream in("7.7 8.8");
      // EXERCISE
      in >> p;
      // VERIFY
      assertUnit(p.getX() == 7.7);
      assertUnit(p.getY() == 8.8);
      assertUnit(p.x == 7.7);
      assertUnit(p.y == 8.8);
   }  // TEARDOWN

   // minimumDistance: two objects moving directly toward each other should have zero minimum distance
   void test_minimumDistance_parallelUp()
   {  // SETUP
      Position p1;
      p1.x = 0.0; 
      p1.y = 0.0;
      VelocityU1 v1;
      Position p2;
      p2.x = 10.0; 
      p2.y = 0.0;
      VelocityU1 v2;
      // EXERCISE
      double d = minimumDistance(p1, v1, p2, v2);
      // VERIFY
      assertUnit(d == 10.0);
      assertUnit(p1.x == 0.0); 
      assertUnit(p1.y == 0.0);
      assertUnit(p2.x == 10.0); 
      assertUnit(p2.y == 0.0);
   }  // TEARDOWN

   // minimumDistance: two objects moving directly toward each other should have zero minimum distance
   void test_minimumDistance_parallelRight()
   {  // SETUP
      Position p1;
      p1.x = 10.0;
      p1.y = 0.0;
      VelocityR1 v1;
      Position p2;
      p2.x = 0.0;
      p2.y = 0.0;
      VelocityR1 v2;
      // EXERCISE
      double d = minimumDistance(p1, v1, p2, v2);
      // VERIFY
      assertUnit(d == 10.0);
      assertUnit(p1.x == 10.0);
      assertUnit(p1.y == 0.0);
      assertUnit(p2.x == 0.0);
      assertUnit(p2.y == 0.0);
   }  // TEARDOWN

   // minimumDistance: two objects moving directly toward each other should have zero minimum distance
   void test_minimumDistance_Cross()
   {  // SETUP
      Position p1;
      p1.x = 0.0;
      p1.y = 0.0;
      VelocityR4U4 v1;
      Position p2;
      p2.x = 0.0;
      p2.y = 4.0;
      VelocityR4D4 v2;
      // EXERCISE
      double d = minimumDistance(p1, v1, p2, v2);
      // VERIFY
      assertUnit(d == 0.0);
      assertUnit(p1.x == 0.0);
      assertUnit(p1.y == 0.0);
      assertUnit(p2.x == 0.0);
      assertUnit(p2.y == 4.0);
   }  // TEARDOWN

};