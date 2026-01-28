%option noyywrap
%{
    #include<stdio.h>
    #include "y.tab.h"
    #include "parsetree.h"
    int val;
%}
number [0-9]+
%%
"begin" {return T_BEGIN;}
"end"   {return T_END;}
"read" {return T_READ;}
"write" {return T_WRITE;}
{number} {val=atoi(yytext);(yylval.no)=makeConstantNode(INTEGER,val,yytext);return number;}
[a-z] {(yylval.no)=makeVariableNode(VARIABLE,yytext,yytext);return ID;}
[\n\t]+ {}
. {return *yytext;}
%%