#include <iostream>

#include "node.h"
#include "encode.h"
#include "decode.h"
#include "header.h"

using namespace std;

/* Main program function.
 * Encodes and decodes text from the input.txt file. */
int main(int argc, char *argv[])
{
    Node* tree;
    tree = encode();
    decode(tree);
    return 0;
}

