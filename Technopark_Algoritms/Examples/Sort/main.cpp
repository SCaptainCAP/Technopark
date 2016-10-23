#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int X;
    int Y;

    Point() : X(0), Y(0){}
};

bool operator < (const Point& l, const Point& r)
{
    return l.X < r.X;
}

bool isLessX (const Point& l, const Point& r)
{
    return l.X < r.X;
}

bool isLessY (const Point& l, const Point& r)
{
    return l.Y < r.Y;
}

template <class T>
bool isLessDefault (const T& l, const T& r)
{
    return l < r;
}

template <class T>
void mySort(T* arr, int l, int r, bool (* isLess)(const T&, const T&))
{
    for (int i = l; i < r; i++)
    {
        for (int j = i + 1; j < r; j++)
        {
            if (isLess(arr[j], arr[i]))
                std::swap(arr[i], arr[j]);
        }
    }
}



int main() {
    std::vector<Point> arr;
    while (true){
        Point pt;
        std::cin >> pt.X >> pt.Y;
        if (std::cin.fail() || std::cin.eof()) {
            break;
        }
        arr.push_back(pt);
    }
    //mySort(, 0, arr.size());
    mySort(arr.data(), 0, arr.size(), isLessX);

    for (int i = 0; i < arr.size(); i++)
    {
        std::cout << "(" << arr[i].X << ", " << arr[i].Y << "), ";
    }
    std::sort;
    return 0;
}