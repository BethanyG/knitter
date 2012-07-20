#ifndef _TEST_GL_CANVAS_
#define _TEST_GL_CANVAS_

#include "header.hpp"
#include "model.hpp"

class TestGLCanvas: public wxGLCanvas {
 public:
  TestGLCanvas(wxWindow *parent, wxWindowID id = wxID_ANY,
               const wxPoint& pos = wxDefaultPosition,
               const wxSize& size = wxDefaultSize, long style = 0,
               const wxString& name = _T("TestGLCanvas"), int *gl_attrib = NULL);

  ~TestGLCanvas(){};

  void OnPaint(wxPaintEvent& event);
  void OnSize(wxSizeEvent& event);
  void OnEraseBackground(wxEraseEvent& event);
  void OnChar(wxKeyEvent& event);
  void OnMouseEvent(wxMouseEvent& event);

  void Init();

  void draw_scene();
  GLfloat get_xrot() {return _xrot;}
  void set_xrot(GLfloat xrot) {_xrot = xrot;}
  GLfloat get_yrot() {return _yrot;}
  void set_yrot(GLfloat yrot) {_yrot = yrot;}
  void draw_surface();

  void set_model(Model* model) {
    _model = model;
    _xrot = 0;
    _yrot = 0;
  }

 private:
  Model* _model;
  GLfloat _xrot;
  GLfloat _yrot;

 public:
  DECLARE_EVENT_TABLE()
};

#endif // _TEST_GL_CANVAS_