/***********************************************************************
 * Header File:
 *    Test Handler : Unit test the Chain of Responsibility handlers
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for each concrete handler and for the way the Skeet
 *    class builds and walks the chain of responsibility.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "handler.h"
#include "skeet.h"
#include "bullet.h"
#include "uiInteract.h"
#include <typeinfo>

/**********************
 * TEST HANDLER
 * Unit test the handlers in the chain of responsibility
 **********************/
class TestHandler : public UnitTest
{
public:
   void run()
   {
      reset();

      // game over
      test_gameOver_space();
      test_gameOver_noSpace();

      // move gun
      test_moveGun_up();
      test_moveGun_rightLeft();
      test_moveGun_spaceAlsoPressed();

      // guide missile
      test_guideMissile_up();
      test_guideMissile_none();

      // pellet
      test_pellet_space();
      test_pellet_noSpace();

      // missile
      test_missile_m();
      test_missile_mWithUp();
      test_missile_noM();

      // bomb
      test_bomb_b();
      test_bomb_noB();

      // building the chain
      test_setLevel_level0();
      test_setLevel_level1();
      test_setLevel_level2();
      test_setLevel_level3();
      test_setLevel_level4();
      test_setLevel_rebuild();

      // walking the chain through Skeet::interact()
      test_interact_buildsChainOnFirstCall();
      test_interact_rebuildsChainOnLevelChange();
      test_interact_level1IgnoresMissile();
      test_interact_level2IgnoresBomb();
      test_interact_pelletBeforeMissileBeforeBomb();
      test_interact_moveGunAndFire();
      test_interact_gameOverRestart();
      test_interact_gameOverTurnsGun();
      test_interact_fireDoesNotChangeScore();

      report("Handler");
   }

private:
   /*****************************************************************
    * Helpers to set the keyboard state and put it back afterwards
    *****************************************************************/
   bool   ui_initialized;
   double ui_timePeriod;
   unsigned long ui_nextTick;
   int    ui_isDownPress;
   int    ui_isUpPress;
   int    ui_isLeftPress;
   int    ui_isRightPress;
   bool   ui_isSpacePress;
   bool   ui_isBPress;
   bool   ui_isMPress;
   bool   ui_isShiftPress;

   void pressKeys(int up = 0, int down = 0, int left = 0, int right = 0,
                  bool space = false, bool m = false, bool b = false,
                  bool shift = false)
   {
      // remember the old values
      ui_initialized  = UserInput::initialized;
      ui_timePeriod   = UserInput::timePeriod;
      ui_nextTick     = UserInput::nextTick;
      ui_isDownPress  = UserInput::isDownPress;
      ui_isUpPress    = UserInput::isUpPress;
      ui_isLeftPress  = UserInput::isLeftPress;
      ui_isRightPress = UserInput::isRightPress;
      ui_isSpacePress = UserInput::isSpacePress;
      ui_isBPress     = UserInput::isBPress;
      ui_isMPress     = UserInput::isMPress;
      ui_isShiftPress = UserInput::isShiftPress;

      // prevent UserInput::initialize() from running and set the keys
      UserInput::initialized  = true;
      UserInput::timePeriod   = 0.0;
      UserInput::nextTick     = 0;
      UserInput::isUpPress    = up;
      UserInput::isDownPress  = down;
      UserInput::isLeftPress  = left;
      UserInput::isRightPress = right;
      UserInput::isSpacePress = space;
      UserInput::isMPress     = m;
      UserInput::isBPress     = b;
      UserInput::isShiftPress = shift;
   }

   void restoreKeys()
   {
      UserInput::initialized  = ui_initialized;
      UserInput::timePeriod   = ui_timePeriod;
      UserInput::nextTick     = ui_nextTick;
      UserInput::isDownPress  = ui_isDownPress;
      UserInput::isUpPress    = ui_isUpPress;
      UserInput::isLeftPress  = ui_isLeftPress;
      UserInput::isRightPress = ui_isRightPress;
      UserInput::isSpacePress = ui_isSpacePress;
      UserInput::isBPress     = ui_isBPress;
      UserInput::isMPress     = ui_isMPress;
      UserInput::isShiftPress = ui_isShiftPress;
   }

   // set the game to a given level in the middle of playing time
   void setTime(Skeet & s, int level)
   {
      s.time.levelNumber = level;
      s.time.framesLeft = (level == 0) ? 0 : FRAMES_PER_SECOND * 15;
   }

   void deleteBullets(Skeet & s)
   {
      for (auto p : s.bullets)
         delete p;
      s.bullets.clear();
   }

   /*****************************************************************
    * GAME OVER
    *****************************************************************/

