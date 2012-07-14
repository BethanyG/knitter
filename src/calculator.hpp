#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include "header.hpp"
#include "structs.hpp"

class Calculator {
 public:
  static void GetSurfacePoints();
  static void DrawCurvedTube(float a, float k, float r, Point3D c, 
                             GLfloat verts[][3], GLfloat norms[][3]);

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
  static void GetKnitStitchTrace(float k, float r, Point3D c, 
                                 Point3D* points, Vector* normals, int number);

  static void ReadSurface(const wxChar *filename);
  static void GetStraightTube();
};

#endif // _CALCULATOR_HPP_
