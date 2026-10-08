#pragma once

class Bird;

/**********************
 * ADVANCE
 * Algorithm Abstraction - Strategy (for the advance function)
 **********************/
class Advance
{
   public:
      virtual void execute(Bird *context) = 0;
      virtual ~Advance() = default;
};

/**********************
 * STANDARDADVANCE
 * concrete advance strategy for the standard bird
 **********************/
class StandardAdvance : public Advance
{
   public:
      void execute(Bird *context);
};

/**********************
 * CRAZYADVANCE
 * concrete advance strategy for the crazy bird
 **********************/
class CrazyAdvance : public Advance
{
   public:
      void execute(Bird *context);
};

/**********************
 * SINKERADVANCE
 * concrete advance strategy for the sinker bird
 **********************/
class SinkerAdvance : public Advance
{
   public:
      void execute(Bird *context);
};

/**********************
 * FLOATERADVANCE
 * concrete advance strategy for the floater bird
 **********************/
class FloaterAdvance : public Advance
{
   public:
      void execute(Bird *context);
};
