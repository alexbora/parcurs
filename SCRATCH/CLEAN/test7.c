/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test7
 * @created     : Joi Iun 02, 2022 21:39:01 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  char buf[1280];
  sprintf(buf, "MIME-Version: 1.0");
  strcat(buf, "Content-Type: multipart/mixed;");
  strcat(buf, "Content-Transfer-Encoding: quoted-printable");
  strcat(buf, "Content-Type: text/plain;");
  strcat(buf, "    name=\"details.txt\" ");
  strcat(buf, "Content-Disposition: attachment;");
  strcat(buf, "\r\n");

  FILE *MailFilePtr = fopen("attachment", "r");
  puts(buf);
  return 0;
}
