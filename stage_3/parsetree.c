#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parsetree.h"
 int var[26];
 int arr[20]={0};
 int label=0;
struct tnode* makeConstantNode(int type, int val, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->val=val;
    temp->type=type;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->left=NULL;
    temp->right=NULL;
    temp->mid=NULL;
    temp->nodetype=CONSTANT;
    return temp;
}
struct tnode* makeVariableNode(int type, char*varname, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->varname=(char*)malloc(sizeof(char)*strlen(varname)+1);
    strcpy(temp->varname,varname);
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->left=NULL;
    temp->right=NULL;
    temp->mid=NULL;
    temp->nodetype=VARIABLE;
    return temp;
}
struct tnode* makelogicalNode(int type,char*op, struct tnode* left, struct tnode* right, char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=left;
    temp->right=right;
    temp->mid=NULL;
    temp->op=malloc(sizeof(char)*strlen(op)+1);
    strcpy(temp->op,op);
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=LOGICAL;
    return temp;
}
struct tnode* makeStmtNode(int type,struct tnode *l, struct tnode *r, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=l;
    temp->right=r;
    temp->op=NULL;
    temp->mid=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=STATEMENT;
    return temp;
}
struct tnode* makeExprNode(int type, char*op , struct tnode*l, struct tnode *r, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    if ((l->type != inttype) || (r->type != inttype)) {
                printf("type mismatch");
                exit(0);
            } else {
                temp->type = inttype;
            }
    temp->op=malloc(sizeof(char)*strlen(op)+1);
    strcpy(temp->op,op);
    temp->type=type;
    temp->left=l;
    temp->right=r;
    temp->mid=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=EXPRESSION;
    return temp;
}
struct tnode* makeifelseNode(int type, struct tnode*left,struct tnode*mid, struct tnode*right, char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=left;
    temp->right=right;
    temp->mid=mid;
    temp->op=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=CONDITIONAL;
    return temp;
}
struct tnode* makeifnode(int type, struct tnode*left, struct tnode*right, char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=left;
    temp->right=NULL;
    temp->mid=right;
    temp->op=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=CONDITIONAL;
    return temp;
}
struct tnode* makeLoopNode(int type, struct tnode*left, struct tnode*right, char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=left;
    temp->right=right;
    temp->mid=NULL;
    temp->op=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=LOOP;
    return temp;
}
struct tnode* make_break_continue(int type,char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->left=NULL;
    temp->right=NULL;
    temp->mid=NULL;
    temp->op=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=type;
    return temp;
}
struct tnode* dowhile(int type, struct tnode*left, struct tnode*right, char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=left;
    temp->right=right;
    temp->mid=NULL;
    temp->op=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=LOOP;
    return temp;
}
struct tnode* repeatuntil(int type, struct tnode*left, struct tnode*right, char* s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=left;
    temp->right=right;
    temp->mid=NULL;
    temp->op=NULL;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=LOOP;
    return temp;
}
 void print(struct tnode* t, int indent) {
    if (t == NULL) return;
    for (int i = 0; i < indent; i++) {
        if(i==indent-1)
            printf("└── ");
        else
            printf("|    ");
    }
    printf("%s\n", t->s);
    if (t->nodetype == CONDITIONAL) {
        print(t->left, indent + 1); 
        if (t->mid != NULL) {
            print(t->mid, indent + 1);
        }
        if (t->right != NULL) {
            print(t->right, indent + 1); 
        }
    } else {
        print(t->left, indent + 1); 
        print(t->right, indent + 1); 
    }
}
int getreg(){
    for(int i=0;i<20;i++){
        if(arr[i]==0){
            arr[i]=1;
            return i;
        }
    }
    printf("Out of registers\n");
    exit(1);
}
void freereg(){
    for(int i=19;i>=0;i--){
        if(arr[i]==1){
            arr[i]=0;
            return;
        }
    }
}
int getLabel(){
    return ++label;
}
reg_index codegen( struct tnode *t,FILE*fp) {
   if(t->left==NULL&&t->right==NULL){
       int p= getreg();
       if(t->nodetype==CONSTANT){
           fprintf(fp,"MOV R%d,%d\n",p,t->val);
       }
       else if(t->nodetype==VARIABLE){
           fprintf(fp,"MOV R%d,[%d]\n",p,t->varname[0]-'a'+4096);
       }
       return p;
   }
   else{
        if(t->op!=NULL&&strcmp(t->op,"=")==0){
            int q= codegen(t->right,fp);
            fprintf(fp,"MOV [%d],R%d\n",t->left->varname[0]-'a'+4096,q);
            freereg();
            return -1;
        }
        if(strcmp(t->s,"read")==0){
             ready(fp,t->left->varname);
             return -1;
        }
        if(strcmp(t->s,"write")==0){
            int q= codegen(t->left,fp);
            writey(fp,q);
            freereg();
            return -1;
        }
        if(t->nodetype==STATEMENT){
             codegen(t->left,fp);
            codegen(t->right,fp);
            return -1;
        } 
        if(t->nodetype==CONDITIONAL&&strcmp(t->s,"if")==0){
            int l1 = getLabel();
            int p = codegen(t->left, fp);
            fprintf(fp, "JZ R%d, L%d\n", p, l1);
            freereg();
             codegen(t->mid, fp);
            fprintf(fp, "L%d:\n", l1);
            
            return -1;
        }
        if(t->nodetype==CONDITIONAL&&strcmp(t->s,"ifelse")==0){
            int l1 = getLabel();
            int l2 = getLabel();
            int p = codegen(t->left, fp);
            fprintf(fp, "JZ R%d, L%d\n", p, l1);
            freereg();
            codegen(t->mid, fp);
            fprintf(fp, "JMP L%d\n", l2);
            fprintf(fp, "L%d:\n", l1);
            codegen(t->right, fp);
            fprintf(fp, "L%d:\n", l2);
        return -1;
           }
        if(t->nodetype==LOOP){
           int l1 = getLabel();
           int l2 = getLabel();
           fprintf(fp, "L%d:\n", l1);         
           int p = codegen(t->left, fp);      
           fprintf(fp, "JZ R%d, L%d\n", p, l2); 
           freereg();                         
           codegen(t->right, fp);            
           fprintf(fp, "JMP L%d\n", l1);      
           fprintf(fp, "L%d:\n", l2);         
            return -1;
        }
        int p = codegen(t->left, fp);
        int q = codegen(t->right, fp);
        if (strcmp(t->op, "+") == 0) fprintf(fp, "ADD R%d, R%d\n", p, q);
        else if (strcmp(t->op, "-") == 0) fprintf(fp, "SUB R%d, R%d\n", p, q);
        else if (strcmp(t->op, "*") == 0) fprintf(fp, "MUL R%d, R%d\n", p, q);
        else if (strcmp(t->op, "/") == 0) fprintf(fp, "DIV R%d, R%d\n", p, q);
        else if (strcmp(t->op, "<") == 0) fprintf(fp, "LT R%d, R%d\n", p, q);
        else if (strcmp(t->op, ">") == 0) fprintf(fp, "GT R%d, R%d\n", p, q);
        else if (strcmp(t->op, "<=") == 0) fprintf(fp, "LE R%d, R%d\n", p, q);
        else if (strcmp(t->op, ">=") == 0) fprintf(fp, "GE R%d, R%d\n", p, q);
        else if (strcmp(t->op, "==") == 0) fprintf(fp, "EQ R%d, R%d\n", p, q);
        else if (strcmp(t->op, "!=") == 0) fprintf(fp, "NE R%d, R%d\n", p, q);
        freereg();
        return p;
   }
   return 0;
}

