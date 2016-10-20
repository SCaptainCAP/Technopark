#include <iostream>
#include <cstring>
/*В большой IT­фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с

желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое

может быть удовлетворено.

Число заявок ≤ 100000.

Формат входных данных:

Вход содержит только пары целых чисел — начала и концы заявок.

Формат выходных данных:

Выход должен содержать натуральное число — максимальное число заявок.
*/
typedef struct task{
    int begin;
    int end;
} task;

int fill_tasks(task *tasks)
{
    int i = 0;
    while (std::cin >> tasks[i].begin >> tasks[i].end)
        i++;
    return i;
}

int closest_task_index(task *tasks, int tasks_size, int begin)
{
    int start = -1;
    for (int i = 0; i < tasks_size; i++)
    {
        if (tasks[i].begin >= begin)
            if (start == -1 || (tasks[i].end < tasks[start].end))
            {
                start = i;
            }
    }
    return start;
}

int max_tasks(task *tasks, int tasks_size)
{
    int count = 0;
    int time_passed = 0;
    int closest = closest_task_index(tasks, tasks_size, 0);
    while (closest != -1)
    {
        time_passed = tasks[closest].end;
        closest = closest_task_index(tasks, tasks_size, time_passed);
        count++;
    }
    return count;
}

int main()
{
    task tasks[100000];
    std::cout << max_tasks(tasks, fill_tasks(tasks));


    return 0;
}