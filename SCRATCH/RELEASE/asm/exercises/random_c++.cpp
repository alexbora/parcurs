/**
 * @author      : alex (alex@mac.local)
 * @file        : rand
 * @created     : Duminică Iul 17, 2022 17:17:33 EEST
 */

#include <iostream>
#include <random>

unsigned rnd(unsigned *arr, size_t n)
{
  std::random_device                                       dev;
  std::mt19937                                             rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(
      arr[0], n - 1); // distribution in range [1, 6]

  return dist6(rng);
}
#ifndef Skip_main
int main(int argc, char *argv[])
{
  unsigned arr[128];
  for (int i = 0; i < 127; i++)
    arr[i] = i;

  printf("%u\n", rnd(arr, 128));
  return 0;
}
#endif
