// Stack.c
// Dan Nguyen

#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"

// stackMemory allocates memory for a stack struct called s
Stack stackMemory(void) {

    Stack s = malloc(sizeof(struct _stack));

    if (s == NULL) {
        fprintf(stderr, "\nERROR: NO MEMORY ALLOCATED\n\n");
        exit(1);
    }

    return s;
}

// Resets opTop and valTop to -1 to indicate stacks are empty
// since opTop and valTop represents the position of the top token
void reset(Stack s) {
    s->opTop = EMPTY;
    s->valTop = EMPTY;
}

// Checks if operator stack is empty
int isOpStackEmpty(Stack s) {
    return s->opTop == EMPTY;
}

// Checks if value stack is empty
int isValStackEmpty(Stack s) {
    return s->valTop == EMPTY;
}

// Peeks at the top of the value stack
double peekValues(Stack s) {

    // value stack is empty
    if (isValStackEmpty(s)) {
        return EMPTY;
    }

    return s->valStack[s->valTop];
}

// Peeks at top of the operator stack
char peekOperators(Stack s) {

    // operator stack is empty
    if (isOpStackEmpty(s)) {
        return EMPTY;
    }

    return s->opStack[s->opTop];
}

// Pushes values into the value stack
void pushValues(Stack s, long double val) {

    // check if stack is full
    if (s->valTop == MAX_INPUT) {
        fprintf(stderr, "\nERROR: TRIED TO PUSH FULL STACK\n\n");
        exit(1);
    }
    
    s->valStack[++s->valTop] = val;
}


// Pushes operators into the operator stack
void pushOperators(Stack s, char op) {

    // check if stack is full
    if (s->valTop == MAX_INPUT) {
        fprintf(stderr, "\nERROR: TRIED TO PUSH FULL STACK\n\n");
        exit(1);
    }

    s->opStack[++s->opTop] = op;
}

// Pops (and returns) the top of the value stack
double popValues(Stack s) {

    // check if stack is empty
    if (isValStackEmpty(s)) {
        fprintf(stderr, "\nERROR: TRIED TO POP EMPTY VALUE STACK\n\n");
        exit(1);
    }

    return s->valStack[s->valTop--];
}

// Pops (and returns) the top of the operator stack
char popOperators(Stack s) {

    // check if stack is empty
    if (isOpStackEmpty(s)) {
        fprintf(stderr, "\nERROR: TRIED TO POP EMPTY OPERATOR STACK\n\n");
        exit(1);
    }

    return s->opStack[s->opTop--];
}

// Destroys the stack struct by freeing allocated memory for stack
void destroyStack(Stack s) {
    free(s);
}