reg_index codegen1( struct tnode *t,FILE*fp, int breaklabel,int continuelabel) {
   if(t->left==NULL&&t->right==NULL){
        if(t->nodetype==BREAK){
            fprintf(fp, "JMP L%d\n", breaklabel); 
            return -1;
        }
        if(t->nodetype==CONTINUE){
            fprintf(fp, "JMP L%d\n", continuelabel); 
            return -1;
        }
       int p= getreg();
       if(t->nodetype==CONSTANT){
           fprintf(fp,"MOV R%d,%d\n",p,t->val);
       }
       else if(t->nodetype==VARIABLE){
           fprintf(fp,"MOV R%d,[%d]\n",p,t->varname[0]-'a'+4096);
       }
       return p;
   }
   else{
        if(t->op!=NULL&&strcmp(t->op,"=")==0){
            int q= codegen1(t->right,fp,breaklabel,continuelabel);
            fprintf(fp,"MOV [%d],R%d\n",t->left->varname[0]-'a'+4096,q);
            freereg();
            return -1;
        }
        if(strcmp(t->s,"read")==0){
             ready(fp,t->left->varname);
             return -1;
        }
        if(strcmp(t->s,"write")==0){
            int q= codegen1(t->left,fp,breaklabel,continuelabel);
            writey(fp,q);
            freereg();
            return -1;
        }
        if(t->nodetype==STATEMENT){
             codegen1(t->left,fp,breaklabel,continuelabel);
            codegen1(t->right,fp,breaklabel,continuelabel);
            return -1;
        } 
        if(t->nodetype==CONDITIONAL&&strcmp(t->s,"if")==0){
            int l1 = getLabel();
            int p = codegen1(t->left, fp,breaklabel,continuelabel);
            fprintf(fp, "JZ R%d, L%d\n", p, l1);
            freereg();
             codegen1(t->mid, fp,breaklabel,continuelabel);
            fprintf(fp, "L%d:\n", l1);
            
            return -1;
        }
        if(t->nodetype==CONDITIONAL&&strcmp(t->s,"ifelse")==0){
            int l1 = getLabel();
            int l2 = getLabel();
            int p = codegen1(t->left, fp,breaklabel,continuelabel);
            fprintf(fp, "JZ R%d, L%d\n", p, l1);
            freereg();
            codegen1(t->mid, fp,breaklabel,continuelabel);
            fprintf(fp, "JMP L%d\n", l2);
            fprintf(fp, "L%d:\n", l1);
            codegen1(t->right, fp,breaklabel,continuelabel);
            fprintf(fp, "L%d:\n", l2);
        return -1;
           }
        if(t->nodetype==LOOP){
           int l1 = getLabel();
           int l2 = getLabel();
           fprintf(fp, "L%d:\n", l1);         
           int p = codegen1(t->left, fp,l2,l1);      
           fprintf(fp, "JZ R%d, L%d\n", p, l2); 
           freereg();                         
           codegen1(t->right, fp,l2,l1);             
           fprintf(fp, "JMP L%d\n", l1);      
           fprintf(fp, "L%d:\n", l2);         
            return -1;
        }
        int p = codegen1(t->left, fp,breaklabel,continuelabel);
        int q = codegen1(t->right, fp,breaklabel,continuelabel);
        if (strcmp(t->op, "+") == 0) fprintf(fp, "ADD R%d, R%d\n", p, q);
        else if (strcmp(t->op, "-") == 0) fprintf(fp, "SUB R%d, R%d\n", p, q);
        else if (strcmp(t->op, "*") == 0) fprintf(fp, "MUL R%d, R%d\n", p, q);
        else if (strcmp(t->op, "/") == 0) fprintf(fp, "DIV R%d, R%d\n", p, q);
        else if (strcmp(t->op, "<") == 0) fprintf(fp, "LT R%d, R%d\n", p, q);
        else if (strcmp(t->op, ">") == 0) fprintf(fp, "GT R%d, R%d\n", p, q);
        else if (strcmp(t->op, "<=") == 0) fprintf(fp, "LE R%d, R%d\n", p, q);
        else if (strcmp(t->op, ">=") == 0) fprintf(fp, "GE R%d, R%d\n", p, q);
        else if (strcmp(t->op, "==") == 0) fprintf(fp, "EQ R%d, R%d\n", p, q);
        else if (strcmp(t->op, "!=") == 0) fprintf(fp, "NE R%d, R%d\n", p, q);
        freereg();
        return p;
   }
   return 0;
}


