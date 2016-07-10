// todo:
//  разобраться с копированием (перегрузка оператора = ) ...все равно не работает
//  insert() сделать

#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED



template <class T>
class MyList {

    ///// !!!!!!!!!!!!!!!!!private!!!!!!!!!!!!!!!!!! /////
    /////        if NOT private #define SUDO         /////
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };
    unsigned int size;
    Node* head;
    Node* tail;

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

        T operator*() { return nodePtr->data; }

        iterator operator++() {
            nodePtr = nodePtr->next;
            return nodePtr;
        }

        iterator operator++(int) {
            nodePtr = nodePtr->next;
            return nodePtr;
        }

        iterator operator--() {
            nodePtr = nodePtr->prev;
            return nodePtr;
        }

        iterator operator--(int) {
            nodePtr = nodePtr->next;
            return nodePtr;
        }

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

    void printList();
    MyList<T>& operator=(T &other);
};

template <typename T>
MyList<T>& MyList<T>::operator=(T &other) {
    // все равно это не работает.
    std::cout << "hey" << std::endl;
    return *this;
}

/* Default constructor */
template <typename T>
MyList<T>::MyList() {
    head = tail = NULL;
    size = 0;
}

/* Default destructor */
template <typename T>
MyList<T>::~MyList() {
    clear();
}

/* Copy constructor */
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

/* A function that clears the list. */
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

/*
 * A function that checks the list is empty.
 * @return bool value;
 */
template <typename T>
bool MyList<T>::isEmpty(){
    return (size == 0); // mb (!size) ?
}

/*
 * A function that return the list size.
 * @return size - the size of the list;
 */
template <typename T>
unsigned int MyList<T>::getSize() {
    return size;
}

/*
 * A function that adds node in the end of the list.
 * @param &data - link to the data value.
 */
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

/*
 * A function that adds node in the front of the list.
 * @param &data - link to the data value.
 */
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

/* A function that remove last element from the list. */
template <typename T>
void MyList<T>::pop_back() {
    std::cout << "pop_back()" << std::endl;
    if(!isEmpty()) {
        std::cout << "not empty " << std::endl;
        if (tail->prev != NULL) {
            std::cout << " tail->prev not NULL" << std::endl;
            tail = tail->prev;
            tail->next = NULL;
        } else {
            std::cout << " tail->prev is NULL" << std::endl;
            head = NULL;
            tail = NULL;
        }
        size--;
    } else {
        std::cout << "is empty" << std::endl;
        std::cerr << std::endl << "Error: can't pop_back. The list is empty." << std::endl;
        exit(1);
    }
    std::cout << "done pop_back()" << std::endl;
}

/* A function that remove first element from the list. */
template <typename T>
void MyList<T>::pop_front(){
    std::cout << "pop_front()" << std::endl;
    if(!isEmpty()) {
        std::cout << "not empty " << std::endl;
        if (head->next != NULL) {
            std::cout << " head->next not NULL" << std::endl;
            head = head->next;
            head->prev = NULL;
        } else {
            std::cout << "head->next is NULL" << std::endl;
            tail = NULL;
            head = NULL;
        }
        size--;
    } else {
        std::cout << "is empty" << std::endl;
        std::cerr << std::endl << "Error: can't pop_back. The list is empty." << std::endl;
        exit(1);
    }
    std::cout << "done pop_front()" << std::endl;
}

/*
 * A function that return the first list element dara.
 * @return T value - data from the first list element.
 */
template <typename T>
T &MyList<T>::front() {
    if(isEmpty()) {
        std::cerr << std::endl << "Error: front element does not exist. The list is empty." << std::endl;
        exit(1);
    }
    return head->data;
}

/*
 * A function that return the last list element data.
 * @return T value - data from the last list element.
 */
template <typename T>
T &MyList<T>::back() {
    if(isEmpty()) {
        std::cerr << std::endl << "Error: back element does not exist. The list is empty." << std::endl;
        exit(1);
    }
    return tail->data;
}

/* A function that prints all list nodes data to the console. */
template<typename T>
void MyList<T>::printList() {
    if (!isEmpty()) {
        iterator itr = head;
        iterator itr_end = tail->next;
        std::cout << "[ | ";
        for (int i = 0; itr != itr_end; itr++, i++) {
            std::cout << i << "=" << *itr << " | ";
        }
        std::cout << "]" << std::endl;
    } else {
        std::cerr << std::endl << "Error: cant print list. The list is empty." << std::endl;
    }
}


#endif // MYLIST_H_INCLUDED
