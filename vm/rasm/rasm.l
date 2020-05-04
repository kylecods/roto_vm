%{
#include <stdio.h>
#include "lex.h"

void hello(char *word);

Token_type Token;
int mapping(Token_type inst);
int line;
int tcount;
%}
comment (##)[^\n]*
%%
[A-Z]*   {;}
[0-9]*    {tcount++; return INTEGER;}
\"[^"\n]*["\n] {;}
[\n]        {line++;}
[ \t]       {;}
{comment}      {;}
"push"            { tcount++; return PSH;}
"add"            { tcount++; return ADD;}
"sub"            { tcount++; return SUB;}
"pop"            { tcount++; return POP; }
"hlt"            { tcount++; return HLT;}
"mul"            { tcount++; return MUL;}
"div"            { tcount++; return DIV;}
"mov"            { tcount++; return MOV;}
"prt"            { tcount++; return PRT;}
"preg"           { tcount++; return PREG;}
"start"		{ tcount++; return START;}
"end"           { tcount++; return END;}

%%

int yywrap(){return 1;}
void start_lexer(char *file){
yyin=fopen(file, "r");
next_token();
}
int mapping(Token_type inst){
switch(inst.instruction){
case PSH:
return 0;
break;
case ADD:
return 1;
break;
case SUB:
return 3;
break;
case POP:
return 2;
break;
case HLT:
return 4;
break;
case MUL:
return 5;
break;
case DIV:
return 6;
break;
case MOV:
return 7;
break;
case PRT:
return 8;
break;
case PREG:
return 9;
break;
case INTEGER:
return Token.ival;
break;
default:
return -1;
break;
}

}

void next_token(void){

Token.instruction = yylex();
if(Token.instruction == INTEGER){
Token.ival = strtoul(yytext,NULL,10);
}
Token.sval = yytext;
Token.linenum = line;
Token.no = tcount;
}
