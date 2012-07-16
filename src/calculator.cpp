#include <cmath>
#include "calculator.hpp"
#include "vars.hpp"

static float pi = 3.1415;

Vector Calculator::CrossProduct(Vector a, Vector b) {
  Vector c;
  c.x = a.y * b.z - a.z * b.y;
  c.y = a.z * b.x - a.x * b.z;
  c.z = a.x * b.y - a.y * b.x;
  return c;
}

Vector Calculator::Normalize(Vector n) {
  Vector a;
  double l = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
  a.x = n.x / l;
  a.y = n.y / l;
  a.z = n.z / l;
  return a;
}

void Calculator::GetPointsAroundCentreWithNormalVector(Point3D c,
                                                       double r, 
                                                       Vector n,
                                                       Point3D* rverts,
                                                       Vector* rnorms, 
                                                       int number) {
  Vector u = Calculator::Normalize(Calculator::CrossProduct(n, Vector(1, 1, 2)));
  Vector v = Calculator::Normalize(Calculator::CrossProduct(n, u));
  double delta = 2 * 3.1415 / number;
  double t = 0;  
  for (int i = 0; i <= number; i++) {
    t = delta * i;
    rverts[i] = Point3D(c.x + r * cos(t) * u.x + r * sin(t) * v.x,
                        c.y + r * cos(t) * u.y + r * sin(t) * v.y,
                        c.z + r * cos(t) * u.z + r * sin(t) * v.z);
    rnorms[i] = Vector(rverts[i].x - c.x,
                       rverts[i].y - c.y,
                       rverts[i].z - c.z);
  }
}

float fx(float t, float k, float r) {
  // t and t + pi are equal in this situation
  if ((t >= 0) && (t <= pi / 4)) return k * r * sin(2 * t) + (-2 * r);
  if ((t >= pi / 4) && (t <= 3 * pi / 4)) return (k - 1) * r * sin(2 * t) + (-r);
  if ((t >= 3 * pi / 4) && (t <= 5 * pi / 4)) return k * r * sin(2 * t);
  if ((t >= 5 * pi / 4) && (t <= 7 * pi / 4)) return (k - 1) * r * sin(2 * t) + r;
  if ((t >= 7 * pi / 4) && (t <= 8 * pi / 4)) return k * r * sin(2 * t) + 2 * r;
}

float px(float t, float k, float r) {
  // t and t + pi are equal in this situation
  if (((t >= 0) && (t <= pi / 4)) ||
      ((t >= 3 * pi / 4) && (t <= 5 * pi / 4)) ||
      ((t >= 7 * pi / 4) && (t <= 8 * pi / 4))) return k * (r * cos(2 * t));
  else return (k - 1) * (r * cos(2 * t));
}

float fy(float t, float k, float r) {
  // t + pi gives -
  return -2 * r * cos(t);
}

float py(float t, float k, float r) {
  // t + pi gives -
  return 2 * r * sin(t);
}

float fz(float t, float k, float r, float s) {
//  if ((t >= 0) && (t <= pi / 8)) return s * sin(4 * t);

  if ((t >= 0) && (t <= pi / 8)) return s;
  if ((t >= pi / 8) && (t <= 3 * pi / 8)) return s / 2 * cos(4 * t - pi / 2) + s / 2;

  if ((t >= 5 * pi / 8) && (t <= 7 * pi / 8)) return s / 2 * cos(4 * t + pi / 2) + s / 2;
  if ((t >= 7 * pi / 8) && (t <= pi)) return s;

  if ((t >= pi) && (t <= 9 * pi / 8)) return s;
  if ((t >= 9 * pi / 8) && (t <= 11 * pi / 8)) return s / 2 * cos(4 * t - pi / 2) + s / 2;

  if ((t >= 13 * pi / 8) && (t <= 15 * pi / 8)) return s / 2 * cos(4 * t + pi / 2) + s / 2;
  if ((t >= 15 * pi / 8) && (t <= 2 * pi)) return s;

  return 0;
}

