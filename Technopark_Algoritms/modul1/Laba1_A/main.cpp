//​ Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и
// вычитания (умножением пользоваться нельзя).

// 5
// 1 4 9 16 25

#include <iostream>
#include <assert.h>

void find_natur_squares(int n, int *array) {
    assert(n >= 1);
    array[0] = 1;
    int ans = 1;
    for (int i = 1; i < n; i++) {
        ans += i + i + 1;
        array[i] = ans;
    }
}

void printArray(int length, int *array){
    for (int i = 0; i < length; i++)
        std::cout << array[i] << std::endl;
}


int main() {
    int n;
    std::cin >> n;

    int *answers = new int[n];
    find_natur_squares(n, answers);
    printArray(n, answers);

    delete [] answers;
    return 0;
}