#include "test_gl_canvas.hpp"

BEGIN_EVENT_TABLE(TestGLCanvas, wxGLCanvas)
EVT_SIZE(TestGLCanvas::OnSize)
EVT_PAINT(TestGLCanvas::OnPaint)
EVT_CHAR(TestGLCanvas::OnChar)
EVT_MOUSE_EVENTS(TestGLCanvas::OnMouseEvent)
EVT_ERASE_BACKGROUND(TestGLCanvas::OnEraseBackground)
END_EVENT_TABLE()

TestGLCanvas::TestGLCanvas(wxWindow *parent, wxWindowID id,
                           const wxPoint& pos, const wxSize& size, long style,
                           const wxString& name, int* gl_attrib)
: wxGLCanvas(parent, id, pos, size, style|wxFULL_REPAINT_ON_RESIZE,
             name, gl_attrib) {
}

void TestGLCanvas::Init() {
  static const GLfloat ambient0[4] = {0.5f, 0.5f, 0.5f, 1.0f};
  static const GLfloat diffuse0[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  static const GLfloat position0[4] = {1.0, 1.0, 1.0f, 0.0f};
  static const GLfloat ambient1[4] = {0.05f, 0.05f, 0.05f, 1.0f};
  static const GLfloat diffuse1[4] = {0.25f, 0.25f, 0.25f, 1.0f};
  static const GLfloat position1[4] = {-1.0, -1.0, 1.0f, 0.0f};

  static const GLfloat front_mat_shininess[1] = {60.0f};
  static const GLfloat front_mat_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
//  static const GLfloat front_mat_diffuse[4] = {0.6f, 0.0f, 0.8f, 1.0f};
//  static const GLfloat front_mat_diffuse[4] = {0.58f, 0.2f, 0.038f, 1.0f}; // brown
  static const GLfloat front_mat_diffuse[4] = {0.58f, 0.3f, 0.038f, 1.0f}; // brown-yellow
//  static const GLfloat front_mat_diffuse[4] = {0.89f, 0.61f, 0.11f, 1.0f}; // yellow
//  static const GLfloat front_mat_diffuse[4] = {0.33f, 0.04f, 0.76f, 1.0f}; // blue
  static const GLfloat lmodel_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};

//  glClearColor(0.7f, 0.3f, 0.9f, 0.0f);
  glClearColor(1.0f, 0.94f, 0.695f, 0);

// model  - background
// 68dd21 - 0091e5
// 953217 - fff1b2
// e49b1d - fff1b2
// 7720c1 - fff1b2

  glEnable(GL_DEPTH_TEST);
//  glPolygonMode(GL_FRONT, GL_LINE);
//  glPolygonMode(GL_BACK, GL_LINE);
  glEnable(GL_NORMALIZE);

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
  glLightfv(GL_LIGHT0, GL_POSITION, position0);
  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glEnable(GL_LIGHT1);

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
  glEnable(GL_LIGHTING);

  //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse);

  float r = _model->get_r();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2 * r, _model->get_columns() * 2 * r,
          -2 * r, _model->get_rows() * 2 * r * 0.75,
          -2.0, 25.0);
  //glOrtho(-2, 2, -2, 2, 0.1, 25);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(_model->get_xc(), _model->get_yc(), -6.0);
  //glTranslatef(0, 0, -6.0);
}


