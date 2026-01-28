%{
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include<ctype.h>
	int yylex();
	void yyerror(char*s);
	int isvalid=0;
    	int prev=0;
%}
%token ID
%%
start: expr'\n'{ if(isvalid){printf("Is Valid ID\n");} else printf("Invalid ID\n"); exit(0); };
expr: expr ID| ;
%%
int yylex(){
    char c;
    scanf("%c",&c);
    if(isalpha(c) && prev==0){
        isvalid=1;
    }
        prev=1;

    if(c=='\n') return c;
    if(prev==1 && !isalnum(c)){
        isvalid=0;
    }
    
    return ID;
}
void yyerror(char*s){
	printf("error");
	}
int main(){
	yyparse();
	return 0;
	}
		


