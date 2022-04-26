/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Duminică Apr 17, 2022 14:22:34 EEST
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>

#ifdef LOG
#undef stderr
#define stderr l
#endif

#ifdef LOG
#define fd open("log", O_CREAT | O_RDWR | O_APPEND, 0777)
#else
#define fd 2 // stderr
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define FIN_MSG "\n\x1b[32m[Task completed]\x1b[0m\n"

extern int array[32];
extern double km;
extern FILE *l;

extern struct Route {
  char *route;
  unsigned long km;
  char *obs;
} route_[128];

void date_cmdl(const int, const int, const int);
void date_now(void);
void net_fetch(const int);
void generate_time(void);
void mix(void);
int write_excel(void);

#endif /* end of include guard MAIN_H */