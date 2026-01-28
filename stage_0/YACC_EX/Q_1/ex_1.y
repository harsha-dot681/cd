%{
	#include<stdio.h>
	#include<stdlib.h>
	int level=0,pos=0;
	int yylex();
	int yyerror(char*s);
%}
%token IF ID
%%
start : stmt'\n'{exit(0);}
stmt: IF { level++;
		printf("IF level is %d\n",level);
			}
		'('expr')' '{'stmt'}'
		{	level--;
		} stmt|
		expr;
expr:expr ID|	;
%%
int yylex(){
	char s;
		scanf("%c",&s);
		if(s=='I'){
			pos++;
			char x;
			scanf("%c",&x);
			if(x=='F'){
				return IF;
				
		}
		}
		else if(s=='{'){
			return '{';
		}
		else if(s=='}'){
			return '}';
			}
		else if(s=='\n'){
			return '\n';
	}
		else if(s=='('){
			return '(';
			}
		else if(s==')'){
			return ')';
			}
		else{
			return ID;
	}
	}
int yyerror (char*s){
	printf("error");
	return 0;
	}		
int main(){
	yyparse();
	return 1;
	}

