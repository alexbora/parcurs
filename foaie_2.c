/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : foaie
 * @created     : Tuesday Feb 02, 2021 22:13:00 EET
 */

#if defined(_WINDOWS) || defined(_WIN32) || defined(_WIN64)
#error "Leave Bill alone, get an Unix box.\n"
#endif

#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <sys/_types/_ucontext.h>
#include <sys/syslimits.h>
#endif
#include <unistd.h>
#include <xlsxwriter.h>

#define COL1 (0)
#define COL2 (1)
#define COL3 (2)
#define COL4 (3)
/* #define COL5 (4) */

#define LXW_COLOR_YELLOW_PALE (0xFFFFCA)
#define NELEMS(x) sizeof(x) / sizeof(x[0])

static struct T { unsigned day, month, year; } current, previous;
static char longdate[128];
/* static unsigned days_pattern[32]; */
static unsigned row;
static char name[256];

static struct Route {
  char* route;
  long km;
  char* obs;
} tmp[128], parcurs[16] = {{"Cluj-Oradea", 321, "Interes Serviciu"},
                           {"Cluj-Turda", 121, "Interes Serviciu"},
                           {"Cluj-Zalau", 156, "Interes Serviciu"},
                           {"Cluj-Baia-Mare", 356, "Interes Serviciu"},
                           {"Cluj-Bistrita", 257, "Interes Serviciu"},
                           {"Cluj-Dej", 101, "Interes Serviciu"},
                           {"Cluj-Cluj", 47, "Interes Serviciu"},
                           {"Acasa-Birou", 30, " "},
                           {"Acasa-Birou", 30, " "},
                           {"Acasa-Birou", 30, " "},
                           {"Acasa-Birou", 30, " "},
                           {"Acasa-Birou", 30, " "},
                           {"Cluj-Cmp. Turzii", 152, "Interes Serviciu"},
                           {"Cluj-Apahida", 85, "Interes Serviciu"},
                           {"Cluj-Bontida", 92, "Interes Serviciu"},
                           {"Cluj-Satu-Mare", 421, "Interes Serviciu"}};

static inline unsigned days_in_month(const unsigned month,
                                     const unsigned year) {
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

static inline bool isholiday(const unsigned day, const unsigned month,
                             const unsigned year) {
  struct tm tm = {.tm_year = (const int)(year - 1900),
                  .tm_mon = (const int)(month - 1),
                  .tm_mday = (const int)day,
                  .tm_isdst = -1};
  mktime(&tm);

  static const struct {
    unsigned day, mon;
  } hol[] = {{1, 1},  {2, 1},   {24, 1}, {30, 4},  {1, 5},
             {2, 5},  {3, 5},   {1, 6},  {20, 6},  {21, 6},
             {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12}};

  if (tm.tm_wday == 0 || tm.tm_wday == 6) return true;

  size_t size = (sizeof(hol) / sizeof(hol[0]));
  for (size_t i = 0; i < size; i++)
    if (day == hol[i].day && month == hol[i].mon) return true;
  return false;
}

static inline const char* month_name(const unsigned day, const unsigned month,
                                     const unsigned year) {
  struct tm tm = {.tm_year = (int)year - 1900,
                  .tm_mon = (int)month - 1,
                  .tm_mday = (const int)day,
                  .tm_isdst = -1};

  /* time_t t = mktime(&tm); */
  static const char* mths[12] = {"ianuarie",  "februarie", "martie",
                                 "aprilie",   "mai",       "iunie",
                                 "iulie",     "august",    "septembrie",
                                 "octombrie", "noiembrie", "decembrie"};
  return mths[tm.tm_mon];
}

static inline void get_previous(void) {
  time_t r = time(0);
  struct tm* tm = localtime(&r);
  current.day = (unsigned)(tm->tm_mday);
  current.month = (unsigned)(tm->tm_mon + 1);
  current.year = (unsigned)(tm->tm_year + 1900);
  /* printf("day %d\n", current.day); */
  /* printf("month %d\n", current.month); */
  /* printf("year %d\n", current.year); */
  previous = current;
  previous.month--;
  if (previous.month == 0) previous.year--;
  strftime(longdate, 64, "%d.%m.%Y", tm);
}

__attribute__((unused)) static inline void shuffle(int* pattern, const int n) {
  int i;
  for (i = 0; i < n; i++) {
    pattern[i] = i;
  }
  for (i = n - 1; i > 0; i--) {
    int j;
    j = rand() % (i + 1);
    if (j != i) {
      int swap;
      swap = pattern[j];
      pattern[j] = pattern[i];
      pattern[i] = swap;
    }
  }
}

static inline void random_shuffle(void) {
  static const size_t n = NELEMS(parcurs);

  for (unsigned i = 0; i < 128; i++) {
    for (unsigned j = 0; j < n; j++) {
      tmp[i] = parcurs[(unsigned long)rand() % n];
    }
  }

  int found, play, cycle, k = 0, recent[128];
  found = play = cycle = k;
  memset(&recent, 0, sizeof(recent));

  const static int parc = NELEMS(parcurs), tmp_size = NELEMS(tmp);

  for (; cycle < tmp_size; cycle++) {
    do {
      play = rand() % parc;
      found = 0;
      for (k = 0; k < parc; k++)
        if (recent[k] == play) found = 1;
    } while (found);

    tmp[cycle] = parcurs[play];
  }

  /* int c[tmp_size]; */
  /* shuffle(c, 32); */
  /* for (unsigned i = 0; i < 32; i++) { */
  /*   printf("%d\t", c[i]); */
  /* } */
  /* puts("\n"); */
}
static inline bool repeating(
    struct Route in[] /*similar to "struct Route *in" */) {
  for (unsigned i = 0; i < 32; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 30) return true;
  }
  return false;
}

