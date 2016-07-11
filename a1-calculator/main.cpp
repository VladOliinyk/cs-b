#include "prepare.h"
#include "calculation.h"

/*
 * The real main function.
 * Make all instead of us.
 * Gets equation string, prepare it, and solve.
*
 * @param argc - the int number of parameters passed to the main function.
 * @param argv - the array of pointers to parameters strings.
*/
void makeAll(int argc, char** argv) {
    do {
    // in configuration.h
    // show input rules
    if (USAGE)
        showUsage();

    //String of equation.
    string equation = "";

    if (argc > 1) {
        equation = argsToString(argc, argv);
    } else {
        equation = getUserString();
    }

    cout << equation << " = " << calculate(equation) << endl;
    } while (repeat());
    closeProgramManually();

    //system("pause");
}

/*
 * The main function.
*
 * @param argc - the int number of parameters passed to the main function.
 * @param argv - the array of pointers to parameters strings.
*/
int main(int argc, char** argv)
{
    makeAll(argc, argv);
    return 0;
}

/*
 * The function which returns string entered by user.
*
 * @return equation - the equation string.
*/
string getUserString() {
    string equation;
    do {
        cout << "Enter the equation: (to exit, enter 'q' as the first character)" << endl;
        //cin.ignore(); // just for sync io streams
        getline(cin, equation);
        if (inputIsCorrect(equation)) {
            if (DEBUG)
                cout << ": user equation [" << equation << "]" << endl;
            break;
        }

    } while (true);

    return equation;
}

/*
 * Translate the arguments from the console
 *  into the equations string.
*
 * @param argc - the int number of parameters passed to the main function.
 * @param argv - the array of pointers to parameters strings.
 * @return equation - the result string which contains all parameters.
*/
string argsToString(int argc, char** argv) {
    string equation;
    for (int i=1; i < argc; i++) {
        equation+=argv[i];
    }
    return equation;
}

/*
 * Fix the equation string.
 *  Removes white space.
 *  Fix repetitive characters.
 *  Corrects the entry of negative numbers.
*
 * @param str - string which need to fix.
 * @result string - fixed string.
*/
string fixEquation(string str) {
    return fixNegativeVariables(fixRepeteSigns(deleteSpaces(str)));
}

/*
 * Removes white space.
*
 * @param str - string which need to fix.
 * @result str - fixed string.
*/
string deleteSpaces(string str) {
    vector<char> vec;

    for (int i = 0; i < (int) str.size(); i++) {
        if (str.at(i) != ' ')
            vec.push_back(str.at(i));
    }

    return string(vec.begin(), vec.end());
}

/*
 * Fix the repetitive characters.
*
 * @param str - string which need to fix.
 * @result str - fixed string.
*/
string fixRepeteSigns(string str) {
    vector<char> vec;

    vec.push_back(str.at(0));
    for (int i = 1; i < (int) str.size(); i++) {
        if ( (str.at(i) != '(') &&
             (str.at(i) != ')') &&
             (str.at(i) == str.at(i-1)) &&
             (!isNumber(str.at(i))) )
            continue;
        vec.push_back(str.at(i));
    }

    if (vec.at(0) == '+') {
        string fixedString(vec.begin()+1, vec.end());
        return fixedString;
    } else if (vec.at(0) == '-') {
        string fixedString(vec.begin(), vec.end());

        return "0"+fixedString;
    } else {
        string fixedString(vec.begin(), vec.end());
        return fixedString;
    }
}


/*
 * Corrects the entry of negative numbers.
 *  Function translate expression like '(-x)' to '(0-x)'.
*
 * @param str - string which need to fix.
 * @result str - fixed string.
*/
string fixNegativeVariables (string str) {
    for (int i=0; i < (int) str.size(); i++) {
        if (str.at(i) == '(') {
            if (str.at(i+1) == '-') {
                str = str.substr(0, i) + "(0" + str.substr(i+1, str.size());
                str = deleteSpaces(str);
                i=0;
            }
        }
    }
    return str;
}

/* Show usage of program. */
void showUsage() {
    cout << endl;
    cout << "=================== USAGE ===================" << endl;
    cout << "  1. Supported operators: + - * /            " << endl;
    cout << "  2. Supported values: all integer numbers   " << endl;
    cout << "  3. Supported parentheses: ( )              " << endl;
    cout << "                                             " << endl;
    cout << "  NOTE:                                      " << endl;
    cout << "       Write all parentheses correctly.      " << endl;
    cout << "=============================================" << endl;
    cout << endl;
}

/*
 * Check the input string for correctness.
*
 * @param str - input string.
 * @return - boolean value.
*/
bool inputIsCorrect(string str) {

    if (str.size() == 0) {
        cout << endl;
        cout << "WARNING: input incorrect." << endl;
        cout << "Please enter the equation next time." << endl;
        cout << endl;
        return false;
    }

    if (str.size() == 1) {
        if (str.at(0) == 'q') {
            closeProgramManually();
        }
    }

    if (numberOfUnpairedParentheses(str) != 0) {
        cout << endl;
        cout << "WARNING: input incorrect." << endl;
        cout << "Please write all parentheses correctly next time." << endl;
        cout << endl;
        return false;
    }

    string forbiddenCharacters = haveForbiddenCharacters(str);
    if ( forbiddenCharacters.size() != 0 ) {
        cout << endl;
        cout << "WARNING: input incorrect." << endl;
        cout << "Please do not use this characters next time:" << endl;
        cout << ":" << forbiddenCharacters << " :" << endl;
        cout << endl;
        return false;
    }

    return true;
}

/*
 * Counts the number of unpaired brackets.
*
 * @param str - input string.
 * @return result - cout of unpaired brackets.
*/
int numberOfUnpairedParentheses(string str) {
    int result = 0;

    for (int i=0; i < str.size(); i++) {
        if (str.at(i) == '(')
            result++;
        if (str.at(i) == ')')
            result--;
    }

    return result;
}

/*
 * Write the forbidden characters if exist.
*
 * @param str - input string.
 * @return fc - string of forbidden characters.
*/
string haveForbiddenCharacters(string str) {
    string fc = "";
    char allowedCharacters[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                '+', '-', '*', '/',
                                '(', ')',
                                ' '
                               };
    // size = 17 characters = 10 numbers + 4 operators + 2 parentheses + 1 space
    int size = 17;

    for (int i=0; i < str.size(); i++) {
        bool isCurCharForbidden = true;

        for (int j=0; j < size; j++) {
            if (str.at(i) == allowedCharacters[j]) {
                isCurCharForbidden = false;
                break;
            }
        }

        if (isCurCharForbidden) {
            fc = fc + " " + str.at(i);
        }
    }

    return fc;
}

/*
 * Function that asks user for one more solve equation cycle.
 * @return bool answer.
 */
bool repeat() {
    string answer;
    do {
        cout << "Solve one more equation? (enter 'y' to repeat; enter 'n' - to exit) : ";
        //cin.ignore(); // just for sync io streams
        getline(cin, answer);
        if (answer.size() > 0) {
            if (answer.at(0) == 'y') {
                return 1;
            }
            if (answer.at(0) == 'n') {
                return 0;
            }
        }

    } while (true);

}

/* Function that close program with farewell message. */
void closeProgramManually() {
    cout << "Glad to see you again, brah!" << endl;
    exit(0);
}
