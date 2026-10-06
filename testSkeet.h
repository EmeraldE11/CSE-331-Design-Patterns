/***********************************************************************
 * Header File:
 *    Test Skeet : Unit test the Skeet class
 * Author:
 *    Br. Helfrich   
 * Summary:
 *    Unit test scaffold for the Skeet class. Currently contains only the
 *    `run()` function which resets and reports results. Add tests here
 *    modeled after other test classes.
 ************************************************************************/

#pragma once

#define DEBUG

#include "unitTest.h"
#include "skeet.h"
#include "bird.h"
#include <string>

/**********************
 * TEST SKEET
 * Unit test the Skeet class
 **********************/ 
class TestSkeet : public UnitTest
{
public:
   void run()
   {
      reset();

      test_spawn_level1Empty();
      test_spawn_level2Empty();
      test_spawn_level3Empty();
      test_spawn_level4Empty();

      test_animate_level1Empty();         
      test_animate_level2Empty();
      test_animate_level3Empty();
      test_animate_level4Empty();
      test_animate_level1Mixed();
      test_animate_level2Mixed();
      test_animate_level3Mixed();
      test_animate_level4Mixed();
      test_animate_level4Bullets();

      test_interact_nothing();
      test_interact_upEmpty();
      test_interact_upBullets();
      test_interact_spaceBullets();
      test_interact_mBullets();
      test_interact_bBullets();
      test_interact_keysBullets();

      report("Skeet");
   }

private:

   void test_spawn_level1Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 800.0;
      dimensions.y = 600.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions are known for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 1 (spawn logic for level 1)
      s.time.levelNumber = 1;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // Preserve any other state we might check
      bool oldBullseye = s.bullseye;
      double oldDimX = s.dimensions.x;
      double oldDimY = s.dimensions.y;

      // EXERCISE
      s.spawn();

