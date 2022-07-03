/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test
 * @created     : Duminică Iul 03, 2022 13:39:20 EEST
 */

#include <string.h>
#define Skipmain
#include "date.c"
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{

  struct Route r1[32] = {{}};

  memset(&r1[0], 0, sizeof(struct Route));

  r1[0].route = "";
  puts(r1[0].route);
  printf("%d\n", r1[0].km);
  return 0;
}
