#include <iostream>
#include <assert.h>
#include <cstring>
/*Дано выражение в инфиксной записи. Вычислить его, используя перевод выражения в постфиксную запись.

Выражение не содержит отрицительных чисел.

Количество операций ≤ 100.

Формат входных данных. ​Строка, состоящая их символов 0123456789­+/*()

Гарантируется, что входное выражение корректно, нет деления на 0, вычислимо в целых числах. Деление целочисленное.

Формат выходных данных.

Значение выражения.


200­(123+34*2)+(48­2)   =   5

1 + 2     =     3
*/
#define DEFAULT_SIZE 4

template <class T>
class Deque {
public:
    Deque(int size);
    Deque();
    ~Deque();

    void PushFront(T data);
    void PushBack(T data);
    T PopBack();
    T PopFront();
    T GetBack();
    T GetFront();
    bool IsEmpty() const;

    void print(bool debug = false) const;

private:
    T* buffer = NULL;
    int bufferSize;
    int minBufferSize;
    int head;
    int tail;
    bool empty;
    void IncreaseBuffer();
    void DecreaseBuffer();
};

template <typename T>
Deque<T>::Deque(int size) : bufferSize(size), minBufferSize(size), head(-1), tail(0), empty(true)
{
    assert(size > 1);
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::Deque() : bufferSize(DEFAULT_SIZE), minBufferSize(DEFAULT_SIZE), head(-1
), tail(0), empty(true)
{
    buffer = new T[bufferSize];
}

template <typename T>
Deque<T>::~Deque()
{
    delete[](buffer);
}

template <typename T>
void Deque<T>::IncreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize * 2)];
    assert(tmpBuffer);

    tmpBuffer[0] = buffer[head];
    for (int i = bufferSize + 1; i < bufferSize * 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i - 1 - bufferSize) % bufferSize];
    }
    head = 0;
    tail = bufferSize + 1;
    bufferSize *= 2;

    delete [](buffer);
    buffer = tmpBuffer;
}

template <typename T>
void Deque<T>::DecreaseBuffer() {
    T* tmpBuffer = new T[(bufferSize / 2)];
    assert(tmpBuffer);
    assert(bufferSize >= minBufferSize);

    tmpBuffer[0] = buffer[head];
    for (int i = 1; i < bufferSize / 2; i++)
    {
        tmpBuffer[i] = buffer[(tail + i - 1) % bufferSize];
    }

    head = 0;
    tail = 1;
    bufferSize /= 2;

    delete [](buffer);
    buffer = tmpBuffer;
}

template <typename T>
void Deque<T>::PushFront(T data)
{
    if (IsEmpty()) {
        buffer[0] = data;
        head = 0;
        tail = 0;
        empty = false;
    }
    else
    {
        head = (head + 1) % bufferSize;
        if (head == tail) {
            head--;
            if (head < 0)
                head = bufferSize - 1;
            IncreaseBuffer();
            head++;
        }
        buffer[head] = data;
    }
}

template <typename T>
void Deque<T>::PushBack(T data) {
    if (IsEmpty()) {
        buffer[bufferSize - 1] = data;
        tail = bufferSize - 1;
        head = bufferSize - 1;
        empty = false;
    }
    else
    {
        tail = (tail - 1);
        if (tail < 0)
            tail = bufferSize - 1;
        if (head == tail) {
            tail = (tail + 1) % bufferSize;
            IncreaseBuffer();
            tail--;
        }
        buffer[tail] = data;
    }

}

template <typename T>
T Deque<T>::PopBack() {
    if (IsEmpty())
        return -1;
    if (tail == head)
        empty = true;
    T data = buffer[tail];
    tail = (tail + 1) % bufferSize;
    int rasst = (tail > head) ? head + bufferSize - tail : head - tail;
    if (rasst < bufferSize / 2  && bufferSize > minBufferSize)
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

    int rasst = (tail > head) ? head + bufferSize - tail : head - tail;
    if (rasst < bufferSize / 2  && bufferSize > minBufferSize)
    {
        DecreaseBuffer();
    }
    return data;
}

template <typename T>
T Deque<T>::GetBack() {
    if (IsEmpty())
        return -1;
    return buffer[tail];
}

