// Convert.c
// Dan Nguyen

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "Calculator.h"
#include "Helper.h"

// Static Helper Functions
static char* deblank(char* input);
static int isLeftParenthesis(char token);
static int isRightParenthesis(char token);
static int isUnaryOperator(char* infix, int i);

// converts infix expressions to postfix
// operands are pushed into postfix expression
// operators are pushed into opStack then popped from opStack into postfix expression
void convert(Stack s, char* infix) {

    // deblank the infix expression
    deblank(infix);

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
            
            if (isUnaryOperator(infix, i)) {
                
                // k is '-' count
                int k;
                char sign;

                // simplify multiple negation
                for (k = 0; precedence(infix[i]) == 1; i++) {
                    if (infix[i] == '-') {
                        k++;
                    }
                }

                if (k % 2 == 0) {
                    sign = '+';
                } else {
                    sign = '-';
                }

                // assign the sign
                s->postfix[++j] = sign;

                // assign the operand
                s->postfix[++j] = infix[i];

            } else {
                while (!isOpStackEmpty(s) && precedence(infix[i]) <= precedence(peekOperators(s))) {
                    s->postfix[++j] = popOperators(s);
                }

                // pushing the found operator into the operator stack
                pushOperators(s, infix[i]);

                // space distinguishes numbers in postfix expression
                s->postfix[++j] = ' ';
            }
        }
    }

    // while there are still operators in the operator stack
    while (!isOpStackEmpty(s)) {
        s->postfix[++j] = popOperators(s);
    }

    // mark end of the string
    s->postfix[++j] = '\0';
}

// removes all white space from the infix expression
static char* deblank(char* input) {

    int i, j;
    char* output = input;

    for (i = 0, j = 0; i < strlen(input); i++, j++) {
        if (input[i] != ' ') {
            output[j] = input[i];
        } else {
            j--;
        }
    }

    output[j] = '\0';

    return output;
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

// differentiates unary and binary operators
static int isUnaryOperator(char* infix, int i) {
    
    // i is the index of the unary operator
    if (precedence(infix[i]) == 1) {

        // consider beginning of expression
        if (i == 0) {
            return TRUE;

        // consider after '('
        } else if (infix[i - 1] == '(') {
            return TRUE;

        // consider after binary operator
        } else if (isOperator(infix[i - 1])) {
            return TRUE;
        }
    }

    return FALSE;
}
