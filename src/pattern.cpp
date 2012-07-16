#include "pattern.hpp"

Pattern::Pattern(const char* pattern, int rows, int columns)
                 : _rows(rows + 1), _columns(columns) {
   for (int i = 0; i < _rows - 1; i++) {
     for (int j = 0; j < _columns; j++) {
       switch (pattern[i * _columns + j]) {
         case '+': _stitches[i][j].set_self(FACE_STITCH_TYPE); break;
         case '-': _stitches[i][j].set_self(BACK_STITCH_TYPE); break;
       }
       _stitches[i + 1][j].set_bottom(_stitches[i][j].get_self());
       if (j != 0) {
         if (_stitches[i][j - 1].get_self() == _stitches[i][j].get_self()) {
           _stitches[i][j - 1].set_right(SAME_STITCH_TYPE);
           _stitches[i][j].set_left(SAME_STITCH_TYPE);
         } else {
           _stitches[i][j - 1].set_right(OPPOSITE_STITCH_TYPE);
           _stitches[i][j].set_left(OPPOSITE_STITCH_TYPE);
         }
       }
       if (j != _columns - 1) {
         if (_stitches[i][j + 1].get_self() == _stitches[i][j].get_self()) {
           _stitches[i][j].set_right(SAME_STITCH_TYPE);
           _stitches[i][j + 1].set_left(SAME_STITCH_TYPE);
         } else {
           _stitches[i][j].set_right(OPPOSITE_STITCH_TYPE);
           _stitches[i][j + 1].set_left(OPPOSITE_STITCH_TYPE);
         }
       }
     }
   }
 }