%{
	#include<stdio.h>
	#include<stdlib.h>
	int yyerror();
	int yylex();
%}
%union{
	char string[100];
	}
%left '+'
%left '*'
%token <string> var
%%
start : expr'\n' {printf("\nComplete");exit(1);}
 ;

expr:  expr '+' expr {printf("+ ");}
 | expr '*' expr {printf("* ");}
 | '(' expr ')'
 | var   {printf("%s",$1);}
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
