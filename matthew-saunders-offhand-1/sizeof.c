#include <stdio.h>

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

  printf("char=%lu, uchar=%lu\nshort=%lu, ushort=%lu\nint=%lu, uint=%lu\nlong=%lu, ulong=%lu\nllong=%lu, ullong=%lu\nfloat=%lu, double=%lu\n",
	 sizeof(c), sizeof(uc), sizeof(s), sizeof(us), sizeof(i), sizeof(ui),
 	 sizeof(l), sizeof(ul), sizeof(ll), sizeof(ull), sizeof(f), sizeof(double));
  return 0;
}
