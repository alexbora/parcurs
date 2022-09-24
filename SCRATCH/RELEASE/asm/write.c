/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : write
 * @created     : Sâmbătă Sep 24, 2022 08:30:50 EEST
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void w(void)
{
  write(1, "a", 1);
}

int main(int argc, char *argv[])
{

  return 0;
}
