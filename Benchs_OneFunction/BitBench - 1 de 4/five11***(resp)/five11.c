#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#define MAX_SIZE 150000

typedef struct linked_list_int {
  int car;
  void* cdr;
} linked_list_int;

typedef struct linked_list_lli {
  linked_list_int* car;
  void* cdr;
} linked_list_lli;

int main(int argc, char *argv[])
{
  FILE *in;
  int i;
  size_t size;
  int outsize,time;
  linked_list_lli *list;
  unsigned char *inbuf, *outbuf, *temp;
  
  struct timeval pre,post;
  
  /* optional input arg */
  inbuf = malloc(MAX_SIZE);

  if (argc > 1) {
    //create_test_data(argv[1]); // for testing purposes
    if ((in = fopen(argv[1], "r")) == NULL) {
      perror(argv[1]);
      exit(1);
    }
    argv++; argc--;
  }
  else
    in = stdin;
  if (argc != 1) {
    printf("Usage: five11 [infile]\n");
    exit(2);
  }
  //size = read_data(in, inbuf);
  size = fread(inbuf, 1, MAX_SIZE, in);
  //
  gettimeofday(&pre,0);
#ifdef SMALL_PROBLEM_SIZE
  for(i=0;i<500;i++){
#else
  for(i=0;i<10000;i++){
#endif    
    
    //list = five11(inbuf);
    int offset,nof_packets, nof_channels,i,j,chan;				/*27*/
    linked_list_int *packet=NULL;							/*28*/
    linked_list_lli *res=NULL;							/*29*/
    offset = 0;									/*30*/
    
      //nof_packets=read_x_bits(inbuf,offset,16);					/*31*/
      //int read_x_bits(unsigned char* buf, int offset, int x) {			/*1*/
      int byte_offset, bit_offset,present,initbits,res_func_int;				/*2*/
      byte_offset = offset >> 3;							/*3*/
      bit_offset = offset & 7;							/*4*/
      initbits = 8-bit_offset;							/*5*/
      present = (int)inbuf[byte_offset] & 255;					/*6*/
      res_func_int = present & ((1 << initbits) - 1);					/*7*/
      while (16 > initbits) {							/*8*/
        byte_offset++;								/*9*/
        present = (int)inbuf[byte_offset] & 255;					/*10*/
        res_func_int = (res_func_int << 8) | present;							/*11*/
        initbits+=8;								/*12*/
      }
      nof_packets = res_func_int >> (initbits-16);							/*13*/
      //
      //

    offset=offset+16;								/*32*/
    for(i=0;i<nof_packets;i++){							/*33*/
      
      
      //nof_channels=read_x_bits(inbuf,offset,5);					/*34*/
        //int read_x_bits(unsigned char* buf, int offset, int x) {			/*1*/
      int byte_offset, bit_offset,present,initbits,res_inteiro2;				/*2*/
      byte_offset = offset >> 3;							/*3*/
      bit_offset = offset & 7;							/*4*/
      initbits = 8-bit_offset;							/*5*/
      present = (int)inbuf[byte_offset] & 255;					/*6*/
      res_inteiro2 = present & ((1 << initbits) - 1);					/*7*/
      while (5 > initbits) {							/*8*/
        byte_offset++;								/*9*/
        present = (int)inbuf[byte_offset] & 255;					/*10*/
        res_inteiro2 = (res_inteiro2 << 8) | present;							/*11*/
        initbits+=8;								/*12*/
      }
      nof_channels = res_inteiro2 >> (initbits-5);							/*13*/
      //
      
      offset+=5;									/*35*/
      for(j=0;j<nof_channels;j++){						/*36*/
        
        
        //chan=read_11_bits(inbuf,offset);						/*37*/
        //int read_11_bits(unsigned char* buf, int offset) {				/*14*/
          int byte_offset, ioffset,present,initbits,res_inteiro = 0;				/*15*/
          int b0,b1,b2;									/*16*/
          byte_offset = offset >> 3;							/*17*/
          ioffset = (8-(offset & 7));							/*18*/
          b0 = (int)inbuf[byte_offset] & 255;						/*19*/
          b1 = (int)inbuf[byte_offset+1] & 255; 						/*20*/
          res_inteiro = b0 << (11-ioffset);							/*21*/
          if (ioffset >= 3) {								/*22*/
            chan =  (res_inteiro | (b1 >> (ioffset-3)))  &  ((1 << 11) - 1);			/*23*/
          }						
          else
            b2 = (int)inbuf[byte_offset+2] & 255;						/*24*/
            chan = (res_inteiro | (b1 << (3-ioffset)) | b2 >> (ioffset+5)) &  ((1 << 11) - 1);	/*25*/
        //}

        //
        
        offset=offset+11;								/*38*/
        //packet = cons1(chan,packet);						/*39*/
        //linked_list_int* cons1(int hd, linked_list_int* tl) {
          linked_list_int *res_func_link;
          res_func_link = (linked_list_int*) malloc(sizeof(linked_list_int));
          res_func_link->car=chan;
          res_func_link->cdr=packet;
          packet = res_func_link;
        //}
        //
      }

      //offset=offset+pad_size(nof_channels);					/*40*/
      //int pad_size(int nof_channels) {						/*44*/
        int bits = 5+nof_channels*11;							/*45*/
        int offsetaux = offset;
        offset = ((8 - (bits & 7)) & 7);						/*46*/
        offset = offset + offsetaux;
      //}
      //
      
      //res = cons2(packet,res);							/*41*/
      //linked_list_lli* cons2(linked_list_int* hd, linked_list_lli* tl) {
        linked_list_lli *res_aux;
        res_aux = (linked_list_lli*) malloc(sizeof(linked_list_lli));
        res_aux->car=packet;
        res_aux->cdr=res;
        res = res_aux;
      //}
      //
      packet=NULL;								/*42*/
    }
      list = res;									/*43*/
    //
    
    //outsize = calc_sum2(list);
    //int calc_sum2(linked_list_lli* list) {						/*47*/
      linked_list_lli *next;							/*48*/
      linked_list_int *hd;								/*49*/
      int res_integer=0;									/*50*/
      while (list!=NULL) {								/*51*/
        next = list->cdr;								/*52*/
        hd = list->car;								/*53*/
        
        //res+=calc_sum1(hd);								/*54*/
        //int calc_sum1(linked_list_int* list) {						/*56*/
          linked_list_int *next2;							/*57*/
          int hd_aux,res_integer2=0;									/*58*/
          while (hd!=NULL) {								/*59*/
            next2 = hd->cdr;								/*60*/
            hd_aux = hd->car;								/*61*/
            res_integer2+=hd_aux;									/*62*/
            hd = next2;								/*63*/
          }
          res_integer+=res_integer2;									/*64*/
        //}
        //
        list = next;								/*55*/
      }
      outsize = res_integer;
    //}
    
    //free_list2(list);
    //void free_list2(linked_list_lli* list) {
      linked_list_lli *next_aux;
      linked_list_int *hd_aux;
      while (list!=NULL) {
        next_aux = list->cdr;
        hd_aux = list->car;
        
        //free_list1(hd);
          //void free_list1(linked_list_int* list) {
            linked_list_int *next_aux2;
            while (hd_aux!=NULL) {
              next_aux2 = hd_aux->cdr;
              free(hd_aux);
              hd_aux = next_aux2;
          //}
        //
        free(list);
        list = next_aux;
      }
    //}
    //
  }
  gettimeofday(&post,0);
  printf("%d\n", outsize);  
  exit(0); 
  }
}