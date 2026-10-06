/***********************************************************************
 * Header File:
 *    Random : Generate a random number
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once

#include <cassert> // for ASSERT()
#include <cstdlib> // for RAND()

// #define DEBUG 1

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer or double
 ****************************************************************/
inline int randomInt(int min, int max, bool setRandom = false)
{
   // This part is to ensure we have predictable random numbers for unit testing. 
   // If the random number generator is not seeded, it will always return the minimum value.
   static bool unitTest = true;
   if (unitTest)
   {
      if (setRandom)
         unitTest = false;
      return min;
   }

   // generate a random number between min and max
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);
   return num;
}

inline double randomDouble(double min, double max, bool setRandom = false)
{
   // This part is to ensure we have predictable random numbers for unit testing. 
   // If the random number generator is not seeded, it will always return the minimum value.
   static bool unitTest = true;
   if (unitTest)
   {
      if (setRandom)
         unitTest = false;
      return min;
   }

   // generate a random number between min and max
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}