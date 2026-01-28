%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    int yywrap();
%}

var     [a-zA-Z]+

%%
{var}      {
                yylval.str = malloc(strlen(yytext) + 1);
                strcpy(yylval.str, yytext);
                return var;
           }
\n       {return '\n';}
[(|)|+|*] {return *yytext;}
.
%%

int yywrap(){
    return 1;
}
