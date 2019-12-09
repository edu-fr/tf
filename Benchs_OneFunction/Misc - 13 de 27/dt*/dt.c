#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum {
  ITERATIONS = 131072,
  size = 2048
};

int main(int argc, char *argv[]) {
  double	*dvec1, *dvec2;
  long i;

  posix_memalign((void**)&dvec1, 16, size * sizeof(double));
  posix_memalign((void**)&dvec2, 16, size * sizeof(double));

  printf( " %i iterations of each test. ", ITERATIONS );
  printf( " inner loop / array size %i.\n", size );

  // With better alias analysis of posix_memalign, we'd avoid reloading
  // dvec1/dvec2 each time through the loop.
  for( i = 0; i < size; i++ ) {
          dvec1[i] = 1.0000001 * cosf((float)(size - i));
          dvec2[i] = 1.0  + 0.0000000001 * sinf((float)i);
  }

  //double_array_divs_variable( dvec1, dvec2 );
  long i2, j;
  for(j = 0; j < ITERATIONS; j++)
    for(i2 = 0; i2 < size; i2++)
      dvec1[i2] /= dvec2[i2];
  
  printf("%f\n", dvec1[0]);
  return 0;
}

