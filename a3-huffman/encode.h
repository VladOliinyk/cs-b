#ifndef ENCODE
#define ENCODE

#include "node.h"
#include <vector>
#include <map>

using namespace std;

/*
 * Overloading operator ()
 * Sort the elements according to pointers, not pointers.
 */
struct sortByCount
{
    bool operator()(Node* left, Node* right) const {
        return left->count < right->count;
    }
};

/* Recursive function that printing each element of tree. */
void printTreeR(Node* root, int lvl = 0);

/* Main function that printing each element of tree.
 * Calling recursive print tree function. */
void printTree(Node* root);

/* Method that creating table of all chars and their char codes.
 * Using @charCode vector to generate char code for each char from tree. */
void createTable(Node* root);

/* Function that turns vectior into a string. */
//string showVector(vector<char> vec);

/* Function that prints input file content. */
void showInputFileData();

Node* encode(string inputFilename, string outputFilenamer);

#endif // ENCODE

