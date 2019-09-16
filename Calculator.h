// Calculator.h
// Dan Nguyen

#ifndef CALCULATOR_H
#define CALCULATOR_H

#define FALSE   0
#define TRUE    !FALSE

// Function Prototype Declarations
void input(Stack s, char* expression);
void convert(Stack s, char* expression);
void evaluate(Stack s);
void output(Stack s);

// Test Calculator Function Prototype Declarations
void testLoop(Stack s, char* infix);
void checkAnswer(Stack s, double answer);
void testCalculator(Stack s);
void additionTest(Stack s);

#endif // CALCULATOR_H
