/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test3
 * @created     : marţi mai 10, 2022 19:21:17 EEST
 */

#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static inline int fn1(void)
{
  return 0;
}

int fn(void)
{
  return fn1();
}

__attribute__((noreturn)) void error(char *error, ...)
{
  va_list argptr;
  char    string[1024];

  // change stdin to non blocking
  fcntl(0, F_SETFL, fcntl(0, F_GETFL, 0) & ~FNDELAY);

  va_start(argptr, error);
  vsprintf(string, error, argptr);
  va_end(argptr);
  fprintf(stderr, "Error: %s\n", string);

  exit(1);
}

void debug_log(char *file, char *fmt, ...)
{
  va_list     argptr     = {0};
  static char data[1024] = {'\0'};
  int         fd         = 0;

  va_start(argptr, fmt);
  vsprintf(data, fmt, argptr);
  va_end(argptr);
  fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
  write(fd, data, strlen(data));
  close(fd);
}

void fnull(char *file, char *fmt, ...)
{
  __asm__("nop");
}

#ifdef DEBUG
#define DEBUG_LOG debug_log
#define LOG       "log_parcurs"
#else
#define DEBUG_LOG fnull
#define LOG       (void *)0
#endif

double Sys_FloatTime(void)
{
  struct timeval  tp;
  struct timezone tzp;
  static int      secbase;

  gettimeofday(&tp, &tzp);

  if (!secbase) {
    secbase = tp.tv_sec;
    return tp.tv_usec / 1000000.0;
  }

  return (tp.tv_sec - secbase) + tp.tv_usec / 1000000.0;
}

int main(int argc, char *argv[])
{

  printf("%f\n", Sys_FloatTime());

  debug_log("test", "1\n");
  debug_log("test", "2\n");

  struct Route {
    char *a;
    int   x;
    void (*fn)(struct Route *);
  };

  typedef struct work_s {
    struct Route route;
  } work_t;

  work_t        w1;
  struct work_s w2 = {{}};

  w1.route = (struct Route){"a", 1, NULL};

  /* sys_error("error"); */
  int ww = 7;
  ww &= 0x7f;
  printf("%d\n", ww);

  static char end1[] =
      "\x1b[?7h\x1b[40m\x1b[2J\x1b[0;1;41m\x1b[1;1H                QUAKE: The "
      "Doomed Dimension \x1b[33mby \x1b[44mid\x1b[41m Software                 "
      "     \x1b[2;1H  "
      "------------------------------------------------------------------------"
      "----  \x1b[3;1H           CALL 1-800-IDGAMES TO ORDER OR FOR TECHNICAL "
      "SUPPORT                 \x1b[4;1H             PRICE: $45.00 (PRICES MAY "
      "VARY OUTSIDE THE US.)                    \x1b[5;1H                      "
      "                                                          \x1b[6;1H  "
      "\x1b[37mYes! You only have one fourth of this incredible epic. That is "
      "because most   \x1b[7;1H   of you have paid us nothing or at most, very "
      "little. You could steal the     \x1b[8;1H   game from a friend. But we "
      "both know you'll be punished by God if you do.    \x1b[9;1H        "
      "\x1b[33mWHY RISK ETERNAL DAMNATION? CALL 1-800-IDGAMES AND BUY NOW!     "
      "        \x1b[10;1H             \x1b[37mRemember, we love you almost as "
      "much as He does.                   \x1b[11;1H                           "
      "                                                     \x1b[12;1H         "
      "   \x1b[33mProgramming: \x1b[37mJohn Carmack, Michael Abrash, John Cash "
      "               \x1b[13;1H       \x1b[33mDesign: \x1b[37mJohn Romero, "
      "Sandy Petersen, American McGee, Tim Willits         \x1b[14;1H          "
      "           \x1b[33mArt: \x1b[37mAdrian Carmack, Kevin Cloud             "
      "              \x1b[15;1H               \x1b[33mBiz: \x1b[37mJay Wilbur, "
      "Mike Wilson, Donna Jackson                      \x1b[16;1H            "
      "\x1b[33mProjects: \x1b[37mShawn Green   \x1b[33mSupport: "
      "\x1b[37mBarrett Alexander                  \x1b[17;1H              "
      "\x1b[33mSound Effects: \x1b[37mTrent Reznor and Nine Inch Nails         "
      "          \x1b[18;1H  For other information or details on ordering "
      "outside the US, check out the    \x1b[19;1H     files accompanying "
      "QUAKE or our website at http://www.idsoftware.com.      \x1b[20;1H    "
      "\x1b[0;41mQuake is a trademark of Id Software, inc., (c)1996 Id "
      "Software, inc.        \x1b[21;1H     All rights reserved. NIN logo is a "
      "registered trademark licensed to        \x1b[22;1H                 "
      "Nothing Interactive, Inc. All rights reserved.                 "
      "\x1b[40m\x1b[23;1H\x1b[0m";
  static char end2[] = "\x1b[?7h\x1b[40m\x1b[2J\x1b[0;1;41m\x1b[1;1H        "
                       "QUAKE \x1b[33mby \x1b[44mid\x1b[41m Software";

  /* printf("%s\n %s\n", end1, end2); */

  time_t    t  = time(0);
  struct tm tm = *localtime(&t);

  mkdir("path", 0777);
  DEBUG_LOG(LOG, asctime(&tm));

  struct test_s {
    int   x;
    char *a;
  } test[4] = {{1, "a"}, {1, "b"}, {1, "a"}};

  printf("diff: %ld\n", &test[2] - &test[0]);
  printf("diff: %ld\n", *&test[2].a - *&test[0].a);

  char *test1 = "a";
  char *test2 = "a";

  printf("%ld\n", test2 - test1);

  return 0;
}
