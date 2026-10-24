/***********************************************************************
 * Header File:
 *    Test Handler : Unit test the Chain of Responsibility handlers
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for each concrete handler, for the way Skeet translates
 *    the keyboard into a Request, and for the way Skeet builds and walks
 *    the chain of responsibility.
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
      test_gameOver_restart();
      test_gameOver_noRestart();

      // move gun
      test_moveGun_clockwise();
      test_moveGun_counterclockwise();
      test_moveGun_ignoresFire();

      // guide missile
      test_guideMissile_clockwise();
      test_guideMissile_none();

      // pellet
      test_pellet_pellet();
      test_pellet_otherTypes();

      // missile
      test_missile_missile();
      test_missile_missileWhileTurning();
      test_missile_otherTypes();

      // bomb
      test_bomb_bomb();
      test_bomb_otherTypes();

      // translating the keyboard into a request
      test_makeRequest_nothing();
      test_makeRequest_space();
      test_makeRequest_m();
      test_makeRequest_b();
      test_makeRequest_allFireKeys();
      test_makeRequest_mAndB();
      test_makeRequest_turning();

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
    * Helpers to build requests, set the keyboard, and set the time
    *****************************************************************/
   Request buildRequest(BulletType fire = BulletType::NONE, bool restart = false,
      int clockwise = 0, int counterclockwise = 0)
   {
      Request request;
      request.fire = fire;
      request.restart = restart;
      request.clockwise = clockwise;
      request.counterclockwise = counterclockwise;
      return request;
   }

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
      ui_initialized = UserInput::initialized;
      ui_timePeriod = UserInput::timePeriod;
      ui_nextTick = UserInput::nextTick;
      ui_isDownPress = UserInput::isDownPress;
      ui_isUpPress = UserInput::isUpPress;
      ui_isLeftPress = UserInput::isLeftPress;
      ui_isRightPress = UserInput::isRightPress;
      ui_isSpacePress = UserInput::isSpacePress;
      ui_isBPress = UserInput::isBPress;
      ui_isMPress = UserInput::isMPress;
      ui_isShiftPress = UserInput::isShiftPress;

      // prevent UserInput::initialize() from running and set the keys
      UserInput::initialized = true;
      UserInput::timePeriod = 0.0;
      UserInput::nextTick = 0;
      UserInput::isUpPress = up;
      UserInput::isDownPress = down;
      UserInput::isLeftPress = left;
      UserInput::isRightPress = right;
      UserInput::isSpacePress = space;
      UserInput::isMPress = m;
      UserInput::isBPress = b;
      UserInput::isShiftPress = shift;
   }

   void restoreKeys()
   {
      UserInput::initialized = ui_initialized;
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
   }

   // set the game to a given level in the middle of playing time
   void setTime(Skeet& s, int level)
   {
      s.time.levelNumber = level;
      s.time.framesLeft = (level == 0) ? 0 : FRAMES_PER_SECOND * 15;
   }

   void deleteBullets(Skeet& s)
   {
      for (auto p : s.bullets)
         delete p;
      s.bullets.clear();
   }

   /*****************************************************************
    * GAME OVER
    *****************************************************************/

    // a restart request resets the time, score, and hit ratio
   void test_gameOver_restart()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 0);
      s.score.points = 42;
      s.hitRatio.numKilled = 3;
      s.hitRatio.numMissed = 4;
      Request request = buildRequest(BulletType::PELLET, true /*restart*/);
      HandlerGameOver handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.time.levelNumber == 1);
      assertUnit(s.time.framesLeft == FRAMES_PER_SECOND * 30);
      assertUnit(s.score.points == 0);
      assertUnit(s.hitRatio.numKilled == 0);
      assertUnit(s.hitRatio.numMissed == 0);
      assertUnit(s.bullets.empty());
   }

   // without a restart request nothing happens and the chain continues
   void test_gameOver_noRestart()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      setTime(s, 0);
      s.score.points = 42;
      Request request = buildRequest(BulletType::MISSILE, false, 1 /*cw*/);
      HandlerGameOver handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.time.levelNumber == 0);
      assertUnit(s.score.points == 42);
   }

   /*****************************************************************
    * MOVE GUN
    *****************************************************************/

    // turning clockwise raises the gun and lets the chain continue
   void test_moveGun_clockwise()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Request request = buildRequest(BulletType::NONE, false, 1 /*cw*/, 0);
      HandlerMoveGun handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(0.325, s.gun.angle);
      assertUnit(s.bullets.empty());
   }

   // turning counterclockwise lowers the gun
   void test_moveGun_counterclockwise()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Request request = buildRequest(BulletType::NONE, false, 0, 1 /*ccw*/);
      HandlerMoveGun handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(0.275, s.gun.angle);
   }

   // the gun handler does not fire anything
   void test_moveGun_ignoresFire()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Request request = buildRequest(BulletType::BOMB, true, 0, 1 /*ccw*/);
      HandlerMoveGun handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(0.275, s.gun.angle);
      assertUnit(s.bullets.empty());
   }

   /*****************************************************************
    * GUIDE MISSILE
    *****************************************************************/

    // turning steers the missiles in flight and lets the chain continue
   void test_guideMissile_clockwise()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.bullets.push_back(new Missile(0.2));
      s.bullets.push_back(new Pellet(0.2));
      Missile expectedMissile(0.2);
      expectedMissile.input(true, false, false);
      Pellet expectedPellet(0.2);
      Request request = buildRequest(BulletType::NONE, false, 1 /*cw*/, 0);
      HandlerGuideMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == false);
      assertUnit(s.bullets.size() == 2);
      assertEquals(expectedMissile.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expectedMissile.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());
      assertEquals(expectedPellet.getVelocity().getDx(), s.bullets.back()->getVelocity().getDx());
      assertEquals(expectedPellet.getVelocity().getDy(), s.bullets.back()->getVelocity().getDy());

      // TEARDOWN
      deleteBullets(s);
   }

   // with no turning the missiles fly straight
   void test_guideMissile_none()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.bullets.push_back(new Missile(0.2));
      Missile expected(0.2);
      Request request = buildRequest();
      HandlerGuideMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == false);
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      deleteBullets(s);
   }

   /*****************************************************************
    * PELLET
    *****************************************************************/

    // a pellet request fires a pellet along the gun and stops the chain
   void test_pellet_pellet()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Pellet expected(0.30);
      Request request = buildRequest(BulletType::PELLET);
      HandlerPellet handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.front()) == typeid(Pellet));
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      deleteBullets(s);
   }

   // the pellet handler ignores every other request
   void test_pellet_otherTypes()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      HandlerPellet handler;

      // EXERCISE
      bool resultNone = handler.handleRequest(buildRequest(BulletType::NONE), s);
      bool resultMissile = handler.handleRequest(buildRequest(BulletType::MISSILE), s);
      bool resultBomb = handler.handleRequest(buildRequest(BulletType::BOMB), s);

      // VERIFY
      assertUnit(resultNone == false);
      assertUnit(resultMissile == false);
      assertUnit(resultBomb == false);
      assertUnit(s.bullets.empty());
   }

   /*****************************************************************
    * MISSILE
    *****************************************************************/

    // a missile request fires a missile along the gun and stops the chain
   void test_missile_missile()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Missile expected(0.30);
      Request request = buildRequest(BulletType::MISSILE);
      HandlerMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.front()) == typeid(Missile));
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      deleteBullets(s);
   }

   // a missile fired while turning gets steered on its first frame
   void test_missile_missileWhileTurning()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Missile expected(0.30);
      expected.input(true, false, false);
      Request request = buildRequest(BulletType::MISSILE, false, 1 /*cw*/, 0);
      HandlerMissile handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      deleteBullets(s);
   }

   // the missile handler ignores every other request
   void test_missile_otherTypes()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      HandlerMissile handler;

      // EXERCISE
      bool resultNone = handler.handleRequest(buildRequest(BulletType::NONE), s);
      bool resultPellet = handler.handleRequest(buildRequest(BulletType::PELLET), s);
      bool resultBomb = handler.handleRequest(buildRequest(BulletType::BOMB), s);

      // VERIFY
      assertUnit(resultNone == false);
      assertUnit(resultPellet == false);
      assertUnit(resultBomb == false);
      assertUnit(s.bullets.empty());
   }

   /*****************************************************************
    * BOMB
    *****************************************************************/

    // a bomb request fires a bomb along the gun and stops the chain
   void test_bomb_bomb()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      s.gun.angle = 0.30;
      Bomb expected(0.30);
      Request request = buildRequest(BulletType::BOMB);
      HandlerBomb handler;

      // EXERCISE
      bool result = handler.handleRequest(request, s);

      // VERIFY
      assertUnit(result == true);
      assertUnit(s.bullets.size() == 1);
      assertUnit(typeid(*s.bullets.front()) == typeid(Bomb));
      assertEquals(expected.getVelocity().getDx(), s.bullets.front()->getVelocity().getDx());
      assertEquals(expected.getVelocity().getDy(), s.bullets.front()->getVelocity().getDy());

      // TEARDOWN
      deleteBullets(s);
   }

   // the bomb handler ignores every other request
   void test_bomb_otherTypes()
   {
      // SETUP
      Position dimensions(800.0, 600.0);
      Skeet s(dimensions);
      HandlerBomb handler;

      // EXERCISE
      bool resultNone = handler.handleRequest(buildRequest(BulletType::NONE), s);
      bool resultPellet = handler.handleRequest(buildRequest(BulletType::PELLET), s);
      bool resultMissile = handler.handleRequest(buildRequest(BulletType::MISSILE), s);

      // VERIFY
      assertUnit(resultNone == false);
      assertUnit(resultPellet == false);
      assertUnit(resultMissile == false);
      assertUnit(s.bullets.empty());
   }

   /*****************************************************************
    * MAKE REQUEST
    *****************************************************************/

    // no keys, empty request
   void test_makeRequest_nothing()
   {
      // SETUP
      pressKeys();
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.restart == false);
      assertUnit(request.fire == BulletType::NONE);
      assertUnit(request.clockwise == 0);
      assertUnit(request.counterclockwise == 0);

      // TEARDOWN
      restoreKeys();
   }

   // space means restart or pellet
   void test_makeRequest_space()
   {
      // SETUP
      pressKeys(0, 0, 0, 0, true /*space*/);
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.restart == true);
      assertUnit(request.fire == BulletType::PELLET);

      // TEARDOWN
      restoreKeys();
   }

   // M means missile
   void test_makeRequest_m()
   {
      // SETUP
      pressKeys(0, 0, 0, 0, false, true /*m*/);
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.restart == false);
      assertUnit(request.fire == BulletType::MISSILE);

      // TEARDOWN
      restoreKeys();
   }

   // B means bomb
   void test_makeRequest_b()
   {
      // SETUP
      pressKeys(0, 0, 0, 0, false, false, true /*b*/);
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.restart == false);
      assertUnit(request.fire == BulletType::BOMB);

      // TEARDOWN
      restoreKeys();
   }

   // with every fire key held, a pellet wins
   void test_makeRequest_allFireKeys()
   {
      // SETUP
      pressKeys(0, 0, 0, 0, true /*space*/, true /*m*/, true /*b*/);
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.fire == BulletType::PELLET);

      // TEARDOWN
      restoreKeys();
   }

   // with M and B held, a missile wins
   void test_makeRequest_mAndB()
   {
      // SETUP
      pressKeys(0, 0, 0, 0, false, true /*m*/, true /*b*/);
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.fire == BulletType::MISSILE);

      // TEARDOWN
      restoreKeys();
   }

   // up and right add up to clockwise, down and left to counterclockwise
   void test_makeRequest_turning()
   {
      // SETUP
      pressKeys(3 /*up*/, 5 /*down*/, 7 /*left*/, 11 /*right*/);
      UserInput ui;

      // EXERCISE
      Request request = Skeet::makeRequest(ui);

      // VERIFY
      assertUnit(request.clockwise == 14);
      assertUnit(request.counterclockwise == 12);
      assertUnit(request.fire == BulletType::NONE);

      // TEARDOWN
      restoreKeys();
   }

   /*****************************************************************
    * SET LEVEL
    *****************************************************************/

    // is the handler at this index of the chain of the given type?
   template <class T>
   bool isHandler(const Skeet& s, size_t index)
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
      assertEquals(0.30, s.gun.angle);   // the restart consumed the request
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