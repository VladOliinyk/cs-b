// todo:
//  разобраться с итератором
//  разобраться с копированием (перегрузка оператора =)
//  нужно ли делать swap ?
//  мб printList ?

#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED

template <class T>
class MyList {

    ///// !!!!!!!!!!!!!!!!!private!!!!!!!!!!!!!!!!!! /////
public:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    unsigned int size;
    Node *head;
    Node *tail;

public:
    MyList();
    ~MyList();
    MyList(const MyList<T> &anotherList);

    bool isEmpty();
    void clear();
    unsigned int getSize();
    void push_back(const T &data);
    void push_front(const T &data);
    void pop_back();
    void pop_front();
    //void insert();
    T &front();
    T &back();

    class iterator {
    public:
        Node* nodePtr;
        iterator() { nodePtr = NULL; }

        iterator(Node* ptr) { nodePtr = ptr; }

        T &operator*() { return nodePtr->data; }

        iterator &operator++() { return (nodePtr = nodePtr->next); }

        iterator &operator--() { return (nodePtr = nodePtr->prev); }

        bool operator==(const iterator &enotherIter) { return nodePtr == enotherIter.nodePtr; }

        bool operator!=(const iterator &enotherIter) { return nodePtr != enotherIter.nodePtr; }

        iterator begin() {
            iterator bgn(head);
            return bgn;
        }

        iterator end() {
            iterator en(tail->next);
            return en;
        }

        bool hasNext() {
            return this->next;
        }
    };

    MyList<T> &operator=(const T &anotherList);
};

template <typename T>
MyList<T>::MyList() {
    head = tail = NULL;
    size = 0;
}

template <typename T>
MyList<T>::~MyList() {
    clear();
}

template <typename T>
MyList<T>::MyList(const MyList<T> &anotherList) {
    head = tail = NULL;
    size = 0;
    if (!anotherList.isEmpty()) {
        for (Node* tmpNode = anotherList.head; tmpNode != NULL; tmpNode = tmpNode->next) {
            push_back(tmpNode->data);
        }
    }
}

template <typename T>
void MyList<T>::clear() {
    while (size != 0) {
        Node* tmpNode = tail;
        if (tail->prev != NULL) {
            tail = tail->prev;
        }
        if (tail->next != NULL) {
            tail->next = NULL;
        }
        delete tmpNode;
        size--;
    }
}

template <typename T>
bool MyList<T>::isEmpty(){
    return (size == 0); // mb (!size) ?
}

template <typename T>
unsigned int MyList<T>::getSize() {
    return size;
}

template <typename T>
void MyList<T>::push_back(const T &data) {
    Node* n = new Node;
    n->data = data;
    n->next = NULL;
    n->prev = NULL;

    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    size++;
}

template <typename T>
void MyList<T>::push_front(const T &data) {
    Node* n = new Node;
    n->data = data;
    n->next = NULL;
    n->prev = NULL;
    if (isEmpty()) {
        head = n;
        tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    size++;
}

template <typename T>
void MyList<T>::pop_back() {
    if(!isEmpty()) {
        if (tail->prev != NULL) {
            tail = tail->prev;
            tail->next = NULL;
        } else {
            head = NULL;
            tail = NULL;
        }
        size--;
    } else {
        std::cerr << std::endl << "Error: can't pop_back. The list is empty." << std::endl;
        exit(1);
    }
}

template <typename T>
void MyList<T>::pop_front(){
    if(!isEmpty()) {
        if (head->next != NULL) {
            head = head->next;
            head->prev = NULL;
        } else {
            head = NULL;
            tail = NULL;
        }
        size--;
    } else {
        std::cerr << std::endl << "Error: can't pop_back. The list is empty." << std::endl;
        exit(1);
    }

}

template <typename T>
T &MyList<T>::front() {
    if(isEmpty()) {
        std::cerr << std::endl << "Error: front element does not exist. The list is empty." << std::endl;
        exit(1);
    }
    return head->data;
}

template <typename T>
T &MyList<T>::back() {
    if(isEmpty()) {
        std::cerr << std::endl << "Error: back element does not exist. The list is empty." << std::endl;
        exit(1);
    }
    return tail->data;
}

// я хз почему перегрузка не работает
// код тела перегрузки просто НЕ выполняется и все
template<typename T>
MyList<T> &MyList<T>::operator=(const T &anotherList) {
    std::cout << "hey" << std::endl;
    return *this;
}


#endif // MYLIST_H_INCLUDED
