#include "settings.hpp"

GLboolean speed_test = GL_FALSE;
GLboolean use_vertex_arrays = GL_FALSE;

GLboolean doubleBuffer = GL_TRUE;

GLboolean smooth = GL_TRUE;
GLboolean lighting = GL_TRUE;

void InitMaterials() {
  static const GLfloat ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  static const GLfloat diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  static const GLfloat position0[4] = {7.0, 7.0, 7.0f, 0.0f};

  static const GLfloat front_mat_shininess[1] = {60.0f};
  static const GLfloat front_mat_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  static const GLfloat front_mat_diffuse[4] = {0.6f, 0.0f, 0.8f, 1.0f};
  static const GLfloat lmodel_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  
  glClearColor(0.7f, 0.3f, 0.9f, 0.0f);
  
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  //glPolygonMode(GL_FRONT, GL_LINE);
  //glPolygonMode(GL_BACK, GL_LINE);
  
  glEnable(GL_NORMALIZE);
  glLightfv(GL_LIGHT5, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glEnable(GL_LIGHT0);
  
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glEnable(GL_LIGHTING);
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse);
}

void Init(float xl, float xr, float yb, float yt) {
  InitMaterials();
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(xl, xr, yb, yt, 0.1, 25.0);  
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef((xl + xr) / 2, (yb + yt) / 2, -6.0);
}

GLenum Args(int argc, wxChar **argv) {
  GLint i;
  
  for (i = 1; i < argc; i++) {
    if (wxStrcmp(argv[i], _T("-sb")) == 0) {
      doubleBuffer = GL_FALSE;
    }
    else if (wxStrcmp(argv[i], _T("-db")) == 0) {
      doubleBuffer = GL_TRUE;
    }
    else if (wxStrcmp(argv[i], _T("-speed")) == 0) {
      speed_test = GL_TRUE;
      doubleBuffer = GL_TRUE;
    }
    else if (wxStrcmp(argv[i], _T("-va")) == 0) {
      use_vertex_arrays = GL_TRUE;
    }
    else {
      wxString msg = _T("Bad option: ");
      msg += argv[i];
      wxMessageBox(msg);
      return GL_FALSE;
    }
  }
  
  return GL_TRUE;
}
