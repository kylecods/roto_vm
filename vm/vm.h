#include "general.h"
#include "opcodes.h"
#include "chunk.h"

#define MAX_VAL 256



typedef enum{
    OK,
    COMPILE_ERROR,
    RUNTIME_ERROR
}VM_flags;
typedef struct{
  Bytecode* code;
  uint8_t* pc;
  Value stack[MAX_VAL];
  Value* top;
  bool state;
}VM;



void init_vm(VM* vm, Bytecode code);
void free_vm(VM* vm);
void push(VM* vm, Value val);
Value pop(VM* vm);
void interpret(const char* source);


