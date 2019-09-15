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

    char expression[MAX_INPUT];

    // initialise the stack once
    Stack s = stackMemory();

    while (1) {

        // reset the information in the stack
        reset(s);

        // get the expression
        printf("> ");
        input(expression);

        // if expression matches kill command line
        if (strncmp(expression, "q", 1) == 0 || strncmp(expression, "exit", 4) == 0) {
            printf("...EXITING...\n\n");
            exit(0);
        }

        // get the expression in postfix
        convert(s, expression);

        // calculate the postfix expression
        evaluate(s);

        // print the result of calculation
        output(s);
    }

    return 0;
}

// input uses fgets to take string from stdin and put it in expression
void input(char* expression) {
    fgets(expression, MAX_INPUT, stdin);
}

// output prints the top and final value in the stack
void output(Stack s) {
    assert(s->valTop == 0);
    printf("> %lf\n", s->valStack[0]);
}
