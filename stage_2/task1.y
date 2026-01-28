%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "parsetree.c"
    int yyerror();
    int yylex();
    extern FILE*yyin;
    FILE*fp;
    %}
%union{
    struct tnode*no;
}
%token T_BEGIN 
%token T_END
%token T_READ T_WRITE
%token<no>number ID 
%type <no>Slist Stmt
%type <no> E
%left '+' '-'
%left '*' '/'
%%
start: T_BEGIN Slist T_END {print($2,0);exit(0);}| T_BEGIN T_END {printf("empty");exit(1);}
;
Slist : Slist Stmt{$$=makeStmtNode(STATEMENT,$1,$2,"STATEMENT");} |Stmt {$$=$1;}
;
Stmt : T_READ '('ID')' {$$=makeStmtNode(READY,$3,NULL,"READ");}|T_WRITE '('E')' {$$=makeStmtNode(WRITEY,$3,NULL,"WRITE");}| ID '=' E {$$=makeExprNode(ASSIGNMENT,'=',$1,$3,"=");}
;
E: E'+'E {
    $$=makeExprNode(PLUS,'+',$1,$3,"+");
}| '('E')' {
    $$=$2;
}|number{
    $$=$1;
} | ID {$$=$1;}
| E '-' E{$$=makeExprNode(MINUS,'-',$1,$3,"-");}
| E '*'E {$$=makeExprNode(MUL,'*',$1,$3,"*");}
| E '/' E {$$=makeExprNode(DIV,'/',$1,$3,"/");}
;
%%
int yyerror(){
    printf("error");
}
int main(){
    yyin=fopen("inputfile.txt","r");
    yyparse();
    return 0;
}