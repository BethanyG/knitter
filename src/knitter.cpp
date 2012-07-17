#include "header.hpp"
#include "vars.hpp"
#include "settings.hpp"
#include "knitter.hpp"
#include "calculator.hpp"
#include "pattern.hpp"

#if !defined(__WXMSW__) && !defined(__WXPM__)
#include "../img/icons/sample.xpm"
#endif

GLfloat xrot;
GLfloat yrot;

static float xc;
static float yc;

//Model model(0, 0, 0, Pattern("", 0, 0));
Model* model = NULL;

static void DrawSurface() {
    GLint i;
    if (model) {
      for (int k = 0; k < (model->_rows); k++) {
        for (int l = 0; l < (model->_columns); l++) {
          glBegin(GL_TRIANGLE_STRIP);
          for (i = 0; i < model->_numverts[k][l]; i++) {
            glNormal3fv(model->_norms[k][l][i]);
            glVertex3fv(model->_verts[k][l][i]);
          }
          glEnd();
        }
      }
    }
}

static void DrawScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(yrot, 0.0f, 1.0f, 0.0f);
  glRotatef(xrot, 1.0f, 0.0f, 0.0f);
  glTranslatef(-xc, -yc, 0.0f);
  
  DrawSurface();
  
  glPopMatrix();
  
  glFlush();
}

MyFrame *frame = NULL;
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  frame = new MyFrame(NULL, wxT("KNITTER"),
                      wxDefaultPosition, 
                      wxSize(700, 700));
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

  frame->m_canvas = new TestGLCanvas(frame, wxID_ANY, wxDefaultPosition,
                                     wxDefaultSize, 0, _T("TestGLCanvas"), 
                                     gl_attrib );
  frame->Show(true);
  frame->m_canvas->SetCurrent();
    
  Pattern pattern("+++++++++++++++++++++++++", 5, 5);

  float a = 0.15;
  float k = 1.4;
  float r = 0.25;
  fprintf(stderr, "%d %d\n", pattern.get_rows(), pattern.get_columns());
  model = new Model(a, k, r, pattern);
  xc = pattern.get_columns() / 2;
  yc = pattern.get_rows() / 2;
  Init(-0.5, yc * 2 * 4 * r + 0.5, -0.5, xc * 2 * 4 * r + 0.5);

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

/*
 * TestGLCanvas implementation
 */

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
  parent->Show(true);
  SetCurrent();
  
//  /* Make sure server supports the vertex array extension */
//  char* extensions = (char *)glGetString(GL_EXTENSIONS);
//  if (!extensions || !strstr(extensions, "GL_EXT_vertex_array")) {
//    use_vertex_arrays = GL_FALSE;
//  }
}

void TestGLCanvas::OnPaint(wxPaintEvent& WXUNUSED(event)) {
  wxPaintDC dc(this);

#ifndef __WXMOTIF__
  if (!GetContext()) return;
#endif

  SetCurrent();

  DrawScene();
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
  switch(event.GetKeyCode()) {
    case WXK_ESCAPE:
      wxTheApp->ExitMainLoop();
      return;
      
    case WXK_LEFT:
      yrot -= 15.0;
      break;
      
    case WXK_RIGHT:
      yrot += 15.0;
      break;
      
    case WXK_UP:
      xrot += 15.0;
      break;
      
    case WXK_DOWN:
      xrot -= 15.0;
      break;
      
    case 's': case 'S':
      smooth = !smooth;
      if (smooth) {
        glShadeModel(GL_SMOOTH);
      } else {
        glShadeModel(GL_FLAT);
      }
      break;
      
    case 'l': case 'L':
      lighting = !lighting;
      if (lighting) {
        glEnable(GL_LIGHTING);
      } else {
        glDisable(GL_LIGHTING);
      }
      break;

    default:
      event.Skip();
      return;
  }

  Refresh(false);
}

void TestGLCanvas::OnMouseEvent(wxMouseEvent& event) {
  static int dragging = 0;
  static float last_x, last_y;
  
  //printf("%f %f %d\n", event.GetX(), event.GetY(), (int)event.LeftIsDown());
  if(event.LeftIsDown()) {
    if(!dragging) {
      dragging = 1;
    } else {
      yrot += (event.GetX() - last_x)*1.0;
      xrot += (event.GetY() - last_y)*1.0;
      Refresh(false);
    }
    last_x = event.GetX();
    last_y = event.GetY();
  } else dragging = 0;
}

void TestGLCanvas::OnEraseBackground(wxEraseEvent& WXUNUSED(event)) {
  // Do nothing, to avoid flashing.
}

