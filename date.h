/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : date
 * @created     : miercuri apr 13, 2022 19:53:43 EEST
 */

#ifndef DATE_H

#define DATE_H

void generate_time(int, char **);

struct Net {
  int month, day;
};

extern struct Net *h_ptr;
extern int         net;

#endif /* end of include guard DATE_H */
