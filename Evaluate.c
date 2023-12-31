// Evaluate.c
// Dan Nguyen

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "Stack.h"
#include "Calculator.h"
#include "Helper.h"

// Static Helper Functions
static int flop(Stack s, int i, int isNegated);
static void calculate(Stack s, char token);
static long long int factorial(long long int value);
static long double power(long double b, long double a);

// evaluates the postfix expression
void evaluate(Stack s) {

    // iterates through the postfix expression until '\0'
    // encountering an operator calculates the sub-expression which is pushed into valStack
    // values are pushed into valStack
    for (int i = 0; s->postfix[i] != '\0'; i++) {
        
        if (isOperator(s->postfix[i])) {

            // operator is at beginning of string
            if (s->postfix[i] == 0) {
                // do nothing

            // if operator is unary
            } else if (isdigit(s->postfix[i + 1]) && precedence(s->postfix[i]) == 1) {
                
                // flag if the unary operator is negation
                if (s->postfix[i++] == '-') {
                    i = flop(s, i, TRUE);
                } else {
                    i = flop(s, i, FALSE);
                }
                
            } else {
                // calculate the stack
                calculate(s, s->postfix[i]);
            }
        } else if (isdigit(s->postfix[i]) || isalpha(s->postfix[i]) || isDecimalPoint(s->postfix[i])) {

            i = flop(s, i, FALSE);
        }
    }
}

// flop is an algorithm to determine the double value from an array of char
static int flop(Stack s, int i, int isNegated) {

    double value = 0.0;

    // loop through number
    for (; !isspace(s->postfix[i]) || s->postfix[i] != '\0'; i++) {

        // !digit is indicator for when a sequence of digits ends
        // do not break if token is a decimal point
        // i-- because performed extra loop
        if (!isdigit(s->postfix[i]) && !isDecimalPoint(s->postfix[i])) {
            goto end;
        }

        // add numbers after decimal place
        if (isDecimalPoint(s->postfix[i])) {
            
            // skip decimal point
            i++;

            // use different algorithm when decimal place is encountered
            for (double divisor = 1.0; !isspace(s->postfix[i]) || s->postfix[i] != '\0'; i++) {
                
                if (isDecimalPoint(s->postfix[i])) {
                    fprintf(stderr, "\nError: Invalid Expression. Check decimal place.\n\n");
                    exit(1);
                }

                // break loop if found space, nondigit token or decimal point
                if (!isdigit(s->postfix[i]) || isspace(s->postfix[i])) {
                    goto end;
                }
                
                divisor *=  10.0;
                value = value + (s->postfix[i] - '0')/divisor;
            }
        } else {
            // add numbers before decimal place
            value = (value * 10.0) + (s->postfix[i] - '0');
        }
    }
    
    // natural termination of for loop
    return i;

    // flop termination of for loop
    end: ;

    if (isNegated) {
        value *= -1;
    }

    pushValues(s, value);

    return --i;
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
