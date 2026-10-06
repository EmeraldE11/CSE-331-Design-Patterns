/***********************************************************************
 * Header File:
 *    Position : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

class Velocity;

/*********************************************
 * POINT
 * A single position.
 *********************************************/
class Position
{
      friend class TestPosition;
      friend class TestGun;
      friend class TestEffect;
      friend class TestBullet;
      friend class TestBird;
      friend class TestPoints;
      friend class TestSkeet;

   public:
      // constructors
      Position() : x(0.0), y(0.0) {}
      Position(double x, double y);
      Position(const Position &pt) : x(pt.x), y(pt.y) {}

      // getters
      virtual double getX() const { return x; }
      virtual double getY() const { return y; }
      virtual bool operator==(const Position &rhs) const
      {
         return x == rhs.x && y == rhs.y;
      }
      virtual bool operator!=(const Position &rhs) const
      {
         return x != rhs.x || y != rhs.y;
      }

      // setters
      virtual void setX(double x) { this->x = x; }
      virtual void setY(double y) { this->y = y; }
      virtual void addX(double dx) { setX(getX() + dx); }
      virtual void addY(double dy) { setY(getY() + dy); }
      virtual void add(const Velocity &v);
      virtual Position &operator+=(const Velocity &v);
      virtual Position &operator=(const Position &rhs)
      {
         x = rhs.x;
         y = rhs.y;
         return *this;
      }

   private:
      double x; // horizontal position
      double y; // vertical position
};

class PositionDummy : public Position
{
   public:
      // constructors
      PositionDummy() { assert(false); }
      PositionDummy(double x, double y) { assert(false); }
      PositionDummy(const Position &pt) { assert(false); }

      // getters
      double getX() const
      {
         assert(false);
         return 0.0;
      }
      double getY() const
      {
         assert(false);
         return 0.0;
      }
      bool operator==(const Position &rhs) const
      {
         assert(false);
         return false;
      }
      bool operator!=(const Position &rhs) const
      {
         assert(false);
         return false;
      }

      // setters
      void setX(double x) { assert(false); }
      void setY(double y) { assert(false); }
      void addX(double dx) { assert(false); }
      void addY(double dy) { assert(false); }
      void add(const Velocity &v) { assert(false); }
      Position &operator+=(const Velocity &v)
      {
         assert(false);
         return *this;
      }
      Position &operator=(const Position &rhs)
      {
         assert(false);
         return *this;
      }
};

/*********************************************
 * VELOCITY
 * Movement
 *********************************************/
class Velocity
{
      friend class TestVelocity;
      friend class TestEffect;
      friend class TestBullet;
      friend class TestBird;
      friend class TestPoints;
      friend class TestSkeet;

   public:
      // constructors
      Velocity() : dx(0.0), dy(0.0) {}
      Velocity(double dx, double dy);
      Velocity(const Velocity &v) : dx(v.dx), dy(v.dy) {}

      // getters
      virtual double getDx() const { return dx; }
      virtual double getDy() const { return dy; }
      virtual bool operator==(const Velocity &rhs) const
      {
         return dx == rhs.dx && dy == rhs.dy;
      }
      virtual bool operator!=(const Velocity &rhs) const
      {
         return dx != rhs.dx || dy != rhs.dy;
      }
      virtual double getSpeed() const { return sqrt(dx * dx + dy * dy); }

      // setters
      virtual void setDx(double dx) { this->dx = dx; }
      virtual void setDy(double dy) { this->dy = dy; }
      virtual void addDx(double dx) { this->dx += dx; }
      virtual void addDy(double dy) { this->dy += dy; }
      virtual Velocity &operator+=(const Velocity &v)
      {
         addDx(v.getDx());
         addDy(v.getDy());
         return *this;
      }
      virtual void add(const Velocity &v) { *this += v; }
      virtual Velocity &operator=(const Velocity &rhs)
      {
         dx = rhs.dx;
         dy = rhs.dy;
         return *this;
      }
      virtual Velocity &operator*=(double mult)
      {
         dx *= mult;
         dy *= mult;
         return *this;
      }
      virtual Velocity operator*(double mult)
      {
         Velocity v(*this);
         v *= mult;
         return v;
      }
      virtual void set(double angle, double speed)
      {
         dx = sin(angle) * speed;
         dy = cos(angle) * speed;
      }
      virtual void turn(double radians = 0.04)
      {
         set(atan2(dx, dy) + radians, getSpeed());
      }

