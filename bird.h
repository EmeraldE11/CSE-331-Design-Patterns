/***********************************************************************
 * Header File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include <memory>
#include "position.h"
#include "advance.h"

 /**********************
  * BIRD
  * Everything that can be shot
  **********************/
class Bird
{
    friend class TestBird;
    friend class TestSkeet;
protected:
    static Position dimensions; // size of the screen
    Position pt;                  // position of the flyer
    Velocity v;                // velocity of the flyer
    double radius;             // the size (radius) of the flyer
    bool dead;                 // is this flyer dead?
    int points;                // how many points is this worth?
    std::unique_ptr<Advance> pAdvance; // how this bird moves (Template Method)

    // derived birds pass in the Advance object that describes how they move
    Bird(Advance* pAdvance) : dead(false), points(0), radius(1.0), pAdvance(pAdvance) { }

public:
    Bird() : dead(false), points(0), radius(1.0), pAdvance(nullptr) { }
    virtual ~Bird() { }

    // setters
    void operator=(const Position& rhs) { pt = rhs; }
    void operator=(const Velocity& rhs) { v = rhs; }
    void kill() { dead = true; }
    void setPoints(int pts) { points = pts; }

    // getters
    bool isDead()           const { return dead; }
    const Position& getPosition() const { return pt; }
    const Velocity& getVelocity() const { return v; }
    Position& getPosition() { return pt; } // Advance uses these to move the bird
    Velocity& getVelocity() { return v; }
    double getRadius()      const { return radius; }
    int getPoints() const { return points; }
    bool isOutOfBounds() const
    {
        return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
            pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
    }

    // special functions
    virtual void draw() = 0;

    // move the bird one frame. Not virtual: every bird hands itself
    // to its Advance object, which runs the template method.
    void advance()
    {
        assert(pAdvance != nullptr);
        pAdvance->advance(*this);
    }
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public Bird
{
    friend class TestSkeet;
public:
    Standard(double radius = 25.0, double speed = 5.0, int points = 10);
    void draw();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public Bird
{
    friend class TestSkeet;
public:
    Floater(double radius = 30.0, double speed = 5.0, int points = 15);
    void draw();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public Bird
{
    friend class TestSkeet;
public:
    Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
    void draw();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public Bird
{
public:
    Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
    void draw();
};


/*********************************************
 * BIRD FAKE
 * A simple fake Bird used in tests. Its `draw()` and `advance()` must never be
 * called during tests; if either is called the test will fail via assert.
 * BirdFake has no Advance object, so advance() trips the assert in Bird.
 *********************************************/
class BirdFake : public Bird
{
public:
    BirdFake() : Bird() {}
    void draw() override
    {
        // If this is called the test should fail.
        assert(false);
    }
};