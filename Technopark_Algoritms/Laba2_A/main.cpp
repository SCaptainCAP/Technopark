/*2_1. ​Даны два массива целых чисел одинаковой длины A[0..n­1] и B[0..n­1]. Необходимо найти первую пару
индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.
Время работы ­ O(n).

n ≤ 100000.

4
4 ­8 6 0
­10 3 1 1

0 1
 */

#include <iostream>
#include <assert.h>

void input_array(int *array, int size)
{
    assert(array);
    for (int i = 0; i < size; i++)
        std::cin >> array[i];
}

int find_max(int *array, int size)
{
    assert(array);
    int max = array[0];
    int index = 0;
    for (int i = 1; i < size; i++)
        if (array[i] > max)
        {
            max = array[i];
            index = i;
        }
    return index;
}

void check(int* A, int* B, int size, int* i0, int* j0)
{
    assert(A);
    assert(B);
    assert(j0);
    assert(i0);

    int max = A[0] + B[0];
    int maxA = A[0];
    *i0 = 0;
    *j0 = 0;
    int ind_tmp_B;

    for (int i = 0; i < size; i++)
    {
        if (A[i] > maxA || i == 0)
        {
            ind_tmp_B = find_max(B + i, size - i);
            if (A[i] + B[ind_tmp_B + i] > max)
            {
                *i0 = i;
                *j0 = ind_tmp_B + i;
                maxA = A[i];
                max = maxA + B[ind_tmp_B + i];
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;

    int *A = new int[n];
    int *B = new int[n];

    int j0 = 0;
    int i0 = 0;

    input_array(A, n);
    input_array(B, n);

    check(A, B, n, &i0, &j0);

    std::cout << i0 << " ";
    std::cout << j0;

    delete[](A);
    delete[](B);

    return 0;
}