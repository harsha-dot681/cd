
#include <stdlib.h>
#include <stdio.h>
typedef struct tnode{
    int val;
    char *op; //indicates the name of the operator for a non leaf node
    struct tnode *left, *right; //left and right branches
} tnode;

//#define YYSTYPE tnode*
struct tnode* makeLeafNode(int n);

/*Make a tnode with operator, left and right branches set*/
struct tnode* makeOperatorNode(char op,struct tnode *l,struct tnode *r);
#define reg_index int;
reg_index getreg();
void freeReg(int p);
void prefix(struct tnode*root);
void postfix(struct tnode*root);
void inorder(struct tnode*root,int*count );
reg_index codeGen(struct tnode*root,FILE*fp);
int evaluate(struct tnode*root);