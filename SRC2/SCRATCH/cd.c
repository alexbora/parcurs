/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : cd
 * @created     : Vineri Mar 18, 2022 15:09:02 EET
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
  FILE *in, *out;
  struct pirate {
    char name[100];
    int booty;     /* in pounds sterling */
    int beard_len; /* in inches */
  } p, blackbeard = {"Edward Teach", 950, 48};
  out = fopen("data", "w");
  if (!out) {
    perror("fopen");
    return 1;
  }
  if (!fwrite(&blackbeard, sizeof(struct pirate), 1, out)) {
    perror("fwrite");
    return 1;
  }
  fclose(out);
  return 0;
}
