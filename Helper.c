// Helper.c
// Dan Nguyen

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "Calculator.h"
#include "Helper.h"

// checks and returns TRUE if token is a decimal point; FALSE otherwise
int isDecimalPoint(char token) {

    if (token == '.') {
        return TRUE;
    }

    return FALSE;
}

// checks and returns TRUE if token is an operator; FALSE otherwise
int isOperator(char token) {

    if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^' || token == '!') {
        return TRUE;
    }

    return FALSE;
}

// checks and returns the index of precedence of the token operator
int precedence(char token) {

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
int isLeftParenthesis(char token) {

    if (token == '(') {
        return TRUE;
    }

    return FALSE;
}

// checks and returns TRUE if token is a right parenthesis; FALSE otherwise
int isRightParenthesis(char token) {

    if (token == ')') {
        return TRUE;
    }

    return FALSE;
}

// resolves the signage of a consecutively signs by checking the operator stack
// only considers -(-1) -> 1--
static char resolveSign(Stack s, char token) {

    // consider initial operator
    if (isOpStackEmpty(s)) {
        return token;
    }

    // only consider '-' and +'
    if (precedence(s->opStack[s->opTop]) == 1) {

        // consider same sign
        if (s->opStack[s->opTop] == s->opStack[s->opTop - 1]) {
            popOperators(s);    
            return '+';

        } else {
            // consider different sign
            popOperators(s);
            return '-';
        }
    }
}

// resolves the signage of a consecutively signed value and pushes the value
// into the value stack
static void resolveValue(Stack s, int i) {

    if (s->postfix[i] != '+' && s->postfix[i] != '-' && s->postfix[i - 1] != '+' && s->postfix[i - 1] != '-') {
        return;
    }
    
    if (s->postfix[i] == s->postfix[i - 1]) {
        pushValues(s, abs(popValues(s)));

    } else {
        pushValues(s, -abs(popValues(s)));
    }
}

// calculate pops the required number of values from the top of valStack
// and pops the top operator from opStack then calculates the popped tokens
static void calculate(Stack s, char token) {

    double a, b;

    switch (token) {

        // addition
        case '+':
            a = popValues(s);
            b = popValues(s);
            pushValues(s, a + b);
            break;

        // subtraction
        case '-':
            a = popValues(s);
            b = popValues(s);
            pushValues(s, b - a);
            break;

        // multiplication
        case '*':
            a = popValues(s);
            b = popValues(s);
            pushValues(s, a * b);
            break;

        // division
        case '/':
            a = popValues(s);
            b = popValues(s);
            pushValues(s, b / a);
            break;

        // power
        case '^':
            a = popValues(s);
            b = popValues(s);
            pushValues(s, power(b, a));
            break;

        // factorial
        case '!':
            pushValues(s, factorial(popValues(s)));
            break;
/*
        // cos
        case "cos":
            break;*/
    }
}

// calculates factorials
// function data type is long long int which must be same data type as returning value
// precise up to 20!
static long long int factorial(long long int value) {

    for (int index = value - 1; index > 0; index--) {
        value *= index;
    }

    return value;
}

// calculates powers
// precise up to 2^1023
static long double power(long double b, long double a) {

    long double value = b;

    for (int i = 1; i < a; i++) {
        value *= b;
    }

    return value;
}
