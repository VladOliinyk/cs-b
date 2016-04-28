#ifndef PREPEAR
#define PREPEAR

#include "configuration.h"

using namespace std;

/* Translate the arguments from the console into the equations string. */
string argsToString(int argc, char** argv);

/* Check the input string for correctness. */
bool inputIsCorrect(string str);

/* Counts the number of unpaired brackets. */
int numberOfUnpairedParentheses(string str);

/* Write the forbidden characters if exist. */
string haveForbiddenCharacters(string str);

/* Fix the equation string. */
string fixEquation(string str);

/* Removes white space. */
string deleteSpaces(string str);

/* Fix the repetitive characters. */
string fixRepeteSigns(string str);

/* Corrects the entry of negative numbers. */
string fixNegativeVariables (string str);

#endif // PREPEAR