   // space during game over resets the time, score, and hit ratio
   void test_gameOver_space()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 0);
      s.score.points = 42;
      s.hitRatio.numKilled = 3;
      s.hitRatio.numMissed = 4;
      pressKeys(0, 0, 0, 0, true /*space*/);
      UserInput ui;
      HandlerGameOver handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.time.levelNumber == 1);
      assertUnit(s.time.framesLeft == FRAMES_PER_SECOND * 30);
      assertUnit(s.score.points == 0);
      assertUnit(s.hitRatio.numKilled == 0);
      assertUnit(s.hitRatio.numMissed == 0);

      // TEARDOWN
      restoreKeys();
   }

   // without space nothing happens and the chain continues
   void test_gameOver_noSpace()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 0);
      s.score.points = 42;
      pressKeys(1 /*up*/, 0, 0, 0, false, true /*m*/, true /*b*/);
      UserInput ui;
      HandlerGameOver handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.time.levelNumber == 0);
      assertUnit(s.score.points == 42);

      // TEARDOWN
      restoreKeys();
   }

   /*****************************************************************
    * MOVE GUN
    *****************************************************************/

   // up turns the gun and lets the chain continue
   void test_moveGun_up()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 1);
      s.gun.angle = 0.30;
      pressKeys(1 /*up*/);
      UserInput ui;
      HandlerMoveGun handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(0.325, s.gun.angle);
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   // right turns the same way as up, left the same way as down
   void test_moveGun_rightLeft()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 1);
      s.gun.angle = 0.30;
      pressKeys(0, 0, 0, 1 /*right*/);
      UserInput uiRight;
      HandlerMoveGun handler;

      // EXERCISE
      bool resultRight = handler.handleRequest(uiRight, s);
      double angleAfterRight = s.gun.angle;
      restoreKeys();
      pressKeys(0, 0, 1 /*left*/, 0);
      UserInput uiLeft;
      bool resultLeft = handler.handleRequest(uiLeft, s);

      // VERIFY
      assertUnit(resultRight == false);
      assertUnit(resultLeft == false);
      assertEquals(0.325, angleAfterRight);
      assertEquals(0.30, s.gun.angle);

      // TEARDOWN
      restoreKeys();
   }

   // the gun handler ignores the fire keys
   void test_moveGun_spaceAlsoPressed()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      s.gun.angle = 0.30;
      pressKeys(0, 1 /*down*/, 0, 0, true /*space*/, true /*m*/, true /*b*/);
      UserInput ui;
      HandlerMoveGun handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(0.275, s.gun.angle);
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   /*****************************************************************
    * GUIDE MISSILE
    *****************************************************************/

   // up steers the missiles in flight and lets the chain continue
   void test_guideMissile_up()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 2);
      s.bullets.push_back(new Missile(0.2));
      s.bullets.push_back(new Pellet(0.2));
      Missile expectedMissile(0.2);
      expectedMissile.input(true, false, false);
      Pellet expectedPellet(0.2);
      pressKeys(1 /*up*/);
      UserInput ui;
      HandlerGuideMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.bullets.size() == 2);
      assertEquals(expectedMissile.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expectedMissile.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());
      assertEquals(expectedPellet.getVelocity().getDx(), s.bullets.back()->getVelocity().getDx());
      assertEquals(expectedPellet.getVelocity().getDy(), s.bullets.back()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   // with no arrow keys the missiles fly straight
   void test_guideMissile_none()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 2);
      s.bullets.push_back(new Missile(0.2));
      Missile expected(0.2);
      pressKeys();
      UserInput ui;
      HandlerGuideMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   /*****************************************************************
    * PELLET
    *****************************************************************/

   // space fires a pellet along the gun and stops the chain
   void test_pellet_space()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 1);
      s.gun.angle = 0.30;
      Pellet expected(0.30);
      pressKeys(0, 0, 0, 0, true /*space*/);
      UserInput ui;
      HandlerPellet handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.front()) == typeid(Pellet));
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   // no space, no pellet
   void test_pellet_noSpace()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      pressKeys(0, 0, 0, 0, false, true /*m*/, true /*b*/);
      UserInput ui;
      HandlerPellet handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   /*****************************************************************
    * MISSILE
    *****************************************************************/

   // M fires a missile along the gun and stops the chain
   void test_missile_m()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 2);
      s.gun.angle = 0.30;
      Missile expected(0.30);
      pressKeys(0, 0, 0, 0, false, true /*m*/);
      UserInput ui;
      HandlerMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.front()) == typeid(Missile));
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   // a missile fired while up is held gets steered on its first frame
   void test_missile_mWithUp()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 2);
      s.gun.angle = 0.30;
      Missile expected(0.30);
      expected.input(true, false, false);
      pressKeys(1 /*up*/, 0, 0, 0, false, true /*m*/);
      UserInput ui;
      HandlerMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   // no M, no missile
   void test_missile_noM()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      pressKeys(1 /*up*/, 0, 0, 0, false, false, true /*b*/);
      UserInput ui;
      HandlerMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   /*****************************************************************
    * BOMB
    *****************************************************************/

   // B fires a bomb along the gun and stops the chain
   void test_bomb_b()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 3);
      s.gun.angle = 0.30;
      Bomb expected(0.30);
      pressKeys(0, 0, 0, 0, false, false, true /*b*/);
      UserInput ui;
      HandlerBomb handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.front()) == typeid(Bomb));
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   // no B, no bomb
   void test_bomb_noB()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      pressKeys(0, 0, 0, 0, false, true /*m*/);
      UserInput ui;
      HandlerBomb handler;

      // EXERCISE
      bool result = handler.handleRequest(ui, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   /*****************************************************************
    * SET LEVEL
    *****************************************************************/

   // is the handler at this index of the chain of the given type?
   template <class T>
   bool isHandler(const Skeet & s, size_t index)
   {
      return index < s.handlers.size() &&
             typeid(*s.handlers[index]) == typeid(T);
   }

   // game over: restart, then the gun
   void test_setLevel_level0()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);

      // EXERCISE
      s.setLevel(0);

      // VERIFY
      assertUnit(s.handlersLevel == 0);
      assertUnit(s.handlers.size() == 2);
      assertUnit(isHandler<HandlerGameOver>(s, 0));
      assertUnit(isHandler<HandlerMoveGun>(s, 1));
   }

   // level 1: gun and pellets
   void test_setLevel_level1()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);

      // EXERCISE
      s.setLevel(1);

      // VERIFY
      assertUnit(s.handlersLevel == 1);
      assertUnit(s.handlers.size() == 2);
      assertUnit(isHandler<HandlerMoveGun>(s, 0));
      assertUnit(isHandler<HandlerPellet>(s, 1));
   }

   // level 2: adds missiles
   void test_setLevel_level2()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);

      // EXERCISE
      s.setLevel(2);

      // VERIFY
      assertUnit(s.handlersLevel == 2);
      assertUnit(s.handlers.size() == 4);
      assertUnit(isHandler<HandlerMoveGun>(s, 0));
      assertUnit(isHandler<HandlerGuideMissile>(s, 1));
      assertUnit(isHandler<HandlerPellet>(s, 2));
      assertUnit(isHandler<HandlerMissile>(s, 3));
   }

   // level 3: adds bombs
   void test_setLevel_level3()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);

      // EXERCISE
      s.setLevel(3);

      // VERIFY
      assertUnit(s.handlersLevel == 3);
      assertUnit(s.handlers.size() == 5);
      assertUnit(isHandler<HandlerMoveGun>(s, 0));
      assertUnit(isHandler<HandlerGuideMissile>(s, 1));
      assertUnit(isHandler<HandlerPellet>(s, 2));
      assertUnit(isHandler<HandlerMissile>(s, 3));
      assertUnit(isHandler<HandlerBomb>(s, 4));
   }

   // level 4: same as level 3
   void test_setLevel_level4()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);

      // EXERCISE
      s.setLevel(4);

      // VERIFY
      assertUnit(s.handlersLevel == 4);
      assertUnit(s.handlers.size() == 5);
      assertUnit(isHandler<HandlerMoveGun>(s, 0));
      assertUnit(isHandler<HandlerGuideMissile>(s, 1));
      assertUnit(isHandler<HandlerPellet>(s, 2));
      assertUnit(isHandler<HandlerMissile>(s, 3));
      assertUnit(isHandler<HandlerBomb>(s, 4));
   }

   // the old chain is thrown away, not added to
   void test_setLevel_rebuild()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.setLevel(4);

      // EXERCISE
      s.setLevel(1);

      // VERIFY
      assertUnit(s.handlersLevel == 1);
      assertUnit(s.handlers.size() == 2);
      assertUnit(isHandler<HandlerMoveGun>(s, 0));
      assertUnit(isHandler<HandlerPellet>(s, 1));
   }

   /*****************************************************************
    * INTERACT
    *****************************************************************/

   // a new Skeet has no chain until interact() is first called
   void test_interact_buildsChainOnFirstCall()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 3);
      assertUnit(s.handlers.empty());
      pressKeys();
      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertUnit(s.handlersLevel == 3);
      assertUnit(s.handlers.size() == 5);

      // TEARDOWN
      restoreKeys();
   }

   // when the level changes, the next interact() rebuilds the chain
   void test_interact_rebuildsChainOnLevelChange()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 1);
      pressKeys();
      UserInput ui;
      s.interact(ui);
      assertUnit(s.handlers.size() == 2);
      setTime(s, 2);

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertUnit(s.handlersLevel == 2);
      assertUnit(s.handlers.size() == 4);

      // TEARDOWN
      restoreKeys();
   }

   // missiles cannot be fired in level 1
   void test_interact_level1IgnoresMissile()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 1);
      pressKeys(0, 0, 0, 0, false, true /*m*/, true /*b*/);
      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   // bombs cannot be fired in level 2
   void test_interact_level2IgnoresBomb()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 2);
      pressKeys(0, 0, 0, 0, false, false, true /*b*/);
      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   // only one shot per frame: pellet first, then missile, then bomb
   void test_interact_pelletBeforeMissileBeforeBomb()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      UserInput ui;

      // EXERCISE / VERIFY: all three keys fire a pellet
      pressKeys(0, 0, 0, 0, true /*space*/, true /*m*/, true /*b*/);
      s.interact(ui);
      restoreKeys();
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.back()) == typeid(Pellet));

      // EXERCISE / VERIFY: M and B fire a missile
      pressKeys(0, 0, 0, 0, false, true /*m*/, true /*b*/);
      s.interact(ui);
      restoreKeys();
      assertUnit(s.bullets.size() == 2);
      assertUnit(typeid(*s.bullets.back()) == typeid(Missile));

      // EXERCISE / VERIFY: B alone fires a bomb
      pressKeys(0, 0, 0, 0, false, false, true /*b*/);
      s.interact(ui);
      restoreKeys();
      assertUnit(s.bullets.size() == 3);
      assertUnit(typeid(*s.bullets.back()) == typeid(Bomb));

      // TEARDOWN
      deleteBullets(s);
   }

   // the gun turns and missiles are steered even when a shot is fired
   void test_interact_moveGunAndFire()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      s.gun.angle = 0.30;
      s.bullets.push_back(new Missile(0.2));
      Missile expectedOld(0.2);
      expectedOld.input(true, false, false);
      Pellet expectedNew(0.325);   // the gun turns before it fires
      pressKeys(1 /*up*/, 0, 0, 0, true /*space*/);
      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertEquals(0.325, s.gun.angle);
      assertUnit(s.bullets.size() == 2);
      assertEquals(expectedOld.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expectedOld.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());
      assertUnit(typeid(*s.bullets.back()) == typeid(Pellet));
      assertEquals(expectedNew.getVelocity().getDx(), s.bullets.back()->getVelocity().getDx());
      assertEquals(expectedNew.getVelocity().getDy(), s.bullets.back()->getVelocity().getDy());

      // TEARDOWN
      restoreKeys();
      deleteBullets(s);
   }

   // space in game over restarts the game and does nothing else
   void test_interact_gameOverRestart()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 0);
      s.gun.angle = 0.30;
      s.score.points = 17;
      pressKeys(1 /*up*/, 0, 0, 0, true /*space*/);
      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertUnit(s.time.levelNumber == 1);
      assertUnit(s.score.points == 0);
      assertEquals(0.30, s.gun.angle);   // the restart consumed the input
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   // in game over without space, the gun can still turn
   void test_interact_gameOverTurnsGun()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 0);
      s.gun.angle = 0.30;
      pressKeys(1 /*up*/);
      UserInput ui;

      // EXERCISE
      s.interact(ui);

      // VERIFY
      assertUnit(s.time.levelNumber == 0);
      assertEquals(0.325, s.gun.angle);
      assertUnit(s.bullets.empty());

      // TEARDOWN
      restoreKeys();
   }

   // the cost of a shot is charged when the bullet dies, not when fired
   void test_interact_fireDoesNotChangeScore()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 4);
      s.score.points = 10;
      UserInput ui;

      // EXERCISE
      pressKeys(0, 0, 0, 0, true /*space*/);
      s.interact(ui);
      restoreKeys();
      pressKeys(0, 0, 0, 0, false, true /*m*/);
      s.interact(ui);
      restoreKeys();
      pressKeys(0, 0, 0, 0, false, false, true /*b*/);
      s.interact(ui);
      restoreKeys();

      // VERIFY
      assertUnit(s.bullets.size() == 3);
      assertUnit(s.score.points == 10);

      // TEARDOWN
      deleteBullets(s);
   }
};
