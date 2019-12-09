/* -*- mode: c -*-
 * $Id: ackermann.c 35417 2007-03-28 04:46:30Z jeffc $
 * http://www.bagley.org/~doug/shootout/
 */

#include <stdio.h>
#include <stdlib.h>
#define STACKSIZE 1000000

struct stack
{
        int top;
        int items[STACKSIZE];
} st;

int main(int argc, char *argv[])
{
    int r,m;
    m = 3;
    st.top = -1;
    int n = ((argc == 2) ? atoi(argv[1]) : 4);
    
    if (st.top == STACKSIZE) {
        fprintf(stderr, "Error: stack overflow\n");
        exit(EXIT_FAILURE);
    } else {
        st.items[++st.top] = m;
    } 
    
    while (!(st.top == -1)) {
        if (st.top == -1) {
            fprintf(stderr, "Error: stack underflow\n");
            exit(EXIT_FAILURE);
        } else {
            m = st.items[st.top--];
        }
        
        if (m == 0)
                n++;
        else if (n == 0){
                n = 1;
                if (st.top == STACKSIZE) {
                    fprintf(stderr, "Error: stack overflow\n");
                    exit(EXIT_FAILURE);
                } else {
                    st.items[++st.top] = m-1;
                }          
            } else {
                n--;
                if (st.top == STACKSIZE) {
                    fprintf(stderr, "Error: stack overflow\n");
                    exit(EXIT_FAILURE);
                } else {
                    st.items[++st.top] = m-1;
                } 
                if (st.top == STACKSIZE) {
                    fprintf(stderr, "Error: stack overflow\n");
                    exit(EXIT_FAILURE);
                } else {
                    st.items[++st.top] = m;
                }
        }
    }
    r = n;
    printf("Result: %d\n", r);
    return 0;
}