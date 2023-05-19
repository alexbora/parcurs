/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge
 * @created     : Vineri Mai 19, 2023 12:26:20 EEST
 */

#include <stdlib.h>
#include <time.h>

int
main(int argc, char* argv[])
{

  struct tm tmx = *localtime(&(time_t){time(NULL)});
  return 0;
}
