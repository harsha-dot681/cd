%option noyywrap
%{
	#include<stdio.h>
	int single_comm=0,multi_comm=0;
	char*fp;
%}
single "//"
multi "/*"
hyphen "/"
star "*"

%%
{single}.* {single_comm++;}
"/\*"([^*]|\*+[^*/])*\*+"/" {multi_comm++;}
%%
int main(){
	fp="inputfile.txt";
	yyin = fopen(fp,"r");
	if(!yyin){
		printf("error");
		return 1;
		}
	yylex();
	printf("single_comments:%d\n multi_comments:%d",single_comm,multi_comm);
	return 1;
}
