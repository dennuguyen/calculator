// Convert.c
// Dan Nguyen

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "Calculator.h"

// External Helper Functions
extern int isDecimalPoint(char token);
extern int isOperator(char token);

// Static Helper Functions
static int precedence(char token);
static int isLeftParenthesis(char token);
static int isRightParenthesis(char token);

// converts infix expressions to postfix
// operands are pushed into postfix expression
// operators are pushed into opStack then popped from opStack into postfix expression
void convert(Stack s, char* infix) {

    // i is position index of infix expression
    // j is position index of postfix expression
    int i, j;

    // pass through the infix expression
    for (i = 0, j = -1; infix[i] != '\0'; i++) {

        // assign operands to postfix expression
        if (isdigit(infix[i]) || isalpha(infix[i]) || isDecimalPoint(infix[i])) {

            s->postfix[++j] = infix[i];

        // push left parenthesis to operator stack
        } else if (isLeftParenthesis(infix[i])) {

            // operator must exist before '('
            // exclude if space exists before '(' or if at beginning of infix
            if (!isOperator(infix[i - 1]) && i > 0 && !isspace(infix[i - 1])) {
                fprintf(stderr, "\nError: Invalid Expression. Check operator before '('.\n\n");
                exit(1);
            }

            pushOperators(s, infix[i]);

        // if encounter a right parenthesis
        // pop operators from operator stack to postfix expression
        // until left parenthesis
        } else if (isRightParenthesis(infix[i])) {

            while (!isOpStackEmpty(s) && !isLeftParenthesis(peekOperators(s))) {
                s->postfix[++j] = popOperators(s);
            }

            // remove left parenthesis from opStack
            assert(isLeftParenthesis(peekOperators(s)));
            popOperators(s);

        // push operator into operator stack unless its precedence is greater than the top operator
        // in operator stack; then assign it to postfix expression
        } else if (isOperator(infix[i])) {

            while (!isOpStackEmpty(s) && precedence(infix[i]) <= precedence(peekOperators(s))) {
                s->postfix[++j] = popOperators(s);
            }

            // pushing the found operator into the operator stack
            pushOperators(s, infix[i]);

            // space distinguishes numbers in postfix expression
            s->postfix[++j] = ' ';
        }
    }

    // while there are still operators in the operator stack
    while (!isOpStackEmpty(s)) {
        s->postfix[++j] = popOperators(s);
    }

    // mark end of the string
    s->postfix[++j] = '\0';
}

// checks and returns TRUE if token is a decimal point; FALSE otherwise
extern int isDecimalPoint(char token) {

    if (token == '.') {
        return TRUE;
    }

    return FALSE;
}

// checks and returns TRUE if token is an operator; FALSE otherwise
extern int isOperator(char token) {

    if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^' || token == '!') {
        return TRUE;
    }

    return FALSE;
}

// checks and returns the index of precedence of the token operator
static int precedence(char token) {

    switch (token) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
        case '!':
            return 3;/*
        case "sin":
        case "cos":
        case "tan":
            return 4;*/
    }

    fprintf(stderr, "\nERROR: INVALID TOKEN OPERATOR\n\n");
    exit(1);
}

// checks and returns TRUE is token is a left parenthesis; FALSE otherwise
static int isLeftParenthesis(char token) {

    if (token == '(') {
        return TRUE;
    }

    return FALSE;
}

// checks and returns TRUE if token is a right parenthesis; FALSE otherwise
static int isRightParenthesis(char token) {

    if (token == ')') {
        return TRUE;
    }

    return FALSE;
}
