/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : foaie
 * @created     : Tuesday Feb 02, 2021 22:13:00 EET
 */

#include <sys/_types/_u_int8_t.h>
#if defined(_WINDOWS) || defined(_WIN32) || defined(_WIN64)
#error "Leave Bill alone, get an Unix box.\n"
#endif
#include <arpa/inet.h>
#include <assert.h>
#include <limits.h>
#include <locale.h>
#include <netdb.h>
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/_types/_size_t.h>
#include <sys/_types/_ssize_t.h>
#include <sys/ioctl.h>  /* ioctl()  */
#include <sys/socket.h> /* socket, connect */
#include <sys/uio.h>
#include <time.h>
#include <unistd.h>
#ifdef __APPLE__
#include <sys/_types/_ucontext.h>
#include <sys/syslimits.h>
#endif
#include <unistd.h>
#include <xlsxwriter.h>

#define u64 uint_fast64_t

#ifdef LOG
#define log f
#else
#define log stderr
#endif

#ifdef L
#undef stderr
#define stderr f
#endif

#define Testclaim(assertion, returnval)                                        \
  if (!(assertion)) {                                                          \
    fprintf(stderr, #assertion, __LINE__ " failed to be true.  \
              Returning " #returnval "\n");                                    \
    return returnval;                                                          \
  }

#define COL1 (0)
#define COL2 (1)
#define COL3 (2)
#define COL4 (3)
/* #define COL5 (4) */

#define LXW_COLOR_YELLOW_PALE (0xFFFFCA)
#define NELEMS(x)             sizeof(x) / sizeof(x[0])

static struct T {
  unsigned day, month, year;
} current, previous;
static char longdate[128];
/* static unsigned days_pattern[32]; */
static unsigned row;
static char name[256];

static struct Route {
  char *route;
  long km;
  char *obs;
} tmp[128], parcurs[16] = {
                {     "Cluj-Oradea", 321, "Interes Serviciu"},
                {      "Cluj-Turda", 121, "Interes Serviciu"},
                {      "Cluj-Zalau", 156, "Interes Serviciu"},
                {  "Cluj-Baia-Mare", 356, "Interes Serviciu"},
                {   "Cluj-Bistrita", 257, "Interes Serviciu"},
                {        "Cluj-Dej", 101, "Interes Serviciu"},
                {       "Cluj-Cluj",  47, "Interes Serviciu"},
                {     "Acasa-Birou",  30,                " "},
                {     "Acasa-Birou",  30,                " "},
                {     "Acasa-Birou",  30,                " "},
                {     "Acasa-Birou",  30,                " "},
                {     "Acasa-Birou",  30,                " "},
                {"Cluj-Cmp. Turzii", 152, "Interes Serviciu"},
                {    "Cluj-Apahida",  85, "Interes Serviciu"},
                {    "Cluj-Bontida",  92, "Interes Serviciu"},
                {  "Cluj-Satu-Mare", 421, "Interes Serviciu"}
};

static inline unsigned days_in_month(const unsigned month, const unsigned year)
{
  if (month == 4 || month == 6 || month == 9 || month == 11)
    return 30;
  else if (month == 2)
    return (((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29
                                                                      : 28);
  return 31;
}

static inline bool isholiday(const unsigned day, const unsigned month,
                             const unsigned year)
{
  struct tm tm = {.tm_year = (const int) (year - 1900),
                  .tm_mon = (const int) (month - 1),
                  .tm_mday = (const int) day,
                  .tm_isdst = -1};
  mktime(&tm);
  /* if (tm.tm_year != 2022) return true; */

  static const struct {
    unsigned day, mon;
  } hol[2024][16] = {
      [2022] = {{1, 1},
                {2, 1},
                {24, 1},
                {22, 4},
                {24, 4},
                {25, 4},
                {1, 5},
                {1, 5},
                {1, 6},
                {12, 6},
                {13, 6},
                {15, 8},
                {30, 11},
                {1, 12},
                {25, 12},
                {26, 12}},
      [2023] = {{1, 1},
                {24, 1},
                {14, 4},
                {17, 4},
                {1, 5},
                {1, 5},
                {5, 1},
                {15, 8},
                {30, 11},
                {1, 12},
                {25, 12},
                {26, 12} }
  };

  if (tm.tm_wday == 0 || tm.tm_wday == 6) return true;

  size_t size = (sizeof(hol) / sizeof(hol[0]));
  for (size_t i = 0; i < size; i++)
    if (day == hol[tm.tm_year][i].day && month == hol[tm.tm_year][i].mon)
      return true;
  return false;

  struct Holiday {
    struct Year {
      int day, month;
    } year;
  } holiday[32];

  holiday[22] = (struct Holiday){1, 1};
  holiday[tm.tm_year - 2000] = (struct Holiday){1, 1};
}

static inline bool isvacation(const unsigned day, const unsigned month)
{
  struct {
    unsigned day, mon;
  } vacation[] = {
      {day, month}
  };

  size_t size = (sizeof(vacation) / sizeof(vacation[0]));
  for (size_t i = 0; i < size; i++)
    if (day == vacation[i].day && month == vacation[i].mon) return true;
  return false;
}

static inline const char *month_name(const unsigned day, const unsigned month,
                                     const unsigned year)
{
  struct tm tm = {.tm_year = (int) year - 1900,
                  .tm_mon = (int) month - 1,
                  .tm_mday = (const int) day,
                  .tm_isdst = -1};

  /* time_t t = mktime(&tm); */
  static const char *const mths[12] = {"ianuarie",  "februarie", "martie",
                                       "aprilie",   "mai",       "iunie",
                                       "iulie",     "august",    "septembrie",
                                       "octombrie", "noiembrie", "decembrie"};
  return mths[tm.tm_mon];
}

static inline void get_previous(void)
{
  /* time_t r = time(0); */
  struct tm *tm = localtime(&(time_t){time(0)});
  current.day = (unsigned) (tm->tm_mday);
  current.month = (unsigned) (tm->tm_mon + 1);
  current.year = (unsigned) (tm->tm_year + 1900);
  /* printf("day %d\n", current.day); */
  /* printf("month %d\n", current.month); */
  /* printf("year %d\n", current.year); */
  previous = current;
  previous.month--;
  if (previous.month == 0) previous.year--;
  strftime(longdate, 64, "%d.%m.%Y", tm);
}

__attribute__((unused)) static inline void shuffle(int *pattern, const int n)
{
  int i;
  for (i = 0; i < n; i++) { pattern[i] = i; }
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

static inline void random_shuffle(void)
{
  static const size_t n = NELEMS(parcurs);

  for (unsigned i = 0; i < 128; i++) {
    for (unsigned j = 0; j < n; j++) {
      tmp[i] = parcurs[(unsigned long) rand() % n];
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
static inline bool
repeating(struct Route in[] /*similar to "struct Route *in" */)
{
  for (unsigned i = 0; i < 32; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 30) return true;
  }
  return false;
}

/* patchwork */
#define add_vacation(p, i) ((p[i]) = (struct Route){"concediu", 0, "concediu"})

/* inefficient, but clear. See below for optimized verdsion */
/* for optimized version,  see belor return main or git checkout testing */

__pure static const ssize_t fetch(const uint_fast64_t year,
                                  const char buf[static const restrict 1])
{
  struct addrinfo hints = {.ai_family = AF_INET,
                           .ai_socktype = SOCK_STREAM,
                           .ai_protocol = IPPROTO_TCP,
                           .ai_flags = AI_PASSIVE},
                  *res = NULL;
  const char *restrict const host =
      "us-central1-romanian-bank-holidays.cloudfunctions.net";
  int register x = getaddrinfo(host, "80", &hints, &res);
  if (x) return 0;

  const int sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (sockfd < 0) return 0;
  x = connect(sockfd, res->ai_addr, res->ai_addrlen);
  if (x) return 0;
  puts("\n\x1b[32mConnected.\x1b[0m\n");

  char header[256] = {'\0'};
  const int len_header =
      sprintf(header,
              "GET /romanian_bank_holidays/?year=%llu HTTP/1.1\r\nHost: "
              "%s\r\n\r\n",
              year, host);

  const ssize_t sent = send(sockfd, header, (size_t) len_header, 0);
  if (sent <= 0) return 0;

  char *restrict p = (char *restrict) buf;
  const ssize_t received = recv(sockfd, p, 4 * 1024, 0);
  if (received < 1) return 0;
  freeaddrinfo(res);
  res = NULL;
  shutdown(sockfd, SHUT_RDWR);
  close(sockfd);
  return received;
}

__const static ssize_t parse(char **in, ssize_t received)
{
  received -= 14;
  while (received--) {
    if (*(*in)++ == '[') break;
  }
  return received;
}

static inline void array_fill(const char in[static restrict const 1],
                              unsigned row[][4])
{
  const register char *restrict x = (const char *restrict) in;
  u64 k = 0;
  do {
    x = strstr(x, "date");
    if (!x) break;
    unsigned register m = atoi(x + 10);
    unsigned register n = atoi(x + 7);
    while (row[m][k]) k++;
    row[m][k] = n;
    k ^= k;
  } while (x++);
}

void fnull(void) { puts("no holiday\n"); }
void fn(void) { puts("holiday\n"); }

int main(int argc, char *argv[argc + 1])
{
  __asm__ volatile("pushf\n"
                   "orl $0x40000, (%rsp)\n"
                   "popf");

  char *buf = malloc(4096);
  ssize_t received = fetch((uint_fast64_t) previous.year, &buf[0]);
  if (received) parse(&buf, received);
  static unsigned array[13][4] = {{'\0'}};
  array_fill(buf, array);

  /* if (row[1][1]) puts("holiday\n"); */
  /* row[2][1] ? puts("holiday\n") : puts("not holiday\n"); */

  /* printf("%d\n", row[1][0]); */
  /* printf("%d\n", row[1][1]); */
  /* printf("%d\n", row[1][2]); */
  /* printf("%d\n", row[1][3]); */

  void (*pf[13][4])(void);
  for (unsigned i = 0; i <= 12; i++) {
    for (unsigned j = 0; j <= 3; j++) { pf[i][j] = array[i][j] ? fn : fnull; }
  }
  pf[12][1]();
  /* printf("%d\n", row[11][1]); */
  /* printf("%s\n", buf); */

  struct Write {
    lxw_workbook *book;
    int row, col;
    union {
      char *string;
      uint_fast64_t no;
    };
    union {
      void (*write_string)(void);
      void (*write_number)(void);
    };
    lxw_format *format;
  };

  struct Write2 {
    lxw_workbook *book;
    lxw_format *format;
    void *data;
    void (*fn)(void);
    int row, col;
  };
  lxw_workbook *new = workbook_new("new");

  /* struct Write w = {new, 1, 1, .string = "test", fn, NULL}; */
  /* struct Write w5 = {new, 1, 1, .no = 10, fn, NULL}; */
  /* struct Write2 w2 = {new, NULL, (char*)"test", fn, 1, 1}; */
  /* struct Write2 w3 = {new, NULL, malloc(sizeof(int)), fn, 1, 1}; */
  /* memcpy(w3.data, &(int){1}, sizeof(int)); */
  struct Write2 w4 = {new, NULL, malloc(sizeof(int)), fn, 1, 1};

  *((int *) w4.data) = 1;

  workbook_close(new);
  return 0;

  FILE *f = fopen("z", "w++");

  srand((unsigned) time(0));
  do {
    random_shuffle();
  } while (repeating(tmp));

  FILE *file = fopen("km", "r+");
  static unsigned km;

  if (argc < 5) {
    get_previous();
    fscanf(file, "%d", &km);
    /* puts(month_name(dy, m, y)); */
    /* printf("%d\n", k); */
    /* puts("default conf\n"); */
  } else {
    previous.day = 1;
    previous.month = (unsigned) atoi(argv[2]);
    previous.year = (unsigned) atoi(argv[3]);
    km = (unsigned) atoi(argv[4]);
    if (km == 0) fscanf(file, "%d", &km);
    /* printf("%d-%d-%d    %d\n", dy, m, y, k); */
    /* previous.month--; */
    if (previous.month == 0) previous.year--;
    /* puts(month_name(dy, m, y)); */
    /* puts("custom conf\n"); */
  }
  fclose(file);
  /* -------------------------------------------------------------------------------------------
   */
  /* efficency */
  struct Data {
    char route[64], km[64], obs[64];
  } data[32] = {{}};

  const unsigned day = days_in_month(2, 2022);
  for (unsigned i = 1; i <= day; i++) {
    if (isholiday(i, 2, 2022)) tmp[i] = (struct Route){"", 0, ""};
  }

  double pa = 0;
  /* efficency .... compute pattern array and use it here*/
  unsigned i = 0;
  for (i = 1; i <= day; i++) {
    strcpy(data[i].route, tmp[i].route);
    strcpy(data[i].obs, tmp[i].obs);
    if (tmp[i].km == 0) strcpy(data[i].km, "");
    pa += tmp[i].km;
  }
  lxw_workbook *w = workbook_new("test.xlsx");
  lxw_worksheet *s = workbook_add_worksheet(w, "1");

  for (i = 0; i < day; i++) {
    printf("%s\n", data[i].km);
    worksheet_write_string(s, i, 1, data[i].km, NULL);
    worksheet_write_string(s, i, 0, data[i].route, NULL);
  }
  worksheet_write_number(s, i, 1, pa, NULL);
  workbook_close(w);
  /* --------------------------------------------------------------------------------------------------
   */
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
  lxw_workbook_options options = {.constant_memory = LXW_FALSE,
                                  .tmpdir = cwd, /* .tmpdir =
                                                    getcwd(NULL, 0), */
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

  lxw_data_validation *data_validation =
      &(lxw_data_validation){.validate = LXW_VALIDATION_TYPE_ANY,
                             .criteria = LXW_VALIDATION_TYPE_ANY,
                             .ignore_blank = LXW_VALIDATION_OFF,
                             .show_input = LXW_VALIDATION_OFF};

  // Set the properties in the workbook.
  lxw_workbook *workbook = workbook_new_opt("foaie.xlsx", &options);
  /* lxw_workbook* workbook = workbook_new_opt(name, &options); */
  /* lxw_workbook* workbook = workbook_new_opt("foaie.xlsx", &options); */
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
  /* worksheet_merge_range(worksheet, row, COL1, row, COL2, "VOLVO
   * ROMÂNIA",
   */
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
  /* format_set_shrink(format_header); */

  worksheet_write_string(worksheet, row + 12, COL1, "Ziua", format_header);
  worksheet_write_string(worksheet, row + 12, COL2, "Km_parcursi",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL3, "Locul deplasarii",
                         format_header);
  worksheet_write_string(worksheet, row + 12, COL4, "Observatii utilizator",
                         format_header);

  unsigned offset = 13;

  lxw_format *format_local = workbook_add_format(workbook);
  format_set_right(format_local, LXW_BORDER_THIN);
  format_set_bg_color(format_local, LXW_COLOR_YELLOW_PALE);
  format_set_border(format_local, LXW_BORDER_THIN);
  format_set_align(format_local, LXW_ALIGN_VERTICAL_CENTER);
  /* worksheet_set_column(worksheet, 0, 0, strlen("parcursi: "),
   * format_bold);
   */
  /* worksheet_set_column(worksheet, 1, 1, strlen("km parcursi"), NULL);
   */
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
      worksheet_write_number(worksheet, i + offset, COL2, (double) tmp[i].km,
                             format_local);
      worksheet_write_string(worksheet, i + offset, COL4, tmp[i].obs,
                             format_local);
      break;
    case true:
      for (unsigned short m = COL2; m < 4; m++) {
        worksheet_write_string(worksheet, i + offset, m, "", format_local);
      }
      break;
    default: break;
    }
    offset++;
  }

  /* efficency ..... calculate beforehand,  not here */
  unsigned total = 0;
  total = km + parcursi;
  for (unsigned i = 0; i < daysinmonth; i++) { printf("%s\n", tmp[i].route); }

  printf("parcursi: %d\t%d\n", parcursi, total);

  lxw_format *format = workbook_add_format(workbook);
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

  lxw_format *format_footer = workbook_add_format(workbook);
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
  /*                         "***NPC = Norma proprie de consum
   * carburanti", */
  /*                         format_footer); */
  /*   worksheet_merge_range(worksheet, r + 2, 0, r + 3, 3, */
  /*                         "*Km. parcurşi între locuinţă şi serviciu
   * sunt "
   */
  /*                         "consideraţi în interesul serviciului.", */
  /*                         format_footer); */
  /*   worksheet_merge_range(worksheet, r + 3, 0, r + 3, 3, */
  /*                         "Total km Interes Personal		 0", */
  /*                         format_footer); */
  /*   worksheet_merge_range(worksheet, r + 5, 0, r + 5, 3, */
  /*                         "Total km Personal Ratio		 0,0%",
   */
  /*                         format_footer); */

  char data_predarii[128];
  sprintf(data_predarii, "Semnătură utilizator:\t\t\t  Data predarii: %s",
          longdate);

  worksheet_write_string(worksheet, r + 7, COL1, data_predarii, format_footer);
  /* worksheet_merge_range(worksheet, r + 7, 0, r + 6, 3, data_predarii,
   */
  /*                       format_footer); */

  format_set_border(format_footer, LXW_BORDER_NONE);

  worksheet_write_string(worksheet, r + 9, COL1, "……………………………………………………",
                         format_footer);
  /* worksheet_merge_range(worksheet, r + 9, 0, r + 8, 3,
   * "……………………………………………………", */
  /*                       format_footer); */

  file = fopen("km", "w+");
  fprintf(file, "%d", total);
  fclose(file);
  fclose(f);

  workbook_close(workbook);
  printf("%s\n", name);

  return 0;
}

#if 0

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
/* #include <xlsxwriter.h> */
#include <stdbool.h>
static inline int isholiday(const int day, const int month, const int year) {
  struct tm tm = {.tm_year = year - 1900,
                  .tm_mon = month - 1,
                  .tm_mday = day,
                  .tm_isdst = -1};
  mktime(&tm);
  static const struct {
    int day, mon;
  } hol[] = {{1, 1},  {2, 1},   {24, 1}, {30, 4},  {1, 5},
             {2, 5},  {3, 5},   {1, 6},  {20, 6},  {21, 6},
             {15, 8}, {30, 11}, {1, 12}, {25, 12}, {26, 12}};
  if (tm.tm_wday == 0 || tm.tm_wday == 6) return 1;
  size_t size = (sizeof(hol) / sizeof(hol[0]));
  for (size_t i = 0; i < size; i++)
    if (day == hol[i].day && month == hol[i].mon) return 1;
  return 0;
}

#define TOTAL 32
#define COUNT 20
#define RANGE 7

struct Route {
  char* route;
  int km;
  char* obs;
};

void shuffle1(void) { printf("shuffle 1\n"); }
void shuffle2(void) { printf("shuffle 2\n"); }

static inline void shuffle(int* pattern, const int n) {
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

bool repeating(struct Route in[]) {
  for (unsigned i = 0; i < TOTAL; i++) {
    if (in[i + 1].km == in[i].km && in[i].km != 0) return true;
  }
  return false;
}

void generate_struct(struct Route in[]) {
  struct Route tune[COUNT] = {
      {"Brandy", 1, "obs"},         {"Respect", 2, "obs"},
      {"Hey Jude", 3, "obs"},       {"The Twist", 4, "obs"},
      {"Uptown Funk", 5, "obs"},    {"Macarena", 6, "obs"},
      {"Killer Queen", 7, "obs"},   {"Lady", 0, "obs"},
      {"Foolish Games", 0, "obs"},  {"Call Me", 0, "obs"},
      {"Royals", 0, "obs"},         {"The Sign", 0, "obs"},
      {"Happy", 0, "obs"},          {"Billie Jean", 0, "obs"},
      {"My Sharona", 0, "obs"},     {"Family Affair", 0, "obs"},
      {"Hurts So Good", 0, "obs"},  {"Smooth", 0, "obs"},
      {"Mack The Knife", 0, "obs"}, {"No One", 0, "obs"}};

  int recent[COUNT] = {};
  int t, play, cycle = 0, found;

shuffle:
  while (cycle < COUNT) {
    do {
      play = rand() % COUNT;
      found = 0;
      for (t = 0; t < RANGE; t++)
        if (recent[t] == play) found = 1;
    } while (found);

    for (t = COUNT - 1; t > 0; t--) {
      recent[t] = recent[t - 1];
    }
    recent[0] = play;
    cycle++;
  }

  struct Route tmp[TOTAL] = {};
  int iSource = 0;
  for (int i = iSource; i < COUNT; i++) {
    if (iSource >= RANGE) {
      iSource = 0;  // reset if at end of source
    }
    tmp[i] = tune[recent[i]];
  }

  if (repeating(tmp)) goto shuffle;

  for (unsigned i = 0; i < TOTAL; i++) {
    in[i] = tmp[i];
  }
}

struct Write_Data {
  void* data;
  void (*func)(void);
};

void validate_data(struct Write_Data in[], struct Route route[]) {
  struct Write_Data tmp[COUNT];
  for (unsigned i = 0; i < COUNT; i++) {
    if (isholiday(i, 1, 2000)) {
      tmp[i].data = NULL;
      tmp[i].func = &shuffle2;
    } else {
      tmp[i].data = (struct Route*)route + i;
      tmp[i].func = &shuffle1;
    }
  }
  for (unsigned i = 0; i < COUNT; i++) {
    in[i] = tmp[i];
  }
}

void func1(struct Route in[]) {
  static int i = 0;
  printf("%s\n", in[i].route);
  i++;
  /* for (unsigned i = 0; i < COUNT; i++) printf("%s\n", in[i].route); */
}
void func2(struct Route in[]) { puts("---\n"); }

int main() {
  /* varianta 1 */
  /* openssl style */
  struct Route out[TOTAL];
  struct Write_Data data[COUNT];
  do {
    generate_struct(out);
  } while (repeating(out));
  validate_data(data, out);

  puts("\nvarianta 1");
  for (unsigned i = 0; i < COUNT; i++) {
    printf("%s\n", out[i].route);
    data[i].func();
  }

  /* varianta 2 */
  puts("\nvarianta 2");
  void (*fp[COUNT])(struct Route[]);
  for (unsigned i = 0; i < COUNT; i++) {
    if (isholiday(i, 1, 2022))
      fp[i] = &func2;
    else {
      fp[i] = &func1;
    }
  }

  for (unsigned i = 0; i < COUNT; i++) {
    fp[i](out);
  }

  /* varianta 3 */
  /* probabil cea mai buna */
  puts("\nvarianta 3");
  struct Final {
    char *route, km[4], *obs;
  } final[TOTAL];
  for (unsigned i = 0; i < TOTAL; i++) {
    if (isholiday(i, 2, 2022)) out[i] = (struct Route){"---\n", 0, NULL};
  }
  /* core is above */
  for (unsigned i = 0; i < TOTAL; i++) {
    final[i].route = out[i].route;
    final[i].obs = out[i].obs;
    if (out[i].km == 0)
      strcpy(final[i].km, "");
    else {
      sprintf(final[i].km, "%d", out[i].km);
    }
  }

  for (unsigned i = 0; i < TOTAL; i++) {
    printf("%s\t%s\n", out[i].route, final[i].km);
  }

  return 0;

  struct Route tune[COUNT] = {
      {"Brandy", 1, "obs"},         {"Respect", 2, "obs"},
      {"Hey Jude", 3, "obs"},       {"The Twist", 4, "obs"},
      {"Uptown Funk", 5, "obs"},    {"Macarena", 6, "obs"},
      {"Killer Queen", 7, "obs"},   {"Lady", 0, "obs"},
      {"Foolish Games", 0, "obs"},  {"Call Me", 0, "obs"},
      {"Royals", 0, "obs"},         {"The Sign", 0, "obs"},
      {"Happy", 0, "obs"},          {"Billie Jean", 0, "obs"},
      {"My Sharona", 0, "obs"},     {"Family Affair", 0, "obs"},
      {"Hurts So Good", 0, "obs"},  {"Smooth", 0, "obs"},
      {"Mack The Knife", 0, "obs"}, {"No One", 0, "obs"}};

  int recent[COUNT];
  int t, play, cycle = 0, found;

  /* initialize stuff */
  srand((unsigned)time(NULL)); /* seed the randomizer */

  /* Randomly play the tunes and keep track */
  while (cycle < COUNT) {
    do {
      play = rand() % COUNT;
      found = 0;
      for (t = 0; t < RANGE; t++)
        if (recent[t] == play) found = 1;
    } while (found);

    for (t = COUNT - 1; t > 0; t--) {
      recent[t] = recent[t - 1];
    }
    recent[0] = play;
    cycle++;
  }

  struct Route tmp[COUNT];
  int iSource = 0;
  for (int i = iSource; i < COUNT; i++) {
    if (iSource >= RANGE) {
      iSource = 0;  // reset if at end of source

      //      shuffle1();
      /* shuffle(recent, RANGE); */
    }
    /* shuffle(recent, RANGE); */
    tmp[i] = tune[recent[i]];
    //  shuffle2();
  }

  for (unsigned i = 0; i < COUNT; i++) {
    printf("route: %s\n", tmp[i].route);
  }

  /* shuffle(recent, 7); */
  /* for (unsigned i = 0; i < COUNT; i++) { */
  /*   tmp[i] = tune[recent[i]]; */
  /* } */
  /* puts("------\n"); */
  /* for (unsigned i = 0; i < COUNT; i++) { */
  /*   printf("route: %s\n", tmp[i].route); */
  /* } */

  return 0;
  void (*pf[7])(void);

  for (unsigned i = 0; i < 7; i++) {
    if (isholiday(i, 2, 2022))
      pf[i] = &shuffle1;
    else {
      pf[i] = &shuffle2;
    }
  }
  for (unsigned i = 0; i < 7; i++) {
    pf[i]();
  }

  return (0);
}

#define HAVE_ASPRINTF
#ifndef HAVE_ASPRINTF
#error "HAVE_ASPRINTF undefined. I simply refuse to " \
               "compile on a system without asprintf."
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef LOG
#define log f
#else
#define log stderr
#endif

#ifdef L
#undef stderr
#define stderr f
#endif

#define Testclaim(assertion, returnval)                                        \
  if (!(assertion)) {                                                          \
    fprintf(stderr, #assertion " failed to be true.  \
              Returning " #returnval,                                          \
            __LINE__ "\n");                                                    \
    return returnval;                                                          \
  }

#define fileprintf(...) fprintf(f, __VA_ARGS__)
#define doubleprintf(human, machine)                                           \
  do {                                                                         \
    printf human;                                                              \
    fileprintf machine;                                                        \
  } while (0)

int main(int argc, char* argv[]) {
  FILE* f = fopen("z", "w++");
  double x = 1;
  if (x < 2) doubleprintf(("x is negative (%g)\n", x), ("NEGVAL: x=%g\n", x));
    /* int h = 0; */
    /* Testclaim(h == 1, 7); */

    /* fclose(f); */

#define Blankcheck(a)                                                          \
  {                                                                            \
    int aval = (#a[0] == '\0') ? 0 : (a + 0);                                  \
    printf("I understand your input to be %i.\n", aval);                       \
  }

  int n = 0;
  n = !n;
  Blankcheck(2);
  Blankcheck(0);
  printf("n: %d\n", n);

#if defined __STDC_NO_ATOMICS__
  printf("no_atomics\n");
#else
  printf("atomics available\n");
#endif
  return 0;
}
#endif
