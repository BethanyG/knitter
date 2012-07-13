#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include "vars.hpp"

class Calculator {
 public:
  static void GetSurfacePoints();
 private:  
  static void ReadSurface(const wxChar *filename);
  static void GetStraightTube();
};

#endif // _CALCULATOR_HPP_
