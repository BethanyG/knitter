#ifndef _MODEL_HPP_
#define _MODEL_HPP_

#include "header.hpp"
#include "structs.hpp"
#include "pattern.hpp"
#include "calculator.hpp"

class Model {
 private:
  const static int MAXROWS = 10;
  const static int MAXCOLUMNS = 10;

 public:
  float _a;
  float _k;
  float _r;
  float _xc;
  float _yc;
  int _rows;
  int _columns;
//  GLfloat _verts[MAXROWS][MAXCOLUMNS][10000][3];
//  GLfloat _norms[MAXROWS][MAXCOLUMNS][10000][3];
//  GLint _numverts[MAXROWS][MAXCOLUMNS];
  GLfloat _traces[MAXROWS][MAXCOLUMNS][19][3];
  Point3D _centres[MAXROWS][MAXCOLUMNS];

 public:
  Model(float a, float k, float r, Pattern pattern) : _a(a), _k(k), _r(r) {
    _rows = pattern.get_rows();
    _columns = pattern.get_columns();
    for (int k = 0; k < _rows; k++) {
      for (int l = 0; l < _columns; l++) {
        _centres[k][l] = Point3D(l * 2 * _r, k * (1.5 * _r - 3 * _a), 0);
      }
    }
    for (int k = 0; k < _rows; k++) {
      for (int l = 0; l < _columns; l++) {
//        Calculator::DrawCurvedTube(_a, _k, _r, pattern.get_stitch_at(k, l),
//                                   _centres[k][l],
//                                   _verts[k][l], _norms[k][l],
//                                   _numverts[k][l]);
         Calculator::GetStitchTrace(_a, _k, _r, pattern.get_stitch_at(k, l),
                                    _centres[k][l], _traces[k][l]);
      }
    }
    _xc = (pattern.get_columns() - 1) * _r;
    _yc = (pattern.get_rows() - 1) * (0.75 * _r - 1.5 * _a);
  }

  float get_r() {return _r;}
  float get_xc() {return _xc;}
  float get_yc() {return _yc;}
  int get_rows() {return _rows;}
  int get_columns() {return _columns;}
};

#endif // _MODEL_HPP_
