/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge8
 * @created     : Duminică Apr 24, 2022 20:35:16 EEST
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STR_(s) #s
#define STR(s)  STR_(s)
#define DEFAULT 100

#define PLAYERCOUNT  1
#define CF_GODMODE   2
#define STSTR_DQDON  "ON"
#define STSTR_DQDOFF "OFF"

struct G {
  struct {
    int   cheats;
    char *message;
    int   health;
    struct {
      int health;
    } * mo;
  } * plyr;
} * g;

static bool Cheat_God(void)
{
  if (PLAYERCOUNT != 1) {
    return false;
  }
  g->plyr->cheats ^= CF_GODMODE;
  if (g->plyr->cheats & CF_GODMODE) {
    if (g->plyr->mo)
      g->plyr->mo->health = 100;

    g->plyr->health  = 100;
    g->plyr->message = STSTR_DQDON;
  } else
    g->plyr->message = STSTR_DQDOFF;
  return true;
}

int main()
{

  g               = (struct G *){0};
  g->plyr         = (struct plyr *){0};
  g->plyr->cheats = 1;

  Cheat_God();
  printf("%s\n", g->plyr->message);

  char *a = STR(DEFAULT);
  a == "100" ? printf("%s\n", a) : 0;

  typedef enum { OK, FAIL } state_t;

  state_t status = OK;
  return 0;
}
