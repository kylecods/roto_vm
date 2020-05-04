#include "general.h"
#include "value.h"
//sb
typedef struct{
    int count;//ponter
    int cap;
    uint8_t *bytecode;
    ValArray vals;
}Bytecode;


void write_byte(Bytecode* code, uint8_t byte);
void free_byte(Bytecode* code);
void create_byte(Bytecode* code);
int ptr_to_vals(Bytecode* code, Value val);