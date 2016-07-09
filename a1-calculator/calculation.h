// calculation.h
// Header file for calculation functions.

#ifndef CALCULATION
#define CALCULATION

#include "configuration.h"
/* Calculate the equation. */
string calculate(string equation);

/* Transform the string into a vector of strings. */
vector<string> transformEquationStringToVector(string equation);

/* Transform the equation vector from infix notation to postfix notation. */
vector<string> transformINtoRPN(vector<string> eVector);

/* Checks if a character is a number. */
bool isNumber(char ch);

/* Get priority of input string. */
int getPriority(string s);

/* Solve first operator in equation vector. */
vector<string> solveOneStep(vector<string> equationVector);

#endif // CALCULATION
