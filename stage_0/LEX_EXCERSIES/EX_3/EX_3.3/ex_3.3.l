%option noyywrap
%{
	#include<stdio.h>
%}
letter [A-Za-z]
%%
{letter}+ {
	if((yytext[0]=='A'||yytext[0]=='a')&&yyleng==3){
		yytext[0]='A';
		printf("%s\n",yytext);
		}
		}
%%
int main(){
	yylex();
	return 1;
	}
