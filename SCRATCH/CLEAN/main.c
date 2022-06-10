#include "main.h"

#include <stdlib.h>

extern int           dayz_in_mon;
extern char          attachment[128];
extern unsigned char arr[32];

int main(int argc, char *argv[])
{
  init_time(argc, argv);

  mix();

  get_km(argc > 3 ? argv[argc - 1] : NULL);

  write_excel();

  write_km();

  mail_me(attachment);

  return 0;
}
