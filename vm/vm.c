#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define arr_len(x) *(&(x) + 1) - (x)
static int stack[256];

//instructions

typedef enum{
  PSH,
  ADD,
  POP,
  SUB,
  HLT,
  MUL,
  DIV,
  MOV,
  PRT,
  PREG
}InstructionSet;

//registers

typedef enum{
  A,
  B,
  C,
  D,
  E,
  F,
  SP,
  PC,
  NUM_REGS
}Registers;

static int registers[NUM_REGS];

int *program;

//instruction counter
int z = 4;



static bool running = true;

//registers
/*Program counter*/
#define PC (registers[PC])
/*stack pointer*/
#define SP (registers[SP])




//fetch cycle
#define FETCH (program[PC])


void eval(int instr){
  switch (instr){
   case HLT:{
     running = false;
     printf("Program ended execution.\n");
     break;
   }
   case PSH:{
     SP = SP + 1;
     PC = PC + 1;
     stack[SP] = program[PC];
     break;
   }
   case POP:{
     SP = SP - 1;
     break;
   }
   case ADD:{
     registers[A] = stack[SP];
     SP = SP - 1;
     
     registers[B] = stack[SP];
     
     registers[C] = registers[B] + registers[A];

     stack[SP] = registers[C];
     
     printf("%d + %d = %d\n", registers[B], registers[A], registers[C]);
     break;
   }
     case MUL:{
     registers[A] = stack[SP];
     SP = SP - 1;
     
     registers[B] = stack[SP];
     
     registers[C] = registers[B] * registers[A];

     stack[SP] = registers[C];
     
     printf("%d * %d = %d\n", registers[B], registers[A], registers[C]);
     break;
   }
   case DIV:{
     registers[A] = stack[SP];
     SP = SP - 1;
     
     registers[B] = stack[SP];
     
     registers[C] = registers[B] / registers[A];

     stack[SP] = registers[C];
     
     printf("%d / %d = %d\n", registers[B], registers[A], registers[C]);
     break;
   }
    case SUB:{
     registers[A] = stack[SP];
     SP = SP - 1;
     
     registers[B] = stack[SP];
     
     registers[C] = registers[B] - registers[A];

     stack[SP] = registers[C];
     
     printf("%d - %d = %d\n", registers[B], registers[A], registers[C]);
     break;
   }
   case MOV: {
     registers[program[PC+2]] = registers[program[PC + 1]];
     PC = PC + 2;
     break;
   }
   case PRT:{
     printf("Value %d\n", registers[program[PC + 1]]);
     PC = PC + 1;
     break;
   }
   case PREG:{
     SP = SP + 1;
     PC = PC + 1;
     stack[SP] = registers[program[PC]];
     break;
   }
  }
  
}

int main(int argv, char **argc){
  
  if(argv <= 1){
    printf("Error no file!!\n");
    return -1;
  }
  
  //read binary file
  FILE *file = fopen(argc[1], "r");
  if(!file){
    printf("Error could not read `%s`\n", argc[1]);

  }

  int num;
  int i = 0;
  
  //allocate memory
  program = malloc(sizeof(*program) * z);
  
  
  while(fscanf(file ,"%d", &num) > 0){
    program[i] = num;
    i++;
    if(i >= z){
      z *=2;
      program = realloc(program, sizeof(*program) * z);
    }
  }
   //y = i;

  fclose(file);


   SP = -1;
  while(running && PC < i){
    eval(FETCH);
    PC = PC + 1;
  }
 
 
  free(program);
  return 0;
}
