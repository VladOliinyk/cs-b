#include <iostream>
#include <string>
#include "myStack.h"


using namespace std;

void printStackInfo(MyStack<int>* localStack) {
    cout << "      Stack size: " << localStack->getSize() << endl
         << " Stack filled in: " << localStack->getFilled() << endl
         << "  Top element = : " << localStack->top() << endl;
}

void testMyStack() {
    MyStack<int>* myIntStack = new MyStack<int>();
    printStackInfo(myIntStack);
    for (int i = 0; i < 10; i++) {
        myIntStack->push(i);
        cout << endl;
        printStackInfo(myIntStack);
    }

    for (int i = 0; i < 10; i++) {
        myIntStack->pop();
        cout << endl;
        printStackInfo(myIntStack);
    }
}


int main()
{

    testMyStack();

    return 0;
}

