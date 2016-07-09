#include "header.h"
#include "decode.h"

#include <fstream>

void decode(Node* root) {
    ///// ///// ///// decoding part ///// ///// /////
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
}
