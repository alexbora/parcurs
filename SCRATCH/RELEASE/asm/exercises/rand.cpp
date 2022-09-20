/**
 * @author      : alex (alex@mac.local)
 * @file        : rand
 * @created     : Duminică Iul 17, 2022 17:17:33 EEST
 */

#include <iostream>
#include <random>

int main()
{
  std::random_device                                       dev;
  std::mt19937                                             rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist6(
      0, 127); // distribution in range [1, 6]

  std::cout << dist6(rng) << std::endl;
}
