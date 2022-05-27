/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : excel2
 * @created     : Miercuri Mai 18, 2022 22:17:44 EEST
 */

#include "main.h"

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <xlsxwriter.h>

#if 0

typedef struct Route {
  char *route;
  float km;
  char *obs;
  void (*fx)(struct Route);
} route_t;

route_t rx[32];

void fn(route_t);

typedef struct Work {
  void (*f)(route_t);
  route_t route;
} work_t;
work_t  w1    = {NULL, {"a", 1, "b"}};
route_t route = {"a", 1, "b", fn};
/* work_t  w2 = {NULL, route}; */

#endif

#define LEN_MAX 128u

extern struct Route route_[128];

#define LXW_COLOR_YELLOW_PALE (0xFFFFCA)
#define COL1                  (uint16_t)(0)
#define COL2                  (uint16_t)(1)
#define COL3                  (uint16_t)(2)
#define COL4                  (uint16_t)(3)
/* extern uint32_t row; */
extern int    dayz_in_mon;
extern double km;
extern char  *luna, longdate[128];
extern int    current_year;
extern int    arr[32];

static void wkend(const struct Route *r, lxw_worksheet *s, uint32_t *row,
                  const uint16_t col, double *parcursi, lxw_format *f)
{
  (void)r;
  (void)parcursi;
  uint32_t tmp_row = *row;
  worksheet_write_string(s, *row, col, "", f);
  worksheet_write_string(s, *row, col + 1, "", f);
  worksheet_write_string(s, *row, col + 2, "", f);
  tmp_row++;
  *row = tmp_row;
  /* (*row)++; */
}

static void wday(const struct Route *r, lxw_worksheet *s, uint32_t *row,
                 const uint16_t col, double *parcursi, lxw_format *f)
{
  worksheet_write_number(s, *row, col, (double)r->km, f);
  worksheet_write_string(s, *row, col + 1, r->route, f);
  worksheet_write_string(s, *row, col + 2, r->obs, f);
  (*parcursi) += (unsigned)r->km;
  (*row)++;
}

typedef void (*fn)(const struct Route *, lxw_worksheet *, uint32_t *,
                   const uint16_t, double *, lxw_format *);

typedef struct Params {
  lxw_worksheet *ws;
  uint32_t      *row;
  const uint32_t col;
  double        *parcurs;
  lxw_format    *format;
} params_t;

/* typedef void (*fn)(const struct Route *, params_t *); */

typedef struct Work {
  struct Route r;
  params_t     params;
  fn           func;
} work_t;

work_t fn_array[32];

struct W {
  struct Route r[32];
  fn           func[32];
};

void gen()
{
  fn fn_tmp[2] = {wkend, wday};
  for (unsigned i = 1; i <= dayz_in_mon; i++) {
    fn_array[i].r    = route_[i];
    fn_array[i].func = fn_tmp[arr[i]];
  }
  struct W w1;

  memcpy(&w1.r, &route_, 32);
}

