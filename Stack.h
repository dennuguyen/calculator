// Stack.h
// Dan Nguyen

#ifndef STACK_H
#define STACK_H

#define MAX_INPUT   50
#define EMPTY       -1

typedef struct _stack* Stack;

typedef struct _stack {

    // stack implementation using arrays
    // values and operators have their own stacks
    double      valStack[MAX_INPUT];
    char        opStack[MAX_INPUT];

    // gives the position of the top node of stack
    int         valTop;
    int         opTop;

    // post-fix expression
    char        postfix[MAX_INPUT];

} stack;

// Stack Functions
Stack stackMemory(void);
void reset(Stack s);
int isOpStackEmpty(Stack s);
int isValStackEmpty(Stack s);
double peekValues(Stack s);
char peekOperators(Stack s);
void pushValues(Stack s, long double val);
void pushOperators(Stack s, char op);
double popValues(Stack s);
char popOperators(Stack s);
void destroyStack(Stack s);

#endif // STACK_H
