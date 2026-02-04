#define inttype 1
#define booltype 0
#define PROGRAM 16
#define STATEMENT 15
#define EXPRESSION 2
#define VARIABLE 3
#define INPUT 4
#define OUTPUT 5
#define ASSIGNMENT 6
#define PLUS 7
#define MINUS 8
#define MUL 9
#define DIV 10
#define CONSTANT 11
#define INTEGER 12
#define READY 13
#define WRITEY 14
#define LOGICAL 17
#define CONDITIONAL 18
#define LOOP 19
#define reg_index int;
#define BREAK 20
#define CONTINUE 21
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct tnode{
    int val;        // value (for constants)
    int type;       // type of the variable
    char* varname;  // variable name (for variable nodes)
    int nodetype;   // node type - asg/opertor/if/while etc.
    struct tnode *left,*right;  //left and right branches
    char*s;
    char*op;
    struct tnode* mid;
}tnode;
/*Create a node tnode*/
void ready(FILE*fp,char*s);
struct tnode* makeConstantNode(int val, int type, char *s);
struct tnode* makeVariableNode(int type, char*varname, char *s);
struct tnode* makelogicalNode(int type,char*op, struct tnode* left, struct tnode* right, char* s);
struct tnode* makeStmtNode(int types, struct tnode *l, struct tnode *r, char *s);
struct tnode* makeExprNode(int type, char*op , struct tnode*l, struct tnode *r, char *s);
struct tnode* makeifelseNode(int type, struct tnode*left,struct tnode*mid, struct tnode*right, char* s);
struct tnode* makeifnode(int type, struct tnode*left, struct tnode*right, char* s);
struct tnode* makeLoopNode(int type, struct tnode*left, struct tnode*right, char* s);
struct tnode* make_break_continue(int type,char* s);
struct tnode* dowhile(int type, struct tnode*left, struct tnode*right, char* s);
struct tnode* repeatuntil(int type, struct tnode*left, struct tnode*right, char* s);
/*Evaluate the parse tree*/
int eval(struct tnode*t);   
/*Generate code for the parse tree*/
reg_index codegen( struct tnode *t,FILE*fp);
reg_index codegen1( struct tnode *t,FILE*fp,int breaklabel,int continuelabel);
reg_index codegen2( struct tnode *t,FILE*fp,int breaklabel,int continuelabel);
void writey(FILE*fp,int p);
void freereg();
int getreg();
int getLabel();
