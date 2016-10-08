/*
Составить программу определения такого максимального подотрезка среди элементов заданного целочисленного массива,
элементы которого увеличиваются по порядку на 1.
Подотрезок массива - это часть ("кусок") массива, который включает в себя все элементы исходного массива от
некоторого начального индекса до некоторого другого конечного индекса без изменения порядка следования элементов.
Элементы подотрезка функция должна вернуть через указатель-параметр, а ее длину — через возвращаемый результат.
*/



#include <stdio.h>
#include <stdlib.h>

int find_subarray(int count, int *array_old, int *new_array) {
    int start = 0;
    int finish = 1;
    int elem_last = array_old[0];
    int longest_start = start;
    int longest_finish = finish;
    int i;
    for (i = 1; i < count; i++) {
        if (array_old[i] - elem_last != 1) {
            if (finish - start > longest_finish - longest_start) {
                longest_start = start;
                longest_finish = finish;
            }
            start = i;
            finish = i + 1;
        } else {
            finish += 1;
        }
        elem_last = array_old[i];
    }

    if (finish - start > longest_finish - longest_start) {
        longest_start = start;
        longest_finish = finish;
    }

    int new_count = longest_finish - longest_start;
    for (i = longest_start; i < longest_finish; i++) {
        new_array[i - longest_start] = array_old[i];
    }
    return new_count;
}

int main() {
    int count;
    int i;

    // Read count of elements
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("[error]");
        return 0;
    };
    int *array = malloc(sizeof(int) * count);

    // Read elements of array
    for (i = 0; i < count; i++) {
        if (scanf("%d", &array[i]) != 1) {
            free(array);
            printf("[error]");
            return 0;
        };
    }

    // Init output array
    int *answer_array = malloc(sizeof(int) * count);


    // Find answer
    int answer_count = find_subarray(count, array, answer_array);
    if (answer_count == 1)
    {
        free(array);
        free(answer_array);
        printf("0");
        return 0;
    }


    // Make output
    printf("%d\n", answer_count);
    for (i = 0; i < answer_count - 1; i++) {
        printf("%d ", answer_array[i]);
    }
    if (answer_count > 1) {
        printf("%d", answer_array[answer_count - 1]);
    }

    free(array);
    free(answer_array);

    return 0;
}