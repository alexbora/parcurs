/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : debug1
 * @created     : Duminică Sep 25, 2022 12:50:53 EEST
 */

#include <stdio.h>
#include <stdlib.h>

#define STR_(x)             #x
#define STR(x)              STR_(x)
#define DEBUG_CONFIG_MSG(x) "DEBUG_CONFIG: " x
#define DEBUG_CONFIG_DEF(x) DEBUG_CONFIG_MSG(#x "=" STR(x))

int main(int argc, char *argv[])
{
  printf("%s\n", DEBUG_CONFIG_DEF("test"));
  return 0;
}