   private:
      double dx; // horizontal velocity
      double dy; // vertical velocity
};

class VelocityDummy : public Velocity
{
   public:
      // constructors
      VelocityDummy() {}
      VelocityDummy(double dx, double dy) { assert(false); }
      VelocityDummy(const Velocity &v) { assert(false); }

      // getters
      double getDx() const
      {
         assert(false);
         return 0.0;
      }
      double getDy() const
      {
         assert(false);
         return 0.0;
      }
      bool operator==(const Velocity &rhs) const
      {
         assert(false);
         return true;
      }
      bool operator!=(const Velocity &rhs) const
      {
         assert(false);
         return true;
      }
      double getSpeed() const
      {
         assert(false);
         return 0.0;
      }

      // setters
      void setDx(double dx) { assert(false); }
      void setDy(double dy) { assert(false); }
      void addDx(double dx) { assert(false); }
      void addDy(double dy) { assert(false); }
      Velocity &operator+=(const Velocity &v)
      {
         assert(false);
         return *this;
      }
      void add(const Velocity &v) { assert(false); }
      Velocity &operator=(const Velocity &rhs)
      {
         assert(false);
         return *this;
      }
      Velocity &operator*=(double mult)
      {
         assert(false);
         return *this;
      }
      Velocity operator*(double mult)
      {
         assert(false);
         return *this;
      }
      void set(double angle, double speed) { assert(false); }
      void turn(double radians = 0.04) { assert(false); }
};

class Velocity0 : public VelocityDummy
{
   public:
      Velocity0() : VelocityDummy() {}
      Velocity0(double dx, double dy) : VelocityDummy(dx, dy) {}
      Velocity0(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 0.0; }
      double getDy() const { return 0.0; }
};

class VelocityR : public VelocityDummy
{
   public:
      VelocityR() : VelocityDummy() {}
      VelocityR(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityR(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 11.11; }
      double getDy() const { return 0.0; }
};
class VelocityR1 : public VelocityDummy
{
   public:
      VelocityR1() : VelocityDummy() {}
      VelocityR1(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityR1(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 1.0; }
      double getDy() const { return 0.0; }
};

class VelocityU : public VelocityDummy
{
   public:
      VelocityU() : VelocityDummy() {}
      VelocityU(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityU(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 0.0; }
      double getDy() const { return 22.22; }
};
class VelocityU1 : public VelocityDummy
{
   public:
      VelocityU1() : VelocityDummy() {}
      VelocityU1(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityU1(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 0.0; }
      double getDy() const { return 1.0; }
};

class VelocityRU : public VelocityDummy
{
   public:
      VelocityRU() : VelocityDummy() {}
      VelocityRU(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityRU(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 11.11; }
      double getDy() const { return 22.22; }
};

class VelocityR4U4 : public VelocityDummy
{
   public:
      VelocityR4U4() : VelocityDummy() {}
      VelocityR4U4(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityR4U4(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 4.0; }
      double getDy() const { return 4.0; }
};

class VelocityR4D4 : public VelocityDummy
{
   public:
      VelocityR4D4() : VelocityDummy() {}
      VelocityR4D4(double dx, double dy) : VelocityDummy(dx, dy) {}
      VelocityR4D4(const Velocity &v) : VelocityDummy(v) {}
      double getDx() const { return 4.0; }
      double getDy() const { return -4.0; }
};

// stream I/O useful for debugging
std::ostream &operator<<(std::ostream &out, const Position &pt);
std::istream &operator>>(std::istream &in, Position &pt);

inline double max(double x, double y) { return (x > y) ? x : y; }
inline double min(double x, double y) { return (x > y) ? y : x; }

double minimumDistance(const Position &pt1, const Velocity &v1,
                       const Position &pt2, const Velocity &v2);
