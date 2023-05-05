/**
 * @author      : alex (alex@mac.local)
 * @file        : fluid
 * @created     : Vineri Mai 05, 2023 16:15:42 EEST
 */

#ifdef USE_GUI
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <cstdio>
extern "C" {
int
mainx(int, char**);
}

int
main(int argc, char* argv[])
{

  printf("%s, %s, %s\n", argv[1], argv[2], argv[3]);

  return 0;
}

#else
#endif
