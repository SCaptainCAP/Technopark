#include <iostream>
#include <vector>
#include <algorithm>

/*
struct mathVector {
    Point p1;
    Point p2;

    mathVector(Point point1, Point point2) : p1(point1), p2(point2) {}
};
*/


struct Point {
    int X;
    int Y;

    Point(int x, int y) : X(x), Y(y){}
};

double angleVector(int x1, int y1, int x2, int y2)
{
    double t = (x1*x2+y1*y2)/(sqrt((double)x1*x1+y1*y1)*sqrt((double)x2*x2+y2*y2));
    if     (t<-1) t=-1;
    else if(t> 1) t= 1;
    return acos(t);
}

bool isLessAngle (const Point& l, const Point& r)
{
    double angleL = angleVector(0, 1, l.X, l.Y) * 180 / 3.1415;
    double angleR = angleVector(0, 1, r.X, r.Y) * 180 / 3.1415;
/*    if (first.X == l.X) {
        if (first.Y < l.Y)
            angleL = 270;
        else
            angleL = 90;
    }
    else {
        angleL = atan((first.Y - l.Y) / (first.X - l.X)) * 180 / 3.14159;//y2-y1)/(x2-x1)
    }
    if (first.X == r.X) {
        if (first.Y < r.Y)
            angleL = 270;
        else
            angleL = 90;
    }
    else {
        angleR = atan((first.Y - r.Y) / (first.X - r.X)) * 180 / 3.14159;//y2-y1)/(x2-x1)
    }*/
    return angleL < angleR;
}

template <class T>
void mySort(T* arr, int l, unsigned long r, bool (* isLess)(const T&, const T&)){
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

    mySort(points.data(), 1, points.size(), isLessAngle);


    for (int i = 0; i < points.size(); i++)
    {
        std::cout << points[i].X << " " << points[i].Y << std::endl;
    }
    return 0;
}