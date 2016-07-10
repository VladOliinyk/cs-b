#include "prepare.h"
#include "calculation.h"

using namespace std;

/*
 * Calculate the equation.
*
 * @param equation - equation string.
 * @return result - result of equation.
*/
string calculate(string equation) {

    equation = fixEquation(equation);
    if (DEBUG)
        cout << ": fixed equation [" << equation << "]" << endl;

    if (DEBUG) {
        cout << ": START OF calculate METHOD" << endl;
        cout << ":  calculate func input [" << equation << "]" << endl;
    }

    string result = "";

    vector<string> equationVector = transformEquationStringToVector(equation);

    if (DEBUG) {
        cout << ":  equation in infix notation: ";
        for (int i=0; i < equationVector.size(); i++) {
            cout << equationVector.at(i) << " ";
        }
        cout << endl;
    }

    equationVector = transformINtoRPN(equationVector);

    if (DEBUG) {
        cout << ":  equation in postfix notation: ";
        for (int i=0; i < equationVector.size(); i++) {
            cout << equationVector.at(i) << " ";
        }
        cout << endl;
    }

    // solving equation step by step
    if (DEBUG) {
        cout << ":  solving equation step by step:" << endl;
    }
    vector<string> tempVector = equationVector;
    while (tempVector.size() != 1) {
        if (DEBUG) {
            cout << ":    current vector: ";
            for (int i=0; i<tempVector.size(); i++) {
                cout << tempVector.at(i) << " ";
            }
            cout << endl;
        }
        tempVector = solveOneStep(tempVector);
        if (DEBUG) {
            cout << ":    after step: ";
            for (int i=0; i<tempVector.size(); i++) {
                cout << tempVector.at(i) << " ";
            }
            cout << endl;
        }
    }

    for (int i=0; i < tempVector.size(); i++) {
        string tempString;
        stringstream ve2s;
        ve2s << tempVector.at(i);
        ve2s >> tempString;
        result+=tempString;
    }

    return result;
}

/*
 * Transform the string into a vector of strings.
 *  Each vector element is either the number or the operation sign.
*
 * @param str - string which need to transform.
 * @return rezVector - vector of strings.
 */
vector<string> transformEquationStringToVector(string str) {

    vector<string> rezVector;

    rezVector.push_back(str.substr(0, 1));

    for (int i=1; i < str.size(); i++) {
        string currentStrSymbol = str.substr(i, 1);

        if ( isNumber(currentStrSymbol.at(0)) ) {
            if ( !isNumber(rezVector.back().at(0))) {
                rezVector.push_back(currentStrSymbol);
            } else {
                rezVector.back()+=currentStrSymbol;
            }
        } else {
            rezVector.push_back(currentStrSymbol);
        }
    }
    return rezVector;
}