void ready(FILE*fp,char*s){
    int p= getreg();
    fprintf(fp,"MOV R%d,\"Read\"\n",p);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"MOV R%d,-1\n",p);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"MOV R%d,%d\n",p ,s[0]-'a'+4096);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"PUSH R%d\n",p); 
    fprintf(fp,"CALL 0\n");
    fprintf(fp,"POP R%d\n",p);
    fprintf(fp,"POP R%d\n",p);
    fprintf(fp,"POP R%d\n",p);
    fprintf(fp,"POP R%d\n",p);
    fprintf(fp,"POP R%d\n",p);
    freereg();
}
void writey(FILE*fp,int p){
    int q= getreg();
    fprintf(fp,"MOV R%d,\"Write\"\n",q );
    fprintf(fp,"PUSH R%d\n",q);
    fprintf(fp,"MOV R%d,-2\n",q);
    fprintf(fp,"PUSH R%d\n",q);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"PUSH R%d\n",p);
    fprintf(fp,"CALL 0\n");
    fprintf(fp,"POP R%d\n",q);
    fprintf(fp,"POP R%d\n",q);
    fprintf(fp,"POP R%d\n",q);
    fprintf(fp,"POP R%d\n",q);
    fprintf(fp,"POP R%d\n",q);
    freereg();
}
int eval(struct tnode* t) {
    if (t == NULL) return 0; 
    if (t->nodetype == CONSTANT) { 
        return t->val; }
    if (t->nodetype == VARIABLE) return var[t->varname[0] - 'a']; 
    if (t->nodetype == STATEMENT) {
        if (t->s != NULL) {
            if (strcmp(t->s, "read") == 0) {
                int x;
                FILE *tty = fopen("/dev/tty", "r");
             if (tty == NULL) {
               printf("Error: Could not open terminal for input\n");
                  return -1;
                              }
              printf("Enter value for %s: ", t->left->varname);
                fflush(stdout);
                 fscanf(tty, "%d", &x);
                  fclose(tty);
                  var[t->left->varname[0] - 'a'] = x;
                      return 0;
                                    }
            if (strcmp(t->s, "write") == 0) {
                printf("%d\n", eval(t->left)); 
                return 0; 
            }
        }
        int l=eval(t->left);
        eval(t->right);
        return l; 
    }
    if (t->op != NULL) {
        if (strcmp(t->op, "=") == 0) {
            int value = eval(t->right);
            var[t->left->varname[0] - 'a'] = value;
            return value; 
        }
        int l = eval(t->left);
        int r = eval(t->right);
        if (strcmp(t->op, "+") == 0) return l + r; 
        if (strcmp(t->op, "-") == 0) return l - r; 
        if (strcmp(t->op, "*") == 0) return l * r; 
        if (strcmp(t->op, "/") == 0) return l / r; 
        if (strcmp(t->op, "<") == 0) return l < r; 
        if (strcmp(t->op, ">") == 0) return l > r; 
        if (strcmp(t->op, "<=") == 0) return l <= r; 
        if (strcmp(t->op, ">=") == 0) return l >= r; 
        if (strcmp(t->op, "==") == 0) return l == r; 
        if (strcmp(t->op, "!=") == 0) return l != r; 
    }
    if (t->nodetype == CONDITIONAL) {
        if (eval(t->left)!=0){ 
            return eval(t->mid); 
        }
        else if (t->right!=NULL){ 
            return eval(t->right);} 
    }
    if (t->nodetype == LOOP) {
        while (eval(t->left)!=0) { 
            eval(t->right); 
        }
        return 0;
    }

    return 0;
}

