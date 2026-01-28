%option noyywrap
%{
    #include<stdio.h>
    #include "y.tab.h"
    #include "parsetree.h"
%}
number [0-9]+
%%
{number} {(yylval.no)=makeLeafNode(atoi(yytext));return number;}
[\n \t]+ {}
. {return *yytext;}
%%