/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : transparency_test
 * @created     : Marţi Mai 23, 2023 15:52:43 EEST
 */

#include <stdlib.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
extern "C" void
setWindowTransparency(Fl_Window*, void*);

int
main(int argc, char* argv[])
{
  Fl_Window* w = new Fl_Window(600, 400, "test");
  setWindowTransparency(w, NULL);
  w->show();

  return Fl::run();
}
