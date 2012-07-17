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
  static const GLfloat ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
  static const GLfloat diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  static const GLfloat position0[4] = {7.0, 7.0, 7.0f, 0.0f};

  static const GLfloat front_mat_shininess[1] = {60.0f};
  static const GLfloat front_mat_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
  static const GLfloat front_mat_diffuse[4] = {0.6f, 0.0f, 0.8f, 1.0f};
  static const GLfloat lmodel_ambient[4] = {0.0f, 0.0f, 0.0f, 1.0f};

  glClearColor(0.7f, 0.3f, 0.9f, 0.0f);

  glEnable(GL_DEPTH_TEST);
//  glPolygonMode(GL_FRONT, GL_LINE);
//  glPolygonMode(GL_BACK, GL_LINE);

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

  float r = _model->get_r();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2 * r, _model->get_xc() * 2 * 4 * r + 2 * r,
          -2 * r, _model->get_yc() * 2 * 4 * r + 2 * r,
          0.1, 25.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(_model->get_xc(), _model->get_yc(), -6.0);
}

void TestGLCanvas::draw_surface() {
  GLint i;
  if (_model) {
    for (int k = 0; k < _model->get_rows(); k++) {
      for (int l = 0; l < _model->get_columns(); l++) {
        glBegin(GL_TRIANGLE_STRIP);
        // TODO: rewrite this part - impossible behaviour!
        for (i = 0; i < _model->_numverts[k][l]; i++) {
          glNormal3fv(_model->_norms[k][l][i]);
          glVertex3fv(_model->_verts[k][l][i]);
        }
        glEnd();
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

