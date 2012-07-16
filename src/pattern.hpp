#ifndef _PATTERN_HPP_
#define _PATTERN_HPP_

#include "stitch.hpp"

class Pattern {
  private:
   const static int MAXROWS = 10;
   const static int MAXSTITCHES = 10;

  public:
    Pattern(const char* pattern, int rows, int columns);

  private:
    Stitch _stitches[MAXROWS][MAXSTITCHES];
    int _rows;
    int _columns;

};

#endif // _PATTERN_HPP_