template <typename T>
T Deque<T>::GetFront() {
    if (IsEmpty())
        return -1;
    return buffer[head];
}

template <typename T>
bool Deque<T>::IsEmpty() const
{
    return empty;
}

template <typename T>
void Deque<T>::print(bool debug) const {
    if (debug)
        std::cout << "Head: " << head << "; Tail: " << tail << std::endl;
    std::cout << "|";
    for (int i = 0; i < bufferSize; i++)
    {
        std::cout << " " << buffer[i] << " |";
    }
    std::cout << std::endl;
}

int priority(char c)
{
    switch (c){
        case '(':
            return 0;
        case ')':
            return 1;
        case '-':
            return 2;
        case '+':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
    }
    return -1;
}

int isOperation(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    else
        return 0;
}

void read_infix_make_postfix(char* str_infix, char* str_postfix)
{
    Deque <char>operations;
    int prior = -1;
    char char_tmp = '0';
    char char_tmp1 = '0';

    int str_postfix_pointer = 0;
    int str_pointer_input = 0;
    int prev_input_number = 0;
    while (true)
    {
        char_tmp = str_infix[str_pointer_input++];
        if (char_tmp == '\0')
            break;

        if (isdigit(char_tmp))
        {
            prev_input_number = 1;
            str_postfix[str_postfix_pointer++] = char_tmp;
            continue;
        }

        if (prev_input_number) {
            str_postfix[str_postfix_pointer++] = ' ';
            prev_input_number = 0;
            //continue;
        }
        if (char_tmp == '(') {
            operations.PushFront(char_tmp);
            continue;
        }
        if (char_tmp == ')') {
            char_tmp1 = operations.PopFront();
            while (char_tmp1 != '(')
            {
                str_postfix[str_postfix_pointer++] = char_tmp1;
                char_tmp1 = operations.PopFront();
            }
            continue;
        }
        prior = priority(char_tmp);
        if (priority(operations.GetFront()) >= prior) {
            str_postfix[str_postfix_pointer++] = operations.PopFront();
        }
        operations.PushFront(char_tmp);
    }
    if (prev_input_number) {
        str_postfix[str_postfix_pointer++] = ' ';
    }
    while (operations.GetFront() != -1)
    {
        str_postfix[str_postfix_pointer++] = operations.PopFront();
    }
//    if (str_postfix[strlen(str_postfix) - 1] == ' ')
//        str_postfix[strlen(str_postfix) - 1] = '\0';
}

int calculate_postfix(char* str)
{
    Deque <int>deque;
    char char_tmp = str[0];
    int int_tmp;
    int str_pointer = 0;
    int a = 0;
    int b = 0;
    char *str_number;

    while (true)
    {
        char_tmp = str[str_pointer++];
        if (char_tmp == '\0')
            break;

        if (char_tmp == ' ')
            continue;

        if (isdigit(char_tmp))
        {
            str_number = str + (str_pointer - 1);
            while (isdigit(char_tmp))
                char_tmp = str[str_pointer++];
            str[str_pointer - 1] = '\0';
            int_tmp = atoi(str_number);
            deque.PushFront(int_tmp);
            str[str_pointer - 1] = ' ';
            continue;
        }
        a = deque.PopFront();
        b = deque.PopFront();
        switch (char_tmp){
            case '-':
                deque.PushFront(b - a);
                break;
            case '+':
                deque.PushFront(b + a);
                break;
            case '*':
                deque.PushFront(b * a);
                break;
            case '/':
                deque.PushFront(b / a);
                break;
        }
    }
    return deque.PopFront();
}


int main()
{
    //char* str_input = (char*) calloc(500, sizeof(char));
    char* str_input = new char[500];
    assert(str_input);
    for (int i = 0; i < 500; i++)
        str_input[i] = '\0';

    std::cin.getline(str_input, 500);

    char* str_postfix = new char[500];
    assert(str_postfix);
    for (int i = 0; i < 500; i++)
        str_postfix[i] = '\0';

    read_infix_make_postfix(str_input, str_postfix);

    std::cout << calculate_postfix(str_postfix);
    std::cout << std::endl;

    delete[](str_input);
    delete[](str_postfix);
    return 0;
}

///200­(123+34*2)+(48­2)   =   5