/* char *get_longdate(void); */
int write_excel(void)
{

  /* puts(get_longdate()); */
  /* prepare array */
  /* set data */
  uint32_t row   = 0;
  unsigned total = 0, offset = 13;
  double   parcursi = 0;

  char name[128], worksheet_name[128], data_predarii[128];
  sprintf(name, "foaie_parcurs_B-151-VGT_%s_%d_Alex_Bora.xlsx", luna,
          current_year);
  sprintf(worksheet_name, "%s %d", luna, current_year);
  sprintf(data_predarii, "Semnătură utilizator:\t\t\t  Data predarii: %s",
          longdate);

  lxw_workbook_options options = {.constant_memory = LXW_FALSE,
                                  .tmpdir          = getcwd(NULL, 0),
                                  .use_zip64       = LXW_TRUE};

  /* set properties */
  lxw_doc_properties properties = {
      .title    = name,
      .subject  = "foaie",
      .author   = "Alex Bora",
      .manager  = "tot el",
      .company  = "Volvo",
      .category = "foaie parcurs",
      .keywords = "foaie parcurs",
      .comments = "VERSION 2.0",
      .status   = "Done",
  };

  lxw_data_validation *data_validation =
      &(lxw_data_validation){.validate     = LXW_VALIDATION_TYPE_ANY,
                             .criteria     = LXW_VALIDATION_TYPE_ANY,
                             .ignore_blank = LXW_VALIDATION_OFF,
                             .show_input   = LXW_VALIDATION_OFF};
  /* open workbook */
  lxw_workbook *workbook = workbook_new_opt(name, &options);
  workbook_set_properties(workbook, &properties);

  /* open worksheet and set properties */
  lxw_worksheet *worksheet = workbook_add_worksheet(workbook, worksheet_name);
  worksheet_activate(worksheet);
  worksheet_select(worksheet);
  worksheet_set_first_sheet(worksheet);
  worksheet_set_portrait(worksheet);
  worksheet_set_paper(worksheet, 9);
  worksheet_print_area(worksheet, 0, 0, 90, 5);
  worksheet_fit_to_pages(worksheet, 1, 1);
  worksheet_ignore_errors(worksheet, LXW_IGNORE_NUMBER_STORED_AS_TEXT,
                          "A1:XFD1048576");
  worksheet_ignore_errors(worksheet, LXW_IGNORE_LIST_DATA_VALIDATION,
                          "A1:XFD1048576");
  worksheet_data_validation_range(worksheet, RANGE("A1:XFD1048576"),
                                  data_validation);
  worksheet_set_column(worksheet, 0, 0, strlen("parcursi: "), NULL);
  worksheet_set_column(worksheet, 1, 1, strlen("km parcursi"), NULL);
  worksheet_set_column(worksheet, 2, 10, 20, NULL);
  worksheet_set_default_row(worksheet, 20, 1);
  /* insert logo */
  worksheet_insert_image(worksheet, row + 1, COL4, "logo.png");

  /* add formats */
  lxw_format *format_bold       = workbook_add_format(workbook);
  lxw_format *format_bold_right = workbook_add_format(workbook);
  lxw_format *format_header     = workbook_add_format(workbook);
  lxw_format *format            = workbook_add_format(workbook);
  lxw_format *format_footer     = workbook_add_format(workbook);
  format_set_bold(format_bold);
  format_set_border(format_bold, LXW_BORDER_NONE);
  format_set_align(format_bold_right, LXW_ALIGN_RIGHT);
  format_set_num_format(format_bold_right, "#,#");
  format_set_align(format_header, LXW_ALIGN_CENTER);
  format_set_border(format_header, LXW_BORDER_THIN);
  format_set_left(format_header, LXW_BORDER_THIN);
  format_set_right(format_header, LXW_BORDER_THIN);
  format_set_pattern(format_header, LXW_PATTERN_SOLID);
  format_set_bg_color(format_header, LXW_COLOR_YELLOW_PALE);
  format_set_align(format_header, LXW_ALIGN_VERTICAL_CENTER);
  format_set_num_format(format, "#,#");
  format_set_align(format, LXW_ALIGN_LEFT);
  format_set_border(format, LXW_BORDER_THIN);
  format_set_pattern(format, LXW_PATTERN_SOLID);
  format_set_bg_color(format, LXW_COLOR_YELLOW_PALE);
  format_set_align(format, LXW_ALIGN_RIGHT);
  format_set_align(format_footer, LXW_ALIGN_LEFT);
  format_set_bottom(format_footer, LXW_BORDER_THIN);

  worksheet_write_string(worksheet, row, COL1, "VOLVO ROMÂNIA", format_bold);
  worksheet_write_string(worksheet, row + 1, COL1, "", format_bold);
  worksheet_write_string(worksheet, row + 2, COL1, "FOAIE DE PARCURS",
                         format_bold);
  worksheet_write_string(worksheet, row + 3, COL1, "", format_bold);
  worksheet_write_string(worksheet, row + 4, COL1, "Luna:", format_bold);
  worksheet_write_string(worksheet, row + 5, COL1, "Anul:", format_bold);
  worksheet_write_string(worksheet, row + 6, COL1,
                         "Nume utilizator:", format_bold);
  worksheet_write_string(worksheet, row + 7, COL1,
                         "Nr. Înmatriculare:", format_bold);
  worksheet_write_string(worksheet, row + 8, COL1,
                         "Tipul maşinii:", format_bold);
  worksheet_write_string(worksheet, row + 9, COL1, "NPC", format_bold);

  worksheet_write_string(worksheet, row + 4, COL3, luna, format_bold);

  /* re set format */
  format_set_align(format_bold, LXW_ALIGN_LEFT);

  worksheet_write_number(worksheet, row + 5, COL3, current_year, format_bold);

  worksheet_write_string(worksheet, row + 6, COL3, "Alex Bora", format_bold);
  worksheet_write_string(worksheet, row + 7, COL3, "B 151 VGT", format_bold);
  worksheet_write_string(worksheet, row + 8, COL3, "Renault Megane 1.5 dcii",
                         format_bold);

  worksheet_write_string(worksheet, row + 11, COL1,
                         "Km initiali:", format_bold);

  worksheet_write_number(worksheet, row + 11, COL2, km, format_bold_right);

  worksheet_write_string(worksheet, row + 12, COL1, "Ziua", format_header);
  worksheet_write_string(worksheet, row + 12, COL2, "Km_parcursi",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL3, "Locul deplasarii",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL4, "Observatii utilizator",
                         format_header);

  row += 13;
  int dayz = dayz_in_mon;

  for (unsigned i = 1; i <= dayz; ++i) {
    worksheet_write_number(worksheet, i + offset - 1, COL1, i, format);
  }

  params_t p1 = {worksheet, &row, 1, &parcursi, format};
  /* for (unsigned i = 0; i < dayz; ++i) { */
  /*   w[i].we(&w[i].r, worksheet, &row, 1, &parcursi, format); */
  /* } */

  struct Route *rr = &(struct Route){"a", 1, "b"};

#if 0
  static const int labels[2] = {&&foo - &&foo, &&foo - &&bar};
  goto *(&&foo + labels[1]);
foo:
  worksheet_write_number(worksheet, row, 1, (double)rr->km, format);
  worksheet_write_string(worksheet, row, 2, rr->route, format);
  worksheet_write_string(worksheet, row, 3, rr->obs, format);
  parcursi += (unsigned)rr->km;
  row++;
#endif
bar:

  total = (unsigned)km + (unsigned)parcursi;
  km    = (unsigned)total;

  worksheet_write_string(worksheet, dayz + offset, COL1,
                         "Km parcursi:", format_header);
  worksheet_write_number(worksheet, dayz + offset, COL2, parcursi, format);

  offset++;

  worksheet_write_string(worksheet, dayz + offset, COL1, "Total",
                         format_header);
  worksheet_write_number(worksheet, dayz + offset, COL2, total, format);

  const unsigned r = dayz + offset + 3;
  worksheet_write_string(worksheet, r + 1, COL1,
                         "***NPC = Norma proprie de consum carburanti",
                         format_footer);
  worksheet_write_string(worksheet, r + 2, COL1,
                         "*Km. parcurşi între locuinţă şi serviciu sunt "
                         "consideraţi în interesul serviciului.",
                         format_footer);
  worksheet_write_string(worksheet, r + 3, COL1,
                         "Total km Interes Personal		 0",
                         format_footer);
  worksheet_write_string(worksheet, r + 5, COL1,
                         "Total km Personal Ratio		 0,0%",
                         format_footer);

  worksheet_write_string(worksheet, r + 7, COL1, data_predarii, format_footer);

  /* reset border */
  format_set_border(format_footer, LXW_BORDER_NONE);

  worksheet_write_string(worksheet, r + 9, COL1, "……………………………………………………",
                         format_footer);
  return workbook_close(workbook);
}
