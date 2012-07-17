#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "header.hpp"
#include "structs.hpp"
#include "pattern.hpp"
#include "calculator.hpp"

class Model {
 private:
  const static int MAXCOLUMNS = 10;
  const static int MAXROWS = 10;

 public:
  float _a;
  float _k;
  float _r;
  int _rows;
  int _columns;
  GLfloat _verts[MAXROWS][MAXCOLUMNS][10000][3];
  GLfloat _norms[MAXROWS][MAXCOLUMNS][10000][3];
  GLint _numverts[MAXROWS][MAXCOLUMNS];
  Point3D _centres[MAXROWS][MAXCOLUMNS];

 public:
  Model(float a, float k, float r, Pattern pattern) : _a(a), _k(k), _r(r) {
    fprintf(stderr, "%d %d", _rows, _columns);
    _rows = pattern.get_rows();
    _columns = pattern.get_columns();
    for (int k = 0; k < _rows; k++) {
      for (int l = 0; l < _columns; l++) {
        _centres[k][l] = Point3D(0.5 + l * 4 * _r,
                                 1 + k * (3 * _r - _a / 2), 0);
      }
    }
    for (int k = 0; k < _rows; k++) {
      for (int l = 0; l < _columns; l++) {
        Calculator::DrawCurvedTube(_a, _k, _r, _centres[k][l],
                                   _verts[k][l], _norms[k][l],
                                   _numverts[k][l]);
      }
    }
  }
};

#endif // _MODEL_HPP_
