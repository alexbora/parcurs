/**
 * @author      : alex (alex@T460)
 * @file        : sterge7
 * @created     : duminică apr 24, 2022 11:46:09 EEST
 */

#include <stdio.h>

struct version_s {
  version_s() { sprintf(string, "%s %s", __DATE__, __TIME__); }
  char string[256];
} version;