void TestGLCanvas::draw_surface() {
  glEnable(GL_AUTO_NORMAL);

//  GLfloat r = 1.0;
//  GLfloat a = 0.25;
//  GLfloat ctrlpoints[19][3] = {
//        {-r, -r, 0},
//        {-r + a, -r, 0}, {-0.25 * r, -0.5 * r - a,  0},
//        {-0.25 * r, -0.5 * r, 0},
//        {-0.25 * r, -0.5 * r + a, 0}, {-0.75 * r, 0.5 * r - a, 0},
//        {-0.75 * r, 0.5 * r, 0},
//        {-0.75 * r, 0.5 * r + a, 0}, {-a, r, 0},
//        {0, r, 0},
//        {a, r, 0}, {0.75 * r, 0.5 * r + a, 0},
//        {0.75 * r, 0.5 * r, 0},
//        {0.75 * r, 0.5 * r - a, 0}, {0.25 * r, -0.5 * r + a, 0},
//        {0.25 * r, -0.5 * r, 0},
//        {0.25 * r, -0.5 * r - a,  0}, {r - a, -r, 0},
//        {r, -r, 0}
//        };
//  glEnable(GL_MAP1_VERTEX_3);
//  glClear(GL_COLOR_BUFFER_BIT);
//  glColor3f(1.0, 1.0, 1.0);
//  int n = 25;
//
//  for (int k = 0; k < 6; ++k) {
//    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[k * 3][0]);
//    glMapGrid1f(n, 0.0, 1.0);
//    glEvalMesh1(GL_LINE, 0, n);
//  }

  glEnable(GL_MAP2_VERTEX_3);
  GLfloat l = 1.35;
  int n = 10;
  GLfloat t = _model->_a;
  GLfloat ctrlpoints2[4][4][3] = {
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
  };


  float delta[2][6][4][4][3] = {{
  {
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}},                       // line 0 of segment 0
    {{0, t * l, t}, {-t, t * l, t}, {-t * l, t, t}, {-t * l, 0, t}},     // line 2 of segment 0
    {{0, t * l, -t}, {-t, t * l, -t}, {-t * l, t, -t}, {-t * l, 0, -t}}, // etc
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}}
  }, {
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}},                       // line 0 of segment 1
    {{-t * l, 0, t}, {-t * l, 0, t}, {-t * l, 0, t}, {-t * l, 0, t}},   // etc
    {{-t * l, 0, -t}, {-t * l, 0, -t}, {-t * l, 0, -t}, {-t * l, 0, -t}},
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}}
  }, {
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}},
    {{-t * l, 0, t}, {-t * l, 0, t}, {0, t * l, t}, {0, t * l, t}},
    {{-t * l, 0, -t}, {-t * l, 0, -t}, {0, t * l, -t}, {0, t * l, -t}},
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}}
  }, {
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}},
    {{0, t * l, t}, {0, t * l, t}, {t * l, 0, t}, {t * l, 0, t}},
    {{0, t * l, -t}, {0, t * l, -t}, {t * l, 0, -t}, {t * l, 0, -t}},
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}}
  }, {
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}},
    {{t * l, 0, t}, {t * l, 0, t}, {t * l, 0, t}, {t * l, 0, t}},
    {{t * l, 0, -t}, {t * l, 0, -t}, {t * l, 0, -t}, {t * l, 0, -t}},
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}}
  }, {
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}},
    {{t * l, 0, t}, {t * l, t, t}, {t, t * l, t}, {0, t * l, t}},
    {{t * l, 0, -t}, {t * l, t, -t}, {t, t * l, -t}, {0, t * l, -t}},
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}}
  }
  }, {
  {
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}},                   // line 0 of segment 0
    {{0, -t * l, -t}, {0, -t * l, -t}, {t * l, 0, -t}, {t * l, 0, -t}}, // line 2 of segment 0
    {{0, -t * l, t}, {0, -t * l, t}, {t * l, 0, t}, {t * l, 0, t}},     // etc
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}}
  }, {
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}},                   // line 0 of segment 1
    {{t * l, 0, -t}, {t * l, 0, -t}, {t * l, 0, -t}, {t * l, 0, -t}},   // etc
    {{t * l, 0, t}, {t * l, 0, t}, {t * l, 0, t}, {t * l, 0, t}},
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}}
  }, {
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}},
    {{t * l, 0, -t}, {t * l, -t, -t}, {t, -t * l, -t}, {0, -t * l, -t}},
    {{t * l, 0, t}, {t * l, -t, t}, {t, -t * l, t}, {0, -t * l, t}},
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}}
  }, {
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}},
    {{0, -t * l, -t}, {-t, -t * l, -t}, {-t * l, -t, -t}, {-t * l, 0, -t}},
    {{0, -t * l, t}, {-t, -t * l, t}, {-t * l, -t, t}, {-t * l, 0, t}},
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}}
  }, {
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}},
    {{-t * l, 0, -t}, {-t * l, 0, -t}, {-t * l, 0, -t}, {-t * l, 0, -t}},
    {{-t * l, 0, t}, {-t * l, 0, t}, {-t * l, 0, t}, {-t * l, 0, t}},
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}}
  }, {
    {{0, 0, -t}, {0, 0, -t}, {0, 0, -t}, {0, 0, -t}},
    {{-t * l, 0, -t}, {-t * l, 0, -t}, {0, -t * l, -t}, {0, -t * l, -t}},
    {{-t * l, 0, t}, {-t * l, 0, t}, {0, -t * l, t}, {0, -t * l, t}},
    {{0, 0, t}, {0, 0, t}, {0, 0, t}, {0, 0, t}}
  }}};

