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

void                           date_cmdl(const int, const int, const int);
__attribute__((noreturn)) void usage(void);
void                           date_now(void);
void                           get_km(void);
void                           write_km(void);

#endif /* end of include guard MAIN_H */
