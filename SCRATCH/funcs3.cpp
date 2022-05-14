#include <stdint.h>
#include <stdio.h>
#include <time.h>

// time_t is already defined.
struct ditits_t {
  char digits[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', 0};
};

struct ditits_t itoa(uint32_t n) {

  const uint64_t p32 = (uint64_t)(1) << 32;

  struct ditits_t digits;
  char *c = &digits.digits[8];

  do {
    const uint64_t u = (uint64_t)(429496730) * n;
    const uint32_t p = (uint32_t)(u / p32);
    const uint32_t r = (uint32_t)(u % p32) / 429496730;
    n = p;
    *c-- = '0' + (char)(r);
  } while (n);

  return digits;
}

ditits_t itoa2(uint32_t n) {

  ditits_t digits;
  char *c = &digits.digits[8];

  do {
    const uint32_t p = n / 10;
    const uint32_t r = n % 10;
    n = p;
    *c-- = '0' + char(r);
  } while (n);

  return digits;
}

char *itoa3(uint32_t n) {

  static char digits[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', 0};
  char *c = &digits[8];

  do {
    const uint32_t p = n / 10;
    const uint32_t r = n % 10;
    n = p;
    *c-- = '0' + (char)(r);
  } while (n);

  return digits;
}

struct date_t {
  int16_t year;
  uint8_t month;
  uint8_t day;
};

struct date_t to_date(int32_t r) {

  const uint32_t z2 = (uint32_t)(-1468000);
  const uint32_t r2_e3 = (uint32_t)(536895458);

  const uint32_t r0 = r + r2_e3;

  const uint32_t n1 = 4 * r0 + 3;
  const uint32_t q1 = n1 / 146097;
  const uint32_t r1 = n1 % 146097 / 4;

  const uint64_t p32 = (uint64_t)(1) << 32;
  const uint32_t n2 = 4 * r1 + 3;
  const uint64_t u2 = (uint64_t)(2939745) * n2;
  const uint32_t q2 = (uint32_t)(u2 / p32);
  const uint32_t r2 = (uint32_t)(u2 % p32) / 2939745 / 4;

  const uint32_t p16 = (uint32_t)(1) << 16;
  const uint32_t n3 = 2141 * r2 + 197913;
  const uint32_t q3 = n3 / p16;
  const uint32_t r3 = n3 % p16 / 2141;

  const uint32_t y0 = 100 * q1 + q2;
  const uint32_t m0 = q3;
  const uint32_t d0 = r3;

  const uint32_t j = r2 >= 306;
  const uint32_t y1 = y0 + j;
  const uint32_t m1 = j ? m0 - 12 : m0;
  const uint32_t d1 = d0 + 1;

  return {(int16_t)(y1 + z2), (uint8_t)(m1), (uint8_t)(d1)};
}

int main(int argc, char *argv[]) {
  ditits_t d;
  d = itoa(100);
  printf("%s\n", d.digits);

  char *p = d.digits;
  while (*p++ == '0')
    ;
  p -= 2;
  puts(p);

  d = itoa2(7);
  puts(d.digits);

  struct date_t date;
  date = to_date(time(0));

  printf("%d\n", date.day);
  printf("%d\n", date.month);
  printf("%d\n", date.year);

  printf("%s\n", itoa3(89));

  return 0;
}
