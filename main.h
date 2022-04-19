/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Duminică Apr 17, 2022 14:22:34 EEST
 */

#ifndef MAIN_H
#define MAIN_H

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern int    array[32];
extern double km;

extern struct Route {
  char         *route;
  unsigned long km;
  char         *obs;
} tmp[128];

void date_cmdl(const int, const int, const int);
void date_now(void);
void net_fetch(void);
void generate_time(void);
void mix(void);

#endif /* end of include guard MAIN_H */