reg_index codegen2( struct tnode *t,FILE*fp, int breaklabel,int continuelabel) {
   if(t->left==NULL&&t->right==NULL){
        if(t->nodetype==BREAK){
           // printf("-1");
            fprintf(fp, "JMP L%d\n", breaklabel);
            return -1;
        }
        if(t->nodetype==CONTINUE){
            fprintf(fp, "JMP L%d\n", continuelabel); 
            return -1;
        }
       int p= getreg();
       if(t->nodetype==CONSTANT){
           fprintf(fp,"MOV R%d,%d\n",p,t->val);
       }
       else if(t->nodetype==VARIABLE){
           fprintf(fp,"MOV R%d,[%d]\n",p,t->varname[0]-'a'+4096);
       }
       return p;
   }
   else{
        if(t->op!=NULL&&strcmp(t->op,"=")==0){
            int q= codegen2(t->right,fp,breaklabel,continuelabel);
            fprintf(fp,"MOV [%d],R%d\n",t->left->varname[0]-'a'+4096,q);
            freereg();
            return -1;
        }
        if(strcmp(t->s,"read")==0){
             ready(fp,t->left->varname);
             return -1;
        }
        if(strcmp(t->s,"write")==0){
            int q= codegen2(t->left,fp,breaklabel,continuelabel);
            writey(fp,q);
            freereg();
            return -1;
        }
        if(t->nodetype==STATEMENT){
             codegen2(t->left,fp,breaklabel,continuelabel);
            codegen2(t->right,fp,breaklabel,continuelabel);
            return -1;
        } 
        if(t->nodetype==CONDITIONAL&&strcmp(t->s,"if")==0){
            int l1 = getLabel();
            int p = codegen2(t->left, fp,breaklabel,continuelabel);
            fprintf(fp, "JZ R%d, L%d\n", p, l1);
            freereg();
             codegen2(t->mid, fp,breaklabel,continuelabel);
            fprintf(fp, "L%d:\n", l1);
            
            return -1;
        }
        if(t->nodetype==CONDITIONAL&&strcmp(t->s,"ifelse")==0){
            int l1 = getLabel();
            int l2 = getLabel();
            int p = codegen1(t->left, fp,breaklabel,continuelabel);
            fprintf(fp, "JZ R%d, L%d\n", p, l1);
            freereg();
            codegen2(t->mid, fp,breaklabel,continuelabel);
            fprintf(fp, "JMP L%d\n", l2);
            fprintf(fp, "L%d:\n", l1);
            codegen2(t->right, fp,breaklabel,continuelabel);
            fprintf(fp, "L%d:\n", l2);
        return -1;
           }
        if(t->nodetype==LOOP){
        if(strcmp(t->s,"while")==0){
           int l1 = getLabel();
           int l2 = getLabel();
           fprintf(fp, "L%d:\n", l1);         
           int p = codegen2(t->left, fp,l2,l1);      
           fprintf(fp, "JZ R%d, L%d\n", p, l2); 
           freereg();                         
           codegen2(t->right, fp,l2,l1);             
           fprintf(fp, "JMP L%d\n", l1);      
           fprintf(fp, "L%d:\n", l2);         
            return -1;
        }
        if(strcmp(t->s,"dowhile")==0){
           int l1 = getLabel();
           int l2 = getLabel();
           fprintf(fp, "L%d:\n", l1);         
           codegen1(t->left, fp,l2,l1);             
           int p = codegen2(t->right, fp,l2,l1);      
           fprintf(fp, "JNZ R%d, L%d\n", p, l1); 
           freereg();                         
           fprintf(fp, "L%d:\n", l2);         
            return -1;
        }
        if(strcmp(t->s,"repeatuntill")==0){
           int l1 = getLabel();
           int l2 = getLabel();
           fprintf(fp, "L%d:\n", l1);         
           codegen2(t->left, fp,l2,l1);             
           int p = codegen2(t->right, fp,l2,l1);      
           fprintf(fp, "JZ R%d, L%d\n", p, l1); 
           freereg();                         
           fprintf(fp, "L%d:\n", l2);         
            return -1;
    }
}
        int p = codegen2(t->left, fp,breaklabel,continuelabel);
        int q = codegen2(t->right, fp,breaklabel,continuelabel);
        if (strcmp(t->op, "+") == 0) fprintf(fp, "ADD R%d, R%d\n", p, q);
        else if (strcmp(t->op, "-") == 0) fprintf(fp, "SUB R%d, R%d\n", p, q);
        else if (strcmp(t->op, "*") == 0) fprintf(fp, "MUL R%d, R%d\n", p, q);
        else if (strcmp(t->op, "/") == 0) fprintf(fp, "DIV R%d, R%d\n", p, q);
        else if (strcmp(t->op, "<") == 0) fprintf(fp, "LT R%d, R%d\n", p, q);
        else if (strcmp(t->op, ">") == 0) fprintf(fp, "GT R%d, R%d\n", p, q);
        else if (strcmp(t->op, "<=") == 0) fprintf(fp, "LE R%d, R%d\n", p, q);
        else if (strcmp(t->op, ">=") == 0) fprintf(fp, "GE R%d, R%d\n", p, q);
        else if (strcmp(t->op, "==") == 0) fprintf(fp, "EQ R%d, R%d\n", p, q);
        else if (strcmp(t->op, "!=") == 0) fprintf(fp, "NE R%d, R%d\n", p, q);
        freereg();
        return p;
   }
   return 0;
}

