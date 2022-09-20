/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : main6
 * @created     : Joi Iul 21, 2022 18:41:53 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int test(int);
int mask(int);

int main()
{
  char A = 'A';
  char B = 'b';
  /* printf("%c\t%c\t%d\n", A |= ' ', B - 32, ' '); */
  /* printf("%d\n", 0b111); */
  /* test('1'); */

  return mask(0b11000);
}
