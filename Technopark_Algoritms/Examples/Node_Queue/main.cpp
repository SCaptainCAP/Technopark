
#include <iostream>
#include <assert.h>

struct Node
{
    int Data;
    Node* Next;
    Node() : Data(0), Next(0) {}
    Node(int data) : Data(data), Next(0) {}

};

class Queue {
public:
    Queue();
    ~Queue();

    void Enqueue(int data);
    int Dequeue();
    bool IsEmpty() const;

private:
    Node* head;
    Node* tail;
};

Queue::Queue() : head(0), tail(0) {}

Queue::~Queue()
{
    while (!IsEmpty() )
    {
        Dequeue();
    }
}

void Queue::Enqueue(int data)
{
    Node* newNode = new Node(data);
    if ( head == 0 )
    {
        assert( tail == 0 );
        head = tail = newNode;
    }
    else
    {
        assert( head != 0);
        head->Next = newNode;
        head = newNode;
    }
}

int Queue::Dequeue() {
    assert( !IsEmpty() );
    int data = tail->Data;
    if ( head == tail )
    {
        delete(tail);
        head = tail = 0;
    }
    else
    {
        Node* tmpNode = tail;
        tail = tail->Next;
        delete(tmpNode);
    }
}

bool Queue::IsEmpty() const
{
    return (head == 0);
}


int main() {
    int n = 0;
    std::cin >> n;
    Queue queue;
    bool result;
    for ( int i = 0; i < n; i++)
    {
        int operation = 0;
        std::cin >> operation;
        int number = 0;
        std::cin >> number;
        switch ( operation )
        {
            case 2:
                if ( queue.Dequeue() != number )
                {
                    result = false;
                }
                break;
            case 3:
                queue.Enqueue(number);
        }
    }
    return 0;
}