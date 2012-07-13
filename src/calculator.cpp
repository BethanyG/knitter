#include "calculator.hpp"

void Calculator::GetSurfacePoints() {
  Calculator::GetStraightTube();
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