#define add_vacation(p, i) ((p[i]) = (struct Route){"", 0, ""})

/* inefficient, but clear. See below for optimized verdsion */
int main(int argc, char** argv) {
  srand((unsigned)time(0));
  do {
    random_shuffle();
  } while (repeating(tmp));

  FILE* file = fopen("km2", "r+");
  static unsigned km;

  if (argc < 5) {
    get_previous();
    fscanf(file, "%d", &km);
    /* puts(month_name(dy, m, y)); */
    /* printf("%d\n", k); */
    /* puts("default conf\n"); */
  } else {
    previous.day = 1;
    previous.month = (unsigned)atoi(argv[2]);
    previous.year = (unsigned)atoi(argv[3]);
    km = (unsigned)atoi(argv[4]);
    if (km == 0) fscanf(file, "%d", &km);
    /* printf("%d-%d-%d    %d\n", dy, m, y, k); */
    /* previous.month--; */
    if (previous.month == 0) previous.year--;
    /* puts(month_name(dy, m, y)); */
    /* puts("custom conf\n"); */
  }
  fclose(file);

  /* efficency */
  /* int n = days_in_month(previous.month, previous.year); */
  /* int km_parcursi = 0; */
  /* while (n--) { */
  /*   days_pattern[n] = !isholiday(n, previous.month, previous.year); */
  /*   /1* printf("%d\n", pattern[n]); *1/ */
  /*   switch (days_pattern[n]) { */
  /*     case 0: */
  /*       km_parcursi += tmp[n].km; */
  /*     case 1: */
  /*       break; */
  /*     default: */
  /*       break; */
  /*   } */
  /* } */
  /* printf("%d\n", km_parcursi); */

  /* sprintf(name, "foaie_parcurs_B-151-VGT_%s_Alex_Bora_%s.xlsx",
   * previous->month, */
  /* t->long_date); */

  sprintf(name, "foaie_parcurs_B-151-VGT_%s_%d_Alex_Bora.xlsx",
          month_name(previous.day, previous.month, previous.year),
          previous.year);
  char worksheet_name[32];
  sprintf(worksheet_name, "%s %d",
          month_name(previous.day, previous.month, previous.year),
          previous.year);

  char cwd[PATH_MAX + 1];
  lxw_workbook_options options = {
      .constant_memory = LXW_FALSE,
      .tmpdir = cwd, /* .tmpdir = getcwd(NULL, 0), */
      .use_zip64 = LXW_TRUE};
  /* char* buf = getcwd(NULL, 0); */

  /* free(buf); */
  getcwd(cwd, sizeof(cwd));

  lxw_doc_properties properties = {
      .title = name,
      .subject = "",
      .author = "Alex Bora",
      .manager = "",
      .company = "Volvo",
      .category = "foaie parcurs",
      .keywords = "foaie parcurs",
      .comments = "",
      .status = "Done",
  };
  lxw_data_validation* data_validation = calloc(1, sizeof(lxw_data_validation));
  data_validation->validate = LXW_VALIDATION_TYPE_ANY;
  data_validation->criteria = LXW_VALIDATION_TYPE_ANY;
  data_validation->ignore_blank = LXW_VALIDATION_OFF;
  data_validation->show_input = LXW_VALIDATION_OFF;

  // Set the properties in the workbook.

  /* lxw_workbook* workbook = workbook_new("foaie.xlsx"); */
  // lxw_workbook* workbook = workbook_new_opt(name, &options);
  lxw_workbook* workbook = workbook_new_opt("foaie.xlsx", &options);
  workbook_set_properties(workbook, &properties);
  lxw_worksheet* worksheet = workbook_add_worksheet(workbook, worksheet_name);
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

  lxw_format* format_bold = workbook_add_format(workbook);
  format_set_bold(format_bold);
  format_set_border(format_bold, LXW_BORDER_NONE);

  worksheet_write_string(worksheet, row, COL1, "VOLVO ROMÂNIA", format_bold);
  worksheet_write_string(worksheet, row + 1, COL1, "", format_bold);
  worksheet_write_string(worksheet, row + 2, COL1, "FOAIE DE PARCURS",
                         format_bold);
  worksheet_write_string(worksheet, row + 3, COL1, "", format_bold);
  /* worksheet_merge_range(worksheet, row, COL1, row, COL2, "VOLVO ROMÂNIA", */
  /* format_bold); */

  /* worksheet_merge_range(worksheet, row + 1, COL1, row + 1, COL2, "", */
  /* format_bold); */
  /* worksheet_merge_range(worksheet, row + 2, COL1, row + 2, COL2, */
  /* "FOAIE DE PARCURS", format_bold); */
  /* worksheet_merge_range(worksheet, row + 3, COL1, row + 3, 1, "",
   * format_bold); */
  worksheet_write_string(worksheet, row + 4, COL1, "Luna:", format_bold);
  worksheet_write_string(worksheet, row + 5, COL1, "Anul:", format_bold);
  worksheet_write_string(worksheet, row + 6, COL1,
                         "Nume utilizator:", format_bold);
  worksheet_write_string(worksheet, row + 7, COL1,
                         "Nr. Înmatriculare:", format_bold);
  worksheet_write_string(worksheet, row + 8, COL1,
                         "Tipul maşinii:", format_bold);
  worksheet_write_string(worksheet, row + 9, COL1, "NPC", format_bold);

  worksheet_write_string(
      worksheet, row + 4, COL3,
      month_name(previous.day, previous.month, previous.year), format_bold);

  format_set_align(format_bold, LXW_ALIGN_LEFT);
  worksheet_write_number(worksheet, row + 5, COL3, previous.year, format_bold);

  worksheet_write_string(worksheet, row + 6, COL3, "Alex Bora", format_bold);
  worksheet_write_string(worksheet, row + 7, COL3, "B 151 VGT", format_bold);
  worksheet_write_string(worksheet, row + 8, COL3, "Renault Megane 1.5 dcii",
                         format_bold);

  worksheet_write_string(worksheet, row + 11, COL1,
                         "Km initiali:", format_bold);

  lxw_format* format_bold_right = workbook_add_format(workbook);
  format_set_align(format_bold_right, LXW_ALIGN_RIGHT);
  format_set_num_format(format_bold_right, "#,#");

  worksheet_write_number(worksheet, row + 11, COL2, km, format_bold_right);

  worksheet_set_default_row(worksheet, 20, 1);

  lxw_format* format_header = workbook_add_format(workbook);
  format_set_align(format_header, LXW_ALIGN_CENTER);
  format_set_border(format_header, LXW_BORDER_THIN);
  format_set_left(format_header, LXW_BORDER_THIN);
  format_set_right(format_header, LXW_BORDER_THIN);
  format_set_pattern(format_header, LXW_PATTERN_SOLID);
  format_set_bg_color(format_header, LXW_COLOR_YELLOW_PALE);
  format_set_align(format_header, LXW_ALIGN_VERTICAL_CENTER);
  /* format_set_shrink(format_header); */

  worksheet_write_string(worksheet, row + 12, COL1, "Ziua", format_header);
  worksheet_write_string(worksheet, row + 12, COL2, "Km_parcursi",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL3, "Locul deplasarii",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL4, "Observatii utilizator",
                         format_header);

  unsigned offset = 13;

  lxw_format* format_local = workbook_add_format(workbook);
  format_set_right(format_local, LXW_BORDER_THIN);
  format_set_bg_color(format_local, LXW_COLOR_YELLOW_PALE);
  format_set_border(format_local, LXW_BORDER_THIN);
  format_set_align(format_local, LXW_ALIGN_VERTICAL_CENTER);
  /* worksheet_set_column(worksheet, 0, 0, strlen("parcursi: "), format_bold);
   */
  /* worksheet_set_column(worksheet, 1, 1, strlen("km parcursi"), NULL); */
  /* worksheet_set_column(worksheet, 2, 10, 20, NULL); */
  /* /1* worksheet_set_column(worksheet, 2, 10, 20, NULL); *1/ */

  const unsigned daysinmonth = days_in_month(previous.month, previous.year);
  unsigned parcursi = 0;
  /* efficency .... compute pattern array and use it here*/
  for (unsigned i = 1; i <= daysinmonth; i++) {
    worksheet_write_number(worksheet, i + offset, COL1, i, format_local);
    /* switch (days_pattern[i]) { */
    switch (isholiday(i, previous.month, previous.year) ? 1 : 0) {
      case false:
        parcursi += tmp[i].km;
        worksheet_write_string(worksheet, i + offset, COL3, tmp[i].route,
                               format_local);
        worksheet_write_number(worksheet, i + offset, COL2, (double)tmp[i].km,
                               format_local);
        worksheet_write_string(worksheet, i + offset, COL4, tmp[i].obs,
                               format_local);
        break;
      case true:
        for (unsigned short m = COL2; m < 4; m++) {
          worksheet_write_string(worksheet, i + offset, m, "", format_local);
        }
        break;
      default:
        break;
    }
    offset++;
  }

  /* efficency ..... calculate beforehand,  not here */
  unsigned total = 0;
  total = km + parcursi;
  for (unsigned i = 0; i < daysinmonth; i++) {
    printf("%s\n", tmp[i].route);
  }

  printf("parcursi: %d\t%d\n", parcursi, total);

  lxw_format* format = workbook_add_format(workbook);
  format_set_num_format(format, "#,#");
  format_set_align(format, LXW_ALIGN_LEFT);
  format_set_border(format, LXW_BORDER_THIN);
  format_set_pattern(format, LXW_PATTERN_SOLID);
  format_set_bg_color(format, LXW_COLOR_YELLOW_PALE);
  format_set_align(format, LXW_ALIGN_RIGHT);

  worksheet_write_string(worksheet, daysinmonth + offset, COL1,
                         "Km parcursi:", format_header);
  worksheet_write_number(worksheet, daysinmonth + offset, COL2, parcursi,
                         format);
  offset++;
  worksheet_write_string(worksheet, daysinmonth + offset, COL1, "Total",
                         format_header);
  worksheet_write_number(worksheet, daysinmonth + offset, COL2, total, format);

  lxw_format* format_footer = workbook_add_format(workbook);
  format_set_align(format_footer, LXW_ALIGN_LEFT);
  format_set_bottom(format_footer, LXW_BORDER_THIN);

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

  /*   worksheet_merge_range(worksheet, r + 1, 0, r, 3, */
  /*                         "***NPC = Norma proprie de consum carburanti", */
  /*                         format_footer); */
  /*   worksheet_merge_range(worksheet, r + 2, 0, r + 3, 3, */
  /*                         "*Km. parcurşi între locuinţă şi serviciu sunt " */
  /*                         "consideraţi în interesul serviciului.", */
  /*                         format_footer); */
  /*   worksheet_merge_range(worksheet, r + 3, 0, r + 3, 3, */
  /*                         "Total km Interes Personal		 0", */
  /*                         format_footer); */
  /*   worksheet_merge_range(worksheet, r + 5, 0, r + 5, 3, */
  /*                         "Total km Personal Ratio		 0,0%", */
  /*                         format_footer); */

  char data_predarii[128];
  sprintf(data_predarii, "Semnătură utilizator:\t\t\t  Data predarii: %s",
          longdate);

  worksheet_write_string(worksheet, r + 7, COL1, data_predarii, format_footer);
  /* worksheet_merge_range(worksheet, r + 7, 0, r + 6, 3, data_predarii, */
  /*                       format_footer); */

  format_set_border(format_footer, LXW_BORDER_NONE);

  worksheet_write_string(worksheet, r + 9, COL1, "……………………………………………………",
                         format_footer);
  /* worksheet_merge_range(worksheet, r + 9, 0, r + 8, 3,
   * "……………………………………………………", */
  /*                       format_footer); */

  file = fopen("km2", "w+");
  fprintf(file, "%d", total);
  fclose(file);

  workbook_close(workbook);
  printf("%s\n", name);
  return 0;
}
