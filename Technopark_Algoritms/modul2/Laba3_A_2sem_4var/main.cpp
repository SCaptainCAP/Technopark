#include <iostream>
struct Point
{
    int coord;
    bool isEnd; //true if end
};
bool pointsCompare(const Point &a, const Point &b) {
    return (a.coord < b.coord);
}


template <class T>
void insert_to_heap(T *arr, int i, int n, bool (*isLess)(const T &, const T &))
{
    int parent;
    while(i > 0)
    {
        parent = (i - 1) / 2;
        if(isLess(arr[i], arr[parent]))
            return;
        std::swap(arr[i], arr[parent]);
        i = parent;
    }
}
template <class T>
void repair_heap(T *arr, int i, int n, bool (*isLess)(const T &, const T &))
{
    int left = 2*i + 1;
    int right = 2*i + 2;

    int largest = i;

    if((left < n) && (!isLess(arr[left], arr[largest])))
        largest = left;
    if((right < n) && (!isLess(arr[right], arr[largest])))
        largest = right;
    if(largest != i)
    {
        std::swap(arr[i], arr[largest]);
        repair_heap(arr, largest, n, isLess);
    }
}
template <class T>
void HeapSort(T* arr, int l, int r, bool (* isLess)(const T&, const T&)) {
    for(int i = l; i <= r; i++) {
        insert_to_heap(arr, i, i + 1, isLess);
    }
    int j = r;
    while(j > 0)
    {
        std::swap(arr[0], arr[j-1]);
        j--;
        repair_heap(arr, 0, j, isLess);
    }
}
int getSingleLayerLength(Point *arr, int n)
{
    int answer = 0;
    int level = 0;
    for (int i = 0; i < n; i++)
    {
        if(abs(level) == 1)
            answer += (arr[i].coord - arr[i - 1].coord);
        if(arr[i].isEnd)
            level--;
        else
            level++;
    }
    return answer;
}

int main()
{
    int n;
    std::cin >> n;
    n *= 2;
    Point *a = new Point[n];
    for (int i = 0; i < n; i++) {
        std::cin >> a[i].coord;
        a[i].isEnd = (i % 2 == 1);
    }

    HeapSort<Point>(a, 0, n, pointsCompare);

    std::cout << getSingleLayerLength(a, n);
    delete[] a;
    return 0;
}