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
#include <_ctype.h>
#include <cstdio>
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

struct tm* __attribute__((constructor)) tim()
{
  setenv("TZ", "Europe/Bucharest", 1);
  tzset();
  time_t     t  = time(0);
  struct tm* tm = localtime(&t);

  puts("constructor");
  return tm;
}

void
btn_clear_cb(Fl_Widget* o, void* v)
{
  Fl_Input** i = (Fl_Input**) v;
  for (Fl_Input** p = i; *p; p++) (*p)->value("");
  o->parent()->redraw();
}

void
choice_cb(Fl_Widget* o, void* v)
{
  Fl_Choice* in = (Fl_Choice*) o;
  /* printf("%d\n", in->value()); */
  Fl_Input** out = (Fl_Input**) v;
  /* const char* mths[] = {"ian", "feb"}; */
  /* out[0]->value(mths[in->value()]); */

  const char* mth =
      "ian\0feb\0mar\0apr\0mai\0iun\0iul\0aug\0sep\0oct\0noi\0dec\0";

  out[0]->value(mth + (4 * in->value()));

  out[0]->textfont(FL_COURIER);
  out[0]->textsize(16);
  /* out[0]->value("ian"); */
  /* printf("out 0: %s\n", out[0]->value()); */
}

void
year_cb(Fl_Widget* o, void* v)
{
  Fl_Choice* in  = (Fl_Choice*) o;
  Fl_Input** out = (Fl_Input**) v;

  const char* year[] = {"2020", "2021", "2022", "2023", "2024", "2025", NULL};

  out[1]->value(year[in->value()]);
  out[1]->textfont(FL_COURIER);
  out[1]->textsize(16);
}

void
btn_cb(Fl_Widget* o, void* v)
{
  Fl_Input** i = (Fl_Input**) v;

  /* printf("FLTK: %s %d\n", i[0]->value(), i[0]->size()); */

  struct Data {
    const char* txt;
    int         len;
  } data[] = {
      {.txt = i[0]->value(), .len = i[0]->size()}
  };
  o->parent()->redraw();
  /* mainx(data); */
  const char* argv[] = {NULL, i[0]->value(), i[1]->value(), i[2]->value()};
  /* printf("%s %s %s\n", i[0]->value(), i[1]->value(), i[2]->value()); */

  mainx(4, argv);
}

void
exit_cb(Fl_Widget* o, void* v)
{
  exit(0);
}

void
add_vacation(Fl_Widget* o, void* v)
{
  Fl_Window* w = new Fl_Window(100, 100, 100, 100, "test");
  w->set_menu_window();
  w->set_modal();
  w->take_focus();
  w->begin();
  Fl_Input* vacation = new Fl_Input(60, 60, 600, 30, "vacation");
  w->end();
  w->show();
  o->parent()->redraw();
}

