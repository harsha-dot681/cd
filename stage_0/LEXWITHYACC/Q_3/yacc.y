%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    int yylex();
    void yyerror();
%}

%union {
    char *str;
}

%token <str> var

%left '+'
%left '*'

%type <str> expr

%%
start : expr '\n'
        {
            printf("%s\n", $1);
            free($1);
            return 0;
        }
      ;

expr  : expr '+' expr
        {
            int len = strlen($1) + strlen($3) + 4;
            $$ = (char *)malloc(len);
            sprintf($$, "+ %s %s", $1, $3);
            free($1);
            free($3);
        }
      | expr '*' expr
        {
            int len = strlen($1) + strlen($3) + 4;
            $$ = (char *)malloc(len);
            sprintf($$, "* %s %s", $1, $3);
            free($1);
            free($3);
        }
      | '(' expr ')'
        {
           $$=$2;
        }
      | var
        {
        	$$=$1;
            //$$ = (char *)malloc(strlen($1) + 1);
            //strcpy($$, $1);
            //free($1);
        }
      ;
%%

void yyerror()
{
    printf("Error\n");
}

int main(void)
{
    yyparse();
    return 0;
}
