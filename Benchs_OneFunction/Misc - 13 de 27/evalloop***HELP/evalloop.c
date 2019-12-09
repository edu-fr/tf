/* 
 * A performance regression test for using the GCC "labels as values" extension
 * and computed gotos to optimize the interpreter loop. This is a trick that has
 * been used by, at least, python, webkit, ruby and dalvik. See:
 * http://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables
 * for a detailed description.
 * 
 * Some uses of this trick, notably python's, can create critical edges in the
 * control flow graph which we must break to achieve reasonable performance.
 */

#include <stdio.h>
#include <stdint.h>

#define TARGET(op) \
        L##op: \
        opcode = op; \
        case op:

uint32_t sum = 0;
int main() __attribute__((noinline));

int main() {
  const int BUFSIZE = 2048;
  // Initialize the command buffer. This must end with a 0, which is the
  // "exit" command for the interpreter loop.
  int cmds[BUFSIZE];
  for (int i = 0; i < BUFSIZE - 1; ++i)
    cmds[i] = i % 31 + 1;
  cmds[BUFSIZE - 1] = 0;
  int *p = &cmds[0];

  // Run the interpreter loop over the buffer enough times to get a performance
  // estimate.
  for (int i = 0; i < 100000; ++i) {
    static void *dispatch[32] = {
    &&L0,
    &&L1,
    &&L2,
    &&L3,
    &&L4,
    &&L5,
    &&L6,
    &&L7,
    &&L8,
    &&L9,
    &&L10,
    &&L11,
    &&L12,
    &&L13,
    &&L14,
    &&L15,
    &&L16,
    &&L17,
    &&L18,
    &&L19,
    &&L20,
    &&L21,
    &&L22,
    &&L23,
    &&L24,
    &&L25,
    &&L26,
    &&L27,
    &&L28,
    &&L29,
    &&L30,
    &&L31   
    };
  
    int opcode = 0;
    while (1) {    
      switch(*p++) {
        TARGET(0) { }
        TARGET(1) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(2) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(3) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(4) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(5) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(6) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(7) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(8) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(9) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(10) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(11) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(12) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(13) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(14) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(15) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(16) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(17) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(18) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(19) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(20) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(21) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(22) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(23) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(24) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(25) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(26) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(27) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(28) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(29) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(30) { sum += opcode; goto *dispatch[*p++]; }
        TARGET(31) { sum += opcode; goto *dispatch[*p++]; }  
      } 
    }

    //END EVAL
  }
  
  printf("Sum: %u\n", sum);
  return 0;
}
