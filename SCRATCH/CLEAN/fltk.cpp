/**
 * @author      : alex (alex@mac.local)
 * @file        : fluid
 * @created     : Vineri Mai 05, 2023 16:15:42 EEST
 */

#ifdef USE_GUI
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <cstdio>
extern "C" {
int
mainx(int, char**);
}

Fl_Window*
make_window(int* dimensions, const char* label)
{
  Fl_Window* w = new Fl_Double_Window(dimensions[0], dimensions[1], label);
  w->show();
  return w;
}

int
main(int argc, char* argv[])
{

  int        dim[2] = {800, 400};
  Fl_Window* w      = make_window(dim, NULL);
  Fl::run();
  printf("%s, %s, %s\n", argv[1], argv[2], argv[3]);

  return 0;
}

#else
#endif
