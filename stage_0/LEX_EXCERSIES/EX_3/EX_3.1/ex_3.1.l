%option noyywrap
%{
	#include<stdio.h>
	int line=0,words=0,chara=0;
	
%}
next_line "\n"
var [A-Za-z]+
%%
{next_line} {line++;}
{var}	 { words++;
		chara=chara+yyleng;
		}
%%
int main(){
	yylex();
	printf("no_of_lines:%d\n no_of_words:%d\n no_of_characters:%d\n",line,words,chara);
	return 1;
	}
