// todo:
//  разобраться с копированием (перегрузка оператора = ) ...все равно не работает

#ifndef MYSTACK_H_INCLUDED
#define MYSTACK_H_INCLUDED

#include <iostream>

template <class T>
class MyStack {

private:
    T* array;
    int filled;
    int size;
    static const int defaultSize = 5;
    static const double resizeMultiplier = 1.6;
    static const double fillingLimitedCoef = 0.7;
    static const double decreaseFillingLimitedCoef = 0.3;
    void resize(double resizeCoef = resizeMultiplier);

public:
    MyStack(int startSize = defaultSize);
    ~MyStack();
    MyStack(const MyStack<T> &anotherStack);

    T& top();
    void pop();
    int getSize();
    void push(const T &newElem);
    int getFilled();
    bool isEmpty();

    MyStack<T>& operator=( MyStack<T> &anotherStack);
};

/* Default constructor */
template <typename T>
MyStack<T>::MyStack(int startSize) {
    size = (startSize > 1) ? startSize : defaultSize;
    filled = 0;
    array = new T[size];
}

/* Default destructor */
template <typename T>
MyStack<T>::~MyStack() {
    delete[] array;
    filled = 0;
    size = 0;
}

/* Copy constructor */
template <typename T>
MyStack<T>::MyStack(const MyStack<T> &anotherStack) {
    size = anotherStack.size;
    filled = anotherStack.filled;
    array = new T[size];
    for (int i = 0; i < size; i++) {
        array[i] = anotherStack.array[i];
    }
}

/*
 * A function that return the stack size (capacity).
 * @return size - the size of the list;
 */
template <typename T>
int MyStack<T>::getSize() {
    return size;
}

/*
 * A function that return the count of elements in stack.
 * @return filled - count of elements in stack;
 */
template <typename T>
int MyStack<T>::getFilled() {
    return filled;
}

/* A function that increases the size of the stack. */
template <typename T>
void MyStack<T>::resize(double resizeCoef) {
    int newSize = (int) size * resizeCoef;
    T* tmpArray = new T[newSize];
    for (int i = 0; i < filled; i++) {
        tmpArray[i] = array[i];
    }
    delete[] array;
    array = tmpArray;
    size = newSize;
}

/*
 * A function that checks the stack is empty.
 * @return bool value;
 */
template <typename T>
bool MyStack<T>::isEmpty() {
    return !filled;
}

/*
 * A function that adds element to the stack.
 * @param &newElem - link to the data value.
 */
template <typename T>
void MyStack<T>::push(const T &newElem) {
    if (filled >= (int)(fillingLimitedCoef*size)) {
        resize();
    }
    array[filled] = newElem;
    filled++;
}

/* A function that remove ещз element from the stack. */
template <typename T>
void MyStack<T>::pop(){
    if (!isEmpty()) {
        filled--;
    }
    if (filled < (size * decreaseFillingLimitedCoef)) {
        resize(1 / resizeMultiplier);
    }
}

/*
 * A function that return top element from the stack.
 * @return T% value - link to the top stack element.
 */
template <typename T>
T& MyStack<T>::top() {
    return (filled) ? array[filled-1] : *array;
}


template <typename T>
MyStack<T> &MyStack<T>::operator=( MyStack<T> &anotherStack) {
    std::cout << "hey operator= for MyStack" << std::endl;
    if (&array != &anotherStack.array) {
        delete[] array;
        size = anotherStack.size;
        array = new T[size];
        filled = anotherStack.filled;
        for (int i = 0; i < filled; i++) {
            array[i] = anotherStack.array[i];
        }
    }
    return *this;
}

#endif // MYSTACK_H_INCLUDED
