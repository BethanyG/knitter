#include <cmath>
#include "calculator.hpp"

void Calculator::GetSurfacePoints() {
  Calculator::DrawCurvedTube();
}

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

double Calculator::MinFrom3(double a, double b, double c) {
  double min;
  if (a < 0) a = -a; else if (a == 0) a = 1e10;
  if (b < 0) b = -b; else if (b == 0) b = 1e10;
  if (c < 0) c = -c; else if (c == 0) c = 1e10;
  min = b <= a ? b : a;
  min = c <= min ? c : min;
  printf("%f %f %f %f\n", a, b, c, min);
  return min;
}

Vector Calculator::GetUVector(Vector n) {
  double min = Calculator::MinFrom3(n.x, n.y, n.z);
  Vector u;  
  if (min == n.x) 
    u = Calculator::CrossProduct(n, Vector(min, 0, 0));
  else if (min == n.y)
    u = Calculator::CrossProduct(n, Vector(0, min, 0));
  else
    u = Calculator::CrossProduct(n, Vector(0, 0, min)); 
  u = Calculator::Normalize(u);
  return u;
}

Vector Calculator::GetVVector(Vector n, Vector u) {
  Vector v;
  v = Calculator::CrossProduct(n, u);
  v = Calculator::Normalize(v);
  return v;
}

void Calculator::GetPointsAroundCentreWithNormalVector(Point3D c,
                                                       double r, 
                                                       Vector n,
                                                       Point3D* rverts,
                                                       Vector* rnorms, 
                                                       int number) {
  Vector u = Calculator::GetUVector(n);
  Vector v = Calculator::GetVVector(n, u);
  double delta = 2 * 3.1415 / number;
  printf("%f %f %f \n", c.x, c.y, c.z);
  printf("%f %f %f -> %f %f %f -> %f %f %f\n", 
         n.x, n.y, n.z, u.x, u.y, u.z, v.x, v.y, v.z);
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

void Calculator::GetTraceAndNormals(Point3D* points, 
                                    Vector* normals, 
                                    int number) {
  float step = 3.1415 / number;
  for (int i = 0; i <= number; i++) {
    double x = i * step / 3.1415;
    points[i] = Point3D(x - 0.5, sin(x * 3.1415) - 0.5, 0);
    normals[i] = Vector(1, cos(x * 3.1415), 0);
  }
}

void Calculator::DrawCurvedTube() {
  int stepsCircle = 20;
  int stepsTube = 20;
  float a = 0.2;
  float step = 2 * 3.1415 / stepsCircle;
  Point3D* points = new Point3D[stepsTube + 1];
  Vector* normals = new Vector[stepsTube + 1];
  Calculator::GetTraceAndNormals(points, normals, stepsTube);
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
  numverts = (stepsCircle + 1) * (stepsTube + 1) * 2;
  // for (int i = 0; i < 20; i++) {
  //   printf("%f %f %f\n", verts[i][0], verts[i][1], verts[i][2]); 
  // }

  wxPrintf(_T("%d vertices, %d triangles\n"), numverts, numverts-2);
}

void Calculator::ReadSurface(const wxChar *filename) {
  FILE *f = wxFopen(filename,_T("r"));
  if (!f) {
    wxString msg = _T("Couldn't read ");
    msg += filename;
    wxMessageBox(msg);
    return;
  }
  numverts = 0;
  while (!feof(f) && numverts<MAXVERTS) {
    fscanf(f, "%f %f %f  %f %f %f",
           &verts[numverts][0], &verts[numverts][1], &verts[numverts][2],
           &norms[numverts][0], &norms[numverts][1], &norms[numverts][2]);
    numverts++;
  }
  numverts--;
  wxPrintf(_T("%d vertices, %d triangles\n"), numverts, numverts-2);
  fclose(f);
}

void Calculator::GetStraightTube() {
  int stepsCircle = 100;
  int stepsTube = 10;
  float a = 0.2;
  float l = 1.5;
  float step = 2 * 3.1415 / stepsCircle;
  for (int j = 0; j < stepsTube; j++) {
    for (int i = 0; i <= stepsCircle; i++) {
      int n = 2 * j * (stepsCircle + 1) + i * 2;
      verts[n][1] = verts[n + 1][1] = a * cos(step * i);
      verts[n][2] = verts[n + 1][2] = a * sin(step * i);
      verts[n][0] = -l / 2 + l * j / stepsTube;
      verts[n + 1][0] = -l / 2 + l * (j + 1) / stepsTube;
      norms[n][1] = norms[n + 1][1] = a * cos(step * i);
      norms[n][2] = norms[n + 1][2] = a * sin(step * i);
      norms[n][0] = norms[n + 1][0] = 0;
    }
  }
  numverts = (stepsCircle + 1) * 2 * stepsTube; 
  wxPrintf(_T("%d vertices, %d triangles\n"), numverts, numverts-2);
}