      // VERIFY
      // spawn() should add two Standard birds under deterministic random (min)
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());

      assertUnit(2 == (int)s.birds.size());
      if (2 == s.birds.size())
      {
         auto it = s.birds.begin();
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);

         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);
      }

      // spawn() should not modify the time framesLeft
      assertEquals(FRAMES_PER_SECOND * 15, s.time.framesLeft);

      // Dimensions and bullseye remain unchanged
      assertEqualsTolerance(oldDimX, s.dimensions.x, tolerance);
      assertEqualsTolerance(oldDimY, s.dimensions.y, tolerance);
      assertEquals(oldBullseye, s.bullseye);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_spawn_level2Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 1024.0;
      dimensions.y = 768.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 2 (spawn logic for level 2)
      s.time.levelNumber = 2;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // EXERCISE
      s.spawn();

      // VERIFY
      // Deterministic random -> all spawn conditions true:
      //   1) initial Standard (size=25, points=12)
      //   2) periodic Standard (size=25, points=12)
      //   3) periodic Sinker (size=25, default points)
      assertUnit(3 == (int)s.birds.size());
      if (3 == s.birds.size())
      {
         auto it = s.birds.begin();

         // first Standard
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         assertEquals(12, (*it)->points);

         // second Standard
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         assertEquals(12, (*it)->points);

         // Sinker
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         // level2 used default Sinker(points) -> default in bird.h is 20
         assertEquals(20, (*it)->points);
      }

      // spawn() should not change time.framesLeft
      assertEquals(FRAMES_PER_SECOND * 15, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();


   }

   void test_spawn_level3Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 640.0;
      dimensions.y = 480.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 3 (spawn logic for level 3)
      s.time.levelNumber = 3;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // EXERCISE
      s.spawn();

      // VERIFY
      // Deterministic random -> all spawn conditions true:
      //   1) Standard(size=20, points=15)
      //   2) Standard(size=20, points=15)
      //   3) Sinker(size=20, points=22)
      //   4) Floater(size=20, default points 15)
      assertUnit(4 == (int)s.birds.size());
      if (4 == s.birds.size())
      {
         auto it = s.birds.begin();

         // Standard #1
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);

         // Standard #2
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);

         // Sinker (explicit points 22 in spawn)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(22, (*it)->points);

         // Floater (default points)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);
      }

      // spawn() should not change time.framesLeft
      assertEquals(FRAMES_PER_SECOND * 15, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();


   }

   void test_spawn_level4Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 4 (spawn logic for level 4)
      s.time.levelNumber = 4;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // EXERCISE
      s.spawn();

      // VERIFY
      // Deterministic random -> all spawn conditions true:
      //   1) Standard(size=15, points=18)
      //   2) Standard(size=15, points=18)
      //   3) Sinker(size=15, points=25)
      //   4) Floater(size=15, points=25)
      //   5) Crazy(size=15, default points 30)
      assertUnit(5 == (int)s.birds.size());
      if (5 == s.birds.size())
      {
         auto it = s.birds.begin();

         // Standard #1
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(18, (*it)->points);

         // Standard #2
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(18, (*it)->points);

         // Sinker (explicit points 25)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(25, (*it)->points);

         // Floater (explicit points 25)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(25, (*it)->points);

         // Crazy (default points 30)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Crazy));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(30, (*it)->points);
      }

      // spawn() should not change time.framesLeft
      assertEquals(FRAMES_PER_SECOND * 15, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();


   }

   void test_animate_level1Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 1000.0;
      dimensions.y = 2000.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Explicitly set the gun
      s.gun.angle = 0.12345;
      s.gun.pt.x = 50.0;
      s.gun.pt.y = 5.0;

      s.time.levelNumber = 1;
      s.time.framesLeft = FRAMES_PER_SECOND * 15; // the reset-like full frames -> playing

      s.score.points = 999;
      s.hitRatio.numKilled = 77;
      s.hitRatio.numMissed = 33;

      // Explicitly set the dimensions and bullseye
      s.dimensions.x = 800.0;
      s.dimensions.y = 600.0;
      s.bullseye = true;

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = s.dimensions;

      // EXERCISE
      s.animate();

      // VERIFY
      // Most things are empty, but spawn() should have run and added birds for level 1
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());

      // Should be two standard birds created in Level 1 (deterministic random returns min)
      assertUnit(2 == (int)s.birds.size());
      if (2 == s.birds.size())
      {
         auto it = s.birds.begin();
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);

         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);
      }

      // Time should have advanced by one frame (framesLeft decremented)
      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // Other state should remain unchanged
      assertEqualsTolerance(0.12345, s.gun.angle, tolerance);
      assertEqualsTolerance(50.0, s.gun.pt.x, tolerance);
      assertEqualsTolerance(5.0, s.gun.pt.y, tolerance);

      assertEquals(999, s.score.points);
      assertEquals(77, s.hitRatio.numKilled);
      assertEquals(33, s.hitRatio.numMissed);

      assertEqualsTolerance(800.0, s.dimensions.x, tolerance);
      assertEqualsTolerance(600.0, s.dimensions.y, tolerance);
      assertEquals(true, s.bullseye);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();

      s.birds.clear();
   }

   void test_animate_level2Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 1024.0;
      dimensions.y = 768.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Explicitly set the gun and UI-independent state to detect unintended changes
      s.gun.angle = 0.5;
      s.gun.pt.x = 10.0;
      s.gun.pt.y = 20.0;
      s.score.points = 42;
      s.hitRatio.numKilled = 2;
      s.hitRatio.numMissed = 1;
      s.dimensions = dimensions;
      s.bullseye = false;

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 2 (spawn logic for level 2)
      s.time.levelNumber = 2;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // EXERCISE
      s.animate();

      // VERIFY
      // Deterministic random -> level2 spawn conditions produce 3 birds:
      //  Standard, Standard, Sinker
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());

      assertUnit(3 == (int)s.birds.size());
      if (3 == s.birds.size())
      {
         auto it = s.birds.begin();

         // Standard #1
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         assertEquals(12, (*it)->points);

         // Standard #2
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         assertEquals(12, (*it)->points);

         // Sinker
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         // default Sinker points (bird.h default is 20)
         assertEquals(20, (*it)->points);
      }

      // Time should have advanced by one frame (framesLeft decremented)
      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // Other state should remain unchanged
      assertEqualsTolerance(0.5, s.gun.angle, tolerance);
      assertEqualsTolerance(10.0, s.gun.pt.x, tolerance);
      assertEqualsTolerance(20.0, s.gun.pt.y, tolerance);
      assertEquals(42, s.score.points);
      assertEquals(2, s.hitRatio.numKilled);
      assertEquals(1, s.hitRatio.numMissed);
      assertEqualsTolerance(dimensions.x, s.dimensions.x, tolerance);
      assertEqualsTolerance(dimensions.y, s.dimensions.y, tolerance);
      assertEquals(false, s.bullseye);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();


   }

   void test_animate_level3Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 640.0;
      dimensions.y = 480.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Explicitly set other state
      s.gun.angle = -0.25;
      s.gun.pt.x = 100.0;
      s.gun.pt.y = 200.0;
      s.score.points = 7;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = true;

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 3 (spawn logic for level 3)
      s.time.levelNumber = 3;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // EXERCISE
      s.animate();

      // VERIFY
      // Deterministic random -> level3 spawn conditions produce 4 birds:
      //  Standard, Standard, Sinker(points=22), Floater
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());

      assertUnit(4 == (int)s.birds.size());
      if (4 == s.birds.size())
      {
         auto it = s.birds.begin();

         // Standard #1
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);

         // Standard #2
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);

         // Sinker (points explicitly 22 in spawn)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(22, (*it)->points);

         // Floater
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);
      }

      // Time should have advanced by one frame (framesLeft decremented)
      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // Other state should remain unchanged
      assertEqualsTolerance(-0.25, s.gun.angle, tolerance);
      assertEqualsTolerance(100.0, s.gun.pt.x, tolerance);
      assertEqualsTolerance(200.0, s.gun.pt.y, tolerance);
      assertEquals(7, s.score.points);
      assertEquals(0, s.hitRatio.numKilled);
      assertEquals(0, s.hitRatio.numMissed);
      assertEqualsTolerance(dimensions.x, s.dimensions.x, tolerance);
      assertEqualsTolerance(dimensions.y, s.dimensions.y, tolerance);
      assertEquals(true, s.bullseye);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();


   }

   void test_animate_level4Empty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Explicitly set other state
      s.gun.angle = 1.234;
      s.gun.pt.x = 5.0;
      s.gun.pt.y = 6.0;
      s.score.points = 1234;
      s.hitRatio.numKilled = 10;
      s.hitRatio.numMissed = 5;
      s.dimensions = dimensions;
      s.bullseye = false;

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Set the time to level 4 (spawn logic for level 4)
      s.time.levelNumber = 4;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // EXERCISE
      s.animate();

      // VERIFY
      // Deterministic random -> level4 spawn conditions produce 5 birds:
      //  Standard, Standard, Sinker(points=25), Floater(points=25), Crazy(points=30)
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());

      assertUnit(5 == (int)s.birds.size());
      if (5 == s.birds.size())
      {
         auto it = s.birds.begin();

         // Standard #1
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(18, (*it)->points);

         // Standard #2
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(18, (*it)->points);

         // Sinker (explicit points 25)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(25, (*it)->points);

         // Floater (explicit points 25)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(25, (*it)->points);

         // Crazy (default points 30)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Crazy));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(30, (*it)->points);
      }

      // spawn() should not change time.framesLeft
      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();


   }

   void test_animate_level1Mixed()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 800.0;
      dimensions.y = 600.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Create two Standard birds and place them in the game
      Standard* standard1 = new Standard(30.0); // will be adjusted below
      Standard* standard2 = new Standard(30.0);

      // Explicitly set positions and velocities (direct member access)
      standard1->pt.x = 50.0;
      standard1->pt.y = 30.0;
      standard1->v.dx = 5.0;
      standard1->v.dy = 2.0;
      standard1->dead = false;
      standard1->radius = 30.0;
      standard1->points = 10;

      standard2->pt.x = 40.0;
      standard2->pt.y = 70.0;
      standard2->v.dx = 3.0;
      standard2->v.dy = -4.0;
      standard2->dead = false;
      standard2->radius = 30.0;
      standard2->points = 10;

      // Add to skeet
      s.birds.push_back(standard1);
      s.birds.push_back(standard2);

      // Explicitly set other state that should remain unchanged
      s.gun.angle = 0.75;
      s.gun.pt.x = 100.0;
      s.gun.pt.y = 10.0;
      s.score.points = 5;
      s.hitRatio.numKilled = 1;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      // Set time to level 1 and playing
      s.time.levelNumber = 1;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // Save expected positions after a Standard::advance()
      // advance() does: v *= 0.995; pt.add(v);
      double standard1Dx = 5.0 * 0.995;     // 4.975
      double standard1Dy = 2.0 * 0.995;     // 1.99

      double standard2Dx = 3.0 * 0.995;     // 2.985
      double standard2Dy = -4.0 * 0.995;    // -3.98

      // EXERCISE
      s.animate();

      // VERIFY
      // One new Standard should have been spawned (periodic spawn), so total 3 birds
      assertUnit(3 == (int)s.birds.size());
      if (3 == s.birds.size())
      {
         auto it = s.birds.begin();

         // First bird: our b1 advanced
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(standard1Dx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(standard1Dy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(50.0 + standard1Dx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(30.0 + standard1Dy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);

         // Second bird: our b2 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(standard2Dx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(standard2Dy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(40.0 + standard2Dx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(70.0 + standard2Dy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);

         // Third bird: spawned Standard (deterministic)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(30.0, (*it)->radius, tolerance);
         assertEquals(10, (*it)->points);
      }

      // Time decremented
      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // Other state unchanged
      assertEqualsTolerance(0.75, s.gun.angle, tolerance);
      assertEqualsTolerance(100.0, s.gun.pt.x, tolerance);
      assertEqualsTolerance(10.0, s.gun.pt.y, tolerance);
      assertEquals(5, s.score.points);
      assertEquals(1, s.hitRatio.numKilled);
      assertEquals(0, s.hitRatio.numMissed);
      assertEqualsTolerance(dimensions.x, s.dimensions.x, tolerance);
      assertEqualsTolerance(dimensions.y, s.dimensions.y, tolerance);
      assertEquals(false, s.bullseye);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();

   }

   void test_animate_level2Mixed()
   {
      // SETUP: 2 Standards + 2 Sinkers present initially
      Position dimensions;
      dimensions.x = 800.0;
      dimensions.y = 600.0;
      Skeet s(dimensions);

      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      Bird::dimensions = dimensions;

      // create originals
      Standard* standard = new Standard(30.0);
      Sinker* sinker = new Sinker(25.0);

      // set explicit positions/velocities and internals
      standard->pt.x = 50.0;
      standard->pt.y = 30.0;
      standard->v.dx = 5.0;
      standard->v.dy = 2.0;
      standard->dead = false;
      standard->radius = 301.0;
      standard->points = 31;

      sinker->pt.x = 60.0;
      sinker->pt.y = 80.0;
      sinker->v.dx = 2.0;
      sinker->v.dy = -1.0;
      sinker->dead = false;
      sinker->radius = 303.0;
      sinker->points = 33;

      s.birds.push_back(standard);
      s.birds.push_back(sinker);

      // other state
      s.gun.angle = 0.1;
      s.gun.pt.x = 1.0;
      s.gun.pt.y = 2.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      // set level 1 playing
      s.time.levelNumber = 2;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // expected positions after advance:
      // Standards: v *= 0.995, then pt += v
      double standardDx = 5.0 * 0.995;
      double standardDy = 2.0 * 0.995;

      // Sinkers: v.addDy(-0.07) then pt += v
      double sinkerDx = 2.0;
      double sinkerDy = -1.0 - 0.07;

      // EXERCISE
      s.animate();

      // VERIFY
      assertUnit(4 == (int)s.birds.size());

      if (4 == s.birds.size())
      {
         auto it = s.birds.begin();

         // st1 advanced
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(standardDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(standardDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(50.0 + standardDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(30.0 + standardDy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(301.0, (*it)->radius, tolerance);
         assertEquals(31, (*it)->points);

         // sk1 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(sinkerDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(sinkerDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(60.0 + sinkerDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(80.0 + sinkerDy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(303.0, (*it)->radius, tolerance);
         assertEquals(33, (*it)->points);

         // spawned Standard
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         assertEquals(12, (*it)->points);

         // spawned Sinker
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertUnit((*it)->dead == false);
         assertEqualsTolerance(25.0, (*it)->radius, tolerance);
         assertEquals(20, (*it)->points);

      }

      // time decremented
      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_animate_level3Mixed()
   {
      // SETUP: 2 Standards + 2 Sinkers present initially for level 3
      Position dimensions;
      dimensions.x = 640.0;
      dimensions.y = 480.0;
      Skeet s(dimensions);

      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      Bird::dimensions = dimensions;

      // create originals
      Standard* standard = new Standard(20.0);
      Sinker* sinker = new Sinker(20.0);
      Floater* floater = new Floater(20.0);

      // explicit positions/velocities and internals for the first three
      standard->pt.x = 50.0;
      standard->pt.y = 30.0;
      standard->v.dx = 5.0;
      standard->v.dy = 2.0;
      standard->radius = 101;
      standard->points = 40;
      standard->dead = false;

      sinker->pt.x = 60.0;
      sinker->pt.y = 80.0;
      sinker->v.dx = 2.0;
      sinker->v.dy = -1.0;
      sinker->dead = false;
      sinker->radius = 102;
      sinker->points = 41;

      floater->pt.x = 20.0;
      floater->pt.y = 40.0;
      floater->v.dx = 1.0;
      floater->v.dy = 3.0;
      floater->dead = false;
      floater->radius = 103;
      floater->points = 42;

      s.birds.push_back(standard);
      s.birds.push_back(sinker);
      s.birds.push_back(floater);

      s.gun.angle = 0.2;
      s.gun.pt.x = 2.0;
      s.gun.pt.y = 3.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = true;

      s.time.levelNumber = 3;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // compute expected post-advance positions and velocities for the three initial birds
      // Standard: v *= 0.995; pt += v;
      double standardDx = 5.0 * 0.995;
      double standardDy = 2.0 * 0.995;
      // Sinker: v.addDy(-0.07); pt += v;
      double sinkerDx = 2.0;
      double sinkerDy = -1.0 - 0.07;
      // Floater: v *= 0.990; pt += v; then v.addDy(0.05)
      double floaterDx = 1.0 * 0.99;
      double floaterDy = 3.0 * 0.99; // used for position

      // EXERCISE
      s.animate();

      // VERIFY
      // level 3 non-empty -> 3 periodic spawns (Standard, Standard, Sinker, Floater)
      // initial 3 + 3 = 6
      assertUnit(6 == (int)s.birds.size());

      if (6 == s.birds.size())
      {
         auto it = s.birds.begin();

         // st1 advanced
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(50.0 + standardDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(30.0 + standardDy, (*it)->pt.y, tolerance);
         // verify velocity stored on the object after advance
         assertEqualsTolerance(standardDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(standardDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(101, (*it)->radius, tolerance);
         assertEquals(40, (*it)->points);

         // sk1 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(60.0 + sinkerDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(80.0 + sinkerDy, (*it)->pt.y, tolerance);
         // verify sinker velocity stored on the object after advance
         assertEqualsTolerance(sinkerDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(sinkerDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(102, (*it)->radius, tolerance);
         assertEquals(41, (*it)->points);

         // fl1 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         // verify floater position after advance
         assertEqualsTolerance(20.0 + floaterDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(40.0 + floaterDy, (*it)->pt.y, tolerance);
         // verify floater final stored velocity (dy includes +0.05)
         assertEqualsTolerance(floaterDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(floaterDy + 0.05, (*it)->v.dy, tolerance);
         assertEqualsTolerance(103, (*it)->radius, tolerance);
         assertEquals(42, (*it)->points);

         // spawned Standard (size=20)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);

         // spawned Sinker (size=20, points=22)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(22, (*it)->points);

         // spawned Floater #2 (size=20)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         assertEqualsTolerance(20.0, (*it)->radius, tolerance);
         assertEquals(15, (*it)->points);

      }

      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_animate_level4Mixed()
   {
      // SETUP: 1 Standard, 1 Sinker, 1 Floater, 1 Crazy initially (4 total)
      // After animate we expect 8 total (initial 4 + 4 spawned)
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      Bird::dimensions = dimensions;

      // create originals
      Standard* standard = new Standard(15.0);
      Sinker* sinker = new Sinker(15.0);
      Floater* floater = new Floater(15.0);
      Crazy* crazy = new Crazy(15.0);

      // explicit positions/velocities and internals for the initial four
      standard->pt.x = 50.0;
      standard->pt.y = 30.0;
      standard->v.dx = 5.0;
      standard->v.dy = 2.0;
      standard->dead = false;
      standard->radius = 15.1;
      standard->points = 60;

      sinker->pt.x = 60.0;
      sinker->pt.y = 80.0;
      sinker->v.dx = 2.0;
      sinker->v.dy = -1.0;
      sinker->dead = false;
      sinker->radius = 15.2;
      sinker->points = 61;

      floater->pt.x = 20.0;
      floater->pt.y = 40.0;
      floater->v.dx = 1.0;
      floater->v.dy = 3.0;
      floater->dead = false;
      floater->radius = 15.3;
      floater->points = 62;

      crazy->pt.x = 25.0;
      crazy->pt.y = 50.0;
      crazy->v.dx = 4.0;
      crazy->v.dy = 1.0;
      crazy->dead = false;
      crazy->radius = 15.4;
      crazy->points = 63;

      s.birds.push_back(standard);
      s.birds.push_back(sinker);
      s.birds.push_back(floater);
      s.birds.push_back(crazy);

      s.gun.angle = 0.3;
      s.gun.pt.x = 3.0;
      s.gun.pt.y = 4.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      s.time.levelNumber = 4;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // Compute initial expected velocities and positions for the four initial birds
      // Standard: v *= 0.995; pt += v;
      double standardDx = 5.0 * 0.995; // 4.975
      double standardDy = 2.0 * 0.995; // 1.99
      // Sinker: v.addDy(-0.07); pt += v;
      double sinkerDx = 2.0;             // 2.0
      double sinkerDy = -1.0 - 0.07;      // -1.07
      // Floater: v *= 0.990; pt += v; then v.addDy(0.05)
      double floaterDx = 1.0 * 0.99;     // 0.99
      double floaterDy = 3.0 * 0.99;     // 2.97
      // new v = v + (-1.5, -1.5); pt += new v
      double crazyDx = 4.0 + (-1.5);   // 2.5
      double crazyDy = 1.0 + (-1.5);   // -0.5

      // EXERCISE
      s.animate();

      // VERIFY
      // level 4 non-empty -> 4 periodic spawns appended (Standard, Sinker, Floater, Crazy)
      // initial 4 + 4 = 8
      assertUnit(8 == (int)s.birds.size());

      if (8 == s.birds.size())
      {
         auto it = s.birds.begin();

         // st1 advanced
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(50.0 + standardDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(30.0 + standardDy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(standardDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(standardDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(15.1, (*it)->radius, tolerance);
         assertEquals(60, (*it)->points);

         // sk1 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(60.0 + sinkerDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(80.0 + sinkerDy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(sinkerDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(sinkerDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(15.2, (*it)->radius, tolerance);
         assertEquals(61, (*it)->points);

         // fl1 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         // verify floater position after advance
         assertEqualsTolerance(20.0 + floaterDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(40.0 + floaterDy, (*it)->pt.y, tolerance);
         // verify floater final stored velocity (dy includes +0.05)
         assertEqualsTolerance(floaterDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(floaterDy + 0.05, (*it)->v.dy, tolerance);
         assertEqualsTolerance(15.3, (*it)->radius, tolerance);
         assertEquals(62, (*it)->points);

         // cr1 advanced
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Crazy));
         assertEqualsTolerance(25.0 + crazyDx, (*it)->pt.x, tolerance);
         assertEqualsTolerance(50.0 + crazyDy, (*it)->pt.y, tolerance);
         assertEqualsTolerance(crazyDx, (*it)->v.dx, tolerance);
         assertEqualsTolerance(crazyDy, (*it)->v.dy, tolerance);
         assertEqualsTolerance(15.4, (*it)->radius, tolerance);
         assertEquals(63, (*it)->points);

         // spawned Standard (size=15, points=18)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Standard));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(18, (*it)->points);

         // spawned Sinker (size=15, points=25)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Sinker));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(25, (*it)->points);

         // spawned Floater (size=15, points=25)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Floater));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(25, (*it)->points);

         // spawned Crazy (size=15, points=30)
         ++it;
         assert(it != s.birds.end());
         assertUnit(typeid(*(*it)) == typeid(Crazy));
         assertEqualsTolerance(15.0, (*it)->radius, tolerance);
         assertEquals(30, (*it)->points);
      }

      assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

      // TEARDOWN
      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_animate_level4Bullets()
   {
      // SETUP
      Position dimensionsOriginal = Bullet::dimensions;
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bullet static dimensions for deterministic construction
      Bullet::dimensions = dimensions;

      // Create one of each bullet kind using deterministic angles
      Pellet* pellet = new Pellet(0.0);
      Bomb*   bomb   = new Bomb(0.5);
      Missile* missile = new Missile(0.2);

      // Add to skeet
      s.bullets.push_back(pellet);
      s.bullets.push_back(bomb);
      s.bullets.push_back(missile);

      // Explicitly set other state that should remain unchanged except gun.angle
      s.gun.angle = 0.30; // initial
      s.gun.pt.x = 150.0;
      s.gun.pt.y = 75.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      s.time.levelNumber = 4;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // Compute initial expected velocities/positions (constructor behavior)
      double pelletDx0   = -15.0 * cos(0.0);
      double pelletDy0   =  15.0 * sin(0.0);
      double pelletStartX = dimensions.x - 1.0;
      double pelletStartY = 1.0;

      double bombDx0     = -10.0 * cos(0.5);
      double bombDy0     =  10.0 * sin(0.5);
      double bombStartX  = dimensions.x - 1.0;
      double bombStartY  = 1.0;

      double missileDx0  = -10.0 * cos(0.2);
      double missileDy0  =  10.0 * sin(0.2);
      double missileStartX = dimensions.x - 1.0;
      double missileStartY = 1.0;

      // Compute expected missile velocity after a single 'up' input (v.turn(0.04))
      double missileSpeed = sqrt(missileDx0 * missileDx0 + missileDy0 * missileDy0);
      double missileAngle0 = atan2(missileDx0, missileDy0); // velocity.Angle uses (dx,dy)
      double missileAngle1 = missileAngle0 + 0.04;
      double missileDx1 = sin(missileAngle1) * missileSpeed;
      double missileDy1 = cos(missileAngle1) * missileSpeed;

      // Preserve UserInput static state
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;

      // Prevent UserInput::initialize() and set 'up' pressed
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 1;    // press UP
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = false;
      UserInput::isBPress = false;
      UserInput::isMPress = false;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;

      UserInput ui;

      double oldGunAngle = s.gun.angle;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      // No new bullets should be created by interact (only input sent to existing bullets)
      assertUnit(3 == (int)s.bullets.size());

      // Pellets and Bombs should be unchanged (input is no-op for them)
      {
         auto it = s.bullets.begin();
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(pelletDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(pelletDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(pelletStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(pelletStartY, (*it)->getPosition().getY(), tolerance);
      }

      {
         auto it = s.bullets.begin();
         ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(bombDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(bombDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(bombStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(bombStartY, (*it)->getPosition().getY(), tolerance);
      }

      // Missile should have been altered by input (turn)
      {
         auto it = s.bullets.begin();
         ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(missileDx1, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(missileDy1, (*it)->getVelocity().getDy(), tolerance);
         // position unchanged (interact does not move bullets)
         assertEqualsTolerance(missileStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(missileStartY, (*it)->getPosition().getY(), tolerance);
      }

      // Gun angle should have elevated by 0.025 for a single 'up' press
      assertEqualsTolerance(oldGunAngle + 0.025, s.gun.angle, tolerance);

      // No effects should have been created by interact alone
      assertUnit(0 == (int)s.effects.size());

      // Time and other state remain unchanged
      assertEquals(FRAMES_PER_SECOND * 15, s.time.framesLeft);
      assertEquals(0, s.score.points);
      assertEquals(0, s.hitRatio.numKilled);
      assertEquals(0, s.hitRatio.numMissed);

      // TEARDOWN
      // restore UserInput static state
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;

      Bullet::dimensions = dimensionsOriginal;  

      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }


   // New test: interact with no key pressed, ensure nothing new is created
   void test_interact_nothing()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 800.0;
      dimensions.y = 600.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Explicitly set the gun (there will be a gun but no bullets created)
      s.gun.angle = 0.42;
      s.gun.pt.x = 150.0;
      s.gun.pt.y = 75.0;

      // Set other visible state that should remain unchanged after interact
      s.score.points = 10;
      s.hitRatio.numKilled = 1;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      // Set time so level-based firing rules are controlled
      s.time.levelNumber = 1;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // retain the old settings for UserInput
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;

      // Prevent UserInput::initialize() from running in tests
      UserInput::initialized = true;

      // Explicitly set all UserInput static flags to known values (no keys pressed)
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 0;
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = false;
      UserInput::isBPress = false;
      UserInput::isMPress = false;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;

      UserInput ui; // default constructed; we manipulated static state above

      // Preserve values for verification
      double oldAngle = s.gun.angle;
      double oldGunX = s.gun.pt.x;
      double oldGunY = s.gun.pt.y;
      int oldScore = s.score.points;
      int oldKilled = s.hitRatio.numKilled;
      int oldMissed = s.hitRatio.numMissed;
      bool oldBullseye = s.bullseye;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      // No bullets should have been added, no effects, points, or birds created by interact alone
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());
      assertUnit(0 == (int)s.birds.size());

      // Gun state should remain unchanged (no up/down/left/right input)
      assertEqualsTolerance(oldAngle, s.gun.angle, tolerance);
      assertEqualsTolerance(oldGunX, s.gun.pt.x, tolerance);
      assertEqualsTolerance(oldGunY, s.gun.pt.y, tolerance);

      // Score and hit ratio should remain unchanged
      assertEquals(oldScore, s.score.points);
      assertEquals(oldKilled, s.hitRatio.numKilled);
      assertEquals(oldMissed, s.hitRatio.numMissed);

      // Bullseye should remain false
      assertEquals(oldBullseye, s.bullseye);

      // TEARDOWN
      // restore UserInput initialization flag so other tests behave normally
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;

      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_interact_upEmpty()
   {
      // SETUP
      Position dimensions;
      dimensions.x = 800.0;
      dimensions.y = 600.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bird static dimensions for deterministic construction
      Bird::dimensions = dimensions;

      // Explicitly set the gun so we can observe the elevation
      s.gun.angle = 0.30; // initial angle
      s.gun.pt.x = 150.0;
      s.gun.pt.y = 75.0;

      // Other state that should remain unchanged
      s.score.points = 10;
      s.hitRatio.numKilled = 1;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      // Set time so level-based behavior is stable
      s.time.levelNumber = 1;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // retain the old settings for UserInput
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;

      // Prevent UserInput::initialize() from running in tests and set keys
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 1;    // press UP
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = false;
      UserInput::isBPress = false;
      UserInput::isMPress = false;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;

      UserInput ui;

      // Preserve old values
      double oldAngle = s.gun.angle;
      int oldBirdCount = (int)s.birds.size();
      int oldScore = s.score.points;
      int oldKilled = s.hitRatio.numKilled;
      int oldMissed = s.hitRatio.numMissed;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      // Gun angle should have elevated by 0.025 for a single 'up' press
      assertEqualsTolerance(oldAngle + 0.025, s.gun.angle, tolerance);

      // No bullets/effects/points should be created by pressing up alone
      assertUnit(0 == (int)s.bullets.size());
      assertUnit(0 == (int)s.effects.size());
      assertUnit(0 == (int)s.points.size());
      assertUnit(0 == (int)s.birds.size());

      // Score and hit ratio remain unchanged
      assertEquals(oldScore, s.score.points);
      assertEquals(oldKilled, s.hitRatio.numKilled);
      assertEquals(oldMissed, s.hitRatio.numMissed);

      // TEARDOWN

      // restore UserInput initialization flag so other tests behave normally
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;

      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_interact_upBullets()
   {
      // SETUP
      Position dimensionsOriginal = Bullet::dimensions;
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bullet static dimensions for deterministic construction
      Bullet::dimensions = dimensions;

      // Create one of each bullet kind using deterministic angles
      Pellet* pellet = new Pellet(0.0);
      Bomb*   bomb   = new Bomb(0.5);
      Missile* missile = new Missile(0.2);

      // Add to skeet
      s.bullets.push_back(pellet);
      s.bullets.push_back(bomb);
      s.bullets.push_back(missile);

      // Explicitly set other state that should remain unchanged except gun.angle
      s.gun.angle = 0.30; // initial
      s.gun.pt.x = 150.0;
      s.gun.pt.y = 75.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      s.time.levelNumber = 4;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // Compute initial expected velocities/positions (constructor behavior)
      double pelletDx0   = -15.0 * cos(0.0);
      double pelletDy0   =  15.0 * sin(0.0);
      double pelletStartX = dimensions.x - 1.0;
      double pelletStartY = 1.0;

      double bombDx0     = -10.0 * cos(0.5);
      double bombDy0     =  10.0 * sin(0.5);
      double bombStartX  = dimensions.x - 1.0;
      double bombStartY  = 1.0;

      double missileDx0  = -10.0 * cos(0.2);
      double missileDy0  =  10.0 * sin(0.2);
      double missileStartX = dimensions.x - 1.0;
      double missileStartY = 1.0;

      // Compute expected missile velocity after a single 'up' input (v.turn(0.04))
      double missileSpeed = sqrt(missileDx0 * missileDx0 + missileDy0 * missileDy0);
      double missileAngle0 = atan2(missileDx0, missileDy0); // velocity.Angle uses (dx,dy)
      double missileAngle1 = missileAngle0 + 0.04;
      double missileDx1 = sin(missileAngle1) * missileSpeed;
      double missileDy1 = cos(missileAngle1) * missileSpeed;

      // Preserve UserInput static state
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;

      // Prevent UserInput::initialize() and set 'up' pressed
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 1;    // press UP
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = false;
      UserInput::isBPress = false;
      UserInput::isMPress = false;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;

      UserInput ui;

      double oldGunAngle = s.gun.angle;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      // No new bullets should be created by interact (only input sent to existing bullets)
      assertUnit(3 == (int)s.bullets.size());

      // Pellets and Bombs should be unchanged (input is no-op for them)
      {
         auto it = s.bullets.begin();
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(pelletDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(pelletDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(pelletStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(pelletStartY, (*it)->getPosition().getY(), tolerance);
      }

      {
         auto it = s.bullets.begin();
         ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(bombDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(bombDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(bombStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(bombStartY, (*it)->getPosition().getY(), tolerance);
      }

      // Missile should have been altered by input (turn)
      {
         auto it = s.bullets.begin();
         ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(missileDx1, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(missileDy1, (*it)->getVelocity().getDy(), tolerance);
         // position unchanged (interact does not move bullets)
         assertEqualsTolerance(missileStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(missileStartY, (*it)->getPosition().getY(), tolerance);
      }

      // Gun angle should have elevated by 0.025 for a single 'up' press
      assertEqualsTolerance(oldGunAngle + 0.025, s.gun.angle, tolerance);

      // No effects should have been created by interact alone
      assertUnit(0 == (int)s.effects.size());

      // Time and other state remain unchanged
      assertEquals(FRAMES_PER_SECOND * 15, s.time.framesLeft);
      assertEquals(0, s.score.points);
      assertEquals(0, s.hitRatio.numKilled);
      assertEquals(0, s.hitRatio.numMissed);

      // TEARDOWN
      // restore UserInput static state
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;

      Bullet::dimensions = dimensionsOriginal;

      // clean up any remaining heap allocations to avoid leaks in test run
      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }


   void test_interact_spaceBullets()
   {
      // SETUP
      Position dimensionsOriginal = Bullet::dimensions;
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bullet static dimensions for deterministic construction
      Bullet::dimensions = dimensions;

      // Create one of each bullet kind using deterministic angles:
      // Pellet(angle=0.0), Bomb(angle=0.5), Missile(angle=0.2)
      Pellet* pellet = new Pellet(0.0);
      Bomb*   bomb   = new Bomb(0.5);
      Missile* missile = new Missile(0.2);

      // Add to skeet
      s.bullets.push_back(pellet);
      s.bullets.push_back(bomb);
      s.bullets.push_back(missile);

      // Explicitly set other state that should remain unchanged
      s.gun.angle = 0.30; // used for newly fired pellet
      s.gun.pt.x = 3.0;
      s.gun.pt.y = 4.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      s.time.levelNumber = 4;
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // Compute initial expected velocities/positions (constructors)
      double pelletDx0   = -15.0 * cos(0.0);
      double pelletDy0   =  15.0 * sin(0.0);
      double pelletStartX = dimensions.x - 1.0;
      double pelletStartY = 1.0;

      double bombDx0     = -10.0 * cos(0.5);
      double bombDy0     =  10.0 * sin(0.5);
      double bombStartX  = dimensions.x - 1.0;
      double bombStartY  = 1.0;

      double missileDx0  = -10.0 * cos(0.2);
      double missileDy0  =  10.0 * sin(0.2);
      double missileStartX = dimensions.x - 1.0;
      double missileStartY = 1.0;

      // Expected new pellet (fired by space): uses gun angle = 0.30
      double newPelletDx = -15.0 * cos(0.30);
      double newPelletDy =  15.0 * sin(0.30);
      double newPelletStartX = dimensions.x - 1.0;
      double newPelletStartY = 1.0;

      // retain the old settings for UserInput
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;

      // Prevent UserInput::initialize() from running in tests and set SPACE pressed
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 0;
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = true; // SPACE pressed
      UserInput::isBPress = true;
      UserInput::isMPress = true;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;

      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      // SPACE is processed first in interact -> new pellet appended: 3 + 1 = 4
      assertUnit(4 == (int)s.bullets.size());

      // Original pellet unchanged
      {
         auto it = s.bullets.begin();
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(pelletDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(pelletDy0, (*it)->getVelocity().getDy(), tolerance);
      }

      // Original bomb unchanged
      {
         auto it = s.bullets.begin();
         ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(bombDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(bombDy0, (*it)->getVelocity().getDy(), tolerance);
      }

      // Original missile unchanged
      {
         auto it = s.bullets.begin();
         ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(missileDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(missileDy0, (*it)->getVelocity().getDy(), tolerance);
      }

      // New pellet appended and has velocity based on gun angle
      {
         auto it = s.bullets.begin();
         ++it; ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(newPelletDx, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(newPelletDy, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(newPelletStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(newPelletStartY, (*it)->getPosition().getY(), tolerance);
      }

      // No effects created by interact alone
      assertUnit(0 == (int)s.effects.size());

      // restore UserInput static state
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;

      // TEARDOWN

      Bullet::dimensions = dimensionsOriginal;

      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

   void test_interact_mBullets()
   {
      // SETUP
      Position dimensionsOriginal = Bullet::dimensions;
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);
   
      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);
   
      // Ensure Bullet static dimensions for deterministic construction
      Bullet::dimensions = dimensions;
   
      // Create one of each bullet kind (existing on screen)
      Pellet* pellet = new Pellet(0.0);
      Bomb* bomb = new Bomb(0.5);
      Missile* missile = new Missile(0.2);
   
      // Add to skeet
      s.bullets.push_back(pellet);
      s.bullets.push_back(bomb);
      s.bullets.push_back(missile);
   
      // Explicitly set other state
      s.gun.angle = 0.30;
      s.gun.pt.x = 3.0;
      s.gun.pt.y = 4.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;
   
      s.time.levelNumber = 4; // allow missiles to be fired
      s.time.framesLeft = FRAMES_PER_SECOND * 15;
   
      // initial velocities/positions from constructors
      double pelletDx0 = -15.0 * cos(0.0);
      double pelletDy0 = 15.0 * sin(0.0);
      double pelletStartX = dimensions.x - 1.0;
      double pelletStartY = 1.0;
   
      double bombDx0 = -10.0 * cos(0.5);
      double bombDy0 = 10.0 * sin(0.5);
      double bombStartX = dimensions.x - 1.0;
      double bombStartY = 1.0;
   
      double missileDx0 = -10.0 * cos(0.2);
      double missileDy0 = 10.0 * sin(0.2);
      double missileStartX = dimensions.x - 1.0;
      double missileStartY = 1.0;
   
      // Expected new missile (fired by M) uses gun.angle = 0.30, speed=10
      double newMissileDx = -10.0 * cos(0.30);
      double newMissileDy = 10.0 * sin(0.30);
      double newMissileStartX = dimensions.x - 1.0;
      double newMissileStartY = 1.0;
   
      // retain the old settings for UserInput
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;
   
      // Prevent UserInput::initialize() from running in tests and set M pressed
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 0;
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = false;
      UserInput::isBPress = false;
      UserInput::isMPress = true; // M pressed
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;
   
      UserInput ui;
   
      // EXERCISE
      s.interact(ui);
   
      // VERIFY
      // New missile appended: original 3 + new = 4
      assertUnit(4 == (int)s.bullets.size());
   
      // Original pellet unchanged
      {
         auto it = s.bullets.begin();
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(pelletDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(pelletDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(pelletStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(pelletStartY, (*it)->getPosition().getY(), tolerance);
      }
   
      // Original bomb unchanged
      {
         auto it = s.bullets.begin();
         ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(bombDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(bombDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(bombStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(bombStartY, (*it)->getPosition().getY(), tolerance);
      }
   
      // Original missile unchanged
      {
         auto it = s.bullets.begin();
         ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(missileDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(missileDy0, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(missileStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(missileStartY, (*it)->getPosition().getY(), tolerance);
      }
   
      // New missile appended and has velocity based on gun angle
      {
         auto it = s.bullets.begin();
         ++it; ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(newMissileDx, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(newMissileDy, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(newMissileStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(newMissileStartY, (*it)->getPosition().getY(), tolerance);
      }
   
      // No effects created by interact alone
      assertUnit(0 == (int)s.effects.size());
   
      // restore UserInput static state
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;
   
      // TEARDOWN

      Bullet::dimensions = dimensionsOriginal;

      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }
   
   
   void test_interact_bBullets()
   {
      // SETUP
      Position dimensionsOriginal = Bullet::dimensions;
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);
   
      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);
   
      // Ensure Bullet static dimensions for deterministic construction
      Bullet::dimensions = dimensions;
   
      // Create one of each bullet kind (existing on screen)
      Pellet* pellet = new Pellet(0.0);
      Bomb* bomb = new Bomb(0.5);
      Missile* missile = new Missile(0.2);
   
      // Add to skeet
      s.bullets.push_back(pellet);
      s.bullets.push_back(bomb);
      s.bullets.push_back(missile);
   
      // Explicitly set other state
      s.gun.angle = 0.30;
      s.gun.pt.x = 3.0;
      s.gun.pt.y = 4.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;
   
      s.time.levelNumber = 4; // allow bombs to be fired (needs >2)
      s.time.framesLeft = FRAMES_PER_SECOND * 15;
   
      // initial velocities/positions from constructors
      double pelletDx0 = -15.0 * cos(0.0);
      double pelletDy0 = 15.0 * sin(0.0);
      double pelletStartX = dimensions.x - 1.0;
      double pelletStartY = 1.0;
   
      double bombDx0 = -10.0 * cos(0.5);
      double bombDy0 = 10.0 * sin(0.5);
      double bombStartX = dimensions.x - 1.0;
      double bombStartY = 1.0;
   
      double missileDx0 = -10.0 * cos(0.2);
      double missileDy0 = 10.0 * sin(0.2);
      double missileStartX = dimensions.x - 1.0;
      double missileStartY = 1.0;
   
      // Expected new bomb (fired by B) uses gun.angle = 0.30, speed=10
      double newBombDx = -10.0 * cos(0.30);
      double newBombDy = 10.0 * sin(0.30);
      double newBombStartX = dimensions.x - 1.0;
      double newBombStartY = 1.0;
   
      // retain the old settings for UserInput
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;
   
      // Prevent UserInput::initialize() from running in tests and set B pressed
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 0;
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = false;
      UserInput::isBPress = true; // B pressed
      UserInput::isMPress = false;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;
   
      UserInput ui;
   
      // EXERCISE
      s.interact(ui);
   
      // VERIFY
      // New bomb appended: original 3 + new = 4
      assertUnit(4 == (int)s.bullets.size());
   
      // Original pellet unchanged
      {
         auto it = s.bullets.begin();
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(pelletDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(pelletDy0, (*it)->getVelocity().getDy(), tolerance);
      }
   
      // Original bomb unchanged
      {
         auto it = s.bullets.begin();
         ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(bombDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(bombDy0, (*it)->getVelocity().getDy(), tolerance);
      }
   
      // Original missile unchanged
      {
         auto it = s.bullets.begin();
         ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(missileDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(missileDy0, (*it)->getVelocity().getDy(), tolerance);
      }
   
      // New bomb appended and has velocity based on gun angle
      {
         auto it = s.bullets.begin();
         ++it; ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(newBombDx, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(newBombDy, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(newBombStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(newBombStartY, (*it)->getPosition().getY(), tolerance);
      }
   
      // No effects created by interact alone
      assertUnit(0 == (int)s.effects.size());
   
      // restore UserInput static state
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;
   
      // TEARDOWN

      Bullet::dimensions = dimensionsOriginal;

      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }
   

   void test_interact_keysBullets()
   {
      // SETUP
      Position dimensionsOriginal = Bullet::dimensions;
      Position dimensions;
      dimensions.x = 1280.0;
      dimensions.y = 720.0;
      Skeet s(dimensions);

      // Ensure lists are empty explicitly
      assert(s.birds.empty() == true);
      assert(s.bullets.empty() == true);
      assert(s.effects.empty() == true);
      assert(s.points.empty() == true);

      // Ensure Bullet static dimensions for deterministic construction
      Bullet::dimensions = dimensions;

      // Create one of each bullet kind (existing on screen)
      Pellet* pellet = new Pellet(0.0);
      Bomb*   bomb   = new Bomb(0.5);
      Missile* missile = new Missile(0.2);

      // Add to skeet
      s.bullets.push_back(pellet);
      s.bullets.push_back(bomb);
      s.bullets.push_back(missile);

      // Explicitly set other state
      s.gun.angle = 0.30;
      s.gun.pt.x = 3.0;
      s.gun.pt.y = 4.0;
      s.score.points = 0;
      s.hitRatio.numKilled = 0;
      s.hitRatio.numMissed = 0;
      s.dimensions = dimensions;
      s.bullseye = false;

      s.time.levelNumber = 4; // allow M and B if code path used (but SPACE takes precedence)
      s.time.framesLeft = FRAMES_PER_SECOND * 15;

      // initial velocities/positions from constructors
      double pelletDx0   = -15.0 * cos(0.0);
      double pelletDy0   =  15.0 * sin(0.0);

      double bombDx0     = -10.0 * cos(0.5);
      double bombDy0     =  10.0 * sin(0.5);

      double missileDx0  = -10.0 * cos(0.2);
      double missileDy0  =  10.0 * sin(0.2);

      // Expected new pellet (SPACE wins when all keys pressed)
      double newPelletDx = -15.0 * cos(0.30);
      double newPelletDy =  15.0 * sin(0.30);
      double newPelletStartX = dimensions.x - 1.0;
      double newPelletStartY = 1.0;

      // retain the old settings for UserInput
      bool ui_initilized = UserInput::initialized;
      double ui_timePeriod = UserInput::timePeriod;
      int ui_nextTick = UserInput::nextTick;
      int ui_isDownPress = UserInput::isDownPress;
      int ui_isUpPress = UserInput::isUpPress;
      int ui_isLeftPress = UserInput::isLeftPress;
      int ui_isRightPress = UserInput::isRightPress;
      bool ui_isSpacePress = UserInput::isSpacePress;
      bool ui_isBPress = UserInput::isBPress;
      bool ui_isMPress = UserInput::isMPress;
      bool ui_isShiftPress = UserInput::isShiftPress;
      void* ui_p = UserInput::p;
      void (*ui_callBack)(const UserInput*, void*) = UserInput::callBack;

      // Prevent UserInput::initialize() from running in tests and set all three pressed
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isDownPress = 0;
      UserInput::isUpPress = 0;
      UserInput::isLeftPress = 0;
      UserInput::isRightPress = 0;
      UserInput::isSpacePress = true; // SPACE pressed - takes precedence
      UserInput::isBPress = true;
      UserInput::isMPress = true;
      UserInput::isShiftPress = false;
      UserInput::p = nullptr;
      UserInput::callBack = nullptr;

      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      // SPACE is processed first in interact -> new pellet appended: 3 + 1 = 4
      assertUnit(4 == (int)s.bullets.size());

      // Original pellet unchanged
      {
         auto it = s.bullets.begin();
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(pelletDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(pelletDy0, (*it)->getVelocity().getDy(), tolerance);
      }

      // Original bomb unchanged
      {
         auto it = s.bullets.begin();
         ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Bomb));
         assertEqualsTolerance(bombDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(bombDy0, (*it)->getVelocity().getDy(), tolerance);
      }

      // Original missile unchanged
      {
         auto it = s.bullets.begin();
         ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Missile));
         assertEqualsTolerance(missileDx0, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(missileDy0, (*it)->getVelocity().getDy(), tolerance);
      }

      // New pellet appended and has velocity based on gun angle
      {
         auto it = s.bullets.begin();
         ++it; ++it; ++it;
         assert(it != s.bullets.end());
         assertUnit(typeid(*(*it)) == typeid(Pellet));
         assertEqualsTolerance(newPelletDx, (*it)->getVelocity().getDx(), tolerance);
         assertEqualsTolerance(newPelletDy, (*it)->getVelocity().getDy(), tolerance);
         assertEqualsTolerance(newPelletStartX, (*it)->getPosition().getX(), tolerance);
         assertEqualsTolerance(newPelletStartY, (*it)->getPosition().getY(), tolerance);
      }

      // No effects created by interact alone
      assertUnit(0 == (int)s.effects.size());

      // restore UserInput static state
      UserInput::initialized = ui_initilized;
      UserInput::timePeriod = ui_timePeriod;
      UserInput::nextTick = ui_nextTick;
      UserInput::isDownPress = ui_isDownPress;
      UserInput::isUpPress = ui_isUpPress;
      UserInput::isLeftPress = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress = ui_isBPress;
      UserInput::isMPress = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
      UserInput::p = ui_p;
      UserInput::callBack = ui_callBack;

      // TEARDOWN

      Bullet::dimensions = dimensionsOriginal;

      for (auto p : s.birds)
         delete p;
      for (auto p : s.bullets)
         delete p;
      for (auto p : s.effects)
         delete p;
      s.birds.clear();
      s.bullets.clear();
      s.effects.clear();
   }

};