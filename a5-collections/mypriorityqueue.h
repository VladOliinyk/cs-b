//todo:
// спросить про варианты printQueue()


#ifndef MYPRIORITYQUEUE
#define MYPRIORITYQUEUE

#include <iostream>

template<typename T>
class MyPriorityQueue {

private:
    struct Node {
        T data;
        int priority = 0;
        Node* above = NULL; // higher priority
        Node* below = NULL; //  lower priority
        int getPriority() {
            return priority;
        }
    };

    int size = 0;
    Node* head;

    void printNode(const Node* node);

public:
    MyPriorityQueue();
    ~MyPriorityQueue();
    MyPriorityQueue(const MyPriorityQueue<T> &anotherQueue);

    bool isEmpty();
    void clear();
    int getSize();
    void push(const T &data, int priority = 1);
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
        Node* tmpNode = anotherQueue;
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
int MyPriorityQueue<T>::getSize() {
    return size;
}

bool comparePriority(int a, int b) {
    return a <= b;
}

template<typename T>
void MyPriorityQueue<T>::push(const T &data, int newPriority) {
    std::cout << " 0:" << std::endl;
    Node *n = new Node;
    n->data = data;
    n->priority = newPriority;

    if (size == 0) {
        //if you are here - queue is empty
        std::cout << " 0:0:" << std::endl;
        n->above = NULL;
        n->below = NULL;
        head = n;
    } else {
        std::cout << " 0:1:" << std::endl;
        //if you are here - queue is NOT empty
        Node* tmpNode = new Node;
        tmpNode = head;
        //int a = tmpNode->priority;
        int a = tmpNode->getPriority();
        if ( a <= newPriority) {
            std::cout << " 0:1:0:" << std::endl;
            //if you are here - top element's priority LESS than newPriority
            //need to add BEFORE top element
            tmpNode->above = n;
            n->below = tmpNode;
            head = n;
        } else {
            std::cout << " 0:1:1:" << std::endl;
            //if you are here - top element's priority MORE than newPriority
            if (size == 1) {
                std::cout << "0:1:1:0:" << std::endl;
                n->above = tmpNode;
                tmpNode->below = n;
            } else {
                std::cout << " 0:1:1:1:" << std::endl;
                if (tmpNode->priority > newPriority) {
                    std::cout << " 0:1:1:1:0:" << std::endl;
                    // here tmpNode.priority still MORE than newPriority
                    while (tmpNode->priority > newPriority) {
                        std::cout << "         -0:" << std::endl;
                        if (tmpNode->below != NULL) {
                            // tmpNode->below exist
                            std::cout << "         -0:0:" << std::endl;
                            tmpNode = tmpNode->below;
                            continue;
                        } else {
                            std::cout << "         -0:1:" << std::endl;

                            // tmpNode->below does not exist

                            //here tmpNode is the last element in queue
                            //  but tmpNode.priority still MORE than newPriority
                            //need to add AFTER tmpNode element
                            std::cout << "              &tmpNode        : " << &tmpNode << std::endl <<
                                         "              &tmpNode->below : " << &tmpNode->below << std::endl <<
                                         "              &n              : " << &n << std::endl <<
                                         "              &n->above       : " << &n->above << std::endl;
                            tmpNode->below = n;
                            n->above = tmpNode;
                            std::cout << std::endl;
                            std::cout << "              &tmpNode        : " << &tmpNode << std::endl <<
                                         "              &tmpNode->below : " << &tmpNode->below << std::endl <<
                                         "              &n              : " << &n << std::endl <<
                                         "              &n->above       : " << &n->above << std::endl;
                            break;
                        }
                    }
                } else {
                    std::cout << " 0:1:1:1:1:" << std::endl;
                    // here tmpNode.priority still LESS than newPriority
                    std::cout << "         -0:2:" << std::endl;
                    //here (I hope) tmpNode is the first element
                    //  which tmpNode.priority <= newPriority
                    //need to add BEFORE tmpNode element
                    n->above = tmpNode->above;
                    n->below = tmpNode;
                    (tmpNode->above)->below = n;
                    tmpNode->above = n;
                }
                std::cout << "         -" << std::endl;
            }
        }
        //end of 'queue is NOT empty'
    }
    std::cout << " -" << std::endl;
    size++;
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
void MyPriorityQueue<T>::printNode(const Node* node) {
    std::cout << "[" << node->data << ":" << node->priority << "]";
}

template<typename T>
void MyPriorityQueue<T>::printQueue(){
    if (!isEmpty()) {
        Node* tmpNode = head;
        if (tmpNode->below == NULL) {
            std::cout << "Here is only 1 element: ";
            printNode(tmpNode);
            std::cout << std::endl;
        } else {
            /* var1 */
            //do {
            //    printNode(tmpNode);
            //    tmpNode = tmpNode->below;
            //} while (tmpNode->below != NULL);
            //printNode(tmpNode);

            /* var2 */
            //for (int i=0; i < size; i++) {
            //    printNode(tmpNode);
            //    tmpNode = tmpNode->below;
            //}

            /* var3 */
            while (true) {
                if (tmpNode->below != NULL) {
                    printNode(tmpNode);
                    tmpNode = tmpNode->below;
                } else {
                     printNode(tmpNode);
                     break;
                }
            }
            std::cout << std::endl << "Total " << size << " elements." << std::endl;

        }
    } else {
        std::cout << "Queue is empty." << std::endl;
    }
}



#endif // MYPRIORITYQUEUE

