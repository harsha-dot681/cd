#include<stdio.h>
#include<stdlib.h>
#include "parsetree.h"
int count=0;
int arr[20]={0};
struct tnode* makeLeafNode(int n){
   struct tnode*temp=malloc(sizeof(struct tnode));
    temp->op=NULL;
    temp->val=n;
    temp->left=NULL;
    temp->right=NULL;
    return temp;
}
struct tnode* makeOperatorNode(char op,struct tnode *l,struct tnode *r){
   struct tnode*temp=malloc(sizeof(struct tnode));
    temp->left=l;
    temp->right=r;
    temp->op=malloc(sizeof(char));
    *(temp->op)=op;
    return temp;
}
void prefix(struct tnode*root){
    if(root!=NULL){
        if(root->op!=NULL){
            printf("%s",root->op);
        }
        else{
            printf("%d",root->val);
        }
        prefix(root->left);
        prefix(root->right);
    }
}
void postfix(struct tnode*root){
    if(root!=NULL){
        postfix(root->left);
        postfix(root->right);
        if(root->op!=NULL){
            printf("%s",root->op);
        }
        else{
            printf("%d",root->val);
        }
    }
}
void inorder(struct tnode*root,int*count ){
    if(root){
        (*count)++;
        inorder(root->left,count);
        inorder(root->right,count);
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
    exit(0);
}
void freereg(){
    for(int i=19;i>=0;i--){
        if(arr[i]==1){
            arr[i]=0;
            return;
        }
    }
}
reg_index codeGen( struct tnode *t,FILE*fp) {
   if(t->left==NULL&&t->right==NULL){
       int p=getreg();
        if(p==-1){
            printf("no register available");
            return -1;
        }
        fprintf(fp,"MOV R%d,%d\n",p,t->val);
        return p;
   }
   else{
       int p= codeGen(t->left,fp);
       int q = codeGen(t->right,fp);
        switch(*(t->op)){
            case '+' : fprintf(fp,"ADD R%d,R%d\n",p,q);break;
            case '-' : fprintf(fp,"SUB R%d,R%d\n",p,q);break;
            case '*' :fprintf(fp,"MUL R%d,R%d\n",p,q);break;
            case '/' :fprintf(fp,"DIV R%d,R%d\n",p,q);break;
        }
        freereg();
        return p;
   }
}
int eval(struct tnode* t){
    if(t->left==NULL&&t->right==NULL){
        return t->val;
    }
    else{
        int p=eval(t->left);
        int q=eval(t->right);
        switch(*(t->op)){
            case '+' : return p+q;
            case '-' : return p-q;
            case '*' : return p*q;
            case '/' : return p/q;
    }
}
}