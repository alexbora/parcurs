/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : iov2
 * @created     : Marţi Oct 11, 2022 19:35:29 EEST
 */

#include "xlsxwriter.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  char *buf = calloc(1, 8);
  memcpy(buf, "txt", 3);
  int fd = open(buf, O_RDONLY);

  char bf[64];
  memset(bf, '\0', 64);
  read(fd, bf, 3);
  printf("printf %s\n", bf);
  puts("1 ");
  puts(buf);

  char          *b = malloc(64);
  lxw_workbook  *w = workbook_new(b);
  lxw_worksheet *s = workbook_add_worksheet(w, "ws");
  worksheet_write_string(s, 0, 0, "sss", NULL);
  workbook_close(w);

  puts("last ");
  puts(b);
  return 0;
}
