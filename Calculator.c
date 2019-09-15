// Calculator.c
// Dan Nguyen

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "Calculator.h"

// Identification of Main Components:
// 1. input
// 2. infix to postfix converter
// 3. evaluate
// 4. output
int main(void) {

    char infix[MAX_INPUT];

    // initialise the stack once
    Stack s = stackMemory();

    while (1) {

        // reset the information in the stack
        reset(s);

        // get the infix expression
        printf("> ");
        input(infix);

        // if infix expression matches kill command line
        if (strncmp(infix, "q", 1) == 0 || strncmp(infix, "exit", 4) == 0) {
            printf("...EXITING...\n\n");
            exit(0);
        }

        // get the expression in postfix
        convert(s, infix);

        // calculate the postfix expression
        evaluate(s);

        // print the result of calculation
        output(s);
    }

    return 0;
}

// input uses fgets to take string from stdin and put it in infix
void input(char* infix) {
    fgets(infix, MAX_INPUT, stdin);
}

// output prints the top and final value in the stack
void output(Stack s) {
    assert(s->valTop == 0);
    printf("> %lf\n", s->valStack[0]);
}
