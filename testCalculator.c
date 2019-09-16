// testCalculator.c
// Dan Nguyen

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Stack.h"
#include "Calculator.h"

void testLoop(Stack s, char* infix) {
    reset(s);
    convert(s, infix);
    evaluate(s);
    output(s);
}

void checkAnswer(Stack s, double answer) {
    if (s->valStack[s->valTop] == answer) {
        printf("Passed!\n\n");
    } else {
        printf("Failed! Answer = %f\n", answer);
    }
}

void testCalculator(Stack s) {
    
    additionTest(s);
    /*subtractionTest(s);
    multiplicationTest(s);
    divisionTest(s);
    powerTest(s);
    factorialTest(s);*/
}

void additionTest(Stack s) {

    char infix[MAX_INPUT];
    char answer[MAX_INPUT];

    // int + int
    strcpy(infix, "1941 + 319\n");
    testLoop(s, infix);
    checkAnswer(s, 2260);

    // float + float
    strcpy(infix, "1931.1391041 + 4294.191000\n");
    testLoop(s, infix);
    checkAnswer(s, 6225.330104);

    // float + int
    strcpy(infix, "1931.1391041 + 4294\n");
    testLoop(s, infix);
    checkAnswer(s, 6225.139104);

    // int + float
    strcpy(infix, "4911 + 648.194108\n");
    testLoop(s, infix);
    checkAnswer(s, 5559.194108);

    // ++
}

void subtractionTest(Stack s) {
    
    // int - int

    // float - float

    // - float - int

    // int - float

    // --

    // +-

    // -+

    // ---

    // ----
}

void multiplicationTest(Stack s) {
    
    // int * int

    // float * float

    // int * float

    // float * int

    // **

    // int * -int

    // -int * int

    // float * - float

    // -float * float
}

void divisionTest(Stack s) {


}

void powerTest(Stack s) {


}

void factorialTest(Stack s) {


}