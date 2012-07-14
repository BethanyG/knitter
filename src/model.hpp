#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "header.hpp"
#include "structs.hpp"

class Model {
 public:
  const static int MAX_STITCHES = 5;
  const static int MAX_ROWS = 5;
 public:
  float _a;
  float _k;
  float _r;
  int _rows;
  int _stitches;
  GLfloat _verts[MAX_ROWS][MAX_STITCHES][10000][3];
  GLfloat _norms[MAX_ROWS][MAX_STITCHES][10000][3];
  Point3D _centres[MAX_ROWS][MAX_STITCHES];
 public:
  Model(float a, float k, float r) : _a(a), _k(k), _r(r) {}
};

#endif // _MODEL_HPP_
