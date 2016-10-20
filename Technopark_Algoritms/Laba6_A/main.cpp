#include <iostream>
#include <assert.h>
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

int calculate_layer(int to_add, int level)
{
    std::cout << "To add: " <<  to_add << ", level: " << level << std::endl;

    if (to_add <= 1)
        return 1;
    if (level == 1)
        return 1;
    int ans = 0;
    int razn = (level < to_add) ? (to_add - level) : 0;
    //if (to_add <= level)
    {
        for (int i = 0; i < min(to_add, level); i++){
            ans += calculate_layer(i + razn, to_add - i - razn);
            //std::cout << "Ans: " <<  ans << std::endl;

        }
    }
//    for (int i = 0; i < to_add - level; i++) {
//        ans += calculate_layer(i + level - to_add, level);
//        std::cout << "Ans: " <<  ans << std::endl;
//    }


    return ans;
}


int main()
{
    int n = 0;
    int ans = 0;
    std::cin >> n;

//    for (int i = 1; i <= n; i++)
//        ans += calculate_layer(n - i, i);
//    std::cout << calculate_layer(3, 3) << std::endl << std::endl;
//    std::cout << calculate_layer(4, 4) << std::endl << std::endl;
//    std::cout << calculate_layer(5, 5) << std::endl << std::endl;
//    std::cout << calculate_layer(7, 7) << std::endl << std::endl;
    std::cout << calculate_layer(n, n);
    return 0;
}

///200­(123+34*2)+(48­2)   =   5