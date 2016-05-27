#include "myStack.cpp"
#include <iostream>
#include <string>


using namespace std;

int main()
{

    cout << "STACK" << endl;
    myStack<char> stack;
    int size = 16;
    int a[size];
    for (int i=0; i < size; i++) {
        a[i] = i;
    }

    for (int i=0; i < size; i++) {
        cout << i << " : pushed" << endl;
        stack.push(a[i]);
    }

    for (int i=0; i < size; i++) {
        cout << "size=" << stack.getSize() <<
                "   top=" << (int) stack.getTop() << endl;
        stack.pop();
    }




    return 0;
}

