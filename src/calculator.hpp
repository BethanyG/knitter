#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include "vars.hpp"

struct Vector {
  double x;
  double y;
  double z;
  Vector(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
  Vector() : x(0), y(0), z(0) {}
};

struct Point3D {
  double x;
  double y;
  double z;
  Point3D(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
  Point3D() : x(0), y(0), z(0) {}
};

class Calculator {
 public:
  static void GetSurfacePoints();
 private:  

  static Vector CrossProduct(Vector a, Vector b);
  static Vector Normalize(Vector n);
  static void GetPointsAroundCentreWithNormalVector(Point3D c,
                                                    double r, 
                                                    Vector n,
                                                    Point3D* rverts,
                                                    Vector* rnorms, 
                                                    int number);
  static void GetSinTrace(Point3D* points, Vector* normals, int number);
  static void DrawCurvedTube();

  static void ReadSurface(const wxChar *filename);
  static void GetStraightTube();
};

#endif // _CALCULATOR_HPP_
