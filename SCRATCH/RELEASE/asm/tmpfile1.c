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
  /* int fd = open("tmp1.xlsx", O_RDWR | O_CREAT); */
  char *buffer = malloc(1024);
  /* FILE *f = fmemopen(buffer, 64, "w++"); */
  FILE *x = fopen("tmp2.xlsx", "w++");

  // setbuf(x, buffer);
  setbuffer(x, buffer, 64 * 1014);
  fprintf(x, "%s\n", "test___");
  lxw_workbook *w = workbook_new_opt(buffer, NULL);
  workbook_add_worksheet(w, "1");
  printf("%s\n", buffer);
  workbook_close(w);

  return 0;
}
