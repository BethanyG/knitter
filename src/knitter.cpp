#include "header.hpp"
#include "knitter.hpp"
#include "test_gl_canvas.hpp"

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "../img/icons/sample.xpm"
#endif

MyFrame *frame = NULL;
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  frame = new MyFrame(NULL, wxT("KNITTER"),
                      wxDefaultPosition,
                      wxSize(800, 600));
  frame->SetIcon(wxICON(sample));
  wxMenu *fileMenu = new wxMenu;
  fileMenu->Append(wxID_EXIT, _T("E&xit"));
  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append(fileMenu, _T("&File"));
  frame->SetMenuBar(menuBar);

#ifdef __WXMSW__
  int *gl_attrib = NULL;
#else
  int gl_attrib[20] = { WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
                        WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1,
                        WX_GL_DOUBLEBUFFER,
#  if defined(__WXMAC__) || defined(__WXCOCOA__)
                        GL_NONE };
#  else
  None };
#  endif
#endif

//  Pattern pattern("+++++++++++++++++++++++++", 5, 5);
//  Pattern pattern("-----+++++-----+++++-----", 5, 5);
  Pattern pattern("--------++++++++--------++++++++--------++++++++--------++++++++", 8, 8);

  Model* model = new Model(0.17, 1.4, 0.25, pattern);

  frame->m_canvas = new TestGLCanvas(frame, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, 0, _T("TestGLCanvas"),
                                     gl_attrib );
  frame->m_canvas->set_model(model);
  frame->m_canvas->SetCurrent();
  frame->Show(true);
  return true;
}

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
END_EVENT_TABLE()

MyFrame::MyFrame(wxFrame *frame, const wxString& title, const wxPoint& pos,
                 const wxSize& size, long style)
: wxFrame(frame, wxID_ANY, title, pos, size, style) {
  m_canvas = NULL;
}

MyFrame::~MyFrame() {
  delete m_canvas;
}

// Intercept menu commands
void MyFrame::OnExit(wxCommandEvent& WXUNUSED(event)) {
  // true is to force the frame to close
  Close(true);
}

