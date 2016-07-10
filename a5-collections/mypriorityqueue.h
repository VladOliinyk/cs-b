#ifndef MYPRIORITYQUEUE
#define MYPRIORITYQUEUE

#include <iostream>

template<typename T>
class MyPriorityQueue {

private:
    struct Node {
        T data;
        int priority;
        Node* above; // higher priority
        Node* below; //  lower priority
    };
    unsigned int size;
    Node* head;

    void printCurNode(const Node* node);

public:
    MyPriorityQueue();
    ~MyPriorityQueue();
    MyPriorityQueue(const MyPriorityQueue<T> &anotherQueue);

    bool isEmpty();
    void clear();
    unsigned int getSize();
    void push(const T &data, const int priority = 0);
    void pop();
    T &top();
    int topPriority();

    void printQueue();


};

template<typename T>
MyPriorityQueue<T>::MyPriorityQueue() {
    head = NULL;
    size = 0;
}

template<typename T>
MyPriorityQueue<T>::~MyPriorityQueue() {
    clear();
}

template<typename T>
MyPriorityQueue<T>::MyPriorityQueue(const MyPriorityQueue<T> &anotherQueue) {
    head = NULL;
    size = 0;
    if (!anotherQueue.isEmpty()) {
        Node* tmpNode = anotherQueue.top;
        while (tmpNode->below != NULL) {
            push(tmpNode, tmpNode->priority);
            tmpNode = tmpNode->below;
        }
    }
}

template<typename T>
bool MyPriorityQueue<T>::isEmpty() {
    return (size == 0);
}

template<typename T>
void MyPriorityQueue<T>::clear() {
    while (size != 0) {
        Node* tmpNode = top;
        if (top->below != NULL) {
            top = top->below;
        }
        delete tmpNode;
        size--;
    }
}

template<typename T>
unsigned int MyPriorityQueue<T>::getSize() {
    return size;
}


template<typename T>
void MyPriorityQueue<T>::push(const T &data, const int priority) {
    //std::cout << "push:" << std::endl;
    //std::cout << "     start" << std::endl;
    Node* n = new Node;
    n->data = data;
    n->priority = priority;
    n->above = NULL;
    n->below = NULL;

    if (head != NULL) {
        //std::cout << "     head != NULL" << std::endl;

        if (head->priority < priority) {
            //std::cout << "     head priority < priority" << std::endl;
            n->below = head;
            head->above = n;
            head = n;
        }

        if (head->priority > priority) {
            //std::cout << "     head priority >= priority" << std::endl;
            Node *tmpNode = new Node;
            tmpNode = head;
            while (tmpNode->priority > priority) {
                //std::cout << "     while cycle" << std::endl;
                if (tmpNode->below != NULL) {
                    tmpNode = tmpNode->below;
                    break;
                } else {
                    // here tmpNode is the last (lower) element
                    tmpNode->below = n;
                    n->above = tmpNode;
                    break;
                }
            }
            // after while tmpNode is the node
            //   which priority less then new element priority
            n->above = tmpNode->above;
            n->below = tmpNode;

            tmpNode->below = n;
            tmpNode = n->below;
            tmpNode->above = n;
        }
    } else {
        //::cout << "     head = NULL" << std::endl;
        // here head == NULL
        head = n;
        head->above = NULL;
        head->below = NULL;
    }
    size++;
    //std::cout << "     size++" << std::endl;
    //std::cout << "    DONE." << std::endl;
}

template<typename T>
void MyPriorityQueue<T>::pop() {
    if (!isEmpty()) {
        if (head->below != NULL) {
            Node* tmpNode = head;

            head = head->below;
            head->above = NULL;

            tmpNode->below = NULL;
            delete tmpNode;
        } else {
            delete head;
        }
        size--;
    } else {
        std::cerr << std::endl << "Error: can't pop. The queue is empty." << std::endl;
        exit(1);
    }
}

template<typename T>
T &MyPriorityQueue<T>::top() {
    if (!isEmpty()) {
        return head->data;
    } else {
        std::cerr << std::endl << "Error: can't return top element. The queue is empty." << std::endl;
        exit(1);
    }
}

template<typename T>
int MyPriorityQueue<T>::topPriority() {
    return head->priority;
}

template<typename T>
void MyPriorityQueue<T>::printCurNode(const Node* node) {
    std::cout << "[" << node->data << ":" << node->priority << "]";
}

template<typename T>
void MyPriorityQueue<T>::printQueue(){
    if (!isEmpty()) {
        Node* tmpNode = head;
        if (tmpNode->below != NULL) {
            while (tmpNode->below != NULL) {
                std::cout << " "; printCurNode(tmpNode);
            }
            std::cout << std::endl << "Total: " << size << " elements." << std::endl;
        } else {
            std::cout << "Only 1 element in queue: "; printCurNode(tmpNode); std::cout << std::endl;
        }
    } else {
        std::cout << "Queue is empty." << std::endl;
    }
}



#endif // MYPRIORITYQUEUE

