
#include <iostream>
#include <assert.h>

template <typename T>
struct Node
{
    T Data;
    Node* Next;
    Node* Prev;
    Node() : Data(0), Next(0), Prev(0) {}
    Node(T data) : Data(data), Next(0), Prev(0) {}

};

template <class T>
class Deque {
public:
    Deque();
    ~Deque();

    void PushFront(T data);
    void PushBack(T data);
    T PopPack();
    T PopFront();
    bool IsEmpty() const;

private:
    Node<T>* head;
    Node<T>* tail;
};


template <typename T>
Deque<T>::Deque() : head(0), tail(0) {}


template <typename T>
Deque<T>::~Deque()
{
    while (!IsEmpty() )
    {
        PopFront();
    }
}


template <typename T>
void Deque<T>::PushFront(T data) {
    Node<T>* newNode = new Node<T>(data);
    if ( head == 0 )
    {
        assert( tail == 0 );
        head = tail = newNode;
    }
    else
    {
        assert( head != 0);

        newNode->Prev = head;
        newNode->Next = tail;
        tail->Prev = newNode;
        head->Next = newNode;
        head = newNode;
    }
}


template <typename T>
void Deque<T>::PushBack(T data) {
    Node<T>* newNode = new Node<T>(data);
    if ( head == 0 )
    {
        assert( tail == 0 );
        head = tail = newNode;
    }
    else
    {
        assert( head != 0);


        newNode->Prev = head;
        newNode->Next = tail;
        tail->Prev = newNode;
        head->Next = newNode;
        tail = newNode;
    }
}


template <typename T>
T Deque<T>::PopPack() {
    if (IsEmpty())
        return -1;
    T data = tail->Data;
    if ( head == tail )
    {
        delete(tail);
        head = tail = 0;
    }
    else
    {
        tail->Next->Prev = head;
        head->Next = tail->Next;
        Node<T>* tmpNode = tail;
        tail = tail->Next;
        delete(tmpNode);
    }
    return data;
}


template <typename T>
T Deque<T>::PopFront() {
    if (IsEmpty())
        return -1;
    T data = head->Data;
    if ( head == tail )
    {
        delete(tail);
        head = tail = 0;
    }
    else
    {
        head->Prev->Next = tail;
        tail->Prev = head->Prev;
        Node<T>* tmpNode = head;
        head = head->Prev;
        delete(tmpNode);
    }
    return data;
}


template <typename T>
bool Deque<T>::IsEmpty() const
{
    return (head == 0);
}



int main() {
    int n, command, definition;
    int nice = 1;
    std::cin >> n;
    Deque<int> deque;
    for (int i = 0; i < n; i++)
    {
        std::cin >> command;
        std::cin >> definition;
        switch (command)
        {
            case 1: // push front
            {
                deque.PushFront(definition);
                break;
            }
            case 2: // pop front
            {
                if (deque.PopFront() != definition)
                    nice = 0;
                break;
            }
            case 3: // push back
            {
                deque.PushBack(definition);
                break;
            }
            case 4: // pop back
            {
                if (deque.PopPack() != definition)
                    nice = 0;
                break;
            }
        }
        if (!nice)
            break;
    }
    if (nice)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}