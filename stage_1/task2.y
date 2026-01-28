%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "parsetree.h"
    int yyerror();
    int yylex();
    FILE*fptr;
    %}
%union{
    struct tnode*no;
}
%token<no>number
%type <no> E
%left '+' '-'
%left '*' '/'
%%
start:E{ fptr = fopen("s1.xsm","w");
            fprintf(fptr,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);

          int temp = codeGen($1, fptr);

          /* move result to memory and prepare system calls */
          fprintf(fptr, "MOV [4096], R%d\n", temp);
          fprintf(fptr, "MOV R0, [4096]\n");

          /* write and exit system calls */
          fprintf(fptr,
              "MOV SP, 4095\n"
              "MOV R1, \"Write\"\n"
              "PUSH R1\n"
              "MOV R1, -2\n"
              "PUSH R1\n"
              "PUSH R0\n"
              "PUSH R1\n"
              "PUSH R1\n"
              "CALL 0\n"
              "POP R0\n"
              "POP R1\n"
              "POP R1\n"
              "POP R1\n"
              "POP R1\n"
              "MOV R1, \"Exit\"\n"
              "PUSH R1\n"
              "MOV R1, -2\n"
              "PUSH R1\n"
              "PUSH R1\n"
              "PUSH R1\n"
              "PUSH R1\n"
              "BRKP\n"
              "CALL 0\n"
          );

          fclose(fptr);exit(0);}
;
E: E'+'E {
    $$=makeOperatorNode('+',$1,$3);
}| '('E')' {
    $$=$2;
}|number{
    $$=$1;
}
| E '-' E{$$=makeOperatorNode('-',$1,$3);}
| E '*'E {$$=makeOperatorNode('*',$1,$3);}
| E '/' E {$$=makeOperatorNode('/',$1,$3);}
;
%%
int yyerror(){
    printf("error");
}
int main(){
    yyparse();
    return 0;
}