Fl_Window*
make_window(int* dimensions, const char* label, Fl_Input** in, int argc,
            char** argv)
{

  const time_t           t  = time(0UL);
  const struct tm* const tm = localtime(&t);

  Fl_Window* w = new Fl_Double_Window(dimensions[0], dimensions[1], label);
  w->clear_border();
  w->box(FL_FLAT_BOX);
  w->resizable();
  w->set_active();
  w->set_modal();
  w->begin();

  in[0] = new Fl_Input(200, 100, 200, 30, "Luna: ");
  in[0]->labelfont(FL_COURIER);
  in[0]->labelsize(16);
  in[0]->textsize(16);

  in[1] = new Fl_Input(200, 150, 200, 30, "Anul: ");
  in[1]->labelfont(FL_COURIER);
  in[1]->labelsize(16);
  in[1]->textsize(16);

  {
    Fl_Choice* choice_year = new Fl_Choice(400, 150, 74, 30, "");
    choice_year->labelfont(FL_COURIER);
    choice_year->labelsize(16);
    choice_year->textsize(16);
    choice_year->textfont(FL_COURIER);
    const char* year[] = {"2020", "2021", "2022", "2023", "2024", "2025", NULL};
    for (const char** i = year; *i; i++) choice_year->add(*i);
    if (tm->tm_year - 120 > 0 && tm->tm_year - 120 < 6)
      choice_year->value(tm->tm_year - 120);
    else {
      write(1, "year", strlen("year"));
      abort();
    }
    choice_year->callback(year_cb, in);
    /* choice_year->when(FL_WHEN_CHANGED); */
  }

  {
    in[2] = new Fl_Input(200, 200, 200, 30, "Km initiali: ");
    in[2]->labelfont(FL_COURIER);
    in[2]->labelsize(16);
    in[2]->textsize(16);
    in[2]->textfont(FL_COURIER);
    in[2]->textsize(16);

    int  f = open("km", O_RDONLY);
    char buf[8];
    while (read(f, buf, 8))
      if (!isnumber(*buf)) break;

    /* char* p = buf; */
    /* int   k; */
    /* while (isnumber(*p++)) k++; */
    /* buf[k] = '\0'; */
    /* buf[5] = '\0'; */
    close(f);

    in[2]->value(buf);
  }

  Fl_Box* box__ = new Fl_Box(100, 30, 200, 30, "initial");
  Fl_Box* box   = new Fl_Box(200, 30, 200, 30, in[2]->value());
  box__->labelsize(16);
  box__->labelfont(FL_COURIER);
  box->labelsize(16);
  box->labelfont(FL_COURIER);

  Fl_Choice* choice_month = new Fl_Choice(400, 100, 64, 30, "");
  choice_month->labelfont(FL_COURIER);
  choice_month->labelsize(16);
  choice_month->textsize(16);
  choice_month->textfont(FL_COURIER);
  /* choice_month->label("Luna: "); */
  /* choice_month->copy_label("lun"); */
  /* std::vector<const char*> mths; */
  /* std::vector<const char*, 10> v; */
  /* std::vector<std::string> svec; */
  /* std::vector<char*> v = {"a"}; */

  const char* mths[] = {"ian", "feb", "mar", "apr", "mai", "iun", "jul",
                        "aug", "sep", "oct", "noi", "dec", NULL};

  for (const char** p = mths; *p; p++) choice_month->add(*p);

  choice_month->value(tm->tm_mon);
  choice_month->callback(choice_cb, in);
  /* in[0]->value(mths[tm->tm_mon]); */

  /* char  initial[32]; */
  const char* initial = mths[tm->tm_mon - 1];
  Fl_Box*     box_    = new Fl_Box(320, 200, 200, 30, initial);
  box_->labelfont(FL_COURIER);
  box_->labelsize(16);

  Fl_Button* btn_ok = new Fl_Button(200, 300, 50, 30, "OK");
  btn_ok->labelfont(FL_COURIER);
  btn_ok->labelsize(16);
  btn_ok->callback(btn_cb, in);

  Fl_Button* btn_clear = new Fl_Button(250, 300, 75, 30, "Clear");
  btn_clear->labelfont(FL_COURIER);
  btn_clear->labelsize(16);
  btn_clear->callback(btn_clear_cb, in);

  Fl_Button* btn_exit = new Fl_Button(350, 300, 75, 30, "Exit");
  btn_exit->labelfont(FL_COURIER);
  btn_exit->labelsize(16);
  btn_exit->callback(exit_cb, NULL);

  Fl_Button* btn_add_vacation = new Fl_Button(350, 350, 75, 30, "Add vacation");
  btn_add_vacation->labelfont(FL_COURIER);
  btn_add_vacation->labelsize(16);
  btn_add_vacation->callback(add_vacation, NULL);
  btn_add_vacation->hide();

  w->end();
  w->show();

  return w;
}

int
main(int argc, char* argv[])
{

  setenv("TZ", "Europe/Bucharest", 1);
  tzset();

  Fl::use_high_res_GL();
  Fl::scheme("plastic");

  Fl_Input* input[4];

  int dim[2] = {600, 400};

  Fl_Window* w = make_window(dim, "Foaie parcurs", input, argc, argv);

  return Fl::run();
}
