#include <iostream>
#include <vector>
#include <cstring>

template <class T>
int digit(T n, int p)//получение p-го байта
{
    return (n>>(8 * p) & 255);
}

template <class T>
void LSD(T* a, int l, int r)
{
    int k = sizeof(T);
    int b[r-l];
    for(int i = 0; i < k; i++)
    {
        int c[256] = {0};
        for(int j = l; j < r; j++)
        {
            c[digit(a[j],i)]++;
        }
        for(int j = 1; j < 256;j++)
        {
            c[j]+=c[j-1];
        }
        for(int j = r-1; j >l-1;j--)
        {
            b[--c[digit(a[j],i)]] = a[j];
        }
        for(int j = l; j < r; j++)
        {
            a[j] = b[j];
        }
    }
}

int main() {
    std::vector<unsigned long long> vect;
    long n = 0;
    unsigned long long tmp;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> tmp;
        vect.push_back(tmp);
    }

    LSD(vect.data(), 0, vect.size());
    for (int i = 0; i < n; i++)
        std::cout << vect[i] << " ";

    return 0;
}