/*
 * Transform the equation vector
 *  from infix notation
 *  to postfix notation.
 * Algorithm: http://natalia.appmat.ru/c&c++/postfisso.html
*
 * @param eVector - equation vector in infix notation;
 * @result oVector - equation vector in postfix notation;
*/
vector<string> transformINtoRPN(vector<string> eVector) {
    if (DEBUG)
        cout << ":    crearing vectors for output and stack";
    vector<string> oVector; // output
    vector<string> sVector; // stack
    if (DEBUG)
        cout << " [completed]" << endl;

    if (DEBUG) {
        cout << ": start checing each element from vector: ";
        for (int i=0; i<eVector.size(); i++)
            cout << "[" << eVector.at(i) << "]";
        cout << endl;
    }
    for (int i=0; i < eVector.size(); i++) {
        if (DEBUG)
            cout << ": : now " << i << " of " << eVector.size() << endl;
        string currentStr = eVector.at(i);
        if (DEBUG)
            cout << ":       current string: [" << currentStr << "]" << endl;

        //step #1
        if (DEBUG)
            cout << ":    1: is [" << currentStr << "] (cur string) a number? ";
        if ( isNumber(currentStr.at(0)) ) {
            if (DEBUG)
                cout << " - Yes." << endl;
            if (DEBUG)
                cout << ":       push [" << currentStr << "] (cur string) to output vector";
            oVector.push_back(currentStr);
            if (DEBUG)
                cout << " [completed]";
            continue;
        } else {
            if (DEBUG)
                cout << " - No." << endl;
            //step #3
            if (DEBUG)
                cout << ":    3: is [" << currentStr << "] (cur string) equal '(' ?";
            if (currentStr == "(") {
                if (DEBUG)
                    cout << " - Yes." << endl;
                if (DEBUG)
                    cout << ":       push [" << currentStr << "] (cur string) to stack vector";
                sVector.push_back(currentStr);
                if (DEBUG)
                    cout << " [complete]" << endl;
                continue;
            } else {
                if (DEBUG)
                    cout << " - No." << endl;
            }

            //step #4
            if (DEBUG)
                cout << ":    4: is [" << currentStr << "] (cur string) equal ')' ?";
            if (currentStr == ")") {
                if (DEBUG)
                    cout << " - Yes." << endl;
                if (DEBUG)
                    cout << ":       while loop:" << endl;
                while ( sVector.back() != "(" ) {
                    if (DEBUG)
                        cout << ":        - push [" << sVector.back() << "] (the top stack element) to output vector";
                    oVector.push_back(sVector.back());
                    if (DEBUG)
                        cout << " [copmlete]" << endl;
                    if (DEBUG)
                        cout << ":        - pop the top stack element";
                    sVector.pop_back();
                    if (DEBUG)
                        cout << " [complete]" << endl;
                }
                if (DEBUG)
                    cout << ":      [while loop complete]" << endl;

                if (DEBUG)
                    cout << ":    4: is the [" << sVector.back() << "] (top stack element) equal '(' ?";
                if (sVector.back() == "(") {
                    if (DEBUG)
                        cout << " - Yes." << endl;
                    if (DEBUG)
                        cout << ":       pop [" << sVector.back() << "] (top stack element)";
                    sVector.pop_back();
                    if (DEBUG)
                        cout << " [complete]" << endl;
                }
                continue;
            }

            //step #2
            if (DEBUG)
                cout << ":    2:" << endl;
            //step #2a
            if (DEBUG)
                cout << ":    2a" << endl;
            if (DEBUG)
                cout << ":       is stack is empty OR top stack element equals '('?";
            if ( (sVector.empty()) || (sVector.back() == "(") ) {
                if (DEBUG)
                    cout << " - Yes." << endl;
                if (DEBUG)
                    cout << ":       push [" << currentStr << "] to stack vector";
                sVector.push_back(currentStr);
                if (DEBUG)
                    cout << " [complete]" << endl;
                continue;
            }
            if (DEBUG)
                cout << ":    2b:" << endl;
            //step #2b
            if (DEBUG)
                cout << ":       is priorty of" << currentStr << "(cur string) > priority of [" << sVector.back() << "] (top stack element)?";
            if (getPriority(currentStr) > getPriority(sVector.back())) {
                if (DEBUG)
                    cout << " - Yes." << endl;
                if (DEBUG)
                    cout << ":       push [" << currentStr << "] (cur string) to stack vector";
                sVector.push_back(currentStr);
                if (DEBUG)
                    cout << " [complete]" << endl;
                continue;
            } else {
                if (DEBUG)
                    cout << " - No." << endl;
                if (DEBUG)
                    cout << ":    2c:" << endl;
                //step #2c
                if (DEBUG)
                    cout << ":       while loop:" << endl;
                while ( true ) {
                    if ( ( sVector.empty() ) ||
                         ( getPriority(currentStr) > getPriority(sVector.back()) ) ||
                         ( sVector.back() == "(" ) ) {
                        break;
                    }

                    if (DEBUG)
                        cout << ":        - push [" << sVector.back() << "] to output string";
                    oVector.push_back(sVector.back());
                    if (DEBUG)
                        cout << " [complete]" << endl;

                    if (DEBUG)
                        cout << ":        - pop [" << sVector.back() << "]";
                    sVector.pop_back();
                    if (DEBUG)
                        cout << " [complete]" << endl;
                }
                if (DEBUG)
                    cout << ":      [while loop complete]" << endl;
                if (DEBUG)
                    cout << ": ?     push [" << currentStr << "] (cur string) to stack";
                sVector.push_back(currentStr);
                if (DEBUG)
                    cout << " [complete]" << endl;
                continue;
            }
        }
    } // end of eVector (input string)

    //step #5
    if (DEBUG)
        cout << ":    end of eVector" << endl;
    if (DEBUG)
        cout << ":    while loop:" << endl;
    while (!sVector.empty()) {
        if (DEBUG)
            cout << ":  - push [" << sVector.back() << "] (top stack element) to output vector";
        oVector.push_back(sVector.back());
        if (DEBUG)
            cout << " [complete]" << endl;

        if (DEBUG)
            cout << ":  - pop [" << sVector.back() << "] (top stack element)";
        sVector.pop_back();
        if (DEBUG)
            cout << " [complete]" << endl;
    }
    if (DEBUG)
        cout << ":    [while loop complete]" << endl;

    if (DEBUG)
        cout << ":    return output vector" << endl;
    return oVector;
}

