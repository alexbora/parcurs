/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : array
 * @created     : Vineri Iul 01, 2022 15:17:18 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int
main()
{

  int  arr1[128] = {[0 ... 125] = 0, [126 ... 127] = 1};
  int* arr2      = arr1 + 3;

  for (int i = 0; i < 6; i++) { printf("%d", arr1[i]); }
}
