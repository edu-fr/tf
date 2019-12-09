#include <stdio.h>
#include <stdlib.h>
#include <complex.h>

int max_i = 65536;

int main() {
  int i, j, r;
    for (j = -39; j < 39; ++j) {
        for (i = -39; i < 39; ++i){
            //printf(loop(j/40.0-0.5 + i/40.0*I) > max_i ? "*" : " ");
                //r = loop(j/40.0-0.5 + i/40.0*I):
                    complex c = j/40.0-0.5 + i/40.0*I;
                    complex z = c;
                    int i2 = 1;
                    while ((((creal(z))*(creal(z)) + (cimag(z))*(cimag(z))) <= 4.0) && i2++ < max_i)
                        z = z*z + c;
                    r = i2;
                //end r
                printf(r > max_i ? "*" : " ");
            //end printf
            }
            printf("\n");
        }
    return 0;
}

