#ifndef _KNITTER_HPP_
#define _KNITTER_HPP_

#include "header.hpp"
#include "knitter.hpp"
#include "calculator.hpp"
#include "pattern.hpp"
#include "test_gl_canvas.hpp"

class MyApp: public wxApp {
 public:
  bool OnInit();
};

class MyFrame: public wxFrame {
 public:
  MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
          const wxSize& size, long style = wxDEFAULT_FRAME_STYLE);

  virtual ~MyFrame();
  
  TestGLCanvas *m_canvas;

 private :
  
  void OnExit(wxCommandEvent& event);

  DECLARE_EVENT_TABLE()
};

#endif // _KNITTER_HPP_

