/**
 * @author      : alex (alex@mac.local)
 * @file        : fluid
 * @created     : Vineri Mai 05, 2023 16:15:42 EEST
 */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Window.H>
#include <Fl/Fl_Input_Choice.H>
#include <ctime>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>

extern "C" {
int
mainx(int, const char**);
/* mainx(void*); */
}

class MyGroup : public Fl_Group
{
public:
  MyGroup(int x, int y, int z, int q, const char* l)
      : Fl_Group(x, y, z, q, l){};
  ~MyGroup(){};
};

void
btn_clear_cb(Fl_Widget* o, void* v)
{
  Fl_Input** i = (Fl_Input**) v;
  for (Fl_Input** p = i; *p; p++) (*p)->value("");
}

void
choice_cb(Fl_Widget* o, void* v)
{
  Fl_Choice* in = (Fl_Choice*) o;
  printf("%d\n", in->value());
  Fl_Input**  out    = (Fl_Input**) v;
  const char* mths[] = {"ian", "feb"};
  out[0]->value(mths[in->value()]);

  const char* mth =
      "ian\0feb\0mar\0apr\0mai\0iun\0iul\0aug\0sep\0oct\0nov\bdec\0";

  out[0]->value(mth + (4 * in->value()));

  /* out[0]->value("ian"); */
  /* printf("out 0: %s\n", out[0]->value()); */
}

void
btn_cb(Fl_Widget* o, void* v)
{
  Fl_Input** i = (Fl_Input**) v;

  printf("FLTK: %s %d\n", i[0]->value(), i[0]->size());

  struct Data {
    const char* txt;
    int         len;
  } data[] = {
      {.txt = i[0]->value(), .len = i[0]->size()}
  };

  /* mainx(data); */
  const char* argv[] = {NULL, i[0]->value(), i[1]->value(), i[2]->value()};
  mainx(4, argv);
}

Fl_Window*
make_window(int* dimensions, const char* label, Fl_Input** in)
{
  Fl_Window* w = new Fl_Double_Window(dimensions[0], dimensions[1], label);
  w->begin();

  in[0] = new Fl_Input(200, 100, 200, 30, "Luna: ");
  in[0]->labelfont(FL_COURIER);
  in[0]->labelsize(16);
  in[0]->textsize(16);

  in[1] = new Fl_Input(200, 150, 200, 30, "Anul: ");
  in[1]->labelfont(FL_COURIER);
  in[1]->labelsize(16);
  in[1]->textsize(16);

  in[2] = new Fl_Input(200, 200, 200, 30, "Km initiali: ");
  in[2]->labelfont(FL_COURIER);
  in[2]->labelsize(16);
  in[2]->textsize(16);

  {
    int  f = open("km.txt", O_RDONLY);
    char buf[16];

    while (read(f, buf, 7))
      ;
    buf[5] = '\0';
    close(f);

    in[2]->value(buf);
  }

  Fl_Box* box = new Fl_Box(200, 30, 200, 30, in[2]->value());
  box->labelsize(16);
  box->labelfont(FL_COURIER);

  Fl_Choice* choice_month = new Fl_Choice(200, 250, 64, 30, "Select month: ");
  choice_month->labelfont(FL_COURIER);
  choice_month->labelsize(16);
  choice_month->textsize(16);
  /* choice_month->label("Luna: "); */
  /* choice_month->copy_label("lun"); */
  /* std::vector<const char*> mths; */
  /* std::vector<const char*, 10> v; */
  /* std::vector<std::string> svec; */
  /* std::vector<char*> v = {"a"}; */

  const char* mths[] = {"ian", "feb", "mar", "apr", "mai", "iun", "jul",
                        "aug", "sep", "oct", "nov", "dec", NULL};

  for (const char** p = mths; *p; p++) choice_month->add(*p);

  time_t     t  = time(0);
  struct tm* tm = localtime(&t);
  choice_month->value(tm->tm_mon);
  choice_month->callback(choice_cb, in);

  Fl_Button* btn_ok = new Fl_Button(200, 300, 50, 30, "OK");
  btn_ok->labelfont(FL_COURIER);
  btn_ok->labelsize(16);
  btn_ok->callback(btn_cb, in);

  Fl_Button* btn_clear = new Fl_Button(250, 300, 75, 30, "Clear");
  btn_clear->labelfont(FL_COURIER);
  btn_clear->labelsize(16);
  btn_clear->callback(btn_clear_cb, in);

  w->end();
  w->show();

  return w;
}

int
main(int argc, char* argv[])
{
  Fl::use_high_res_GL();
  Fl::scheme("plastic");

  setenv("TZ", "Europe/Bucharest", 1);
  tzset();

  Fl_Input* input[4];

  int        dim[2] = {800, 400};
  Fl_Window* w      = make_window(dim, "", input);

  return Fl::run();
}