float pz(float t, float k, float r, float s){
//  if ((t >= 0) && (t <= pi / 8)) return s * 4 * cos(4 * t);

  if ((t >= pi / 8) && (t <= 3 * pi / 8)) return s / 2 * (-sin(4 * t - pi / 2) * 4);

  if ((t >= 5 * pi / 8) && (t <= 7 * pi / 8)) return s / 2 * (-sin(4 * t + pi / 2) * 4);

  if ((t >= 9 * pi / 8) && (t <= 11 * pi / 8)) return s / 2 * (-sin(4 * t - pi / 2) * 4);

  if ((t >= 13 * pi / 8) && (t <= 15 * pi / 8)) return s / 2 * (-sin(4 * t + pi / 2) * 4);

  return 0;
}

void Calculator::GetKnitStitchTrace(float a, float k, float r, Point3D c,
                                    Point3D* points,
                                    Vector* normals, int number) {
  int part = (number - 1) / 8;
  float step = pi / 4 / part;
  for (int i = 0; i <= 8 * part; i++){
    float t = i * step;
    points[i] = Point3D(c.x + fx(t, k, r), c.y + fy(t, k, r), c.z + fz(t, k, r, -a));
    normals[i] =  Vector(px(t, k, r), py(t, k, r), pz(t, k, r, -a));
  }
//  for (int i = 0; i <= part * 8; i++) {
//    printf("Point %d %f %f %f\t", i, points[i].x, points[i].y, points[i].z);
//    printf("Normal %d %f %f %f\n", i, normals[i].x, normals[i].y, normals[i].z);
//  }
}

void Calculator::DrawCurvedTube(float a, float k, float r, Point3D c,
                                GLfloat verts[][3], GLfloat norms[][3], GLint& numverts) {
  int stepsCircle = 8;
  int stepsTube = 10 * 8 + 1;
  float step = 2 * 3.1415 / stepsCircle;
  
  Point3D* points = new Point3D[stepsTube + 1];
  Vector* normals = new Vector[stepsTube + 1];
  Calculator::GetKnitStitchTrace(a, k, r, c, points, normals, stepsTube);
  
  Point3D* rverts0 = new Point3D[stepsCircle + 1];
  Vector* rnorms0 = new Vector[stepsCircle + 1];  
  Calculator::GetPointsAroundCentreWithNormalVector(points[0], a, normals[0],
                                                    rverts0, rnorms0, 
                                                    stepsCircle);
  Point3D* rverts1;
  Vector* rnorms1;  
  for (int j = 1; j <= stepsTube; j++) {
    rverts1 = new Point3D[stepsCircle + 1];
    rnorms1 = new Vector[stepsCircle + 1];  
    Calculator::GetPointsAroundCentreWithNormalVector(
        points[j], a, normals[j], rverts1, rnorms1, stepsCircle);
    for (int i = 0; i <= stepsCircle; i++) {
      int n = 2 * (j - 1) * (stepsCircle + 1) + i * 2;
      verts[n][0] = rverts0[i].x;
      verts[n][1] = rverts0[i].y;
      verts[n][2] = rverts0[i].z;
      verts[n + 1][0] = rverts1[i].x;
      verts[n + 1][1] = rverts1[i].y;
      verts[n + 1][2] = rverts1[i].z;
      norms[n][0] = rnorms0[i].x; 
      norms[n][1] = rnorms0[i].y; 
      norms[n][2] = rnorms0[i].z; 
      norms[n + 1][0] = rnorms1[i].x;
      norms[n + 1][1] = rnorms1[i].y;
      norms[n + 1][2] = rnorms1[i].z;
    }
    delete[] rverts0;
    delete[] rnorms0;
    rverts0 = rverts1;
    rnorms0 = rnorms1;
  }

  delete[] rverts0;
  delete[] rnorms0;
  delete[] points;
  delete[] normals;
  numverts = (stepsCircle + 1) * (stepsTube) * 2;
}
