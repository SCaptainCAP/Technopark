#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#define true 1
#define false 0
#define DEF_STRING_SIZE 100


void exit_f()
{
    printf("[ERROR]");
    exit(EXIT_SUCCESS);
}

typedef struct stackchar
{
    char data;
    struct stackchar *next;
} stackchar;

stackchar* create_nodechar(char data)
{
    stackchar *node = malloc(sizeof(stackchar));

    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

void pushchar(stackchar **head, char data)
{
    stackchar *node = create_nodechar(data);
    assert(node);
    node->next = *head;
    *head = node;
}

char popchar(stackchar **head)
{
    if (!(*head))
        exit_f();
    stackchar *tmp = *head;
    char data = (*head)->data;
    *head = (*head)->next;
    free(tmp);
    return data;
}

char upperchar(stackchar **head)
{
    if (!(head) || !(*head))
        return '\0';
    return (*head)->data;
}

void kill_stackchar(stackchar **head)
{
    assert(head);
    stackchar *tmp = *head;
    stackchar *tmp1 = *head;
    while (tmp1 != NULL)
    {
        tmp1 = tmp->next;
        free(tmp);
    }

}

typedef struct stackint
{
    int data;
    struct stackint *next;
} stackint;

stackint* create_nodeint(int data)
{
    stackint *node = malloc(sizeof(stackint));

    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

void pushint(stackint **head, int data)
{
    stackint *node = create_nodeint(data);
    assert(node);
    node->next = *head;
    *head = node;
}

int popint(stackint **head)
{
    if (!(*head))
        exit_f();
    stackint *tmp = *head;
    int data = (*head)->data;
    *head = (*head)->next;
    free(tmp);
    return data;
}

int upperint(stackint **head)
{
    if (!(head) || !(*head))
        return '\0';
    return (*head)->data;
}

void kill_stackint(stackint **head)
{
    assert(head);
    stackint *tmp = *head;
    stackint *tmp1 = *head;
    while (tmp1 != NULL)
    {
        tmp1 = tmp1->next;
        free(tmp);
    }
}


int priority(char c)
{
    switch (c){
        case '(':
            return 0;
        case ')':
            return 1;
        case '-':
            return 2;
        case '+':
            return 2;
        case '*':
            return 3;
        case '/':
            return 3;
    }
    return -1;
}

int isOperation(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    else
        return 0;
}

void read_infix_make_postfix(char* str_infix, char* str_postfix)
{
    stackchar** operations = malloc(sizeof(stackchar**));
    int prior = -1;
    char char_tmp = '0';
    char char_tmp1 = '0';

    int str_postfix_pointer = 0;
    int str_pointer_input = 0;
    int prev_input_number = 0;
    while (true)
    {
        char_tmp = str_infix[str_pointer_input++];
        if (char_tmp == '\0')
            break;

        if (isdigit(char_tmp))
        {
            prev_input_number = 1;
            str_postfix[str_postfix_pointer++] = char_tmp;
            continue;
        }

        if (prev_input_number) {
            str_postfix[str_postfix_pointer++] = ' ';
            prev_input_number = 0;
            //continue;
        }
        if (char_tmp == '(') {
            pushchar(operations, char_tmp);
            //operations.PushFront(char_tmp);
            continue;
        }
        if (char_tmp == ')') {
            char_tmp1 = popchar(operations);//operations.PopFront();
            while (char_tmp1 != '(')
            {
                str_postfix[str_postfix_pointer++] = char_tmp1;
                char_tmp1 = popchar(operations);//operations.PopFront();
            }
            continue;
        }
        prior = priority(char_tmp);
        while (priority(upperchar(operations)) >= prior) {
            str_postfix[str_postfix_pointer++] = popchar(operations);
        }
        pushchar(operations, char_tmp);
        //operations.PushFront(char_tmp);
    }
    if (prev_input_number) {
        str_postfix[str_postfix_pointer++] = ' ';
    }
    while (upperchar(operations) != '\0')
    {
        str_postfix[str_postfix_pointer++] = popchar(operations);
    }
    kill_stackchar(operations);
    free(operations);
//    if (str_postfix[strlen(str_postfix) - 1] == ' ')
//        str_postfix[strlen(str_postfix) - 1] = '\0';
}

int calculate_postfix(char* str)
{
    char char_tmp = str[0];
    int int_tmp;
    int str_pointer = 0;
    int a = 0;
    int b = 0;
    char *str_number;
    stackint** st = malloc(sizeof(stackint**));

    while (true)
    {
        char_tmp = str[str_pointer++];
        if (char_tmp == '\0')
            break;

        if (char_tmp == ' ')
            continue;

        if (isdigit(char_tmp))
        {
            str_number = str + (str_pointer - 1);
            while (isdigit(char_tmp))
                char_tmp = str[str_pointer++];
            str[str_pointer - 1] = '\0';
            int_tmp = atoi(str_number);
            pushint(st, int_tmp);
            str[str_pointer - 1] = ' ';
            continue;
        }
        a = popint(st);
        b = popint(st);
        switch (char_tmp){
            case '-':
                pushint(st, b - a);
                break;
            case '+':
                pushint(st, b + a);
                break;
            case '*':
                pushint(st, b * a);
                break;
            case '/':
                pushint(st, b / a);
                break;
        }
    }
    int tmp = popint(st);
    kill_stackint(st);
    free(st);
    return tmp;
}

int read_line(char **str)
{
    *str = malloc(DEF_STRING_SIZE * sizeof(char));
    assert(*str);

    char tmp = '\0';
    int i = 0;
    int strsize = DEF_STRING_SIZE;
    while (scanf("%c", &tmp) == 1 && tmp != '\n' && tmp != EOF)
    {
        if (i >= strsize)
        {
            strsize *= 2;
            char *tmp_str = realloc(*str, strsize * sizeof(char));
            assert(tmp_str);
            *str = tmp_str;
        }
        (*str)[i] = tmp;
        i++;
    }
    if (i >= strsize)
    {
        strsize += 1;
        char *tmp_str = realloc(*str, strsize * sizeof(char));
        assert(tmp_str);
        *str = tmp_str;
    }
    (*str)[i] = '\0';
    return strsize;

}

void null_line(char *str, int n)
{
    for (int i = 0; i < n; i++)
        str[i] = '\0';
}

int main()
{
    //char* str_input = (char*) calloc(DEF_STRING_SIZE, sizeof(char));
    char* str_input;
    int str_size = read_line(&str_input);
    if (str_size == -1)
        exit_f();

    char* str_postfix = calloc(sizeof(char), str_size);

    read_infix_make_postfix(str_input, str_postfix);

    printf("%d\n", calculate_postfix(str_postfix));
    //std::cout << std::endl;

    free(str_input);
    free(str_postfix);
    return 0;
}