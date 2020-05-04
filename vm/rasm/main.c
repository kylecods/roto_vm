#include <stdio.h>
#include "lex.h"


/*
*Stretchy buffer
*Sean Barrett's work
*/

#ifndef STB_STRETCHY_BUFFER_H_INCLUDED
#define STB_STRETCHY_BUFFER_H_INCLUDED

#ifndef NO_STRETCHY_BUFFER_SHORT_NAMES
#define sb_free   stb_sb_free
#define sb_push   stb_sb_push
#define sb_count  stb_sb_count
#define sb_add    stb_sb_add
#define sb_last   stb_sb_last
#endif

#define stb_sb_free(a)         ((a) ? free(stb__sbraw(a)),0 : 0)
#define stb_sb_push(a,v)       (stb__sbmaybegrow(a,1), (a)[stb__sbn(a)++] = (v))
#define stb_sb_count(a)        ((a) ? stb__sbn(a) : 0)
#define stb_sb_add(a,n)        (stb__sbmaybegrow(a,n), stb__sbn(a)+=(n), &(a)[stb__sbn(a)-(n)])
#define stb_sb_last(a)         ((a)[stb__sbn(a)-1])

#define stb__sbraw(a) ((int *) (void *) (a) - 2)
#define stb__sbm(a)   stb__sbraw(a)[0]
#define stb__sbn(a)   stb__sbraw(a)[1]

#define stb__sbneedgrow(a,n)  ((a)==0 || stb__sbn(a)+(n) >= stb__sbm(a))
#define stb__sbmaybegrow(a,n) (stb__sbneedgrow(a,(n)) ? stb__sbgrow(a,n) : 0)
#define stb__sbgrow(a,n)      (*((void **)&(a)) = stb__sbgrowf((a), (n), sizeof(*(a))))

#include <stdlib.h>

static void * stb__sbgrowf(void *arr, int increment, int itemsize)
{
   int dbl_cur = arr ? 2*stb__sbm(arr) : 0;
   int min_needed = stb_sb_count(arr) + increment;
   int m = dbl_cur > min_needed ? dbl_cur : min_needed;
   int *p = (int *) realloc(arr ? stb__sbraw(arr) : 0, itemsize * m + sizeof(int)*2);
   if (p) {
      if (!arr)
         p[1] = 0;
      p[0] = m;
      return p+2;
   } else {
      #ifdef STRETCHY_BUFFER_OUT_OF_MEMORY
      STRETCHY_BUFFER_OUT_OF_MEMORY ;
      #endif
      return (void *) (2*sizeof(int)); // try to force a NULL pointer exception later
   }
}
#endif // STB_STRETCHY_BUFFER_H_INCLUDED
#define in_expr_start(t) \
(t==PSH   || t==ADD    || t==SUB    || \
  t==POP  || t==HLT    || t==MUL    || \
  t==DIV  || t==MOV    || t==PRT    || \
   t==PREG || t==INTEGER)




extern Token_type Token;
extern int mapping(Token_type inst);
FILE *yxin;
int *var = NULL;
int num;
int main(int argc, char** argv){
  //yxin = fopen(argv[1], "r");
	start_lexer(argv[1]);
	int i = 0;
	FILE *newout = fopen(argv[2],"w");
	//printf("Number of tokens %d\n\n",Token.instruction);
	while(1){
	  if(Token.instruction == START){
	    next_token();
	  }
	  if(Token.instruction == END){
	    break;
	  }
	  if(Token.instruction == INTEGER){
	    
	      sb_push(var, mapping(Token));
	      printf("%d\n", var[i]);
	      fprintf(newout, " %d", var[i]);
	      next_token();
	      i++;
	  }else{
	    sb_push(var, mapping(Token));
	    printf("%d\n", var[i]);
     	    fprintf(newout, "\n%d ", var[i]);
	    next_token();
	    i++;
	  }
	}
	printf("Number of tokens %d\n\n",Token.no);
        fclose(newout);
	FILE *yout = fopen("test.bin", "wb");
	
	fwrite(&var,sizeof(var),1,yout);
	fclose(yout);

		FILE *yin = fopen("test.bin", "rb");
		while(fread(&var,sizeof(var),1,yin) > 0){
		  for(int z = 0; z < 7; z++){
	           printf("fileval %d\n",var[z]);
		   
		}
		}
                 
		
		fclose(yin);
	sb_free(var);
	return 0;
}
