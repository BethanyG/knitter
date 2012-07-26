#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include "header.hpp"
#include "structs.hpp"
#include "stitch.hpp"

class Calculator {
 public:
  static void DrawCurvedTube(float a, float k, float r, Stitch st, Point3D c,
                             GLfloat verts[][3], GLfloat norms[][3], GLint& numverts);
  static void GetStitchTrace(float a, float k, float r,
                             Stitch st, Point3D c, GLfloat trace[][3]);

 private:
  static Vector CrossProduct(Vector a, Vector b);
  static Vector Normalize(Vector n);
  static void GetPointsAroundCentreWithNormalVector(Point3D c,
                                                    double r,
                                                    Vector n,
                                                    Point3D* rverts,
                                                    Vector* rnorms,
                                                    int number);
  static void GetKnitStitchTrace(float a, float k, float r, Stitch st, Point3D c,
                                 Point3D* points, Vector* normals, int number);
};

#endif // _CALCULATOR_HPP_
