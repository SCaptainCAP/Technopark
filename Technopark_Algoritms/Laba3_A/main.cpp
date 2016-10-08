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
template <typename T>
void input_array(T *array, int size)
{
    assert(array);
    for (int i = 0; i < size; i++)
        std::cin >> array[i];
}
template <typename T>
void print_array(T *array, int size)
{
    assert(array);
    for (int i = 0; i < size; i++)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}

int two(int stepen)
{
    return  1 << stepen;
}


void fill_ans(int* A, int* B, int *ans, int n, int m)
{
    assert(A);
    assert(B);
    assert(ans);
    int l, r, mid, rasst, rasst_last;
    int moved = 0;
    int now = 0;
    for (int i = 0; i < m; i++)
    {
        now = B[i];
        moved = 0;
        // check if B[i] is not in A
        if (B[i] <= A[0])
            ans[i] = 0;
        else if (B[i] >= A[n - 1])
            ans[i] = n - 1;
        else
        // B[i] is definitely in A, A is definitely bigger than 1 element
        {
            rasst_last = A[0] - B[i];
            rasst = A[1] - B[i];
            l = 0;
            r = 1;
            while (rasst_last < rasst && rasst < 0)
            {
                l = r;
                r = r << 1;
                if (r >= n)
                    r = n - 1;
                rasst_last = A[l] - B[i];
                rasst = A[r] - B[i];
            }
            if (rasst_last > 0)
                moved = 1;
            if (moved) //moved
            {
                r = r >> 1;
                l = r >> 1;
            }
            if (r - l == 1)
            {
                if (abs(B[i] - A[l]) <= abs(B[i] - A[r]))
                    ans[i] = l;
                else
                    ans[i] = r;
            }
            else {
                rasst_last = A[l] - B[i];
                while (l < r - 1) {
                    mid = (l + r) / 2;
                    if (A[mid] >= B[i])
                        r = mid;
                    else if (A[mid] <= B[i])
                        l = mid;
                }
                if (abs(B[i] - A[l]) <= abs(B[i] - A[r]))
                    ans[i] = l;
                else
                    ans[i] = r;
            }
        }
    }
}

int main() {
    int n, m;

    std::cin >> n;
    int *A = new int[n];
    input_array(A, n);

    std::cin >> m;
    int *B = new int[m];
    input_array(B, m);

    int *ans = new int[m];

    fill_ans(A, B, ans, n, m);

    print_array(ans, m);

    delete(A);
    delete(B);
    delete(ans);

    return 0;
}