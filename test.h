/***********************************************************************
 * Header File:
 *    Test : The test class - which runs the test runner
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The function runs all the unit tests
 ************************************************************************/

#pragma once

#include "testPosition.h"
#include "testVelocity.h"
#include "testGun.h"
#include "testEffect.h"
#include "testBullet.h"
#include "testBird.h"
#include "testPoints.h"
#include "testSkeet.h"
#include "random.h"

 /**********************
  * TEST RUNNER
  * The test harness which runs all the unit tests
  **********************/
inline void testRunner()
{
   // run the unit tests
   TestPosition().run();
   TestVelocity().run();
   TestGun().run();
   TestEffect().run();
   TestBullet().run();
   TestBird().run();
   TestPoints().run();
   TestSkeet().run();

   // reset the random number generators
   randomInt(0, 1, true);
   randomDouble(1.1, 2.2, true);
}