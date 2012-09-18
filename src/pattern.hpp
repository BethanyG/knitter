#ifndef _PATTERN_HPP_
#define _PATTERN_HPP_

#include "stitch.hpp"

class Pattern {
  private:
   const static int MAXROWS = 20;
   const static int MAXCOLUMNS = 20;

  public:
    Pattern(const char* pattern, int rows, int columns);
    int get_rows() {return _rows;}
    int get_columns() {return _columns;}
    Stitch get_stitch_at(int row, int column) {return _stitches[row][column];}

  private:
    Stitch _stitches[MAXROWS][MAXCOLUMNS];
    int _rows;
    int _columns;

};

#endif // _PATTERN_HPP_
