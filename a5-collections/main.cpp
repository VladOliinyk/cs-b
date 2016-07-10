#include <iostream>
#include <string>
#include "myStack.h"
#include "myList.h"
#include <vector>
#include "myavltree.h"

#define stackTest_simple 0
#define stackTest_overloading 0

#define listTest_simple false
#define listTest_overloading false


using namespace std;

void printStackInfo(MyStack<int>* localStack) {
    cout << "      Stack size: " << localStack->getSize() << endl
         << " Stack filled in: " << localStack->getFilled() << endl
         << "  Top element = : " << localStack->top() << endl;
}

void testMyStack() {
    ///// simple stack tests ///// start /////
    if (stackTest_simple) {
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
    ///// simple stack tests ///// end /////

    ///// is overloading = work ? ///// start /////
    if (stackTest_overloading) {
        MyStack<int>* myStack = new MyStack<int>();
        cout << "before filling: " << endl
             << "myStack  " << myStack << "   size=" << myStack->getSize() << endl;
        myStack->push(0);
        myStack->push(1);
        myStack->push(2);
        myStack->push(3);
        myStack->push(4);
        myStack->push(5);
        cout << " after filling: " << endl
             << "myStack  " << myStack << "   size=" << myStack->getSize() << endl << endl;

        MyStack<int>* myStack2 = new MyStack<int>();
        cout << "before filling: " << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl;
        myStack2->push(10);
        myStack2->push(11);
        myStack2->push(12);
        cout << " after filling: " << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl << endl;


        cout << "before 'myStack2 = myStack': " << endl
             << "myStack  " << myStack << "   size=" << myStack->getSize() << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl << endl;
        myStack2->operator=(*myStack);
        cout << " after 'myStack2 = myStack': " << endl
             << "myStack  " << myStack << "   size=" << myStack->getSize() << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl;

        MyStack<int>* myStack3 = new MyStack<int>();
        cout << "before 'myStack3 = myStack2': " << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl
             << "myStack3 " << myStack3 << "   size=" << myStack3->getSize() << endl;
        myStack3 = myStack2;
        myStack2->push(1231);
        myStack2->push(1231);
        myStack2->push(1231);
        myStack2->push(1231);
        cout << " after 'myStack3 = myStack2': " << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl
             << "myStack3 " << myStack3 << "   size=" << myStack3->getSize() << endl;
    }
    // перегрузка оператора = не работает
    // оно просто копирует поинтер на другой стек
    ///// is overloading = work ? ///// end /////
}


// !!! need to non privat variables !!! //
void printPrivatListInfo(MyList<int>* list) {
    cout << "list->head " << list->head << endl;
    cout << "list->tail " << list->tail << endl;
    cout << "list->size " << list->getSize() << endl;
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
    if (listTest_simple) {
        MyList<int> *listS = new MyList<int>();
        printPrivatListInfo(listS);

        for (int i=0; i < 5; i++) {
            cout << endl;
            cout << "push_back(" << i*2 << ")" << " ... ";
            listS->push_back(i*2);
            cout << "OK" << endl;
            printPrivatListInfo(listS);
        }

        for (int i=0; i < 6; i++) {
            cout << endl;
            cout << "pop_front #" << i << " ... ";
            listS->pop_front();
            cout << "OK" << endl;
            printPrivatListInfo(listS);
        }
    }
    ///// push/pop simple test ? ///// end /////


    ///// is overloading = work ? ///// start /////
    if (listTest_overloading) {
        MyList<int> *list1 = new MyList<int>();
        cout << "----- LIST 1 BEFORE FILLING: -----" << endl;
        printPrivatListInfo(list1);
        list1->printList();
        cout << "----- ----- ---------- ----- -----" << endl;

        for (int i = 0; i < 10; i++) {
            list1->push_back(i+10);
        }

        cout << "----- LIST 1  AFTER FILLING: -----" << endl;
        printPrivatListInfo(list1);
        list1->printList();
        cout << "----- ----- ---------- ----- -----" << endl;

        MyList<int> *list2 = new MyList<int>();
        cout << "----- LIST 2 BEFORE FILLING: -----" << endl;
        printPrivatListInfo(list2);
        list2->printList();
        cout << "----- ----- ---------- ----- -----" << endl;

        for (int i = 0; i < 5; i++) {
            list2->push_back(i+50);
        }

        cout << "----- LIST 2  AFTER FILLING: -----" << endl;
        printPrivatListInfo(list2);
        list2->printList();
        cout << "----- ----- ---------- ----- -----" << endl;


        cout << "----- LIST 1&2 BEFORE list2 = list1 : -----" << endl;
        list1->printList();
        list2->printList();
        cout << "----- ----- ----- --- --- ----- ----- -----" << endl;

        list2->operator =(*list1);
        list2 = list1;
        list1->head->data=88;

        cout << "----- LIST 1&2  AFTER list2 = list1 : -----" << endl;
        list1->printList();
        list2->printList();
        cout << "----- ----- ----- --- --- ----- ----- -----" << endl;
    }
    ///// is overloading = work ? ///// end ///// - nope


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

#include <queue>
#include "mypriorityqueue.h"

void testMyQueue() {
    MyPriorityQueue<int> *myIntQueue = new MyPriorityQueue<int>();
    myIntQueue->printQueue();
    cout << "start FOR" << endl;
    for (int i=0; i < 10; i++) {
        myIntQueue->push(i);
    }
    cout << "size = " << myIntQueue->getSize() << endl;
    myIntQueue->printQueue();

    cout << myIntQueue->top() << endl;
    myIntQueue->pop();
    cout << "size = " << myIntQueue->getSize() << endl;
    cout << myIntQueue->top() << endl;

}

/* Main function */
int main()
{
    testMyStack();
    testMyList();
    testMyQueue();

    return 0;
}

