#include <iostream>

#include "header.h"

using namespace std;

/*
 * Generate output filename from input filename string.
 * @return output - output filename
 */
string generateOutputFileName(string input) {
    string output;
    output = "output_"+input;
    return output;
}


/*
 * The function which returns filename.
 * Asks the user for a file name.
 * @return filename - an input text filename. ('input.txt' is an default filename)
*/
string getUserFileName() {
    cout << "Please enter the input file name." << endl <<
            " (enter 'q' to use defaul filename: 'input.txt')" << endl;
    string filename;
    getline(cin, filename);
    if (filename.size() == 1) {
        return "input.txt";
    }
    if (filename.at(0) == 'q' && filename.size() == 1) {
        return "input.txt";
    }
    return filename;

}

/*
 * The real main function.
 * Make all instead of us.
 * Gets equation string. Encode it. Decode it.
*/
void makeAll() {
    string filename = getUserFileName();
    string outputFilename = generateOutputFileName(filename);
    cout << "Input file is '" << filename << "'" << endl;

    // this 'Node* tree' need to save charCodes tree.
    Node* tree;
    tree = encode(filename, outputFilename);

    decode(tree, outputFilename);
}

/* Main function.
 * Encodes and decodes text from the input file (specified in the config.h file). */
int main()
{
    makeAll();
    return 0;
}

