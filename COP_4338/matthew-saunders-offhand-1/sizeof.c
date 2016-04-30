#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
  char c;
  unsigned char uc;
  short s;
  unsigned short us;
  int i;
  unsigned int ui;
  long l;
  unsigned long ul;
  long long ll;
  unsigned long long ull;
  float f;
  double d;
  unsigned UMIN = 0;

  printf("char=%d, char_min=%d, char_max=%d\n", sizeof(c), SCHAR_MIN, SCHAR_MAX); 
  printf("uchar=%d, uchar_min=%u, uchar_max=%u\n", sizeof(uc), UMIN, UCHAR_MAX); 
  printf("short=%d, short_min=%d, short_max=%d\n", sizeof(s), SHRT_MIN, SHRT_MAX); 
  printf("ushort=%d, ushort_min=%u, ushort_max=%d\n", sizeof(us), UMIN, USHRT_MAX);
  printf("int=%d, int_min=%d, int_max=%d\n", sizeof(i), INT_MIN, INT_MAX);
  printf("uint=%d, uint_min=%u, uint_max=%u\n", sizeof(ui), UMIN, UINT_MAX);
  printf("long=%d, long_min=%ld, long_max=%ld\n", sizeof(l), LONG_MIN, LONG_MAX);
  printf("ulong=%d, ulong_min=%lu, ulong_max=%lu\n", sizeof(ul), UMIN, ULONG_MAX);
  printf("llong=%d, llong_min=%lld, llong_max=%lld\n", sizeof(ll), LLONG_MIN, LLONG_MAX);
  printf("ullong=%d, ullong_min=%lu, ullong_max=%llu\n", sizeof(ull), UMIN, ULLONG_MAX);
  printf("float=%d, float_min=%e, float_max=%e\n", sizeof(f), FLT_MIN, FLT_MAX);
  printf("double=%d, double_min=%e, double_max=%e\n", sizeof(d), DBL_MIN, DBL_MAX);
  return 0;
}
