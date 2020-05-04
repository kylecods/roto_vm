#include "chunk.h"
#include "memory.h"



void create_byte(Bytecode* code){
    code->count = 0;
    //code->cap = 0;
    code->bytecode = NULL;
    //lines
    create_vals(&code->vals);

    //values

}

void write_byte(Bytecode* code, uint8_t byte){
    //already initialized   
//     if(code->cap < code->count + 1){
//     int old_cap = code->cap;
//     code->cap = GROW_CAPACITY(old_cap);
//     code->bytecode = GROW_ARRAY(code->bytecode, uint8_t, old_cap, code->cap);
    
//     }
//    code->bytecode[code->count] = byte;
    sb_push(code->bytecode, byte);
    code->count++; 
}

void free_byte(Bytecode* code){
//    FREE_ARRAY(uint8_t, code->bytecode, code->cap);
    sb_free(code->bytecode);
   free_vals(&code->vals);
   create_byte(code);
}

int ptr_to_vals(Bytecode* code, Value val){
    write_vals(&code->vals, val);
    return code->vals.count - 1; //like we are popping?
}