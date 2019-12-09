#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#define MAX_SIZE 4000000
#define ITER 10

int main(int argc, char *argv[])
{
  FILE *in,*out;
  int i;
  size_t size;
  int outsize,time;
  unsigned char *inbuf, *outbuf, *temp;
  char *outfilename;
  char postfix[] = ".c";
  struct timeval pre,post;
  
  
  /* optional input arg */
  inbuf = malloc(MAX_SIZE);
  outbuf = malloc(MAX_SIZE);

  if (argc > 1) {
    //create_test_data(argv[1]); // for testing purposes
    if ((in = fopen(argv[1], "r")) == NULL) {
      perror(argv[1]);
      exit(1);
    }
    outfilename = malloc(strlen(argv[1]) + strlen(postfix) + 1);
    strcpy(outfilename,argv[1]);
    strcat(outfilename,postfix);
    free(outfilename);
    argv++; argc--;
  }
  else
    in = stdin;
  if (argc != 1) {
    printf("Usage: drop_0XX [infile]\n");
    exit(2);
  }
  //size = read_data(in, inbuf);
  size = fread(inbuf, 1, MAX_SIZE, in);
  //
  gettimeofday(&pre,0);
  for(i=0;i<20;i++){
    temp = inbuf;
    
    //outsize = drop_0xx(temp, outbuf, size*8);
    int left = size*8;                                                /*2*/
    unsigned short ibuf = 0;                                        /*3*/
    unsigned short obuf = 0;                                        /*4*/
    unsigned char res;                                              /*5*/
    int outoff = 0;                                                 /*6*/

    /* The Macro contains lines 7-14 */ 
    #define IN(N) \
      { \
      if ((left -= 3) < 0) break; \
      if (N < 3) ibuf |= *temp++ << (8 - N); \
      if ((res = (ibuf >> (16-3))) >= 4) \
        { \
          obuf = (obuf << 3) | res; \
          outoff += 3; \
          if ((outoff & 7) < 3) *outbuf++ = (obuf >> (outoff & 7)); \
        } \
      ibuf <<= 3; \
    }

    for (;;) {                                                      /*15*/
      IN(0)                                                         /*16*/
      IN(5)                                                         /*17*/
      IN(2)                                                         /*18*/
      IN(7)                                                         /*19*/
      IN(4)                                                         /*20*/
      IN(1)                                                         /*21*/
      IN(6)                                                         /*22*/
      IN(3)                                                         /*23*/
        }

    if ((outoff & 7) != 0)                                          /*24*/
      {*outbuf++ = (obuf << (8 - (outoff & 7)));}                      /*25*/
    outsize = ((outoff) >> 3);
  //   
  
  gettimeofday(&post,0);
  time = ((post.tv_sec*1000000+post.tv_usec)-(pre.tv_sec*1000000+pre.tv_usec));
  printf("%d\n", outsize);
  exit(0); 
  }
}