/*
 * Checks if a character is a number.
*
 * @param ch - character which need to check.
 * @return true - if symbol is number.
 * @return false - if symbol is not number.
*/
bool isNumber(char ch) {
    char numbers[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i=0; i < 10; i++) {
        if (ch == numbers[i])
            return true;
    }
    return false;
}

/*
 * Get priority of input string.
*
 * @param str - input string.
 * @return integer value.
*/
int getPriority(string str) {

    // priority of '*' or '/' biger than priority of '-' or '+'

    if ( (str == "*") || (str == "/") )
        return 2;

    if ( (str == "-") || (str == "+") )
        return 1;
}

/*
 * Solve first operator in equation vector.
 *  The function finds the first operator in the vector
 *  and produces its action.
*
 * @param equationVector - input equation vector.
 * @return tempVector - vector with solved first operator.
*/
vector<string> solveOneStep(vector<string> equationVector) {
    string currentStr = "";
    vector<string> tempVector;
    double tempRezult;
    string tempStrRezult;
    int i;
    if (DEBUG)
        cout << ":     solve one step: " << endl;

    for (i=0; i < equationVector.size(); i++) {
        currentStr = equationVector.at(i);
        if (DEBUG)
            cout << ":       curent str: [" << currentStr << "]" << endl;
        if ( (isNumber(currentStr.at(0))) || (currentStr.size() > 1) ) {
            continue;
        } else {
            stringstream myStrStream1;
            myStrStream1 << equationVector.at(i-2);
            double operand1; myStrStream1 >> operand1;

            stringstream myStrStream2;
            myStrStream2 << equationVector.at(i-1);
            double operand2; myStrStream2 >> operand2;

            char curentOperator = currentStr.at(0);
            if ( (curentOperator == '-') && ((currentStr.size() > 1)) ) {
                curentOperator = currentStr.at(1);
            }

            if (DEBUG)
                cout << ":        " << "[" << operand1 << "] " << curentOperator << " [" << operand2 << "]" << endl;

            switch (curentOperator) {
            case '+':
                tempRezult = operand1 + operand2;
                break;
            case '-':
                tempRezult = operand1 - operand2;
                break;
            case '*':
                tempRezult = operand1 * operand2;
                break;
            case '/':
                tempRezult = operand1 / operand2;
                break;
            default:
                break;
            }
            break;
        }
    }

    for (int j=0; j < i-2; j++) {
        tempVector.push_back(equationVector.at(j));
    }
    stringstream d2s;
    d2s << tempRezult;
    d2s >> tempStrRezult;
    tempVector.push_back(tempStrRezult);
    for (int j=i+1; j < equationVector.size(); j++) {
        tempVector.push_back(equationVector.at(j));
    }
    if (DEBUG) {
        cout << ":        rezult vector: ";
        for (int i=0; i < tempVector.size(); i++) {
            cout << "[" << tempVector.at(i) << "] ";
        }
        cout << endl;
    }

    return tempVector;
}
