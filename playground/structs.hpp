#ifndef _STRUCTS_HPP_
#define _STRUCTS_HPP_

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

#endif // _STRUCTS_HPP_
