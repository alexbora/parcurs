/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : simpleform
 * @created     : Miercuri Oct 19, 2022 21:01:31 EEST
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  printf("Content-type: text/html\n\n");
  printf("<html>\n");
  printf("<body>\n");
  printf("<h1>The value entered was: ");
  printf("%s</h1>\n", getenv("QUERY_STRING"));
  printf("</body>\n");
  printf("</html>\n");
  return 0;
}
