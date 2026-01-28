%{
	#include<stdio.h>
	#include "y.tab.h"
	#include<string.h>
	#include<stdlib.h>
	int yywrap();
%}
%%
[A-Za-z]+ { strcpy(yylval.string,yytext);return var;}
\n {return '\n';}
. {return *yytext;}
%%
int yywrap(){
	return 1;
}
