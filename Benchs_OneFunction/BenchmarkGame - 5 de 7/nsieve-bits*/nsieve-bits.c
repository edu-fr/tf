/*
** The Great Computer Language Shootout
** http://shootout.alioth.debian.org/
** contributed by Mike Pall
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int bits;

int main(int argc, char **argv)
{
  unsigned int m, sz = 10000 << 12;
  bits *primes = (bits *)malloc((((sz) / 8) + sizeof(bits)));
  if (!primes) return 1;
  for (m = 0; m <= 2; m++) {
    unsigned int i, j, count = 0, n = sz >> m;
    memset(primes, 0xff, (((n) / 8) + sizeof(bits)));
    for (i = 2; i <= n; i++)
      if (((primes)[(i) / (sizeof(bits) * 8)] & (1 << ((i) % (sizeof(bits) * 8))))) {
	count++;
	for (j = i + i; j <= n; j += i)
	  if (((primes)[(j) / (sizeof(bits) * 8)] & (1 << ((j) % (sizeof(bits) * 8))))) (primes)[(j) / (sizeof(bits) * 8)] ^= (1 << ((j) % (sizeof(bits) * 8)));
      }
    printf("Primes up to %8d %8d\n", n, count);
  }
  free(primes);
  return 0;
}