#include <stdlib.h>

int* a;

void foo(int i) {
  a[0] = i;
  a[1] = i * i;
  a[2] = i ^ i;
}

int main(int argc, char** argv) {
  a = (int*)malloc(10 * sizeof(int));
  foo(argc);
  foo(argc);
  foo((argc + 1) * (argc + 1));
  foo((argc + 1) * (argc + 1));
}
