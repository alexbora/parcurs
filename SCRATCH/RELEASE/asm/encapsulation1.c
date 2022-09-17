/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : encapsulation1
 * @created     : Sâmbătă Sep 17, 2022 14:06:43 EEST
 */

#include <stdlib.h>
#include <time.h>

static inline long long _get_time(void)
{
  return time(0);
}

long long get_time(void)
{
  /* return _get_time(); */
  return time(0);
}
