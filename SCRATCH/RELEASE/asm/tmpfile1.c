/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : tmpfile1
 * @created     : Saturday Oct 15, 2022 12:44:51 UTC
 */

#include "xlsxwriter.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = open("tmp1.txt", O_RDWR | O_CREAT);
  char *buffer = malloc(1024);
  FILE *f = fmemopen(buffer, 64, "w++");
  setbuf(f, buffer);
  fprintf(f, "%s\n", "test");
  printf("%s\n", buffer);
  lxw_workbook *w = workbook_new(buffer);
  workbook_close(w);

  return 0;
}
