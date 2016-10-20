#include <iostream>
#include <assert.h>
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

#define PLUS 1
#define MINUS 2
#define MULTI 3
#define DIVIDE 4
#define NONE 0


class CalcStack {
public:
    CalcStack();
    ~CalcStack();
    void erase();
    void push(int data);
    void push(CalcStack* stack);
    void setAction(int action);
    int calculate();
    void setAnswer(int answer);
private:
    CalcStack *a_stack, *b_stack;
    int size;
    int action;
    int answered;
    int answer;
};

void CalcStack::erase() {
    size = 0;
    action = NONE;
    delete(a_stack);
    delete(b_stack);
    answered = 0;
}

void CalcStack::push(int data) {
    if (size == 0) {
        a_stack = new CalcStack();
        a_stack->setAnswer(data);
    }
    if (size == 1) {
        b_stack = new CalcStack();
        b_stack->setAnswer(data);
    }
    size++;
}

void CalcStack::push(CalcStack *stack) {
    if (size == 0) {
        a_stack = stack;
    }
    if (size == 1) {
        b_stack = stack;
    }
    size++;
}

void CalcStack::setAction(int action) {
    this->action = action;
}

int CalcStack::calculate() {
    if (answered)
        return answer;
    if (size == 0)
        return 0;
    if (size == 1)
        return a_stack->answer;

    int a = 0;
    a = a_stack->calculate();
    int b = 0;
    b = b_stack->calculate();

    int ans = 0;
    if (action == PLUS)
        ans = a + b;
    if (action == MINUS)
        ans = a - b;
    if (action == MULTI)
        ans = a * b;
    if (action == DIVIDE)
    {
        if (b == 0)
            return 0;
        ans = a / b;
    }
    a_stack->setAnswer(ans);
    delete(b_stack);
    size = 1;
    return ans;
}

void CalcStack::setAnswer(int answer) {
    this->answer = answer;
    this->answered = 1;
}

CalcStack::CalcStack(): size(0), action(NONE), answered(0) {
    a_stack = NULL;
    b_stack = NULL;
}

CalcStack::~CalcStack() {
    delete(a_stack);
    delete(b_stack);
}


int main()
{
    CalcStack base;
    int tmp = 0;
    char sign = '0';
    while (std::cin.fail())
    {
        std::cin >> tmp;
        std::cin >> sign;
    }
    return 0;
}

///200­(123+34*2)+(48­2)   =   5