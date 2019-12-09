#include "stdlib.h"
#include "stdio.h"

#define ARRAY_SIZE 500000
#define NLOOPS1 5
#define NLOOPS2 200

// RNG implemented localy to avoid library incongruences
#ifdef RAND_MAX
#undef RAND_MAX
#endif
#define RAND_MAX 32767
static unsigned long long int next = 1;
 
int main() {
    int i1, j, duplicate;
    int *rndArr;

    next = 1;

	for (i1 = 0; i1 < NLOOPS1; i1++) {
        //rndArr = createRandomArray(ARRAY_SIZE);
        int i2, len;
        int *result;

        len = ARRAY_SIZE + 1;
        result = (int*)malloc(len * sizeof(int));
        for (i2 = 0; i2 < len; i2++)
            result[i2] = i2;
        //result[0] = randInt(1, ARRAY_SIZE);
        int max, min, k1, n;
        min = 1;
        max = ARRAY_SIZE;
        n = (max - min) + 1;
            //k = (int)(n * (rand() / (RAND_MAX + 1.0)));
        next = next * 1103515245 + 12345;
        int auxiliar = (unsigned int)(next / 65536) % RAND_MAX+1;
            //
        k1 = (int)(n * (auxiliar / (RAND_MAX + 1.0)));
        result[0] = (k1 == n) ? k1 + min - 1 : k1 + min;
        //

        //shuffle(result, len);
        
        size_t j, k, i;
        int aux;

        for(i = len-1; i > 0; --i) {
            //k = (int)((i + 1) * (rand() / (RAND_MAX + 1.0)));
            //RAND
                next = next * 1103515245 + 12345;
                int auxiliar2 = (unsigned int)(next / 65536) % RAND_MAX+1;
            //
            k = (int)((i + 1) * (auxiliar2 / (RAND_MAX + 1.0)));
            j = (k == (i + 1)) ? k - 1 : k;
            aux = result[i];
            result[i] = result[j];
            result[j] = aux;
        }
        
        rndArr = result;
        for (j = 0; j < NLOOPS2; j++){
            //duplicate = findDuplicate(rndArr, ARRAY_SIZE+1);
            int result = 0;
            for (int i = 0; i < len; i++){
                result = result ^ (i + 1) ^ rndArr[i];
            }    
            result ^= ARRAY_SIZE + 1;
            duplicate = result;
        }
        free(rndArr);
		printf("Found duplicate: %d\n", duplicate);
	}
    return 0;
}