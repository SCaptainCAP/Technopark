#include <iostream>


int partition(int *arr, int l, int r) {
    int pivot = arr[1];
    int i = l + 1;
    int j = r - 1;
    while (true) {
        while (i < r && arr[i] < pivot) {
            i++;
        }
        while (j > l && arr[j] > pivot) {
            j--;
        }
        if (i >= j) {
            std::swap(arr[i], arr[j]);
            return i;
        }
        std::swap(arr[i], arr[j]);
        i++;
        j--;
    }
}

int findKStatistics(int* arr, int l, int r, int k)
{
    int pivotPos = partition(arr, l, r);
    if (pivotPos == k) {
        return arr[pivotPos];
    }
    if (pivotPos > k) {
        return findKStatistics(arr, l, pivotPos, k);
    }
    return findKStatistics(arr, pivotPos + 1, r, k);
}

//void generateFile() {
//    freopen("tests/1.txt", "w", std::cout);
//    std::cout << 1000 << " " << 125 << "\n";
//    for (int i = 0; i < 1000; i++) {
//        std::cout << rand() << " ";
//    }
//}

int main()
{


    int n = 0;
    int k = 0;
    std::cin >> n;
    std::cin >> k;
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    std::cout << findKStatistics(arr, 0, n, k);
    return 0;
}