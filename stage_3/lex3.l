%option noyywrap
%{
    #include<stdio.h>
    #include "y.tab.h"
    #include<stdlib.h>
    #include "parsetree.h"
    int val;
%}
number [0-9]+
%%
[ \t\r\n]+ {}
"<=" {return LE;}
">=" {return GE;}
"==" {return EQ;}
"!=" {return NE;}
"begin" {return T_BEGIN;}
"end"   {return T_END;}
"read" {return T_READ;}
"write" {return T_WRITE;}
"if"  {return T_IF;}
"endif" {return T_ENDIF;}
"then"  {return T_then;}
"else"  {return T_ELSE;}
"while" {return T_WHILE;}
"do"    {return T_DO;}
"endwhile" {return T_ENDWHILE;}
{number} {val=atoi(yytext);(yylval.no)=makeConstantNode(inttype,val,yytext);
return number;}
[a-z] {(yylval.no)=makeVariableNode(inttype,yytext,yytext);
return ID;}
. {return *yytext;}
%%