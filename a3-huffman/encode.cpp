#include "encode.h"
#include "config.h"
#include "node.h"

#include <fstream>
#include <list>
#include <iomanip>
#include <bitset>

using namespace std;

/* Global vector with char code for char. */
vector<char> charCode;

/* Global map of all chars from input file and their codes. */
map<char, vector<char> > table;

/* Recursive function that printing each element of tree. */
void printTreeR(Node* root, int lvl) {
    if (DEBUG || SHOW_TREE) {
        if (root != NULL) {
            printTreeR(root->left, lvl+2);
            for (int i=0; i < lvl; i++) {
                cout << "    ";
            }

            if (root->ch)
                cout << "#" << root->count << " [" << root->ch << "]" << endl;
            else
                cout << "#" << root->count << " []"<< endl;

            printTreeR(root->right, lvl+2);
        }
    }
}
/* Main function that printing each element of tree.
 * Calling recursive print tree function. */
void printTree(Node* root) {
    if (DEBUG || SHOW_TREE) {
        cout << endl << "Tree:" << endl;
        printTreeR(root);
        cout << endl << endl;
    }
}

/* Method that creating table of all chars and their char codes.
 * Using @charCode vector to generate char code for each char from tree. */
void createTable(Node* root) {

    if (root->left != NULL) {
        charCode.push_back('0');
        createTable(root->left);
    }

    if (root->right != NULL) {
        charCode.push_back('1');
        createTable(root->right);
    }
    if (DEBUG) {
        cout << "Now seting [" << root->ch << "] to table" << endl;
    }

    if (root->ch) {
        table[root->ch] = charCode;
    }

    charCode.pop_back();
}

/* Function that turns vectior into a string. */
string showVector(vector<char> vec) {

    string str = "";

    for (int i = 0; i < (int) vec.size(); i++) {
        str+=vec.at(i);
    }
    return str;
}

/* Function that prints input file content. */
void showInputFileData() {
    if (DEBUG || SHOW_INPUT_FILE) {
        ifstream tempInputFile(INPUT_FILE);
        cout << "=== Start of input file: ===" << endl;
        while(!tempInputFile.eof()) {
            char buff[1];
            tempInputFile >> buff;
            cout << buff;
        }
        cout << endl << "===  End of input file.  ===" << endl;
        tempInputFile.close();
    }
}

Node* encode() {
    ///// ///// ///// encoding part ///// ///// /////
    showInputFileData();

    // Open input file and write the characters from a file into the map.
    ifstream inputFile(INPUT_FILE, ios::in | ios::binary);

    // Create map of all characters from input file.
    map<char, int> myMap;
    while(!inputFile.eof()) {
        myMap[inputFile.get()]++;
    }
    // Reset file pointer to start of file.
    inputFile.clear();
    inputFile.seekg(0);

    // list of pointer to all chars from input file
    list<Node*> myList;
    map<char, int>::iterator itr_mymap;
    // for all maps setting nodes for each element
    for (itr_mymap = myMap.begin(); itr_mymap != myMap.end(); itr_mymap++) {
        Node *ptr = new Node;
        ptr->ch = itr_mymap->first;
        ptr->count = itr_mymap->second;
        ptr->left = NULL;
        ptr->right = NULL;
        myList.push_back(ptr);
    }

    // creating a tree of chars
    while (myList.size() != 1) {
        myList.sort(sortByCount());

        Node *son_l = myList.front();
        myList.pop_front();

        Node *son_r = myList.front();
        myList.pop_front();

        Node *parent = new Node(son_l, son_r);
        myList.push_back(parent);
    }
    Node* root = myList.front();

    createTable(root);
    printTree(root);

    if (DEBUG || SHOW_TABLE) {
        map<char, vector<char> >::iterator itr_table;
        cout << "Char table: " << endl;
        for (itr_table = table.begin(); itr_table != table.end(); itr_table++) {
            cout << "[" << setw(2) << itr_table->first << setw(2) << "]" << " : " << showVector(itr_table->second) << endl;
        }
    }

    if (DEBUG || SHOW_CHAR_CODES_STRING) {
        string final = "";
        while(!inputFile.eof()) {
            char tempChar = inputFile.get();
            vector<char> tmp = table[tempChar];
            for (int j = 0; j < (int) tmp.size(); j++) {
                final+=tmp[j];
            }
        }
        inputFile.clear();
        inputFile.seekg(0);
        cout << "Char codes string: " << final << endl;
    }

    ofstream myOutputFile("output.txt");
    int counter = 0;
    char buff = 0;

    // Coding all chars from input file to binary view by 8 btis
    while (!inputFile.eof()) {
        char tempChar = inputFile.get();
        vector<char> charCode = table[tempChar];
        for (int j = 0; j < (int) charCode.size(); j++) {

            char null = 0;
            int shift = 7 - counter;
            int curCharCode = charCode[j] & 1;

            if (DEBUG) {
                cout << "    counter = " << counter << endl;
                cout << "current char: '" << tempChar << "' : " << charCode[j] << endl;
                cout << "curChar code: " << bitset<8>(curCharCode) << endl;
                cout << "      shift = " << shift << endl;
                cout << "        null: " << bitset<8>(null) << endl;
            }

            null = (curCharCode << shift);
            if (DEBUG) {
                cout << " after shift: " << bitset<8>(null) << endl;
                cout << "currend buff: " << bitset<8>(buff) << endl;
                cout << "              --------" << endl;
            }

            buff = buff | null;
            if (DEBUG) {
                cout << "    new buff: " << bitset<8>(buff) << endl << endl;
            }

            counter++;
            if (counter == 8) {
                counter = 0;
                if (DEBUG) {
                    cout << "buff to file: ";
                    cout << bitset<8>(buff) << endl;
                }
                myOutputFile << buff;
                buff = 0;
            }
        }
    }

    // if count of encoded bits is not a multiple of 8 adding '0' in the end
    if ( (counter != 8) || (counter != 0) ) {
        for (int i=counter; i <= (7 - counter); i++) {
            buff = buff | 0 << (7 - counter);
        }
    }

    myOutputFile<<buff;
    myOutputFile.close();

    if (DEBUG) {
        cout << "-- FILE CLOSED --" << endl << endl;
    }

    return root;
}
