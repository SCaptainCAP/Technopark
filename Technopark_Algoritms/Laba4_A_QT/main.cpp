#include <iostream>
#include <assert.h>
#include <cmath>
#define DEFAULT_SIZE 10

template <class T>
class Deque {
public:
    Deque(int size);
    Deque();
    ~Deque();

    void PushFront(T data);
    void PushBack(T data);
    T PopPack();
    T PopFront();
    bool IsEmpty() const;

private:
    T* buffer;
    int bufferSize;
    int minBufferSize;
    int head;
    int tail;
    bool empty;
    void IncreaseBuffer();
    void DecreaseBuffer();
};


template <typename T>
Deque<T>::Deque(int size) : bufferSize(size), minBufferSize(size), head(0), tail(size - 1), empty(true)
{
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::Deque() : bufferSize(DEFAULT_SIZE), minBufferSize(DEFAULT_SIZE), head(0), tail(DEFAULT_SIZE - 1), empty(true)
{
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::~Deque()
{
    while (!IsEmpty() )
    {
        PopFront();
    }
}

template <typename T>
void Deque<T>::IncreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize * 2)];
    assert(tmpBuffer);

    tmpBuffer[0] = buffer[head];
    for (int i = bufferSize + 1; i < bufferSize * 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i) % bufferSize];
    }

    head = 0;
    tail = bufferSize + 1;

    buffer = tmpBuffer;
    delete(tmpBuffer);
    bufferSize *= 2;
}

template <typename T>
void Deque<T>::DecreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize / 2)];
    assert(tmpBuffer);

    tmpBuffer[0] = buffer[head];
    for (int i = bufferSize + 1; i < bufferSize * 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i) % bufferSize];
    }

    head = 0;
    tail = bufferSize + 1;

    buffer = tmpBuffer;
    delete(tmpBuffer);
    bufferSize *= 2;
}

template <typename T>
void Deque<T>::PushFront(T data)
{
    empty = false;
    head = (head + 1) % bufferSize;
    if (head == tail && bufferSize > minBufferSize) {
        IncreaseBuffer();
        head++;
    }
    buffer[head] = data;
}


template <typename T>
void Deque<T>::PushBack(T data) {
    empty = false;
    tail = (tail - 1);
    if (tail < 0)
        tail = bufferSize - 1;
    if (head == tail && bufferSize > minBufferSize) {
        IncreaseBuffer();
        tail--;
    }
    buffer[tail] = data;
}


template <typename T>
T Deque<T>::PopPack() {
    if (IsEmpty())
        return -1;
    if (tail == head)
        empty = true;
    T data = buffer[tail];
    tail = (tail + 1) % bufferSize;
    if (std::abs(tail - head) + 1 < bufferSize / 2)
    {
        DecreaseBuffer();
    }
    return data;
}


template <typename T>
T Deque<T>::PopFront() {
    if (IsEmpty())
        return -1;
    if (tail == head)
        empty = true;
    T data = buffer[head];
    head = (head - 1);
    if (head < 0)
        head = bufferSize - 1;
    if (std::abs(tail - head) + 1 < bufferSize / 2)
    {
        DecreaseBuffer();
    }
    return data;
}


template <typename T>
bool Deque<T>::IsEmpty() const
{
    return empty;
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

    }
    if (nice)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
