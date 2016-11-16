#include <iostream>
#include <cstring>
#include <vector>

int count_sort(int *data, unsigned long n) {
    int minValue = data[0];
    int maxValue = data[0];
    for (int i = 1; i < n; i++) {
        minValue = std::min(minValue, data[i]);
        maxValue = std::max(maxValue, data[i]);
    }

    int valuesCount = maxValue - minValue + 1;
    int *valuesData = new int[valuesCount];
    memset(valuesData, 0, valuesCount * sizeof(int));

    for (int i = 0; i < n; i++) {
        valuesData[data[i] - minValue]++;
    }

    int p = 0;
    for (int i = 0; i < valuesCount; i++) {
        for (int j = 0; j < valuesData[i]; j++) {
            data[p] = minValue + i;
            p++;
        }
    }
}


int main() {
    std::vector<int> data;
    int value = 0;
    while (std::cin >> value) {
        data.push_back(value);
    }

    count_sort(&data[0], data.size());

    for (int i = 0; i < data.size(); i++)
        std::cout << data[i];

    return 0;
}