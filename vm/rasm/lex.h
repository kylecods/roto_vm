typedef struct{
  int instruction;
  int ival;
  char *sval;
  int  linenum;
  int no;
}Token_type;

typedef enum{
  PSH,
  ADD,
  POP,
  SUB,HLT,MUL,DIV,MOV,PRT,PREG,INTEGER,START,END

}InstructionSet;

void start_lexer(char *file);
void next_token(void);
