%{
    #include "translation.h"
    int first = 1, addr = 2040,label=0;
    extern FILE *yyin;
    FILE *fp;
    struct labelNode*head=NULL;
%}

%%

"L"[0-9]+[:][ \t]*  {     label=0;
                    char *label_name = malloc(strlen(yytext));
                    strcpy(label_name, yytext);
                    label_name[strlen(yytext)-1] = '\0';
                    if (first) {
                        append_labelNode(&head,label_name, addr);
                        addr -= 2;
                    }
                }

"JZ R"[0-9]+[,]" L"[0-9]+ {
                    if (!first) {
                        if (yytext[5] == ',') {
                            fprintf(fp, "JZ R%c, %d", yytext[4], getAddr(head,yytext + 7));
                        }
                        else {
                            fprintf(fp, "JZ R%c%c, %d", yytext[4], yytext[5], getAddr(head,yytext + 8));
                        }
                    }
                    label=1;
                }

"JNZ R"[0-9]+[,]" L"[0-9]+ {
                    if (!first) {
                        if (yytext[6] == ',') {
                            fprintf(fp, "JNZ R%c, %d", yytext[5], getAddr(head,yytext + 8));
                        }
                        else {
                            fprintf(fp, "JNZ R%c%c, %d", yytext[5], yytext[6], getAddr(head,yytext + 9));
                        }
                        label=1;
                    }
                }

"JMP L"[0-9]+ {
                    if (!first) {
                        fprintf(fp, "JMP %d", getAddr(head,yytext + 4));
                        label=1;
                    }
                }

"\n" {
    addr += 2;
    if (!first) {
        if(label){
        fprintf(fp, "\n");
        }
         label=0;
    }
}

. {
    if (!first) {
        fprintf(fp, "%s", yytext);
        label=1;
    }
}

%%

int yywrap() {
    if (first) {
        yyin = fopen("s3.xsm", "r");
        first = 0;
        return 0;
    }
    if (!first) {
        return 1;
    }
}
int main() {
    fp = fopen("t2.xsm", "w");
    yyin = fopen("s3.xsm", "r");
    yylex();
    return 0;
    }