/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge8
 * @created     : Duminică Apr 24, 2022 20:35:16 EEST
 */

#include <stdio.h>
#include <stdlib.h>

#define STR_(s) #s
#define STR(s)  STR_(s)
#define DEFAULT 100

int main()
{

  char *a = STR(DEFAULT);
  a == "100" ? printf("%s\n", a) : 0;

  return 0;
}
