#ifndef MYLIST_H_INCLUDED
#define MYLIST_H_INCLUDED

template <class T>
class MyList {

///// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! /////
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

    void isEmpty();
    void clear();
    unsigned int getSize();
    void push_back(const T &data);
    void push_front(const T &data);
    void pop_back();
    void pop_front();
    //void insert();
    T &front();
    T &back();
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
void MyList<T>::isEmpty(){
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
}

template <typename T>
void MyList<T>::pop_front(){
}

template <typename T>
T &MyList<T>::front() {
    if(isEmpty()) {
        std::cerr << "Error: front element does not exist. The list is empty." << std::endl;
//        exit();
    }
    return head->data;
}

template <typename T>
T &MyList<T>::back() {
    if(isEmpty()) {
        std::cerr << "Error: back element does not exist. The list is empty." << std::endl;
//        exit(1);
    }
    return tail->data;
}


#endif // MYLIST_H_INCLUDED
