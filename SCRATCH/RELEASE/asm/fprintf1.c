/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : fprintf1
 * @created     : Miercuri Oct 12, 2022 11:49:19 EEST
 */

#include "xlsxwriter.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(void)
{
  char  buf[64];
  FILE *f = fmemopen(buf, 64, "w++");
  workbook_new(buf);

  return 0;
}
