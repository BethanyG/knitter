#ifndef _KNITTER_HPP_
#define _KNITTER_HPP_

class MyApp: public wxApp {
 public:
  bool OnInit();
};

#if wxUSE_GLCANVAS

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
  
  DECLARE_EVENT_TABLE()
};

#endif // # wxUSE_GLCANVAS


class MyFrame: public wxFrame {
 public:
  MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
          const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

  virtual ~MyFrame();
  
#if wxUSE_GLCANVAS
  TestGLCanvas *m_canvas;
#endif
  
 private :
  
  void OnExit(wxCommandEvent& event);

  DECLARE_EVENT_TABLE()
};

#endif // _KNITTER_HPP_

