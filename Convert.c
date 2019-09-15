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
void convert(Stack s, char* expression) {

    // i is position index of infix expression
    // j is position index of postfix expression
    int i, j;

    // pass through the infix expression
    for (i = 0, j = -1; expression[i] != '\0'; i++) {

        // assign operands to postfix expression
        if (isdigit(expression[i]) || isalpha(expression[i]) || isDecimalPoint(expression[i])) {

            s->postfix[++j] = expression[i];

        // push left parenthesis to operator stack
        } else if (isLeftParenthesis(expression[i])) {

            // operator must exist before '('
            // exclude if space exists before '(' or if at beginning of expression
            if (!isOperator(expression[i - 1]) && i > 0 && !isspace(expression[i - 1])) {
                fprintf(stderr, "Error: Invalid Expression. Check operator before '('.");
                free(s);
                return;
            }

            pushOperators(s, expression[i]);

        // if encounter a right parenthesis
        // pop operators from operator stack to postfix expression
        // until left parenthesis
        } else if (isRightParenthesis(expression[i])) {

            while (!isOpStackEmpty(s) && !isLeftParenthesis(peekOperators(s))) {
                s->postfix[++j] = popOperators(s);
            }

            // remove left parenthesis from opStack
            assert(isLeftParenthesis(peekOperators(s)));
            popOperators(s);

        // push operator into operator stack unless its precedence is greater than the top operator
        // in operator stack; then assign it to postfix expression
        } else if (isOperator(expression[i])) {

            while (!isOpStackEmpty(s) && precedence(expression[i]) <= precedence(peekOperators(s))) {
                s->postfix[++j] = popOperators(s);
            }

            // pushing the found operator into the operator stack
            pushOperators(s, expression[i]);

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
