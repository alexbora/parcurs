/**
 * @author      : alex (alex@mac.local)
 * @file        : fluid
 * @created     : Vineri Mai 05, 2023 16:15:42 EEST
 */

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Window.H>
#include <cstdio>

extern "C" {
int
mainx(void*);
}

class MyGroup : public Fl_Group
{
public:
  MyGroup(int x, int y, int z, int q, const char* l)
      : Fl_Group(x, y, z, q, l){};
  ~MyGroup(){};
};

void
btn_cb(Fl_Widget* o, void* v)
{
  Fl_Input** i = (Fl_Input**) v;

  printf("%s %d\n", i[0]->value(), i[0]->size());

  struct Data {
    const char* txt;
    int         len;
  } data[4] = {
      {.txt = i[0]->value(), .len = i[0]->size()}
  };

  mainx(data);
}

Fl_Window*
make_window(int* dimensions, const char* label, Fl_Input** in)
{
  Fl_Window* w = new Fl_Double_Window(dimensions[0], dimensions[1], label);
  w->begin();

  in[0] = new Fl_Input(200, 200, 200, 30, "Test");
  in[0]->labelfont(FL_COURIER);
  in[0]->labelsize(16);
  in[0]->textsize(16);

  Fl_Button* btn = new Fl_Button(300, 300, 100, 50, "OK");
  btn->callback(btn_cb, in);

  w->end();
  w->show();

  return w;
}

int
main(int argc, char* argv[])
{

  Fl_Input* input[4];

  Fl::scheme("gtk+");

  int        dim[2] = {800, 400};
  Fl_Window* w      = make_window(dim, "", input);

  return Fl::run();
}
