// https://www.youtube.com/watch?v=KNVPFVG49Oc

#include <iostream>
#include <fstream>
#include <string>

#include <map>
#include <list>
#include <vector>

#include <bitset>
#include <iomanip>

#define DEBUG 0
#define SHOW_TABLE 1
#define SHOW_CHAR_CODES_STRING 1

using namespace std;

string getUserString() {
    string str;
    cout << "Enter your string: ";
    getline(cin, str);
    return str;
}

class Node
{
public:
    char ch = NULL;
    int count;
    Node *left, *right;

    Node() {
        left = NULL;
        right = NULL;
    }

    Node(Node *son_l, Node *son_r) {
        left = son_l;
        right = son_r;
        count = son_l->count + son_r->count;
    }
};

struct sortByCount
{
    bool operator()(Node* left, Node* right) const {
        return left->count < right->count;
    }
};

void printTreeR(Node* root, int lvl=0) {
    if (DEBUG) {
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

void printTree(Node* root) {
    if (DEBUG) {
        cout << endl << "Tree:" << endl;
    }
    printTreeR(root);
    if (DEBUG) {
        cout << endl << endl;
    }
}

vector<char> charCode;
map<char, vector<char> > table;
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

string showVector(vector<char> vec) {

    string str = "";

    for (int i=0; i < vec.size(); i++) {
        str+=vec.at(i);
    }
    return str;
}


int main(int argc, char *argv[])
{
    map<char, int> myMap;

    // with string
    /*
    string str = getUserString();
    cout << "Initial string: " << str << endl;

    for (int i = 0; i < str.size(); i++) {
        myMap[str.at(i)]++;
    }*/
    // with string end

    // with file
    ifstream inputFile("input.txt", ios::in | ios::binary);
    while(!inputFile.eof()) {
        myMap[inputFile.get()]++;
    }
    inputFile.clear();
    inputFile.seekg(0);
    // with file end

    list<Node*> myList;

    map<char, int>::iterator itr_mymap;
    for (itr_mymap = myMap.begin(); itr_mymap != myMap.end(); itr_mymap++) {
        Node *ptr = new Node;
        ptr->ch = itr_mymap->first;
        ptr->count = itr_mymap->second;
        ptr->left = NULL;
        ptr->right = NULL;
        myList.push_back(ptr);
    }

    /// show root element in myList
    list<Node*>::iterator itr_mylist;
    if (DEBUG) {
        for (itr_mylist = myList.begin(); itr_mylist != myList.end(); itr_mylist++) {
            cout << (*itr_mylist)->ch << ":" << (*itr_mylist)->count << endl;
        }
    }

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
    /// show table
    map<char, vector<char> >::iterator itr_table;
    if (DEBUG || SHOW_TABLE) {
        cout << "Char table: " << endl;
        for (itr_table = table.begin(); itr_table != table.end(); itr_table++) {
            cout << "[" << setw(2) << itr_table->first << setw(2) << "]" << " : " << showVector(itr_table->second) << endl;
        }
    }

    string final = "";
    //with string
    /*for (int i = 0; i < str.size(); i++) {
        vector<char> tmp = table[str.at(i)];
        for (int j = 0; j < tmp.size(); j++) {
            final+=tmp[j];
        }
    }*/
    // with string end

    //with file
    while(!inputFile.eof()) {
        char tempChar = inputFile.get();
        vector<char> tmp = table[tempChar];
        for (int j = 0; j < tmp.size(); j++) {
            final+=tmp[j];
        }
    }
    inputFile.clear();
    inputFile.seekg(0);
    //with file end

    if (DEBUG || SHOW_CHAR_CODES_STRING) {
        cout << "Char codes string: " << final << endl;
    }

    ofstream myOutputFile("output.txt");
    int counter = 0;
    char buff = 0;
    // with string
    /*for (int i = 0; i < str.size(); i++) {
        vector<char> charCode = table[str.at(i)];
        for (int j = 0; j < charCode.size(); j++) {

            char null = 0;
            int shift = 7 - counter;
            int curCharCode = charCode[j] & 1;

            if (DEBUG) {
                cout << "    counter = " << counter << endl;
                cout << "current char: '" << str.at(i) << "' : " << charCode[j] << endl;
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
    }*/
    // with string end

    // with file

    while (!inputFile.eof()) {
        char tempChar = inputFile.get();
        vector<char> charCode = table[tempChar];
        for (int j = 0; j < charCode.size(); j++) {

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
    // with file end


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



    ifstream myInputFile("output.txt", ios::in | ios::binary);

    setlocale(LC_ALL,"Russian");

    Node *p = root;
    int i_counter=0;
    char byte;
    byte = myInputFile.get();
    cout << "Decoded string: ";
    while(!myInputFile.eof()) {
        bool b = byte & (1 << (7-i_counter) ) ;
        (b) ? p=p->right : p=p->left;

        if (p->left==NULL && p->right==NULL) {
            cout << p->ch;
            p=root;
        }
        i_counter++;
        if (i_counter==8) {
            i_counter=0;
            byte = myInputFile.get();
        }
    }
    myInputFile.close();
    cout << endl;
    return 0;
}

