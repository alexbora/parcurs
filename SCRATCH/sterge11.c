/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge11
 * @created     : Joi Apr 28, 2022 16:32:07 EEST
 */

#include <stdio.h>
#include <stdlib.h>

static const char read_str[] =
    "0SV 0SN 0MO 0WF 0MT 0MP 0SW 1SP 1VO 1CC 1CA 1CB 1ST 1MF 1CL 1SZ 1SS 1AZ "
    "1AS 1BZ 1BS 1VZ 1VS 1MZ 1MS 2SP 2VO 2CC 2CA 2CB 2ST 2MF 2CL 2SZ 2SS 2AZ "
    "2AS 2BZ 2BS 2VZ 2VS 2MZ 2MS";

int main(int argc, char *argv[])
{
  puts(read_str + 1);
  printf("\n%ld\n", (read_str + 5 - read_str) / 4);
  return 0;
}
