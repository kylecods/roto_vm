#include "vm.h"

void reset_stack(VM* vm) {
    vm->top = vm->stack;
}
void init_vm(VM* vm, Bytecode bcode){
  reset_stack(vm);
  vm->code = &bcode;
  vm->pc = vm->code->bytecode;
  vm->state = true;
    
}

void free_vm(VM* vm){
  free_byte(vm->code);
}




void push(VM* vm, Value val){
  *vm->top = val;
   vm->top++;
}

Value pop(VM *vm){
  vm->top--;
  return *vm->top;
}

Value peek_at(VM* vm, int offset){
  return vm->top[-1 - offset];
}
typedef void (*Instructions)(VM *vm);

typedef struct{
  Instructions instr;
  Opcodes ops;
}INSTR;

//  OP_VALS,
//     OP_ADD,
//     OP_SUB,
//     OP_MUL,
//     OP_DIV,

void op_vals(VM* vm){
#define READ_BYTE() (*vm->pc++)
#define READ_CONST() (vm->code->vals.values[READ_BYTE()])
  Value value = READ_CONST();
  
  push(vm, value);
  //vm->result = OK;
#undef READ_BYTE
#undef READ_CONST
}
void op_vnil(VM* vm) {
    push(vm, INT_VAL(0));
}
void op_tbool(VM* vm) {
    push(vm, BOOL_VAL(true));
}

void op_fbool(VM* vm) {
    push(vm, BOOL_VAL(false));
}

void op_add(VM* vm) {
    int b = pop(vm).i32;
    int a = pop(vm).i32;

    push(vm, INT_VAL(a + b));
}
void op_sub(VM* vm) {
    int b = pop(vm).i32;
    int a = pop(vm).i32;

    push(vm, INT_VAL(a - b));
}

void op_mul(VM* vm) {
    int b = pop(vm).i32;
    int a = pop(vm).i32;

    push(vm, INT_VAL(a * b));
}
void op_div(VM* vm) {
    int b = pop(vm).i32;
    int a = pop(vm).i32;

    push(vm, INT_VAL(a / b));
}
void op_jmp(VM* vm) {
#define READ_SHORT() (vm->pc+=2, (uint16_t)((vm->pc[-2] << 8) | vm->pc[-1]))
    uint16_t offset = READ_SHORT();
    vm->pc += offset;
#undef READ_SHORT
}
void op_prt(VM* vm){
  Value val = pop(vm);
  
  if (val.type == INT) {
      printf("Val: %d", val.i32);
  }else if (val.type == DOUBLE) {
      printf("Val: %g", val.dbl);
  }
  else if(val.type == BOOLEAN)
  {
      printf(val.boolean ? "true": "false");
  }
  printf("\n");

}
void op_return(VM* vm) {
    vm->state = false;
}

INSTR ocodes[] = {
  {NULL, OP_NOP},
  {op_vals,OP_ANY},
  {op_vnil,OP_NIL},
  {op_tbool, OP_TBOOL},
  {op_fbool, OP_FBOOL},
  {op_add, OP_ADD},
  {op_sub, OP_SUB},
  {op_mul, OP_MUL},
  {op_div, OP_DIV},
  {op_jmp, OP_JMP},
  {NULL, OP_NOP},
  {NULL, OP_NOP},
  {op_prt, OP_PRT},
  {op_return, OP_RETURN}
};

INSTR* get_ops(uint8_t opcodes){
  return &ocodes[opcodes];
}

void run(VM* vm){
#define READ_BYTE() (*vm->pc++)
    while (vm->state) {
        
        uint8_t ops = READ_BYTE();
        Instructions instr = get_ops(ops)->instr;
        instr(vm);
  }
  
#undef READ_BYTE
}


/**********
**opcodes**
***********/

//arithmetic for the procedure stack

 

void interpret(const char* source){
  
  Bytecode code;

  create_byte(&code);
  write_byte(&code, OP_ANY); 
  write_byte(&code, (uint8_t)ptr_to_vals(&code, INT_VAL(450)));


  write_byte(&code, OP_ANY);
  write_byte(&code, (uint8_t)ptr_to_vals(&code, INT_VAL(450)));
  
  write_byte(&code, OP_ADD);
  write_byte(&code, OP_PRT);
  
  write_byte(&code, OP_TBOOL);
  write_byte(&code, OP_PRT);

  write_byte(&code, OP_NIL);
  write_byte(&code, OP_PRT);

  write_byte(&code, OP_ANY);
  write_byte(&code, (uint8_t)ptr_to_vals(&code, DOUBLE_VAL(45.2)));
  write_byte(&code, OP_PRT);

  write_byte(&code, OP_RETURN);

  VM vm;
  init_vm(&vm, code);
  
 // VM_flags res = 
  run(&vm);
  //free_vm(&vm);

  free_byte(&code);
  //return res;
}







