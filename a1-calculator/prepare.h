#ifndef PREPEAR
#define PREPEAR

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

/* The global switcher for output the info about the process of solving. */
#define DEBUG false

/* The global switcher for output the info about usage. */
#define USAGE false

/* Show usage of program. */
void showUsage();


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


string getUserString();
#endif // PREPEAR
