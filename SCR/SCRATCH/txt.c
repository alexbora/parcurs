

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *arr[] = {
    "ianuarie\0\0",      "februarie\0",     "martie\0\0\0\0",  "aprilie\0\0\0",
    "mai\0\0\0\0\0\0\0", "iunie\0\0\0\0\0", "iulie\0\0\0\0\0", "august\0\0\0\0",
    "septembrie",        "octombrie\0",     "noiembrie\0",     "decembrie\0",
};

char *str =
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0ianuarie\0\0\0\0\0\0\0\0februarie\0\0\0\0"
    "\0\0\0martie\0\0\0\0\0\0\0\0\0\0aprilie\0\0\0\0\0\0\0\0\0mai\0\0\0\0\0\0\0"
    "\0\0\0\0\0\0iunie\0\0\0\0\0\0\0\0\0\0\0iulie\0\0\0\0\0\0\0\0\0\0\0august\0"
    "\0\0\0\0\0\0\0\0\0septembrie\0\0\0\0\0\0octombrie\0\0\0\0\0\0\0noiembrie\0"
    "\0\0\0\0\0\0decembrie\0\0\0\0\0\0\0";

static char *concat(s1, s2) /* Name starts in column one here */
    char *s1,
    *s2;
{ /* Open brace in column one here */
  return NULL;
}
static char *literal_mon(int month) {
  return &"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0ianuarie\0\0\0\0\0\0\0\0februari"
          "e\0\0\0"
          "\0\0\0\0martie\0\0\0\0\0\0\0\0\0\0aprilie\0\0\0\0\0\0\0\0\0mai\0"
          "\0\0\0\0"
          "\0\0\0\0\0\0\0\0iunie\0\0\0\0\0\0\0\0\0\0\0iulie\0\0\0\0\0\0\0\0"
          "\0\0\0au"
          "gust\0\0\0\0\0\0\0\0\0\0septembrie\0\0\0\0\0\0octombrie\0\0\0\0"
          "\0\0\0noi"
          "embrie\0\0\0\0\0\0\0decembrie\0\0\0\0\0\0\0"[16 * month];

  /* (char*)"text" + 16 * 9; */
}
int main(int argc, char *argv[]) {
  for (unsigned i = 0; i < 12; ++i) {
    printf("%ld\n", strlen(arr[i]));
  }
  puts(str + 16 * 10);

  int x = 0;
  int y = 0;

  int z = (x == y) | x;

  printf("X: %d\n", z);

  return 0;
}
