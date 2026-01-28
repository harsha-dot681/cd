%{
	#include<stdio.h>
	#include "y.tab.h"
	int yywrap();
%}
%%
[A-Za-z] { yylval.c=yytext[0];return ID;}
[A-Za-z]+ { return var;}
\n {return '\n';}
. {return *yytext;}
%%
int yywrap(){
	return 1;
}
