/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : epoll
 * @created     : Sâmbătă Noi 05, 2022 13:30:40 EET
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <sys/event.h>

union attr {
  struct is {
    int def;
  } boolt;
  struct data {
    unsigned def;
  } data;
};

int main(int argc, char *argv[])
{
  union attr a;
  a.boolt.def = 7;
  printf("%d\n", a.data.def);

  return 0;
}
