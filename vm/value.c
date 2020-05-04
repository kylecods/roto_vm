#include "value.h"
#include "memory.h"

void create_vals(ValArray* vals){
    vals->count = 0;
    vals->cap = 0;
    vals->values = NULL;
}

void write_vals(ValArray* vals, Value val){
//    if(vals->cap < vals->count + 1){
//     int old_cap = vals->cap;
//     vals->cap = GROW_CAPACITY(old_cap);
//     vals->values = GROW_ARRAY(vals->values, Value, old_cap, vals->cap);
//   }
//   vals->values[vals->count] = val;
    sb_push(vals->values, val);
     vals->count++;
}

void free_vals(ValArray* vals){
    // FREE_ARRAY(Value,vals->values,vals->cap);
    sb_free(vals->values);
    create_vals(vals);
}
