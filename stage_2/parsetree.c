#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parsetree.h"
int var[26];
int arr[20]={0};
struct tnode *makeConstantNode(int type, int val, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->val=val;
    temp->type=type;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->left=NULL;
    temp->right=NULL;
    temp->nodetype=INTEGER;
    return temp;
}
struct tnode *makeVariableNode(int type, char*varname, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->varname=(char*)malloc(sizeof(char)*strlen(varname)+1);
    strcpy(temp->varname,varname);
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->left=NULL;
    temp->right=NULL;
    temp->nodetype=VARIABLE;
    return temp;
}
struct tnode *makeStmtNode(int type, struct tnode *l, struct tnode *r, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->type=type;
    temp->left=l;
    temp->right=r;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=STATEMENT;
    return temp;
}
struct tnode *makeExprNode(int type, char op , struct tnode*l, struct tnode *r, char *s){
    struct tnode*temp=malloc(sizeof(struct tnode));
    temp->op=op;
    temp->type=type;
    temp->left=l;
    temp->right=r;
    temp->s=(char*)malloc(sizeof(char)*strlen(s)+1);
    strcpy(temp->s,s);
    temp->nodetype=EXPRESSION;
    return temp;
}
void print(struct tnode*root,int level){
   if(root){
       for (int i = 0; i < level; i++)
        printf("│  ");

    printf("├─ %s\n", root->s);
     print(root->left,level+1);
     print(root->right,level+1);
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
reg_index codegen( struct tnode *t,FILE*fp) {
   if(t->left==NULL&&t->right==NULL){
       int p= getreg();
       if(t->nodetype==INTEGER){
           fprintf(fp,"MOV R%d,%d\n",p,t->val);
       }
       else if(t->nodetype==VARIABLE){
           fprintf(fp,"MOV R%d,[%d]\n",p,t->varname[0]-'a'+4096);
       }
       return p;
   }
   else{
        if(t->op=='='){
            int q= codegen(t->right,fp);
            fprintf(fp,"MOV [%d],R%d\n",t->left->varname[0]-'a'+4096,q);
            freereg();
            return -1;
        }
        if(t->type==READY){
             ready(fp,t->left->varname);
             return -1;
        }
        if(t->type==WRITEY){
            int q= codegen(t->left,fp);
            writey(fp,q);
            freereg();
            return -1;
        }
        if(t->type==STATEMENT){
             codegen(t->left,fp);
            codegen(t->right,fp);
            return -1;
        }   
        int p= codegen(t->left,fp);
        int q= codegen(t->right,fp);
        switch((t->op)){
            case '+' : fprintf(fp,"ADD R%d,R%d\n",p,q);break;
            case '-' : fprintf(fp,"SUB R%d,R%d\n",p,q);break;
            case '*' :fprintf(fp,"MUL R%d,R%d\n",p,q);break;
            case '/' :fprintf(fp,"DIV R%d,R%d\n",p,q);break;
        }
        freereg();
        return p;
   }
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
int eval(struct tnode*t){
    if(t==NULL){
        return -1;
    }  
    if(t->right==NULL&&t->left==NULL){
        if(t->type==INTEGER){
            return t->val;
        }
        if(t->type==VARIABLE){
            return var[t->varname[0]-'a'];
        }
    }
    else{
        if(t->op=='='){
           int p=eval(t->right);
           var[t->left->varname[0]-'a']=p;
           return -1;

        }
        if(t->type==WRITEY){
            printf("%d\n",var[t->left->varname[0]-'a']);
            return -1;
        }
        if(t->type == READY){
    int x;

    FILE *tty = fopen("/dev/tty", "r");
    if(tty == NULL){
        printf("Error opening tty\n");
        exit(1);
    }

    printf("Enter value: ");
    fflush(stdout);

    fscanf(tty, "%d", &x);

    fclose(tty);
    var[t->left->varname[0] - 'a'] = x;

    return -1;
}
        if(t->type==STATEMENT){
            eval(t->left);
            eval(t->right);
            return -1;
        }
        int d=eval(t->left);
        int e= eval(t->right);
        switch(t->op){
            case '+': return d+e;
            case '*': return d*e;
            case '-': return d-e;
            case '/': return d/e;
        }
    }
}