/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : arduino1
 * @created     : Monday Oct 17, 2022 17:50:47 UTC
 */

#include <stdio.h>

int main(int argc, char *argv[]) {
  char buffer[16] = {'\0'};
  char *str = "F";
  int i = 0;
  sprintf(buffer, "%02X", (unsigned char)str[i]);
  puts(buffer);
  printf("%s\n", buffer);

  int val = 1;
  scanf("%x", &val);
  printf("val we get : %x\n", val);

  return 0;
}
