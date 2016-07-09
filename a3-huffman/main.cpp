#include <iostream>

#include "header.h"

using namespace std;

/* Main program function.
 * Encodes and decodes text from the input file (specified in the config.h file). */
int main()
{
    Node* tree;
    tree = encode();
    decode(tree);
    return 0;
}

