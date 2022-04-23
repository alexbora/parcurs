/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : date
 * @created     : miercuri apr 13, 2022 19:53:43 EEST
 */

#ifndef DATE_H

#define DATE_H

struct Net {
  int month, day;
};

extern struct Net *h_ptr;
extern int current_year;
extern char longdate[32];
extern char *luna;
extern unsigned dayz;

#endif /* end of include guard DATE_H */
