#include "settings.hpp"

GLboolean speed_test = GL_FALSE;
GLboolean use_vertex_arrays = GL_FALSE;

GLboolean doubleBuffer = GL_TRUE;

GLboolean smooth = GL_TRUE;
GLboolean lighting = GL_TRUE;

void InitMaterials() {
  static const GLfloat ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
  static const GLfloat diffuse[4] = {0.5f, 1.0f, 1.0f, 1.0f};
  static const GLfloat position0[4] = {0.0f, 0.0f, 20.0f, 0.0f};
  static const GLfloat position1[4] = {0.0f, 0.0f, -20.0f, 0.0f};
  static const GLfloat front_mat_shininess[1] = {60.0f};
  static const GLfloat front_mat_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  static const GLfloat front_mat_diffuse[4] = {0.5f, 0.28f, 0.38f, 1.0f};
  /*
    static const GLfloat back_mat_shininess[1] = {60.0f};
    static const GLfloat back_mat_specular[4] = {0.5f, 0.5f, 0.2f, 1.0f};
    static const GLfloat back_mat_diffuse[4] = {1.0f, 1.0f, 0.2f, 1.0f};
  */
  static const GLfloat lmodel_ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  static const GLfloat lmodel_twoside[1] = {GL_FALSE};
  
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glEnable(GL_LIGHT0);
  
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glEnable(GL_LIGHT1);
  
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
  glEnable(GL_LIGHTING);
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse);
}

void Init() {
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  
  InitMaterials();
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 5.0, 25.0);
  
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -6.0);
  
// #ifdef GL_EXT_vertex_array
//   if (use_vertex_arrays) {
//     glVertexPointerEXT(3, GL_FLOAT, 0, numverts, verts);
//     glNormalPointerEXT(GL_FLOAT, 0, numverts, norms);
//     glEnable(GL_VERTEX_ARRAY_EXT);
//     glEnable(GL_NORMAL_ARRAY_EXT);
//   }
// #endif
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
