/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : excel
 * @created     : Marţi Apr 19, 2022 19:11:39 EEST
 */

#include "date.h"
#include "excel.h"
#include "main.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <xlsxwriter.h>

int arr[3] = {1, 0, 1};

void (*fp[32])(lxw_worksheet *, uint32_t *, const uint16_t, const char *,
               lxw_format *);

static void wkend(lxw_worksheet *s, uint32_t *row, const uint16_t col,
                  const char *text, lxw_format *f)
{
  (void)text;
  worksheet_write_string(s, *row, col, "", f);
  (*row)++;
}
static void wday(lxw_worksheet *s, uint32_t *row, const uint16_t col,
                 const char *text, lxw_format *f)
{
  worksheet_write_string(s, *row, col, text, f);
  worksheet_write_number(s, *row, col + 1, 1, f);
  worksheet_write_string(s, *row, col + 2, "inte", f);
  (*row)++;
}

struct Work {
  struct {
    char *route;
    float km;
    char *obs;
  };
  void (*write)(lxw_worksheet *, uint32_t *, const uint16_t, struct Work,
                lxw_format *);
};

struct Work2 {
  struct Route *r;
  void (*write)(struct Work *w);
};

void workload()
{
  struct Work w[32];
  for (unsigned i = 0; i < 2; i++) {
    fp[i]   = arr[i] ? wkend : wday;
    w[i].km = arr[i] ? 1 : 0;
    if (arr[i])
      w[i] = (struct Work){tmp[i].route, tmp[i].km, tmp[i].obs, wday};
  }

  struct Work2 w2[2] = {{.r = &(struct Route){NULL, 0, NULL}, NULL}};
}

void write_excel(void)
{
  int  row = 0;
  char name[128], worksheet_name[32];
  sprintf(name, "foaie_parcurs_B-151-VGT_%s_%d_Alex_Bora.xlsx", luna,
          current_year);
  sprintf(worksheet_name, "%s %d", luna, current_year);

  lxw_workbook_options options = {.constant_memory = LXW_FALSE,
                                  .tmpdir          = getcwd(NULL, 0),
                                  .use_zip64       = LXW_TRUE};

  lxw_doc_properties properties = {
      .title    = name,
      .subject  = "foaie",
      .author   = "Alex Bora",
      .manager  = "",
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

  lxw_workbook *workbook = workbook_new_opt(name, &options);

  workbook_set_properties(workbook, &properties);
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

  worksheet_insert_image(worksheet, 1, 3, "logo.png");

  lxw_format *format_bold = workbook_add_format(workbook);
  format_set_bold(format_bold);
  format_set_border(format_bold, LXW_BORDER_NONE);

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

  format_set_align(format_bold, LXW_ALIGN_LEFT);
  worksheet_write_number(worksheet, row + 5, COL3, current_year, format_bold);

  worksheet_write_string(worksheet, row + 6, COL3, "Alex Bora", format_bold);
  worksheet_write_string(worksheet, row + 7, COL3, "B 151 VGT", format_bold);
  worksheet_write_string(worksheet, row + 8, COL3, "Renault Megane 1.5 dcii",
                         format_bold);

  worksheet_write_string(worksheet, row + 11, COL1,
                         "Km initiali:", format_bold);

  lxw_format *format_bold_right = workbook_add_format(workbook);
  format_set_align(format_bold_right, LXW_ALIGN_RIGHT);
  format_set_num_format(format_bold_right, "#,#");

  worksheet_write_number(worksheet, row + 11, COL2, km, format_bold_right);

  worksheet_set_default_row(worksheet, 20, 1);

  lxw_format *format_header = workbook_add_format(workbook);
  format_set_align(format_header, LXW_ALIGN_CENTER);
  format_set_border(format_header, LXW_BORDER_THIN);
  format_set_left(format_header, LXW_BORDER_THIN);
  format_set_right(format_header, LXW_BORDER_THIN);
  format_set_pattern(format_header, LXW_PATTERN_SOLID);
  format_set_bg_color(format_header, LXW_COLOR_YELLOW_PALE);
  format_set_align(format_header, LXW_ALIGN_VERTICAL_CENTER);

  worksheet_write_string(worksheet, row + 12, COL1, "Ziua", format_header);
  worksheet_write_string(worksheet, row + 12, COL2, "Km_parcursi",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL3, "Locul deplasarii",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL4, "Observatii utilizator",
                         format_header);

  workbook_close(workbook);
}
