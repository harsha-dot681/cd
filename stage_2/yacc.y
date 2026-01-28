%{
    #include<stdio.h>
    #include<stdlib.h>
  //  #include "parsetree.c"
    int yyerror();
    int yylex();
    FILE*fptr;
    %}
%union{
    struct tnode*no;
}
%token BEGIN END READ WRITE
%token<no>number ID
%type <no> E
%left '+' '-'
%left '*' '/'
%%
program: BEGIN Slist END {{ fptr = fopen("s1.xsm","w");
            fprintf(fptr,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
            fprintf(fptr,"MOV SP,4120");
            fclose(fptr);;exit(1);}}| BEGIN END {{ fptr = fopen("s1.xsm","w");
            fprintf(fptr,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",0,2056,0,0,0,0,0,0);
            fprintf(fptr,"MOV SP,4120");
            fclose(fptr);;exit(1);}}
;
Slist : Slist Stmt |Stmt
;
Stmt : InputStmt | OutputStmt |AsgStmt
;
InputStmt :READ '('ID')'
;
OutputStmt : WRITE '('E')'
;
AsgStmt : ID '=' E
;
E: E'+'E {
    $$=makeOperatorNode('+',$1,$3);
}| '('E')' {
    $$=$2;
}|number{
    $$=$1;
}
;
| E '-' E{$$=makeOperatorNode('-',$1,$3);}
;
| E '*'E {$$=makeOperatorNode('*',$1,$3);}
;
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