
#include <stdint.h>
#include <stdio.h>
#include <time.h>

static struct Date {
  int16_t year;
  uint8_t month;
  uint8_t day;
} today;

static void to_date(int32_t r)
{
  const uint32_t z2    = (uint32_t)(-1468000);
  const uint32_t r2_e3 = (uint32_t)(536895458);

  const uint32_t r0 = (uint32_t)((uint32_t)r + r2_e3);

  const uint32_t n1 = 4 * r0 + 3;
  const uint32_t q1 = n1 / 146097;
  const uint32_t r1 = n1 % 146097 / 4;

  const uint64_t p32 = (uint64_t)(1) << 32;
  const uint32_t n2  = 4 * r1 + 3;
  const uint64_t u2  = (uint64_t)(2939745) * n2;
  const uint32_t q2  = (uint32_t)(u2 / p32);
  const uint32_t r2  = (uint32_t)((u2 % p32) / 2939745 / 4);

  const uint32_t p16 = (uint32_t)(1) << 16;
  const uint32_t n3  = 2141 * r2 + 197913;
  const uint32_t q3  = n3 / p16;
  const uint32_t r3  = n3 % p16 / 2141;

  const uint32_t y0 = 100 * q1 + q2;
  const uint32_t m0 = q3;
  const uint32_t d0 = r3;

  const uint32_t j  = r2 >= 306;
  const uint32_t y1 = y0 + j;
  const uint32_t m1 = j ? m0 - 12 : m0;
  const uint32_t d1 = d0 + 1;

  struct Date tmp = {(int16_t)((int16_t)y1 + (int16_t)z2), (uint8_t)(m1),
                     (uint8_t)(d1)};
  today           = tmp;
}

static inline int days_from_civil(int16_t y, const uint8_t m, const uint8_t d)
{
  y -= m <= 2;
  const int era = (y >= 0 ? y : y - 399) / 400;
  const int yoe = (y - era * 400);                                 // [0, 399]
  const int doy = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + d - 1; // [0, 365]
  const int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy; // [0, 146096]
  return era * 146097 + doe - 719468;
}

static inline unsigned long is_multiple_of_100(unsigned n)
{
  const unsigned long multiplier   = 42949673;
  const unsigned long bound        = 42949669;
  const unsigned long max_dividend = 1073741799;
  const unsigned long offset       = max_dividend / 2 / 100 * 100; //  536870800
  return multiplier * (n + offset) < bound;
}

static inline int is_leap(const int16_t y)
{
  return (y & (is_multiple_of_100((const unsigned)y) ? 15 : 3)) == 0;
}

static inline int last_day_of_mon(int year, int mon)
{
  return mon != 2                 ? ((mon ^ (mon >> 3))) | 30
         : is_leap((int16_t)year) ? 29
                                  : 28;
}

static inline int weekday_from_days(const int z)
{
  return (z + 4) % 7;
}

int main()
{
  int days = days_from_civil(2022, 5, 14);
  to_date(days);

  printf("%d %d %d\n", today.day, today.month, today.year);
  printf("%d\n", last_day_of_mon(today.year, today.month));
  printf("%d\n", weekday_from_days(days + 1));

  return 0;
}
