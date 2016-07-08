#include <iostream>
#include <string>
#include "myStack.h"
#include "myList.h"
#include <vector>


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

    MyList<int> *list = new MyList<int>();
    cout << "list.head " << list->head << endl;
    cout << "list.tail " << list->tail << endl;


    cout << endl;
    list->push_back(1);
    cout << "list.head " << list->head << endl;
    cout << "list.tail " << list->tail << endl;
    cout << "list.head->data " << list->head->data << endl;
    cout << "list.head->next " << list->head->next << endl;
    cout << "list.head->prev " << list->head->prev << endl;
    cout << "list.tail->data " << list->tail->data << endl;
    cout << "list.tail->next " << list->tail->next << endl;
    cout << "list.tail->prev " << list->tail->prev << endl;

    cout << endl;
    list->push_back(2);
    cout << "list.head " << list->head << endl;
    cout << "list.tail " << list->tail << endl;
    cout << "list.head->data " << list->head->data << endl;
    cout << "list.head->next " << list->head->next << endl;
    cout << "list.head->prev " << list->head->prev << endl;
    cout << "list.tail->data " << list->tail->data << endl;
    cout << "list.tail->next " << list->tail->next << endl;
    cout << "list.tail->prev " << list->tail->prev << endl;

    cout << endl;
    list->push_back(3);
    cout << "list.head " << list->head << endl;
    cout << "list.tail " << list->tail << endl;
    cout << "list.head->data " << list->head->data << endl;
    cout << "list.head->next " << list->head->next << endl;
    cout << "list.head->prev " << list->head->prev << endl;
    cout << "list.tail->data " << list->tail->data << endl;
    cout << "list.tail->next " << list->tail->next << endl;
    cout << "list.tail->prev " << list->tail->prev << endl;
    //testMyStack();

    return 0;
}

