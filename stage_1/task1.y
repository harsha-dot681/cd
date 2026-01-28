%{
    #include<stdio.h>
    #include<stdlib.h>
    #include "parsetree.h"
    int yyerror();
    int yylex();
    FILE*fptr;
    int res;
    %}
%union{
    struct tnode*no;
}
%token<no>number
%type <no> E
%left '+' '-'
%left '*' '/'
%%
start:E{ res=eval($1);printf("%d\n",res);exit(0);}
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