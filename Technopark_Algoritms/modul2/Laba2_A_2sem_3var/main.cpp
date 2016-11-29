#include <iostream>
#include <vector>
#include <cmath>

struct Elka {
    int Arrive = 0;
    int Depart = 0;
    Elka(int arrive, int depart) : Arrive(arrive), Depart(depart){}
    Elka() {}
};

bool lessElka(const Elka& e1, const Elka& e2) {
    return e1.Depart < e2.Depart;
}

template <class T>
class Heap{
private:
    std::vector<T> a;
    bool (*isLess)(const T& el1,const T& el2);
public:
    Heap(bool (* isLesss)(const T&, const T&)) : isLess(isLesss) {}
    void insert(T x)
    {
        a.push_back(x);
        unsigned long index = a.size() - 1;
        while (index > 0) {
            unsigned long parentIndex = (index - 1) / 2;
            if (!isLess(a[index],a[parentIndex]))
                return;
            std::swap(a[index], a[parentIndex]);
            index = parentIndex;
        }
    }

    void repair(int i = 0)
    {
        int left = 2*i + 1;
        int right = 2*i + 2;

        int largest = i;
        if (left < a.size() && isLess(a[left], a[i]))
            largest = left;
        if (right < a.size() && isLess(a[right], a[largest]))
            largest = right;

        if (largest != i) {
            std::swap(a[i], a[largest]);
            repair(largest);
        }
    }

    T pop_max() {
        T tmp = a[0];
        a[0] = a[a.size() - 1];
        a.erase(a.begin() + a.size() - 1);
        if (a.empty()) return tmp;
        repair();
        return tmp;
    };

    T get_max() {return a[0]; };

    bool is_empty() {
        return a.size() == 0;
    }
};

/*template <class T>
void heap_sort(T *data, int n, bool (* isLess)(const T&, const T&)) {
    T *buff = new T[n+1];
    for (int i = 0; i < n; ++i) {
        heap_insert(buff, i, data[i], isLess);
    }
    for (int i = 0; i < n; ++i) {
        data[n-1-i] = buff[1];
        heap_pop(buff, n - i, isLess);
    }
    delete [] buff;

}*/

int main() {
    int n = 0;
    std::cin >> n;
    Heap<Elka> heap(lessElka);

    int x = 0;
    int y = 0;
    int answer = 1;
    for (int i = 0; i < n; i++) {
        std::cin >> x >> y;
        if (!heap.is_empty()) {
            if (heap.get_max().Depart >= x) {
                answer++;
            } else {
                heap.pop_max();
            }
        }
        heap.insert(Elka(x, y));
    }

    std::cout << answer;
    return 0;

}