/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : pirate
 * @created     : Luni Noi 14, 2022 17:44:08 EET
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  struct pirate {
    char     name[100]; /* real name */
    unsigned booty;     /* in pounds sterling */
    unsigned beard_len; /* in inches */
  } p, blackbeard = {"Edward Teach", 950, 48};

  FILE *out = fopen("data", "w");
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
