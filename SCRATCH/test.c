/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test
 * @created     : duminică feb 27, 2022 10:36:59 EET
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char name2[64], surname2[64], address2[64];
  int id2, id3;

  FILE *fp;
  fp = fopen("test.txt", "r");
  while (fscanf(fp, "%s %s %d.%d %s\n", name2, surname2, &id2, &id3,
                address2) == 5)
    printf("name: %s %s, id: %d %d, address %s\n", name2, surname2, id2, id3,
           address2);

  fclose(fp);
  return 0;
}
