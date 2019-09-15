// Calculator.h
// Dan Nguyen

#ifndef CALCULATOR_H
#define CALCULATOR_H

#define FALSE   0
#define TRUE    !FALSE

// Function Prototype Declarations
void input(char* expression);
void convert(Stack s, char* expression);
void evaluate(Stack s);
void output(Stack s);

#endif // CALCULATOR_H
