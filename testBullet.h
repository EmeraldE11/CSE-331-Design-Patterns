/***********************************************************************
 * Header File:
 *    Test Bullet : Unit test the Bullet class
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for the Bullet class. Tests set inputs explicitly and
 *    verify internals via friendship with Bullet and its derived classes.
 ************************************************************************/

#pragma once

#define DEBUG

#include "unitTest.h"
#include "bullet.h"
#include "effect.h"
#include <list>
#include <typeinfo>
#include <cassert>

 /***************************************************
  * TEST BULLET
  * Unit tests for the Bullet class. Tests set members explicitly
  ***************************************************/
class TestBullet : public UnitTest
{
public:
   void run()
   {
      reset();

      // Move tests
      test_move_bulletStationary();
      test_move_bulletMove();
      test_move_bulletNearRightBoundary();
      test_move_bulletOverRightBoundary();
      test_move_bulletNearBottom();
      test_move_bulletOverBottom();
      test_move_bulletNearTop();
      test_move_bulletOverTop();
      test_move_bulletNearLeft();
      test_move_bulletOverLeft();
      test_move_bombNotDead();
      test_move_bombExpired();
      test_move_shrapnelNotDead();
      test_move_shrapnelExpired();

      // Death tests
      test_death_bullet();
      test_death_pellet();
      test_death_missile();
      test_death_shrapnel();
      test_death_bomb();

      report("Bullet");
   }

   // Move: stationary bullet should not change position and effects list should
   // remain containing the single EffectDummy we supplied.
   // name: test_move_bulletStationary
   // setup:
   //    - save Bullet::dimensions and set to (100,100)
   //    - create a Pellet and explicitly set pt=(1.1,2.2), v=(0,0),
   //      radius=5, dead=false, value=10
   //    - create effects list with single EffectDummy
   // exercise:
   //    - call move(effects)
   // verify:
   //    - effects still has one element and it is EffectDummy
   //    - bullet position is unchanged
   void test_move_bulletStationary()
   {  // SETUP

      Position oldDimensions = Bullet::dimensions;      // save and set dimensions
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      BulletFake b; // create a concrete bullet 
      b.pt.x = 1.1;
      b.pt.y = 2.2;
      b.v.dx = 0.0;
      b.v.dy = 0.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      std::list<Effect*> effects;
      effects.push_back(new EffectDummy()); // create effects list with a single EffectDummy

      // EXERCISE
      b.move(effects);

      // VERIFY    
      assertUnit(effects.size() == 1); // still one effect and it is an EffectDummy
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);
      assertEqualsTolerance(1.1, b.pt.x, tolerance); // bullet didn't move
      assertEqualsTolerance(2.2, b.pt.y, tolerance);

