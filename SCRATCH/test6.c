/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : test6
 * @created     : Vineri Mai 27, 2022 20:23:43 EEST
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *functionId;
  void (*callback)(void *data);
  char *name;
  char *description;
} Function;

typedef struct {
  Function *fArr;
  size_t    used;
  size_t    size;
} Array;

void initFunctionArray(Array *fa, size_t initialSize);
void insertFunctionArray(Array *fa, Function f);

Array functionArray;

static void function1(void *vp)
{
  int *i = vp;
  printf("PRINT: %d\n", *i);
}

static void function2(void *vp)
{
  char *s = vp;
  printf("PRINT: %s\n", s);
}

static void addFunction(Function f)
{
  insertFunctionArray(&functionArray, f);
}

int main(void)
{
  initFunctionArray(&functionArray, 5);

  // create new struct for function and assign function to callback member
  Function fun;
  fun.name        = "Function1";
  fun.functionId  = "FUNCTION1";
  fun.description = "Description for Function 1";
  fun.callback = &function1; // <-- doesn't seem to matter if I assign it as a
                             // value or as a pointer?!

  Function fun2;
  fun2.name        = "Function2";
  fun2.functionId  = "FUNCTION2";
  fun2.description = "Description for Function 2";
  fun2.callback    = &function2;

  fun2.callback("{fun:\"test\"}");

  int v = 17;
  fun.callback(&v);

  // store functions in array
  addFunction(fun);
  addFunction(fun2);

  for (size_t i = 0; i < functionArray.used; i++) {
    printf("PRINT: %s (%p)\n", functionArray.fArr[i].functionId,
           (void *)functionArray.fArr[i].callback);
    functionArray.fArr[i].callback("777");
  }

  return 0;
}

void initFunctionArray(Array *fa, size_t initialSize)
{
  fa->fArr = (Function *)malloc(initialSize * sizeof(Function));
  fa->used = 0;
  fa->size = initialSize;
  for (size_t i = 0; i < initialSize; i++) {
    memset(&fa->fArr[i], 0, sizeof(Function));
  }
}

void insertFunctionArray(Array *fa, Function f)
{
  if (fa->used == fa->size) {
    fa->size *= 2;
    fa->fArr = (Function *)realloc(fa->fArr, fa->size * sizeof(Function));
  }
  // Copy name
  fa->fArr[fa->used].name = (char *)malloc(strlen(f.name) + 1);
  strcpy(fa->fArr[fa->used].name, f.name);
  // Copy ID
  fa->fArr[fa->used].functionId = f.functionId;
  // Fix!
  fa->fArr[fa->used].callback = f.callback;
  fa->used++;
}
