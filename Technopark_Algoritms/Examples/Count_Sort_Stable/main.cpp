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

    /*int p = 0;
    for (int i = 0; i < valuesCount; i++) {
        for (int j = 0; j < valuesData[i]; j++) {
            data[p] = minValue + i;
            p++;
        }
    }*/
    for (int i = 1; i < valuesCount; i++) {
        valuesData[i] += valuesData[i - 1];
    }

    int* tempData = new int[n];
    memset(tempData, 0, n * sizeof(int));

    for (int i = n - 1; i >= 0; i--) {
        int valueIndex = data[i] - minValue;
        valuesData[valueIndex]--;
        tempData[valuesData[valueIndex]] = data[i];
    }

    memcpy(data, tempData, n * sizeof(int));

    delete [] valuesData;
    delete [] tempData;
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