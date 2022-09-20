/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main9
 * @created     : Duminică Iul 31, 2022 13:51:46 EEST
 */

#include <stdio.h>

int ride(void);

int main()
{
  FILE *f = fopen("myfile.txt", "w++");
  ride();
  return 0;
}
