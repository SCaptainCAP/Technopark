#include <iostream>
#include <cstring>
/*Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.

Формат входных данных:

        На вход подается количество кубиков N.

Формат выходных данных:

        Вывести число различных пирамид из N кубиков.

ВЫСОКАЯ ПИРАМИДА
*/
int min(int a, int b){
    return (a < b) ? a : b;
}

long int calculate_layer(int to_add, int level, long int **buffer, int depth)
{

    if (to_add <= 1)
        return 1;
    if (level == 1)
        return 1;

    if (buffer[to_add][level] != -1)
        return buffer[to_add][level];

    long int ans = 0;
    int razn = (to_add > level) ? (to_add - level) : 0;
    {
        for (int i = 0; i < min(to_add, level); i++){
            buffer[i + razn][to_add - i - razn] = calculate_layer(i + razn, to_add - i - razn, buffer, depth + 1);
            ans += buffer[i + razn][to_add - i - razn];
        }
    }


    return ans;
}

long int find(int n)
{
    long int ans = 0;
    long int **buffer = new long int*[n + 1];
    for(int i = 0; i < n + 1; i++) {
        buffer[i] = new long int[n + 1];
        for (int j = 0; j < n + 1 ; j++) {
            buffer[i][j] = -1;
        }
    }

    ans = calculate_layer(n, n, buffer, 0);

    for(int i = 0; i < n; ++i) {
        delete [] buffer[i];
    }
    delete [] buffer;
    return ans;
}
int main()
{
    int n = 0;
    std::cin >> n;

    std::cout << find(n);
    return 0;
}