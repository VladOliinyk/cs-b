//todo:
// спросить про
//              list2 = list1;
//              (list2)->operator =(*list1);
//                      *ну и про вектор аналогично


#include "myStack.h"
#include "myList.h"
#include "mypriorityqueue.h"

#include <iostream>
#include <cstdlib>

#define stackTest_simple 0
#define stackTest_overloading 0

#define listTest_simple 0
#define listTest_overloading 0

#define queueTest_linear_priority 0
#define queueTest_random_priority 0
#define queueTest_pop_and_print 0

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

        cout << endl;
        MyStack<int>* myStack3 = new MyStack<int>();
        myStack3->operator =(*myStack2);
        cout << "before 'myStack3 = myStack2': " << endl
             << "myStack2 " << myStack2 << "   size=" << myStack2->getSize() << endl
             << "myStack3 " << myStack3 << "   size=" << myStack3->getSize() << endl;
        cout << endl << "push 5 elem to myStack2" << endl;
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
#ifdef SUDO
        cout << "list->head " << list->head << endl;
        cout << "list->tail " << list->tail << endl;
#endif
    cout << "list->size " << list->getSize() << endl;
#ifdef SUDO
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
#endif
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

        for (int i=0; i < 5; i++) {
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

        for (int i = 0; i < 8; i++) {
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

        //list2 = list1;
        (list2)->operator =(*list1);
        list1->push_front(1);

        cout << "----- LIST 1&2  AFTER list2 = list1 : -----" << endl;
        list1->printList();
        list2->printList();
        cout << "----- ----- ----- --- --- ----- ----- -----" << endl;

        list1->pop_front();
        list1->push_back(1);

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

void testMyQueue() {
    ///// linear priority push test ///// start /////
    if (queueTest_linear_priority) {
        MyPriorityQueue<int> *myIntQueue2 = new MyPriorityQueue<int>();
        cout << "start FOR" << endl;
        for (int i=1; i < 11; i++) {
            cout << "size = " << myIntQueue2->getSize() << endl;
            cout << "push(" << i << ", " << 20-i << ")" << endl;
            myIntQueue2->push(i, 20-i);
        }
        cout << "size = " << myIntQueue2->getSize() << endl;
        myIntQueue2->printQueue();
        cout << "pop" << endl;
        myIntQueue2->pop();
        myIntQueue2->printQueue();
    }
    ///// linear priority push test ///// end /////


    ///// random priority push test ///// start /////
    if (queueTest_random_priority) {
        MyPriorityQueue<string> *myStringQueue = new MyPriorityQueue<string>();
        cout << "string queue FOR:" << endl;
        string str[5] = {"hello", "my", "awesome", "friend", "!"};
        for (int i=0; i < 5; i++) {
            myStringQueue->printQueue();
            string tmpStr = str[i];
            int tmpPr = rand() % 100+1;
            cout << endl << "now push(" << tmpStr << ", " << tmpPr << ");" << endl;
            myStringQueue->push(tmpStr, tmpPr);
        }

        myStringQueue->printQueue();
        cout << endl;
        cout << endl << "now push(MAYTHE4thBWITHU, 60)" << endl;
        myStringQueue->push("MAYTHE4thBWITHU", 60);
        myStringQueue->printQueue();
    }
    ///// random priority push test ///// end /////


    ///// pop and print test ///// start /////
    if (queueTest_pop_and_print) {
        MyPriorityQueue<char> *myCharQueue = new MyPriorityQueue<char>();
        myCharQueue->push('a');
        myCharQueue->push('b');
        myCharQueue->push('c');
        myCharQueue->push('d');

        cout << "size = " << myCharQueue->getSize() << endl;
        cout << myCharQueue->top() << endl;
        myCharQueue->printQueue();

        myCharQueue->pop();
        cout << "size = " << myCharQueue->getSize() << endl;
        cout << myCharQueue->top() << endl;
        myCharQueue->printQueue();

        myCharQueue->pop();
        cout << "size = " << myCharQueue->getSize() << endl;
        cout << myCharQueue->top() << endl;
        myCharQueue->printQueue();

        myCharQueue->pop();
        cout << "size = " << myCharQueue->getSize() << endl;
        cout << myCharQueue->top() << endl;
        myCharQueue->printQueue();

        myCharQueue->pop();
        cout << "size = " << myCharQueue->getSize() << endl;
        myCharQueue->printQueue();
    }
    ///// pop and print test ///// end /////
}

/* Main function */
int main()
{
    testMyStack();
    testMyList();
    testMyQueue();
    cout << "All right :)" << endl;
    return 0;
}

