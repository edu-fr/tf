#include <stdio.h>
#include <string.h>

void *malloc(size_t);

typedef unsigned short UChar;

static UChar staticData[]  = {'H', 'E', 'L', 'L', 'O', ' ', 'W', 'O', 'R', 'L', 'D', '!', 'H', 'E', 'L', 'L'};
static const size_t staticDataLength = sizeof(staticData) / sizeof(staticData[0]);

int main(int argc, char **argv)
{
  size_t numberOfIterations;
  for (numberOfIterations = 0; numberOfIterations < 32; numberOfIterations++){
    //doTest(i);
      const size_t numberOfCharacters = numberOfIterations;
      const size_t testDataLength = ((numberOfCharacters + staticDataLength - 1) / staticDataLength) * staticDataLength;
      UChar* testData = malloc(sizeof(UChar) * testDataLength);
      size_t i;
      for (i = 0; i < testDataLength; i += staticDataLength)
        memcpy(testData + i, staticData, staticDataLength * sizeof(staticData[0]));

      UChar* result = malloc(sizeof(UChar) * testDataLength); 
      printf("iterations (%ld characters)\n", numberOfIterations);

      memset(result, 0, sizeof(UChar) * testDataLength);
    #ifdef SMALL_PROBLEM_SIZE
      size_t j;
      for (j = 0; j < 100000; j++){
          //lower_StringImpl(testData, numberOfCharacters, result):
          size_t j;
          UChar ored = 0;
          for (j = 0; j < numberOfCharacters; j++) {
            UChar c = testData[j];
            ored |= c;
            //output[j] = toASCIILower(c):
            result[j] = c | ((c >= 'A' && c <= 'Z') << 5);
            //end toASCIILower;
          }
          //end lower_StringImpl;
      }
    #else
      
      for (i = 0; i < 10000000; i++){
        //lower_StringImpl(testData, numberOfCharacters, result):
        size_t j;
        UChar ored = 0;
        for (j = 0; j < numberOfCharacters; j++) {
          UChar c = testData[j];
          ored |= c;
          //output[j] = toASCIILower(c):
          result[j] = c | ((c >= 'A' && c <= 'Z') << 5);
          //end toASCIILower;
        }
        //end lower_StringImpl;
      }
    #endif
    //end doTest1
  }
  return 0;
}
