%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "machine.h"
%}

%union {
  int i;
  char *strval;
  struct Operand *oper;
  struct Instruction *inst;
}

%token TOKNUM
%token TOKREG
%token TOKCOMA
%token TOKOPAREN
%token TOKCR
%token TOKCPAREN
%token TOKNUMBER 
%token TOKID
%token TOKIMM
%type <i> TOKIMM TOKNUMBER 
%type <strval> TOKREG TOKID TOKLABEL 
%type <oper> operand
%type <inst> inst
%token TOKNOP
%token TOKMOV
%token TOKAND
%token TOKSW
%token TOKLW
%token TOKPUSH
%token TOKPOP
%token TOKCALL
%token TOKRET
%token TOKPRINT
%token TOKREAD
%token TOKADD
%token TOKSUB
%token TOKDIV
%token TOKMUL
%token TOKCMP
%token TOKJMP
%token TOKJMPE
%token TOKJMPL
%token TOKHLT
%token TOKLABEL
%token TOKDMP
%token TOKDBG
%token TOKSEG
%token TOKLOOP
%start input


%%

input       : /* empty */
            | input inst TOKCR {
                code[count++]=*$2;
                if ($2->src.lab && !strcmp($2->src.lab, "3")) {
                  code[count++]=$2[1];
                  code[count++]=$2[2];
                }
            }
;

inst: 
      TOKNOP { $$ = malloc(sizeof(struct Instruction)); $$->op=NOP;}
    | TOKMOV operand TOKCOMA operand  { $$ = malloc(sizeof(struct Instruction)); $$->op=MOV; $$->src=*$2; $$->dst=*$4;}
    | TOKAND operand TOKCOMA operand  { $$ = malloc(sizeof(struct Instruction)); $$->op=AND; $$->src=*$2; $$->dst=*$4;}
    | TOKSW operand TOKCOMA operand  { $$ = malloc(sizeof(struct Instruction)); $$->op=SW; $$->src=*$2; $$->dst=*$4;}
    | TOKLW operand TOKCOMA operand  { $$ = malloc(sizeof(struct Instruction)); $$->op=LW; $$->src=*$2; $$->dst=*$4;}
    | TOKPUSH operand { $$ = malloc(sizeof(struct Instruction)); $$->op=PUSH; $$->src=*$2;}
    | TOKPOP operand  { $$ = malloc(sizeof(struct Instruction)); $$->op=POP; $$->src=*$2;}
    | TOKCALL operand { $$ = malloc(sizeof(struct Instruction)); $$->op=CALL; $$->src=*$2; }
    | TOKRET { $$ = malloc(sizeof(struct Instruction)); $$->op=RET; }
    | TOKPRINT operand { $$ = malloc(sizeof(struct Instruction)); $$->op=PRINT ; $$->src=*$2;}
    | TOKREAD operand  { $$ = malloc(sizeof(struct Instruction)); $$->op=READ; $$->src=*$2;}
    | TOKADD operand TOKCOMA operand { $$ = malloc(sizeof(struct Instruction)); $$->op=ADD; $$->src=*$2; $$->dst=*$4;}
    | TOKSUB operand TOKCOMA operand { $$ = malloc(sizeof(struct Instruction)); $$->op=SUB; $$->src=*$2; $$->dst=*$4;}
    | TOKMUL operand TOKCOMA operand { $$ = malloc(sizeof(struct Instruction)); $$->op=MUL; $$->src=*$2; $$->dst=*$4;}
    | TOKDIV operand TOKCOMA operand { $$ = malloc(sizeof(struct Instruction)); $$->op=DIV; $$->src=*$2; $$->dst=*$4;}
    | TOKCMP operand TOKCOMA operand { $$ = malloc(sizeof(struct Instruction)); $$->op=CMP; $$->src=*$2; $$->dst=*$4;}
    | TOKJMP operand { $$ = malloc(sizeof(struct Instruction)); $$->op=JMP; $$->src=*$2; }
    | TOKJMPE operand { $$ = malloc(sizeof(struct Instruction)); $$->op=JMPE; $$->src=*$2; }
    | TOKJMPL operand { $$ = malloc(sizeof(struct Instruction)); $$->op=JMPL; $$->src=*$2; }
    | TOKLABEL { $$ = malloc(sizeof(struct Instruction)); $$->op=LABEL; $$->src.lab=$1; }
    | TOKHLT { $$ = malloc(sizeof(struct Instruction)); $$->op=HLT;}
    | TOKDMP { $$ = malloc(sizeof(struct Instruction)); $$->op=DMP;}
    | TOKDBG { $$ = malloc(sizeof(struct Instruction)); $$->op=DBG;}
    | TOKSEG { $$ = malloc(sizeof(struct Instruction)); $$->op=SEG;}
    | TOKLOOP operand { 
        $$ = malloc(sizeof(struct Instruction)*3);
        $$->op=ADD; $$->src.lab = "3"; $$->src.type=IMM; $$->src.val=-1; $$->dst.type=REG; $$->dst.val=3;
        $$[1].op=CMP; $$[1].src.type=IMM; $$[1].src.val=0; $$[1].dst.type=REG; $$[1].dst.val=3;
        $$[2].op=JMPL; $$[2].src=*$2;
    }
    ;


operand:
          TOKREG { $$ = malloc(sizeof(struct Operand)); $$->type=REG; $$->val=reg($1);}
        | TOKOPAREN TOKREG TOKCPAREN { $$ = malloc(sizeof(struct Operand)); $$->type=MEM; $$->lab="0"; $$->val=reg($2);}
        | TOKNUMBER { $$ = malloc(sizeof(struct Operand)); $$->type=MEM; $$->val=$1;}
        | TOKIMM { $$ = malloc(sizeof(struct Operand)); $$->type=IMM; $$->val=$1;}
        | TOKID  { $$ = malloc(sizeof(struct Operand)); $$->type=LABELOP; $$->lab=$1;}
        ;

%%



