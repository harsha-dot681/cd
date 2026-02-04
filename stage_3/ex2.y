    %{
        #include<stdio.h>
        #include<stdlib.h>
        #include "parsetree.h"
        extern FILE*yyin;
        int yyerror(const char*);
        int yylex();
        FILE*fptr;
        extern int yylineno;
        %}
    %union{
        struct tnode*no;
    }
    %token T_BEGIN T_END T_READ T_WRITE T_IF T_ENDIF T_then T_ELSE T_WHILE T_DO T_ENDWHILE LE GE NE EQ T_BREAK T_CONT REPEAT_ UNTILL_
    %nonassoc T_then
    %nonassoc T_ELSE
    %token<no>number ID
    %type <no> E Stmt Ifstmt Whilestmt Slist program
    %left EQ NE '<' '>' LE GE
    %left '+' '-'
    %left '*' '/'
    %%
    program: T_BEGIN Slist T_END {fptr=fopen("s3.xsm","w+");fprintf(fptr,"%d\n%d\n%d\n%d\n%d\n%d\n\%d\n%d\n",0,2056,0,0,0,0,0,0);fprintf(fptr,"MOV SP,4122\n");codegen2($2,fptr,-1,-1);;exit(0);}| T_BEGIN T_END {$$=NULL;}
    ;
    Slist : Slist Stmt{$$=makeStmtNode(STATEMENT,$1,$2,"STATEMENTS");} |Stmt {$$=$1;}
    ;
    Stmt : T_READ '('ID')'';' {$$=makeStmtNode($3->type,$3,NULL,"read");}| T_WRITE '('E')'';' {$$=makeStmtNode($3->type,$3,NULL,"write");} |ID '=' E';'{$$=makeExprNode($1->type,"=",$1,$3,"=");}|Ifstmt';'{$$=$1;}|Whilestmt';'{$$=$1;}|T_BREAK';'{$$=make_break_continue(BREAK,"break");}|T_CONT ';'{$$=make_break_continue(CONTINUE,"cont");}|REPEAT_ Slist UNTILL_ '(' E ')' ';'{$$=repeatuntil($2->type,$2,$5,"repeatuntill");}| T_DO Slist T_WHILE'(' E')'';'{$$=dowhile($2->type,$2,$5,"dowhile");}
    ;
    Ifstmt: T_IF '('E')' T_then Slist T_ELSE Slist T_ENDIF  {$$=makeifelseNode($6->type,$3,$6,$8,"ifelse");}
            | T_IF '('E')' T_then Slist T_ENDIF {$$=makeifnode($3->type,$3,$6,"if");}
    ;
    Whilestmt:  T_WHILE '('E')' T_DO Slist T_ENDWHILE {$$=makeLoopNode($6->type,$3,$6,"while");}
    ;
    E: E'+'E { $$=makeExprNode(inttype,"+",$1,$3,"+");}
    |'('E')' { $$=$2;}
    |number{ $$=$1;}
    |ID {$$=$1;}
    | E '-'E {$$=makeExprNode(inttype,"-",$1,$3,"-");}
    | E '*'E {$$=makeExprNode(inttype,"*",$1,$3,"*");}
    | E '/'E {$$=makeExprNode(inttype,"/",$1,$3,"/");}
    | E'<' E {$$=makelogicalNode(booltype,"<",$1,$3,"<");}
    | E '>'E {$$=makelogicalNode(booltype,">",$1,$3,">");}
    | E LE E {$$=makelogicalNode(booltype,"<=",$1,$3,"<=");}
    | E GE E {$$=makelogicalNode(booltype,">=",$1,$3,">=");}
    | E NE E {$$=makelogicalNode(booltype,"!=",$1,$3,"!=");}
    | E EQ E {$$=makelogicalNode(booltype,"==",$1,$3,"==");}
    ;
    %%
    int yyerror(const char *s){
        printf("Parse error: %s at %d \n", s,yylineno);
        return 0;
    }
    int main(int argc,char* argv[]){
        yyin=fopen(argv[1],"r");
        yyparse();
        return 0;
    }