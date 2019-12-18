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
        default:
            return -1;
    }

    fprintf(stderr, "\nERROR: INVALID TOKEN OPERATOR\n\n");
    exit(1);
}
