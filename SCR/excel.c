/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : excel
 * @created     : Marţi Apr 19, 2022 19:11:39 EEST
 */

#include "excel.h"
#include "date.h"
#include "main.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xlsxwriter.h>

typedef void (*fx)(const struct Route *, lxw_worksheet *, uint32_t *,
                   const uint16_t, double *, lxw_format *);

struct Work {
  struct Route r;
  fx we;
};

static void wkend(const struct Route *r, lxw_worksheet *s, uint32_t *row,
                  const uint16_t col, double *parcursi, lxw_format *f) {
  (void)r;
  (void)parcursi;
  worksheet_write_string(s, *row, col, "", f);
  worksheet_write_string(s, *row, col + 1, "", f);
  worksheet_write_string(s, *row, col + 2, "", f);
  (*row)++;
}

static void wday(const struct Route *r, lxw_worksheet *s, uint32_t *row,
                 const uint16_t col, double *parcursi, lxw_format *f) {
  worksheet_write_number(s, *row, col, (double)r->km, f);
  worksheet_write_string(s, *row, col + 1, r->route, f);
  worksheet_write_string(s, *row, col + 2, r->obs, f);
  (*parcursi) += (unsigned)r->km;
  (*row)++;
}

static struct Work *prepare_work(void) {
  static struct Work wa[32] = {0};

  for (unsigned i = 0; i < dayz; i++) {
    if (!array[i])
      wa[i] = (struct Work){.r = route_[i], .we = wday};
    else
      wa[i] = (struct Work){.r = {0}, .we = wkend};
  }

  /* for (unsigned i = 0; i < dayz; i++) */
  /* wa[i].f(&wa[i].r); */

  return &wa[0];
}

int write_excel(void) {

  /* prepare array */
  const struct Work *w = prepare_work();

  /* set data */
  uint32_t row = 0;
  const unsigned daysinmonth = dayz;
  unsigned total = 0, offset = 13;
  double parcursi = 0;

  char name[128], worksheet_name[128], data_predarii[128];
  sprintf(name, "foaie_parcurs_B-151-VGT_%s_%d_Alex_Bora.xlsx", luna,
          current_year);
  sprintf(worksheet_name, "%s %d", luna, current_year);
  sprintf(data_predarii, "Semnătură utilizator:\t\t\t  Data predarii: %s",
          longdate);

  lxw_workbook_options options = {.constant_memory = LXW_FALSE,
                                  .tmpdir = getcwd(NULL, 0),
                                  .use_zip64 = LXW_TRUE};

  /* set properties */
  lxw_doc_properties properties = {
      .title = name,
      .subject = "foaie",
      .author = "Alex Bora",
      .manager = "tot el",
      .company = "Volvo",
      .category = "foaie parcurs",
      .keywords = "foaie parcurs",
      .comments = "VERSION 2.0",
      .status = "Done",
  };

  lxw_data_validation *data_validation =
      &(lxw_data_validation){.validate = LXW_VALIDATION_TYPE_ANY,
                             .criteria = LXW_VALIDATION_TYPE_ANY,
                             .ignore_blank = LXW_VALIDATION_OFF,
                             .show_input = LXW_VALIDATION_OFF};
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
  lxw_format *format_bold = workbook_add_format(workbook);
  lxw_format *format_bold_right = workbook_add_format(workbook);
  lxw_format *format_header = workbook_add_format(workbook);
  lxw_format *format = workbook_add_format(workbook);
  lxw_format *format_footer = workbook_add_format(workbook);
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

  for (unsigned i = 1; i <= dayz; ++i) {
    worksheet_write_number(worksheet, i + offset - 1, COL1, i, format);
  }

  for (unsigned i = 0; i < dayz; ++i) {
    w[i].we(&w[i].r, worksheet, &row, 1, &parcursi, format);
  }

  total = (unsigned)km + (unsigned)parcursi;
  km = (unsigned)total;

  worksheet_write_string(worksheet, daysinmonth + offset, COL1,
                         "Km parcursi:", format_header);
  worksheet_write_number(worksheet, daysinmonth + offset, COL2, parcursi,
                         format);

  offset++;

  worksheet_write_string(worksheet, daysinmonth + offset, COL1, "Total",
                         format_header);
  worksheet_write_number(worksheet, daysinmonth + offset, COL2, total, format);

  const unsigned r = daysinmonth + offset + 3;
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