/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : transparency_test
 * @created     : Marţi Mai 23, 2023 15:52:43 EEST
 */

#include <CoreFoundation/CoreFoundation.h>
#include <iostream>
#include <objc/objc-runtime.h>
#include <objc/objc.h>
#include <stdlib.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#ifdef __cplusplus
extern "C" {
#endif
void
transparency(Fl_Window*, double);
#ifdef __cplusplus
}
#endif

int
main(int argc, char* argv[])
{
  Fl_Window* w = new Fl_Window(600, 400, "test");
  w->set_modal();
  transparency(w, 10 / 255.0);
  w->show();

  return Fl::run();
}
