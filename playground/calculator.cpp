#include <cmath>
#include "calculator.hpp"

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

float fz(float t, float k, float r, float bottom, float top, bool left_change, bool right_change) {
//  if ((t >= 0) && (t <= pi / 8)) return s * sin(4 * t);
  // left
  if ((t >= 0) && (t <= pi / 8))
    if (left_change)
      return bottom * sin(4 * t);
    else
      return bottom;
  // left curve
  if ((t >= pi / 8) && (t <= 3 * pi / 8)) return bottom / 2 * cos(4 * t - pi / 2) + bottom / 2;
  // left middle : return 0
  // top curve
  if ((t >= 5 * pi / 8) && (t <= 7 * pi / 8)) return top / 2 * cos(4 * t + pi / 2) + top / 2;
  // top
  if ((t >= 7 * pi / 8) && (t <= 9 * pi / 8)) return top;
  // top curve
  if ((t >= 9 * pi / 8) && (t <= 11 * pi / 8)) return top / 2 * cos(4 * t - pi / 2) + top / 2;
  // right middle : return 0
  // right curve
  if ((t >= 13 * pi / 8) && (t <= 15 * pi / 8)) return bottom / 2 * cos(4 * t + pi / 2) + bottom / 2;
  // right
  if ((t >= 15 * pi / 8) && (t <= 2 * pi))
    if (right_change)
      return bottom * sin(4 * t + pi);
    else
      return bottom;
  return 0;
}

float pz(float t, float k, float r, float bottom, float top, bool left_change, bool right_change){
  // left
  if ((t >= 0) && (t <= pi / 8))
    if (left_change)
      return bottom * 4 * cos(4 * t);
  // left curve
  if ((t >= pi / 8) && (t <= 3 * pi / 8)) return bottom / 2 * (-sin(4 * t - pi / 2) * 4);
  // top curve
  if ((t >= 5 * pi / 8) && (t <= 7 * pi / 8)) return top / 2 * (-sin(4 * t + pi / 2) * 4);
  // top curve
  if ((t >= 9 * pi / 8) && (t <= 11 * pi / 8)) return top / 2 * (-sin(4 * t - pi / 2) * 4);
  // right curve
  if ((t >= 13 * pi / 8) && (t <= 15 * pi / 8)) return bottom / 2 * (-sin(4 * t + pi / 2) * 4);
  // right
  if ((t >= 15 * pi / 8) && (t <= 2 * pi))
    if (right_change)
      return bottom * 4 * cos(4 * t + pi);
  return 0;
}

void Calculator::GetKnitStitchTrace(float a, float k, float r,
                                    Stitch st,
                                    Point3D c,
                                    Point3D* points,
                                    Vector* normals, int number) {
//  printf("%d %d %d %d\n", st.get_self(), st.get_bottom(), st.get_left(), st.get_right());
  float bottom = 0;
  switch (st.get_bottom()) {
    case BACK_STITCH_TYPE: bottom = a * 1.5; break;
    case FACE_STITCH_TYPE: bottom = -a * 1.5; break;
  }
  float top = 0;
  switch (st.get_self()) {
    case BACK_STITCH_TYPE: top = a * 1.5; break;
    case FACE_STITCH_TYPE: top = -a * 1.5; break;
  }
  bool left_change = (st.get_left() == OPPOSITE_STITCH_TYPE);
  bool right_change = (st.get_right() == OPPOSITE_STITCH_TYPE);

  int part = (number - 1) / 8;
  float step = pi / 4 / part;
  for (int i = 0; i <= 8 * part; i++){
    float t = i * step;
    points[i] = Point3D(c.x + fx(t, k, r), c.y + fy(t, k, r), c.z + fz(t, k, r, bottom, top, left_change, right_change));
    normals[i] =  Vector(px(t, k, r), py(t, k, r), pz(t, k, r, bottom, top, left_change, right_change));
  }
//  for (int i = 0; i <= part * 8; i++) {
//    printf("Point %d %f %f %f\t", i, points[i].x, points[i].y, points[i].z);
//    printf("Normal %d %f %f %f\n", i, normals[i].x, normals[i].y, normals[i].z);
//  }
}

void Calculator::DrawCurvedTube(float a, float k, float r, Stitch st, Point3D c,
                                GLfloat verts[][3], GLfloat norms[][3], GLint& numverts) {
  int stepsCircle = 25;
  int stepsTube = 10 * 16 + 1;
  float step = 2 * 3.1415 / stepsCircle;

  Point3D* points = new Point3D[stepsTube + 1];
  Vector* normals = new Vector[stepsTube + 1];
  Calculator::GetKnitStitchTrace(a, k, r, st, c, points, normals, stepsTube);

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

void Calculator::GetStitchTrace(float a, float k, float r,
                                Stitch st, Point3D c, GLfloat trace[][3]) {
  GLfloat ctrlpoints[19][3] = {
        {-r, -r, 0},
        {-r + a, -r, 0}, {-(1 - k) * r, -0.5 * r - a,  0},
        {-(1 - k) * r, -0.5 * r, 0},
        {-(1 - k) * r, -0.5 * r + a, 0}, {-k * r, 0.5 * r - a, 0},
        {-k * r, 0.5 * r, 0},
        {-k * r, 0.5 * r + a, 0}, {-a, r, 0},
        {0, r, 0},
        {a, r, 0}, {k * r, 0.5 * r + a, 0},
        {k * r, 0.5 * r, 0},
        {k * r, 0.5 * r - a, 0}, {(1 - k) * r, -0.5 * r + a, 0},
        {(1 - k) * r, -0.5 * r, 0},
        {(1 - k) * r, -0.5 * r - a,  0}, {r - a, -r, 0},
        {r, -r, 0}
        };
  float bottom = 0;
  switch (st.get_bottom()) {
    case BACK_STITCH_TYPE: bottom = a * 3; break;
    case FACE_STITCH_TYPE: bottom = -a * 3; break;
  }
  float top = 0;
  switch (st.get_self()) {
    case BACK_STITCH_TYPE: top = a * 3; break;
    case FACE_STITCH_TYPE: top = -a * 3; break;
  }
  bool left_change = (st.get_left() == OPPOSITE_STITCH_TYPE);
  bool right_change = (st.get_right() == OPPOSITE_STITCH_TYPE);
  for (int i = 0; i < 19; i++) {
    trace[i][0] = ctrlpoints[i][0] + c.x;
    trace[i][1] = ctrlpoints[i][1] + c.y;
    trace[i][2] = ctrlpoints[i][2] + c.z;
  }
  if (bottom != 0) {
    trace[0][2] += bottom;
    trace[1][2] += bottom;
    trace[17][2] += bottom;
    trace[18][2] += bottom;
    trace[0][1] += a;
    trace[1][1] += a;
    trace[17][1] += a;
    trace[18][1] += a;
  }
  if (top != 0) {
    trace[8][2] += top;
    trace[9][2] += top;
    trace[10][2] += top;
    trace[8][1] -= a;
    trace[9][1] -= a;
    trace[10][1] -= a;
  }
}
