/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : sterge9
 * @created     : Marţi Apr 26, 2022 20:40:57 EEST
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum arms { wp_chainsaw };
enum arms a = wp_chainsaw;

#define PLAYERCOUNT 1

struct Plyr {
  int   weaponowned[2];
  char *message;
} plyr_, *plyr;

struct G {
  struct Plyr *plyr;
} gg, *g;

static bool Cheat_Choppers(void)
{
  if (PLAYERCOUNT != 1) {
    return false;
  }
  g->plyr->weaponowned[wp_chainsaw] = true;
  g->plyr->message                  = "Chainsaw!";
  return true;
}

int main(int argc, char *argv[])
{
  plyr    = &plyr_;
  g       = &gg;
  gg.plyr = plyr;
  Cheat_Choppers();

  printf("%d\n", g->plyr->weaponowned[wp_chainsaw]);
  if (g->plyr->weaponowned[wp_chainsaw])
    printf("%s\n", gg.plyr->message);
  return 0;
}
