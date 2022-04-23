/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main
 * @created     : Duminică Apr 17, 2022 14:22:34 EEST
 */

#ifndef MAIN_H
#define MAIN_H

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define FIN_MSG       "\n\x1b[32m[Task completed]\x1b[0m\n"

extern int    array[32];
extern double km;

extern struct Route {
  char         *route;
  unsigned long km;
  char         *obs;
} route_[128];

void date_cmdl(const int, const int, const int);
void date_now(void);
void net_fetch(void);
void generate_time(void);
void mix(void);
void write_excel();
void x_error(char *);

static inline char *test(char *a)
{
  return (a);
}

#endif /* end of include guard MAIN_H */
