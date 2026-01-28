#define PROGRAM 0
#define STATEMENT 1
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
#define reg_index int;
typedef struct tnode {
    int val;        // value of a number for NUM nodes.
    int type;       // type of variable
    char* varname;  // name of a variable for ID nodes
    int nodetype;   // information about non-leaf nodes - read/write/connector/+/* etc.
    struct tnode *left,*right;  // left and right branches
    char*s; //string repersentation of the node
    char op; //to repersent operand type
}tnode;

/*Create a node tnode*/
struct tnode *makeConstantNode(int, int, char *);
struct tnode *makeVariableNode(int, char*, char *);
struct tnode *makeStmtNode(int, struct tnode *, struct tnode *, char *);
struct tnode *makeExprNode(int, char, struct tnode*, struct tnode *, char *);
void print(struct tnode*,int);
int getreg();
void freereg();
reg_index codegen(struct tnode*,FILE*);
void ready(FILE*, char*);
void writey(FILE*, int);
int eval(struct tnode*);