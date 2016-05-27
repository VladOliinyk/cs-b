
#ifndef MYSTACK
#define MYSTACK

template <typename T>
class myStack
{
private:
    T *stackPtr;        // stack pointer
    int size;           // capacity of stack (max size)
    int top;            // size of stack & number of top element

public:
    myStack(int = 10);              // defauls stack with 10 elements
    myStack(const myStack <T> &);   // copy constructor
    ~myStack();                     // destructor

    int getSize() const;
    void push(const T &);
    void pop();
    T getTop() const;
    T *getPtr() const;

    int getC();
};


template <typename T>
myStack<T>::myStack(int userSize)
    : size(userSize)
{
    stackPtr = new T[userSize];
    top = 0;
}

template <typename T>
myStack<T>::myStack(const myStack<T> & otherStack) :
    size(otherStack.getSize())
{
    stackPtr = new T[size];
    top = otherStack.getTop();

    for(int i = 0; i < top; i++)
        stackPtr[i] = otherStack.getPtr()[i];
}

template <typename T>
myStack<T>::~myStack()
{
    delete [] stackPtr;
}

template <typename T>
int myStack<T>::getSize() const
{
    return top;
}

template <typename T>
void myStack<T>::push(const T &value)
{
        top++;
        stackPtr[top] = value;
}

template <typename T>
void myStack<T>::pop()
{
    top--;
    stackPtr[top];
}

template <typename T>
T myStack<T>::getTop() const
{
    return stackPtr[top];
}

template <typename T>
T *myStack<T>::getPtr() const
{
    return stackPtr;
}



template <typename T>
int myStack<T>::getC()
{
    return size;
}

#endif