// k - segment of curve
// s - number of line inside one side of segment (semi-tube) k
// i - number of base point on line s
// j - coordinate of base point i

  for (int row = 0; row < _model->get_rows(); ++row) {
  for (int column = 0; column < _model->get_columns(); ++column) {

  for (int k = 0; k < 6; ++k) {
    for (int s = 0; s < 4; ++s) {
      for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
          ctrlpoints2[s][i][j] = _model->_traces[row][column][k * 3 + i][j] + delta[0][k][s][i][j];
        }
      }
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
            0, 1, 12, 4, &ctrlpoints2[0][0][0]);
    glMapGrid2f(n, 0.0, 1.0, n, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, n, 0, n);

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int s = 0; s < 4; ++s) {
          ctrlpoints2[s][i][j] = _model->_traces[row][column][k * 3 + i][j] + delta[1][k][s][i][j];
        }
      }
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
            0, 1, 12, 4, &ctrlpoints2[0][0][0]);
    glMapGrid2f(n, 0.0, 1.0, n, 0.0, 1.0);
    glEvalMesh2(GL_FILL, 0, n, 0, n);
  }

  }
  }
}

void TestGLCanvas::draw_scene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(_yrot, 0.0f, 1.0f, 0.0f);
  glRotatef(_xrot, 1.0f, 0.0f, 0.0f);
  glTranslatef(-_model->get_xc(), -_model->get_yc(), 0.0f);
  glTranslatef(0, 0, 0);
  draw_surface();
  glPopMatrix();
  glFlush();
}

void TestGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
  wxPaintDC dc(this);
#ifndef __WXMOTIF__
  if (!GetContext()) return;
#endif
  SetCurrent();
  Init();
  draw_scene();
  SwapBuffers();
}

void TestGLCanvas::OnSize(wxSizeEvent& event) {
  wxGLCanvas::OnSize(event);
  int w, h;
  GetClientSize(&w, &h);
#ifndef __WXMOTIF__
  if (GetContext())
#endif
  {
    SetCurrent();
    glViewport(0, 0, (GLint) w, (GLint) h);
  }
}

void TestGLCanvas::OnChar(wxKeyEvent& event) {
//  switch(event.GetKeyCode()) {
//    case WXK_ESCAPE:
//      wxTheApp->ExitMainLoop();
//      return;
//
//    case WXK_LEFT:
//      yrot -= 15.0;
//      break;
//
//    case WXK_RIGHT:
//      yrot += 15.0;
//      break;
//
//    case WXK_UP:
//      xrot += 15.0;
//      break;
//
//    case WXK_DOWN:
//      xrot -= 15.0;
//      break;
//
//    case 's': case 'S':
//      smooth = !smooth;
//      if (smooth) {
//        glShadeModel(GL_SMOOTH);
//      } else {
//        glShadeModel(GL_FLAT);
//      }
//      break;
//
//    case 'l': case 'L':
//      lighting = !lighting;
//      if (lighting) {
//        glEnable(GL_LIGHTING);
//      } else {
//        glDisable(GL_LIGHTING);
//      }
//      break;
//
//    default:
//      event.Skip();
//      return;
//  }
//
//  Refresh(false);
}

void TestGLCanvas::OnMouseEvent(wxMouseEvent& event) {
  static int dragging = 0;
  static float last_x, last_y;

  if(event.LeftIsDown()) {
    if(!dragging) {
      dragging = 1;
    } else {
      _yrot += (event.GetX() - last_x) * 1.0;
      _xrot += (event.GetY() - last_y) * 1.0;
      Refresh(false);
    }
    last_x = event.GetX();
    last_y = event.GetY();
  } else dragging = 0;
}

void TestGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event)) {
  // Do nothing, to avoid flashing.
}

