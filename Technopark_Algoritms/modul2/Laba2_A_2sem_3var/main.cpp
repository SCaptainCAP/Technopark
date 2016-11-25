#include <iostream>
#include <vector>
#include <cmath>

struct Elka {
    int Arrive;
    int Depart;
    Elka(int arrive, int depart) : Arrive(arrive), Depart(depart){}
};

bool lessDepart(const Elka& e1, const Elka& e2) {
    return e1.Depart > e2.Depart;
}

template <class T>
void heap_insert(T *heap, int n, T x, bool (* isLess)(const T&, const T&)) {
    heap[n+1] = x;
    for (int i = n+1; i > 1;) {
        if (isLess(heap[i],heap[i/2])) {
            std::swap(heap[i], heap[i/2]);
            i = i/2;
        } else {
            break;
        }

    }

}

template <class T>
void heap_pop(T *heap, int n) {
    std::swap(heap[n],heap[1]);
    for (int i = 1; 2*i < n;) {
        i *= 2;
        if (i+1 < n && heap[i] < heap[i+1]) {
            i += 1;
        }
        if (heap[i/2] < heap[i]) {
            std::swap(heap[i/2], heap[i]);
        }
    }
}

template <class T>
void heapSort(T* arr, int l, int r, bool (* isLess)(const T&, const T&)){

    T *buff = new T[r-l];
    for (int i = l; i < r; ++i) {
        heap_insert(buff, i, arr[i], isLess);
    }
    for (int i = l; i < r; ++i) {
        arr[r-1-i] = buff[1];
        heap_pop(buff, r - i);
    }
    delete [] buff;
}1451

int main() {
    std::vector<Elka> elki;

    int n = 0;
    std::cin >> n;

    int x = 0;
    int y = 0;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        elki.push_back(Elka(x,y));
    }

    heapSort(elki.data(), 0, elki.size(), lessDepart);
    return 0;

}