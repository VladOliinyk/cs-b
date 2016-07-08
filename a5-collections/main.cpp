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
    ///// simple stack tests ///// start /////
    /*
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
    }*/
    ///// simple stack tests ///// end /////


    ///// is overloading = work ? ///// start /////
    MyStack<int>* myStack = new MyStack<int>();
    cout << myStack << endl;
    myStack->push(1);
    myStack->push(2);
    myStack->push(3);
    cout << myStack << endl;

    MyStack<int>* myStack2 = new MyStack<int>();
    cout << myStack2 << endl;
    myStack2 = myStack;
    cout << myStack2 << endl;
    // перегрузка оператора = не работает
    // оно просто копирует поинтер на стек
    ///// is overloading = work ? ///// end /////
}

/* !!! need to non privat variables !!! */
void printPrivatListInfo(MyList<int>* list) {
    cout << "list->head " << list->head << endl;
    cout << "list->tail " << list->tail << endl;
    if (list->head != NULL && list -> tail != NULL) {
        cout << "list->head->data " << list->head->data << endl;
        cout << "list->head->next " << list->head->next << endl;
        cout << "list->head->prev " << list->head->prev << endl;
        cout << "list->tail->data " << list->tail->data << endl;
        cout << "list->tail->next " << list->tail->next << endl;
        cout << "list->tail->prev " << list->tail->prev << endl;
    } else {
        cout << "WARN: can't print list node data. List is empty." << endl;
    }
}

void testMyList() {

    ///// push/pop simple test ? ///// start /////
    /*
    MyList<int> *list = new MyList<int>();
    printPrivatListInfo(list);

    for (int i=0; i < 5; i++) {
        cout << endl;
        cout << "push_back(" << i*2 << ")" << " ... ";
        list->push_back(i*2);
        cout << "OK" << endl;
        printPrivatListInfo(list);
    }

    for (int i=0; i < 6; i++) {
        cout << endl;
        cout << "pop_front #" << i << " ... ";
        list->pop_front();
        cout << "OK" << endl;
        printPrivatListInfo(list);
    } */
    ///// push/pop simple test ? ///// end /////


    ///// is overloading = work ? ///// start /////
    /*
    MyList<int> *list1 = new MyList<int>();
    for (int i = 0; i < 10; i++) {
        list1->push_back(i+10);
        //cout << "1#" << i << " = " << list1->tail->data << endl;
    }

    MyList<int> *list2 = new MyList<int>();
    for (int i = 0; i < 10; i++) {
        list1->push_back(i+50);
        //cout << "2#" << i << " = " << list1->tail->data << endl;
    }

    MyList<int> *list3 = new MyList<int>();

    cout << "list1 = " << list1 << endl <<
            "list2 = " << list2 << endl <<
            "list3 = " << list3 << endl << endl;

    list3=list1;

    MyList<int> *list4 = list1;

    cout << "list1 = " << list1 << endl <<
            "list2 = " << list2 << endl <<
            "list3 = " << list3 << endl <<
            "list4 = " << list4 << endl << endl;
    // я хз, оно просто копирует поинтер на head и все

    list3->pop_front();
    list3->pop_back();

    cout << "list1 = " << list1 << endl <<
            "list2 = " << list2 << endl <<
            "list3 = " << list3 << endl <<
            "list4 = " << list4 << endl << endl;

    list1->clear();
    list3->pop_front();
    list3->pop_back();
    //да, он реально просто копирует указатель и игнорирует мою перегрузку оператора =
    cout << "list1 = " << list1 << endl <<
            "list2 = " << list2 << endl <<
            "list3 = " << list3 << endl <<
            "list4 = " << list4 << endl;
    */
    ///// is overloading = work ? ///// end /////


    ///// direction test ///// start /////
    /*
    MyList<int> *list = new MyList<int>();
    list->push_back(2);
    list->push_back(6);

    cout << "    list->head: " << list->head << endl;
    cout << "&list->front(): " << &list->front() << endl;
    cout << " list->front(): " << list->front() << endl;
    cout << "    head->next: " << list->head->next << endl;
    cout << "    head->prev: " << list->head->prev << endl;


    cout << endl;
    cout << "    list->tail: " << list->tail << endl;
    cout << " &list->back(): " << &list->back() << endl;
    cout << "  list->back(): " << list->back() << endl;
    cout << "    tail->next: " << list->tail->next << endl;
    cout << "    tail->prev: " << list->tail->prev << endl;
    */
    ///// direction test ///// end /////
}


int main()
{
    //testMyStack();
    //testMyList();
    return 0;
}

