%{
	#include<stdio.h>
	#include<stdlib.h>
	int yyerror();
	int yylex();
%}
%union{
	char c;
	}
%left '+'
%left '*'
%token <c> ID
%token var
%%
start : expr'\n' {printf("\nComplete");exit(1);}
 ;

expr:  expr '+' expr {printf("+ ");}
 | expr '*' expr {printf("* ");}
 | '(' expr ')'
 | ID    {printf("%c ",$1);}
 ;
%%

int yyerror()
{
 printf("\nerror");
}

int main()
{
  yyparse();
  return 1;
}
