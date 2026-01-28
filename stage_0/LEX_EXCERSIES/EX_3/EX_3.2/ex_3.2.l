%option noyywrap
%{
	#include<stdio.h>
	int integer=0,Float=0;
%}
number [0-9]
%%
{number}+ {integer++;}
{number}*.{number}* { Float++;}
%%
int main(){
	yylex();
	printf("no_of_integers:%d\n no_of_Floats:%d",integer,Float);
	return 1;
	}

