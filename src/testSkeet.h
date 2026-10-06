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

#include "bird.h"
#include "skeet.h"
#include "unitTest.h"
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

         // Ensure Bird static dimensions are known for deterministic
         // construction
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
         // spawn() should add two Standard birds under deterministic random
         // (min)
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
         s.birds.clear();
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
         s.birds.clear();
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
         s.birds.clear();
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
         s.birds.clear();
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
         s.time.framesLeft =
            FRAMES_PER_SECOND * 15; // the reset-like full frames -> playing

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
         // Most things are empty, but spawn() should have run and added birds
         // for level 1
         assertUnit(0 == (int)s.bullets.size());
         assertUnit(0 == (int)s.effects.size());
         assertUnit(0 == (int)s.points.size());

         // Should be two standard birds created in Level 1 (deterministic
         // random returns min)
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

         // Explicitly set the gun and UI-independent state to detect unintended
         // changes
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
         s.birds.clear();
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
            // Floater default points is 15
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
         s.birds.clear();
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
         //  Standard, Standard, Sinker(points=25), Floater(points=25),
         //  Crazy(points=30)
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

            // Sinker (points=25)
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Sinker));
            assertEqualsTolerance(15.0, (*it)->radius, tolerance);
            assertEquals(25, (*it)->points);

            // Floater (points=25)
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

         // Time should have advanced by one frame (framesLeft decremented)
         assertEquals(FRAMES_PER_SECOND * 15 - 1, s.time.framesLeft);

         // Other state should remain unchanged
         assertEqualsTolerance(1.234, s.gun.angle, tolerance);
         assertEqualsTolerance(5.0, s.gun.pt.x, tolerance);
         assertEqualsTolerance(6.0, s.gun.pt.y, tolerance);
         assertEquals(1234, s.score.points);
         assertEquals(10, s.hitRatio.numKilled);
         assertEquals(5, s.hitRatio.numMissed);
         assertEqualsTolerance(dimensions.x, s.dimensions.x, tolerance);
         assertEqualsTolerance(dimensions.y, s.dimensions.y, tolerance);
         assertEquals(false, s.bullseye);

         // TEARDOWN
         // clean up any remaining heap allocations to avoid leaks in test run
         for (auto p : s.birds)
            delete p;
         s.birds.clear();
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
         Standard *b1 = new Standard(30.0); // will be adjusted below
         Standard *b2 = new Standard(30.0);

         // Explicitly set positions and velocities (direct member access)
         b1->pt.x = 50.0;
         b1->pt.y = 30.0;
         b1->v.dx = 5.0;
         b1->v.dy = 2.0;
         b1->dead = false;
         b1->radius = 30.0;
         b1->points = 10;

         b2->pt.x = 40.0;
         b2->pt.y = 70.0;
         b2->v.dx = 3.0;
         b2->v.dy = -4.0;
         b2->dead = false;
         b2->radius = 30.0;
         b2->points = 10;

         // Add to skeet
         s.birds.push_back(b1);
         s.birds.push_back(b2);

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
         double b1_dx_after = 5.0 * 0.995; // 4.975
         double b1_dy_after = 2.0 * 0.995; // 1.99
         double b1_x_expected = 50.0 + b1_dx_after;
         double b1_y_expected = 30.0 + b1_dy_after;

         double b2_dx_after = 3.0 * 0.995;  // 2.985
         double b2_dy_after = -4.0 * 0.995; // -3.98
         double b2_x_expected = 40.0 + b2_dx_after;
         double b2_y_expected = 70.0 + b2_dy_after;

         // EXERCISE
         s.animate();

         // VERIFY
         // One new Standard should have been spawned (periodic spawn), so total
         // 3 birds
         assertUnit(3 == (int)s.birds.size());
         if (3 == s.birds.size())
         {
            auto it = s.birds.begin();

            // First bird: our b1 advanced
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Standard));
            assertEqualsTolerance(b1_x_expected, (*it)->pt.x, tolerance);
            assertEqualsTolerance(b1_y_expected, (*it)->pt.y, tolerance);
            assertEqualsTolerance(30.0, (*it)->radius, tolerance);
            assertEquals(10, (*it)->points);

            // Second bird: our b2 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Standard));
            assertEqualsTolerance(b2_x_expected, (*it)->pt.x, tolerance);
            assertEqualsTolerance(b2_y_expected, (*it)->pt.y, tolerance);
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
         s.birds.clear();
      }

      void test_animate_level2Mixed()
      {
         // SETUP: 2 Standards + 2 Sinkers present initially
         Position dimensions;
         dimensions.x = 800.0;
         dimensions.y = 600.0;
         Skeet s(dimensions);

         s.birds.clear();
         s.bullets.clear();
         s.effects.clear();
         s.points.clear();

         Bird::dimensions = dimensions;

         // create originals
         Standard *st1 = new Standard(30.0);
         Sinker *sk1 = new Sinker(25.0);

         // set explicit positions/velocities and internals
         st1->pt.x = 50.0;
         st1->pt.y = 30.0;
         st1->v.dx = 5.0;
         st1->v.dy = 2.0;
         st1->dead = false;
         st1->radius = 301.0;
         st1->points = 31;

         sk1->pt.x = 60.0;
         sk1->pt.y = 80.0;
         sk1->v.dx = 2.0;
         sk1->v.dy = -1.0;
         sk1->dead = false;
         sk1->radius = 303.0;
         sk1->points = 33;

         s.birds.push_back(st1);
         s.birds.push_back(sk1);

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
         double st1_dx = 5.0 * 0.995, st1_dy = 2.0 * 0.995;
         double st1_x = 50.0 + st1_dx, st1_y = 30.0 + st1_dy;

         // Sinkers: v.addDy(-0.07) then pt += v
         double sk1_dx = 2.0, sk1_dy = -1.0 - 0.07;
         double sk1_x = 60.0 + sk1_dx, sk1_y = 80.0 + sk1_dy;

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
            assertEqualsTolerance(st1_x, (*it)->pt.x, tolerance);
            assertEqualsTolerance(st1_y, (*it)->pt.y, tolerance);
            assertEqualsTolerance(301.0, (*it)->radius, tolerance);
            assertEquals(31, (*it)->points);

            // sk1 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Sinker));
            assertEqualsTolerance(sk1_x, (*it)->pt.x, tolerance);
            assertEqualsTolerance(sk1_y, (*it)->pt.y, tolerance);
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

         // cleanup
         for (auto p : s.birds)
            delete p;
         s.birds.clear();
      }

      void test_animate_level3Mixed()
      {
         // SETUP: 2 Standards + 2 Sinkers present initially for level 3
         Position dimensions;
         dimensions.x = 640.0;
         dimensions.y = 480.0;
         Skeet s(dimensions);

         s.birds.clear();
         s.bullets.clear();
         s.effects.clear();
         s.points.clear();

         Bird::dimensions = dimensions;

         // create originals
         Standard *st1 = new Standard(20.0);
         Sinker *sk1 = new Sinker(20.0);
         Floater *fl1 = new Floater(20.0);

         // explicit positions/velocities and internals for the first three
         st1->pt.x = 50.0;
         st1->pt.y = 30.0;
         st1->v.dx = 5.0;
         st1->v.dy = 2.0;
         st1->radius = 101;
         st1->points = 40;
         st1->dead = false;

         sk1->pt.x = 60.0;
         sk1->pt.y = 80.0;
         sk1->v.dx = 2.0;
         sk1->dead = false;
         sk1->radius = 102;
         sk1->points = 41;

         fl1->pt.x = 20.0;
         fl1->pt.y = 40.0;
         fl1->v.dx = 1.0;
         fl1->v.dy = 3.0;
         fl1->dead = false;
         fl1->radius = 103;
         fl1->points = 42;

         s.birds.push_back(st1);
         s.birds.push_back(sk1);
         s.birds.push_back(fl1);

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

         // compute expected post-advance positions and velocities for the three
         // initial birds Standard: v *= 0.995; pt += v;
         double st1_dx_initial = st1->v.dx;
         double st1_dy_initial = st1->v.dy;
         double st1_dx_expected = st1_dx_initial * 0.995;
         double st1_dy_expected = st1_dy_initial * 0.995;
         double st1_x = st1->pt.x + st1_dx_expected;
         double st1_y = st1->pt.y + st1_dy_expected;

         // Sinker: v.addDy(-0.07); pt += v;
         double sk1_dx_initial = sk1->v.dx;
         double sk1_dy_initial = sk1->v.dy;
         double sk1_dx_expected = sk1_dx_initial;
         double sk1_dy_expected = sk1_dy_initial - 0.07;
         double sk1_x = sk1->pt.x + sk1_dx_expected;
         double sk1_y = sk1->pt.y + sk1_dy_expected;

         // Floater: v *= 0.990; pt += v; then v.addDy(0.05)
         double fl1_dx_initial = fl1->v.dx;
         double fl1_dy_initial = fl1->v.dy;
         double fl1_dx_expected = fl1_dx_initial * 0.99;
         double fl1_dy_expected = fl1_dy_initial * 0.99; // used for position
         double fl1_x = fl1->pt.x + fl1_dx_expected;
         double fl1_y = fl1->pt.y + fl1_dy_expected;
         // final stored velocity after advance (includes the +0.05 on dy)
         double fl1_dx_final = fl1_dx_expected;
         double fl1_dy_final = fl1_dy_expected + 0.05;

         // EXERCISE
         s.animate();

         // VERIFY
         // level 3 non-empty -> 3 periodic spawns (Standard, Standard, Sinker,
         // Floater) initial 3 + 3 = 6
         assertUnit(6 == (int)s.birds.size());

         if (6 == s.birds.size())
         {
            auto it = s.birds.begin();

            // st1 advanced
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Standard));
            assertEqualsTolerance(st1_x, (*it)->pt.x, tolerance);
            assertEqualsTolerance(st1_y, (*it)->pt.y, tolerance);
            // verify velocity stored on the object after advance
            assertEqualsTolerance(st1_dx_expected, (*it)->v.dx, tolerance);
            assertEqualsTolerance(st1_dy_expected, (*it)->v.dy, tolerance);
            assertEqualsTolerance(101, (*it)->radius, tolerance);
            assertEquals(40, (*it)->points);

            // sk1 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Sinker));
            assertEqualsTolerance(sk1_x, (*it)->pt.x, tolerance);
            assertEqualsTolerance(sk1_y, (*it)->pt.y, tolerance);
            // verify sinker velocity stored on the object after advance
            assertEqualsTolerance(sk1_dx_expected, (*it)->v.dx, tolerance);
            assertEqualsTolerance(sk1_dy_expected, (*it)->v.dy, tolerance);
            // NOTE: two radius checks were present previously; keep both to
            // avoid changing behavior
            assertEqualsTolerance(102, (*it)->radius, tolerance);
            assertEquals(41, (*it)->points);

            // fl1 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Floater));
            // verify floater position after advance
            assertEqualsTolerance(fl1_x, (*it)->pt.x, tolerance);
            assertEqualsTolerance(fl1_y, (*it)->pt.y, tolerance);
            // verify floater final stored velocity (dy includes +0.05)
            assertEqualsTolerance(fl1_dx_final, (*it)->v.dx, tolerance);
            assertEqualsTolerance(fl1_dy_final, (*it)->v.dy, tolerance);
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

         for (auto p : s.birds)
            delete p;
         s.birds.clear();
      }

      void test_animate_level4Mixed()
      {
         // SETUP: 1 Standard, 1 Sinker, 1 Floater, 1 Crazy initially (4 total)
         // After animate we expect 8 total (initial 4 + 4 spawned)
         Position dimensions;
         dimensions.x = 1280.0;
         dimensions.y = 720.0;
         Skeet s(dimensions);

         s.birds.clear();
         s.bullets.clear();
         s.effects.clear();
         s.points.clear();

         Bird::dimensions = dimensions;

         // create originals
         Standard *st1 = new Standard(15.0);
         Sinker *sk1 = new Sinker(15.0);
         Floater *fl1 = new Floater(15.0);
         Crazy *cr1 = new Crazy(15.0);

         // explicit positions/velocities and internals for the initial four
         st1->pt.x = 50.0;
         st1->pt.y = 30.0;
         st1->v.dx = 5.0;
         st1->v.dy = 2.0;
         st1->dead = false;
         st1->radius = 15.1;
         st1->points = 60;

         sk1->pt.x = 60.0;
         sk1->pt.y = 80.0;
         sk1->v.dx = 2.0;
         sk1->v.dy = -1.0;
         sk1->dead = false;
         sk1->radius = 15.2;
         sk1->points = 61;

         fl1->pt.x = 20.0;
         fl1->pt.y = 40.0;
         fl1->v.dx = 1.0;
         fl1->v.dy = 3.0;
         fl1->dead = false;
         fl1->radius = 15.3;
         fl1->points = 62;

         cr1->pt.x = 25.0;
         cr1->pt.y = 50.0;
         cr1->v.dx = 4.0;
         cr1->v.dy = 1.0;
         cr1->dead = false;
         cr1->radius = 15.4;
         cr1->points = 63;

         s.birds.push_back(st1);
         s.birds.push_back(sk1);
         s.birds.push_back(fl1);
         s.birds.push_back(cr1);

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

         // compute expected post-advance positions and velocities for the four
         // initial birds Standard: v *= 0.995; pt += v;
         double st1_dx_initial = 5.0;
         double st1_dy_initial = 2.0;
         double st1_dx_expected = st1_dx_initial * 0.995; // 4.975
         double st1_dy_expected = st1_dy_initial * 0.995; // 1.99
         double st1_x_expected = 50.0 + st1_dx_expected;  // 54.975
         double st1_y_expected = 30.0 + st1_dy_expected;  // 31.99

         // Sinker: v.addDy(-0.07); pt += v;
         double sk1_dx_initial = 2.0;
         double sk1_dy_initial = -1.0;
         double sk1_dx_expected = sk1_dx_initial;        // 2.0
         double sk1_dy_expected = sk1_dy_initial - 0.07; // -1.07
         double sk1_x_expected = 60.0 + sk1_dx_expected; // 62.0
         double sk1_y_expected = 80.0 + sk1_dy_expected; // 78.93

         // Floater: v *= 0.990; pt += v; then v.addDy(0.05)
         double fl1_dx_initial = 1.0;
         double fl1_dy_initial = 3.0;
         double fl1_dx_expected = fl1_dx_initial * 0.99; // 0.99
         double fl1_dy_expected = fl1_dy_initial * 0.99; // 2.97
         double fl1_x_expected = 20.0 + fl1_dx_expected; // 20.99
         double fl1_y_expected = 40.0 + fl1_dy_expected; // 42.97
         double fl1_dx_final = fl1_dx_expected;          // 0.99
         double fl1_dy_final = fl1_dy_expected + 0.05;   // 3.02

         // Crazy:
         // deterministic random -> randomInt(0,15) == 0 so it modifies velocity
         // by randomDouble(min) = -1.5 new v = v + (-1.5, -1.5); pt += new v
         double cr1_dx_initial = 4.0;
         double cr1_dy_initial = 1.0;
         double cr1_dx_expected = cr1_dx_initial + (-1.5); // 2.5
         double cr1_dy_expected = cr1_dy_initial + (-1.5); // -0.5
         double cr1_x_expected = 25.0 + cr1_dx_expected;   // 27.5
         double cr1_y_expected = 50.0 + cr1_dy_expected;   // 49.5

         // EXERCISE
         s.animate();

         // VERIFY
         // level 4 non-empty -> 4 periodic spawns appended (Standard, Sinker,
         // Floater, Crazy) initial 4 + 4 = 8
         assertUnit(8 == (int)s.birds.size());

         if (8 == s.birds.size())
         {
            auto it = s.birds.begin();

            // st1 advanced
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Standard));
            assertEqualsTolerance(st1_x_expected, (*it)->pt.x, tolerance);
            assertEqualsTolerance(st1_y_expected, (*it)->pt.y, tolerance);
            assertEqualsTolerance(st1_dx_expected, (*it)->v.dx, tolerance);
            assertEqualsTolerance(st1_dy_expected, (*it)->v.dy, tolerance);
            assertEqualsTolerance(15.1, (*it)->radius, tolerance);
            assertEquals(60, (*it)->points);

            // sk1 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Sinker));
            assertEqualsTolerance(sk1_x_expected, (*it)->pt.x, tolerance);
            assertEqualsTolerance(sk1_y_expected, (*it)->pt.y, tolerance);
            assertEqualsTolerance(sk1_dx_expected, (*it)->v.dx, tolerance);
            assertEqualsTolerance(sk1_dy_expected, (*it)->v.dy, tolerance);
            assertEqualsTolerance(15.2, (*it)->radius, tolerance);
            assertEquals(61, (*it)->points);

            // fl1 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Floater));
            assertEqualsTolerance(fl1_x_expected, (*it)->pt.x, tolerance);
            assertEqualsTolerance(fl1_y_expected, (*it)->pt.y, tolerance);
            assertEqualsTolerance(fl1_dx_final, (*it)->v.dx, tolerance);
            assertEqualsTolerance(fl1_dy_final, (*it)->v.dy, tolerance);
            assertEqualsTolerance(15.3, (*it)->radius, tolerance);
            assertEquals(62, (*it)->points);

            // cr1 advanced
            ++it;
            assert(it != s.birds.end());
            assertUnit(typeid(*(*it)) == typeid(Crazy));
            assertEqualsTolerance(cr1_x_expected, (*it)->pt.x, tolerance);
            assertEqualsTolerance(cr1_y_expected, (*it)->pt.y, tolerance);
            assertEqualsTolerance(cr1_dx_expected, (*it)->v.dx, tolerance);
            assertEqualsTolerance(cr1_dy_expected, (*it)->v.dy, tolerance);
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
         for (auto p : s.birds)
            delete p;
         s.birds.clear();
      }
};