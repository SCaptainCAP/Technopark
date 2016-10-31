#include <iostream>

#include <iostream>
#include <assert.h>

template <typename T>
struct Node
{
    T Data;
    Node* Next;
    Node() : Next(0){}
    Node(T data) : Next(data){}

};

template <class T>
class StackList {
public:
    StackList();
    ~StackList();

    void PushBack(T data);
    T PopBack();
    T operator[] (int i);
    T get(int i);
    T* getAddr(int i);
    bool IsEmpty() const;
    int Size() const;

    void print(bool debug = false) const;

protected:
    Node<T>* start;
};


template <typename T>
StackList<T>::StackList() : start(0){}


template <typename T>
StackList<T>::~StackList()
{
    while (!IsEmpty() )
    {
        PopBack();
    }
}


template <typename T>
void StackList<T>::PushBack(T data) {
    Node<T>* newNode = new(std::nothrow) Node<T>;
    if (newNode == NULL)
    {
        throw std::runtime_error("ERROR: Not enough memory");
    }
    else
    {
        newNode->Data = data;
        if (IsEmpty()) {
            start = newNode;
            return;
        }
        Node<T>* node_tmp = start;
        while (node_tmp->Next != NULL)
            node_tmp = node_tmp->Next;
        node_tmp->Next = newNode;
    }
}


template <typename T>
T StackList<T>::PopBack() {
    if (IsEmpty())
        throw std::runtime_error("ERROR: popBack from empty stack");
    Node<T>* node_tmp = start;
    Node<T>* prev = start;
    while (node_tmp->Next != NULL) {
        prev = node_tmp;
        node_tmp = node_tmp->Next;
    }
    T data = node_tmp->Data;
    if (prev == node_tmp) { //last element popped
        free(node_tmp);
        start = NULL;
    }
    else {
        free(node_tmp);
        prev->Next = NULL;
    }
    return data;
}


template <typename T>
bool StackList<T>::IsEmpty() const
{
    return (start == 0);
}

template <typename T>
int StackList<T>::Size() const
{
    int ans = 0;
    Node<T>* tmp = start;
    while (tmp->Next) {
        tmp = tmp->Next;
        ans++;
    }
    return ans;
}

template <typename T>
T StackList<T>::operator[](int i) {
    Node<T>* node_tmp = start;
    int j = 0;
    while (i < j || node_tmp->Next != NULL) {
        node_tmp = node_tmp->Next;
        j++;
    }
    if (i == j)
        return node_tmp->Data;
    else
        throw std::runtime_error("ERROR: indexing out of range of buffer");
}

template <typename T>
T StackList<T>::get(int i) {
    Node<T>* node_tmp = start;
    int j = 0;
    while (i < j || node_tmp->Next != NULL) {
        node_tmp = node_tmp->Next;
        j++;
    }
    if (i == j)
        return node_tmp->Data;
    else
        throw std::runtime_error("ERROR: indexing out of range of buffer");
}

template <typename T>
T* StackList<T>::getAddr(int i) {
    Node<T>* node_tmp = start;
    int j = 0;
    while (i < j || node_tmp->Next != NULL) {
        node_tmp = node_tmp->Next;
        j++;
    }
    if (i == j)
        return &node_tmp->Data;
    else
        throw std::runtime_error("ERROR: indexing out of range of buffer");
}

template <typename T>
void StackList<T>::print(bool debug) const {
    Node<T>* tmp = start;
    std::cout << "|";
    while (tmp->Next) {
        std::cout << " " << tmp->Data << " |";
        tmp = tmp->Next;
    }
}