      // TEARDOWN 
      Bullet::dimensions = oldDimensions;
      for (auto e : effects)
         delete e;
      effects.clear();
   }

   // Move: moving bullet should update position by velocity (dx=10, dy=20)
   // name: test_move_bulletMove
   // setup:
   //    - save Bullet::dimensions and set to (100,100)
   //    - create a Pellet and explicitly set pt=(1.1,2.2), v=(10,20),
   //      radius=5, dead=false, value=10
   //    - create effects list with single EffectDummy
   // exercise:
   //    - call move(effects)
   // verify:
   //    - effects still has one element and it is EffectDummy
   //    - bullet position is updated (by velocity)
   void test_move_bulletMove()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      BulletFake b;
      b.pt.x = 1.1;
      b.pt.y = 2.2;
      b.v.dx = 10.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);
      assertEqualsTolerance(1.1 + 10.0, b.pt.x, tolerance);
      assertEqualsTolerance(2.2 + 20.0, b.pt.y, tolerance);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }


   // Move: near the right/top edge but still within bounds after moving
   void test_move_bulletNearRightBoundary()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      BulletFake b;
      b.pt.x = 194.0;
      b.pt.y = 20.0;
      b.v.dx = 10.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);
      assertEqualsTolerance(194.0 + 10.0, b.pt.x, tolerance);// position should have been updated to (204, 40)
      assertEqualsTolerance(20.0 + 20.0, b.pt.y, tolerance);    
      assertUnit(b.dead == false); // bullet should NOT be marked dead (still within bounds considering radius)

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }

   // Move: bullet pushed over right boundary and should be marked dead
   void test_move_bulletOverRightBoundary()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      // start so that after adding dx=16 the x >= dimensions.x + radius (205 + 10 = 210)
      b.pt.x = 195.0;
      b.pt.y = 20.0;
      b.v.dx = 16.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      // position should have been updated to (196 + 15, 20 + 20)
      assertEqualsTolerance(195.0 + 16.0, b.pt.x, tolerance);
      assertEqualsTolerance(20.0 + 20.0, b.pt.y, tolerance);

      // bullet should be marked dead (moved beyond right boundary including radius)
      assertUnit(b.dead == true);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }


   // Move: near the bottom edge but still within bounds after moving
   void test_move_bulletNearBottom()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      b.pt.x = 100.0;
      b.pt.y = 16.0;    // after dy = -20 ->  -4.0 (still > -radius (-5))
      b.v.dx = 0.0;
      b.v.dy = -20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      assertEqualsTolerance(100.0 + 0.0, b.pt.x, tolerance);
      assertEqualsTolerance(16.0 + (-20.0), b.pt.y, tolerance);
      assertUnit(b.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) delete e;
      effects.clear();
   }

   // Move: bullet pushed over the bottom and should be marked dead
   void test_move_bulletOverBottom()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      b.pt.x = 100.0;
      b.pt.y = 14.0;    // after dy = -20 -> -6.0 (< -radius (-5))
      b.v.dx = 0.0;
      b.v.dy = -20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      assertEqualsTolerance(100.0 + 0.0, b.pt.x, tolerance);
      assertEqualsTolerance(14.0 + (-20.0), b.pt.y, tolerance);
      assertUnit(b.dead == true);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) delete e;
      effects.clear();
   }

   // Move: near the top edge but still within bounds after moving
   void test_move_bulletNearTop()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      b.pt.x = 100.0;
      b.pt.y = 189.0;   // after dy = 20 -> 209.0 (< dimensions.y + radius = 210)
      b.v.dx = 0.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      assertEqualsTolerance(100.0 + 0.0, b.pt.x, tolerance);
      assertEqualsTolerance(189.0 + 20.0, b.pt.y, tolerance);
      assertUnit(b.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) delete e;
      effects.clear();
   }

   // Move: bullet pushed over the top boundary and should be marked dead
   void test_move_bulletOverTop()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      b.pt.x = 100.0;
      b.pt.y = 190.0;   // after dy = 20 -> 210.0 (>= dimensions.y + radius = 210)
      b.v.dx = 0.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      assertEqualsTolerance(100.0 + 0.0, b.pt.x, tolerance);
      assertEqualsTolerance(190.0 + 20.0, b.pt.y, tolerance);
      assertUnit(b.dead == true);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) delete e;
      effects.clear();
   }

   // Move: near the left edge but still within bounds after moving
   void test_move_bulletNearLeft()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      b.pt.x = 6.0;     // after dx = -10 -> -4.0 (still > -radius (-5))
      b.pt.y = 100.0;
      b.v.dx = -10.0;
      b.v.dy = 0.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      assertEqualsTolerance(6.0 + (-10.0), b.pt.x, tolerance);
      assertEqualsTolerance(100.0 + 0.0, b.pt.y, tolerance);
      assertUnit(b.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) delete e;
      effects.clear();
   }

   // Move: bullet pushed over the left boundary and should be marked dead
   void test_move_bulletOverLeft()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;

      BulletFake b;
      b.pt.x = 4.0;     // after dx = -10 -> -6.0 (< -radius (-5))
      b.pt.y = 100.0;
      b.v.dx = -10.0;
      b.v.dy = 0.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      assertEqualsTolerance(4.0 + (-10.0), b.pt.x, tolerance);
      assertEqualsTolerance(100.0 + 0.0, b.pt.y, tolerance);
      assertUnit(b.dead == true);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) delete e;
      effects.clear();
   }

   // Move: Bomb with timeToDie=2 should not be dead after one move
   void test_move_bombNotDead()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 205.0;
      Bullet::dimensions.y = 205.0;
      Bomb b(0.0);
      b.pt.x = 1.1;
      b.pt.y = 2.2;
      b.v.dx = 10.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      b.timeToDie = 2;
      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(b.timeToDie == 1); // timeToDie decremented from 2 -> 1   
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      // position updated
      assertEqualsTolerance(1.1 + 10.0, b.pt.x, tolerance);
      assertEqualsTolerance(2.2 + 20.0, b.pt.y, tolerance);

      // Bomb should not be dead yet (timeToDie decremented from 2 -> 1)
      assertUnit(b.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }

   // Move: Bomb with timeToDie=1 should be dead after one move
   void test_move_bombExpired()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;

      Bomb b(0.0);
      b.pt.x = 1.1;
      b.pt.y = 2.2;
      b.v.dx = 10.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      b.timeToDie = 1;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      b.move(effects);

      // VERIFY
      assertUnit(b.timeToDie == 0); // timeToDie decremented from 1 -> 0   
      assertUnit(effects.size() == 1);
      Effect* first = effects.front();
      assertUnit(dynamic_cast<EffectDummy*>(first) != nullptr);

      // position updated
      assertEqualsTolerance(1.1 + 10.0, b.pt.x, tolerance);
      assertEqualsTolerance(2.2 + 20.0, b.pt.y, tolerance);

      // Bomb should be dead (timeToDie decremented from 1 -> 0 and kill() called)
      assertUnit(b.dead == true);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }

   // Move: Shrapnel with timeToDie=2 should NOT be dead after one move
   void test_move_shrapnelNotDead()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;

      Bomb bomb(0.0);

      Shrapnel s(bomb);
      s.pt.x = 1.1;
      s.pt.y = 2.2;
      s.v.dx = 10.0;
      s.v.dy = 20.0;
      s.timeToDie = 2;   // will decrement to 1
      s.dead = false;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      s.move(effects);

      // VERIFY
      assertUnit(effects.size() == 2);
      Effect* last = effects.back();
      assertUnit(dynamic_cast<Streek*>(last) != nullptr);

      assertEqualsTolerance(1.1 + 10.0, s.pt.x, tolerance);
      assertEqualsTolerance(2.2 + 20.0, s.pt.y, tolerance);

      // should not be dead yet
      assertUnit(s.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }

   // Move: Shrapnel with timeToDie=1 should expire and be marked dead after move
   void test_move_shrapnelExpired()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;

      Bomb bomb(0.0);

      Shrapnel s(bomb);
      s.pt.x = 1.1;
      s.pt.y = 2.2;
      s.v.dx = 10.0;
      s.v.dy = 20.0;
      s.timeToDie = 1;   // will decrement to 0 and kill()
      s.dead = false;

      std::list<Effect*> effects;
      effects.push_back(new EffectDummy());

      // EXERCISE
      s.move(effects);

      // VERIFY
      assertUnit(effects.size() == 2);
      Effect* last = effects.back();
      assertUnit(dynamic_cast<Streek*>(last) != nullptr);

      assertEqualsTolerance(1.1 + 10.0, s.pt.x, tolerance);
      assertEqualsTolerance(2.2 + 20.0, s.pt.y, tolerance);

      // should be dead now
      assertUnit(s.dead == true);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto e : effects) 
         delete e;
      effects.clear();
   }



   // Death: calling base Bullet::death should do nothing for BulletFake
   void test_death_bullet()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      BulletFake b;
      b.pt.x = 1.1;
      b.pt.y = 2.2;
      b.v.dx = 10.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      std::list<Bullet*> bullets; // start empty

      // EXERCISE
      b.death(bullets);

      // VERIFY
      assertUnit(bullets.empty());
      assertEqualsTolerance(1.1, b.pt.x, tolerance);
      assertEqualsTolerance(2.2, b.pt.y, tolerance);
      assertUnit(b.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto pb : bullets) 
         delete pb;
      bullets.clear();
   }

   // Death: calling base Bullet::death should do nothing for Pellet
   void test_death_pellet()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      Pellet p(0.0);
      p.pt.x = 1.1;
      p.pt.y = 2.2;
      p.v.dx = 10.0;
      p.v.dy = 20.0;
      p.radius = 5.0;
      p.dead = false;
      p.value = 10;
      std::list<Bullet*> bullets; // start empty

      // EXERCISE
      p.death(bullets);

      // VERIFY
      // base class death should leave the list unchanged
      assertUnit(bullets.empty());
      // bullet unchanged
      assertEqualsTolerance(1.1, p.pt.x, tolerance);
      assertEqualsTolerance(2.2, p.pt.y, tolerance);
      assertUnit(p.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto pb : bullets) 
         delete pb;
      bullets.clear();
   }

   // Death: calling base Bullet::death should do nothing for Missile
   void test_death_missile()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      Missile m(0.0);
      m.pt.x = 1.1;
      m.pt.y = 2.2;
      m.v.dx = 10.0;
      m.v.dy = 20.0;
      m.radius = 5.0;
      m.dead = false;
      m.value = 10;
      std::list<Bullet*> bullets; // start empty

      // EXERCISE
      m.death(bullets);

      // VERIFY
      // base class death should leave the list unchanged
      assertUnit(bullets.empty());
      // bullet unchanged
      assertEqualsTolerance(1.1, m.pt.x, tolerance);
      assertEqualsTolerance(2.2, m.pt.y, tolerance);
      assertUnit(m.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto pb : bullets) 
         delete pb;
      bullets.clear();
   }

   // Death: calling base Bullet::death should do nothing for Shrapnel
   void test_death_shrapnel()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      Shrapnel s(0.0);
      s.pt.x = 1.1;
      s.pt.y = 2.2;
      s.v.dx = 10.0;
      s.v.dy = 20.0;
      s.radius = 5.0;
      s.dead = false;
      s.value = 10;
      std::list<Bullet*> bullets; // start empty

      // EXERCISE
      s.death(bullets);

      // VERIFY
      // base class death should leave the list unchanged
      assertUnit(bullets.empty());
      // bullet unchanged
      assertEqualsTolerance(1.1, s.pt.x, tolerance);
      assertEqualsTolerance(2.2, s.pt.y, tolerance);
      assertUnit(s.dead == false);

      // TEARDOWN
      Bullet::dimensions = oldDimensions;
      for (auto pb : bullets)
         delete pb;
      bullets.clear();
   }


   // Death: Bomb::death should create 20 Shrapnel with deterministic values
   void test_death_bomb()
   {  // SETUP
      Position oldDimensions = Bullet::dimensions;
      Bullet::dimensions.x = 200.0;
      Bullet::dimensions.y = 200.0;
      Bomb b(0.0);
      b.pt.x = 1.1;
      b.pt.y = 2.2;
      b.v.dx = 10.0;
      b.v.dy = 20.0;
      b.radius = 5.0;
      b.dead = false;
      b.value = 10;
      std::list<Bullet*> bullets;

      // EXERCISE
      b.death(bullets);

      // VERIFY
      assertUnit(bullets.size() == 20);
      for (auto pb : bullets)
      {
         // each entry should be a Shrapnel
         Shrapnel* s = dynamic_cast<Shrapnel*>(pb);
         assertUnit(s != nullptr);
         if (nullptr != s)
         {
            // position copied from bomb
            assertEqualsTolerance(1.1, s->pt.x, tolerance);
            assertEqualsTolerance(2.2, s->pt.y, tolerance);

            // timeToDie deterministic minimum (randomInt min)
            assertUnit(s->timeToDie == 5);

            // velocity deterministic minimums from randomDouble(min,...)
            assertEqualsTolerance(0.0, s->v.getDx(), tolerance);
            assertEqualsTolerance(10.0, s->v.getDy(), tolerance);

            // shrapnel value and radius expectations
            assertUnit(s->value == 0);
            assertEqualsTolerance(3.0, s->radius, tolerance);
         }

      }

      // TEARDOWN
      for (auto pb : bullets)
         delete pb;
      bullets.clear();
      Bullet::dimensions = oldDimensions;
   }



};