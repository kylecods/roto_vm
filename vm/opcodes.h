typedef enum{
    OP_NOP,
    OP_ANY,
    OP_NIL,
    OP_TBOOL,
    OP_FBOOL,
    OP_ADD, // handle integer arithmetic for now
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_JMP,
    OP_NOT,
    OP_AND,
    OP_PRT,
    OP_RETURN
}Opcodes;