/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : date
 * @created     : miercuri apr 13, 2022 19:53:43 EEST
 */

#ifndef DATE_H

#define DATE_H

void generate_time(void);
void net_fetch(void);
void process_cmdl(int argc, char **argv);

struct Net {
  int month, day;
};

extern struct Net *h_ptr;
/* extern int         net; */
extern int  current_year;
extern char longdate[64];
extern char luna[16];

extern struct Route tmp;
void                mix();

extern int array[32];

#endif /* end of include guard DATE_H */
