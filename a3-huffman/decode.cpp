#include "decode.h"
#include "header.h"

#include <fstream>

using namespace std;

void decode(Node* root, string outputFilename_str) {
    ///// ///// ///// decoding part ///// ///// /////
    const char* outputFilename = outputFilename_str.c_str();
    ifstream myInputFile(outputFilename, ios::in | ios::binary);
    setlocale(LC_ALL,"Russian");

    Node *p = root;
    int i_counter=0;
    char byte;
    byte = myInputFile.get();
    if (SHOW_DECODED_STRING) {
        cout << "Decoded string: ";
    }
    while(!myInputFile.eof()) {
        bool b = byte & (1 << (7-i_counter) ) ;
        (b) ? p=p->right : p=p->left;

        if (p->left==NULL && p->right==NULL) {
            if (SHOW_DECODED_STRING) {
                cout << p->ch;
            }
            p=root;
        }
        i_counter++;
        if (i_counter==8) {
            i_counter=0;
            byte = myInputFile.get();
        }
    }
    myInputFile.close();
    if (SHOW_DECODED_STRING) {
        cout << endl;
    }
}
