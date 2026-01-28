%option noyywrap
%{
 #include <stdlib.h>
 #include <stdio.h>
%}

number [0-9]+

%%

{number} {
	if(atoi(yytext)%2==0){printf("%d is even number\n",atoi(yytext));}
	else{ printf("%d is odd number\n",atoi(yytext));}
	}

%%

int main()
{
 yylex();
 return 1;
}
