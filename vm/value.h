#include "general.h"

typedef enum{
    INT,
    FLOAT,
    DOUBLE,
    BOOLEAN,
}ValueType;


typedef struct {
    ValueType type;
    union{
        int i32;
        float flt;
        double dbl;
        bool boolean;
    };
}Value;

//value initialization helper macros
#define INT_VAL(val) ((Value){INT, {.i32 = val } })
#define FLOAT_VAL(val) ((Value){FLOAT, {.flt = val } })
#define DOUBLE_VAL(val) ((Value){DOUBLE, {.dbl = val } })
#define BOOL_VAL(val) ((Value){BOOLEAN, {.boolean = val } })

#define AS_NUMBER(value) ((value).i32);
//sb
typedef struct {
    int count;//pointer
    int cap;
    Value* values;
}ValArray;

void create_vals(ValArray* vals);
void free_vals(ValArray* vals);
void write_vals(ValArray* vals, Value val);