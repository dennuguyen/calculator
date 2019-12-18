// Helper.h
// Dan Nguyen

#ifndef HELPER_H
#define HELPER_H

// Helper Functions
int isDecimalPoint(char token);
int isOperator(char token);
int precedence(char token);

// Helper Functions used in Convert.c
int isLeftParenthesis(char token);
int isRightParenthesis(char token);

// Helper Functions used in Simplify.c
char resolveSign(Stack s, char token);

// Helper Functions used in Evaluate.c
void resolveValue(Stack s, int i);
void calculate(Stack s, char token);
long long int factorial(long long int value);
long double power(long double b, long double a);

#endif // HELPER_H