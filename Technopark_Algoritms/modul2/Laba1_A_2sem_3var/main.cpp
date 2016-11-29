#include <iostream>
#include <vector>
#include <cmath>

struct Point {
    int X;
    int Y;
    double angle;
    Point(int x, int y) : X(x), Y(y){}
};

bool isLessAngle (const Point& l, const Point& r)
{

    return l.angle > r.angle;
}

template <class T>
void insertionSort(T* arr, int l, unsigned long r, bool (* isLess)(const T&, const T&)){
    for (int i = l; i < r; i++)
    {
        T tmp = arr[i];
        int j = i;
        for (; j > l && isLess(tmp, arr[j - 1]); j--) {
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}

void setCurveStart(std::vector<Point> &vect) {
    int minx = vect[0].X;
    int miny = vect[0].Y;
    int min_index = 0;
    for (int i = 1; i < vect.size(); i++) {
        if (vect[i].X == minx) {
            if (vect[i].Y < miny) {
                miny = vect[i].Y;
                min_index = i;
            }
            continue;
        }
        if (vect[i].X < minx) {
            minx = vect[i].X;
            miny = vect[i].Y;
            min_index = i;
        }
    }
    std::swap(vect[0],vect[min_index]);
}

void fillCurveAngles(std::vector<Point> &vect) {
    for (int i = 1; i < vect.size(); i++) {
        if(vect[i].X == vect[0].X)
            vect[i].angle = 3.1415 / 2;
        else
            vect[i].angle = atan2(vect[i].Y - vect[0].Y, vect[i].X - vect[0].X);
    }
}


int main() {
    std::vector<Point> points;

    int n = 0;
    std::cin >> n;

    int x = 0;
    int y = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        points.push_back(Point(x,y));
    }

    setCurveStart(points);
    fillCurveAngles(points);

    insertionSort(points.data(), 1, points.size(), isLessAngle);


    for (int i = 0; i < points.size(); i++)
    {
        std::cout << points[i].X << " " << points[i].Y << std::endl;
    }
    return 0;

}