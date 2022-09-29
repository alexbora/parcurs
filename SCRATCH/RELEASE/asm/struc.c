/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : struc
 * @created     : Joi Sep 29, 2022 18:32:17 EEST
 */

#include <stdlib.h>

// Your program headers that define the structs here
#include <stddef.h>
#include <stdio.h>

#define OFFSET(x, str, mem)                                                    \
  printf("#define " #x " %d\n", (int)offsetof(str, mem))
#define SIZE(x, str)   printf("#define " #x " %d\n", (int)sizeof(str))
#define HEADER_START() printf("#ifndef ASM_OFFSET_H\n#define ASM_OFFSET_H\n")
#define HEADER_END()   printf("#endif\n")

int main(int argc, char *argv[])
{

  HEADER_START();

  char *struct_name;
  char *struct_name_member_name;
  char *member_name;

  OFFSET(struct_name_member_name, struct_name,
         member_name); // Substitute your struct name and member name here

  SIZE(struct_name_size,
       struct_name); // This macro is to get the size of a struct

  HEADER_END();

  return 0;
}
