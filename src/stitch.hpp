#ifndef _STITCH_HPP_
#define _STITCH_HPP_

#include "stitch_type.hpp"

class Stitch {

 public:
  Stitch(): _self(NONE_STITCH_TYPE), _bottom(NONE_STITCH_TYPE),
            _left(NONE_STITCH_TYPE), _right(NONE_STITCH_TYPE) {}
  StitchType get_self() {return _self;}
  void set_self(StitchType self) {_self = self;}
  StitchType get_bottom() {return _bottom;}
  void set_bottom(StitchType bottom) {_bottom = bottom;}
  StitchType get_left() {return _left;}
  void set_left(StitchType left) {_left = left;}
  StitchType get_right() {return _right;}
  void set_right(StitchType right) {_right = right;}

 private:
  StitchType _self, _bottom, _left, _right;
};

#endif // _STITCH_HPP_