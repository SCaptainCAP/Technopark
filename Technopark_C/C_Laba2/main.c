#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#define true 1
#define false 0
#define positive 1
#define negative 0
#define DEF_STRING_SIZE 100
#define DEF_LN_SIZE 100

void exit_f()
{
    printf("[ERROR]");
    exit(EXIT_SUCCESS);
}

////////MATHEMATICA DECLARATION BEGIN////////////
int max(int left, int right) {
    return (left > right) ? left : right;
}

////////MATHEMATICA DECLARATION END//////////////
////////STACKCHAR DECLARATION BEGIN//////////////
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

void kill_stackchar(stackchar *head)
{
    stackchar *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }

}
////////STACKCHAR DECLARATION END//////////////

////////LONG NUMBER DECLARATION BEGIN//////////////
typedef struct ln
{
    int* data;
    int size;
    int buf_size;
    int sign;
} ln;

ln* make_ln(char *str) {
    assert(str);
    ln *ans = malloc(sizeof(ln));
    assert(ans);
    ans->data = malloc(sizeof(int) * DEF_LN_SIZE);
    assert(ans->data);
    ans->size = 0;
    ans->buf_size = DEF_LN_SIZE;
    ans->sign = positive;
    while (str[ans->size] != '\0') {
        ans->data[ans->size] = str[ans->size] - '0';
        ans->size++;
        if (ans->size == ans->buf_size) {
            int* tmp = realloc(ans->data, sizeof(int) * ans->buf_size * 2);
            assert(tmp);
            ans->data = tmp;
            ans->buf_size *= 2;
        }
    }
    return ans;
}

void normalize_ln_first_zeors(ln* ans) {
    assert(ans);
    // check first zeros
    int i = 0;
    for (i = 0; i < ans->size; i++) {
        if (ans->data[i] != 0)
            break;
    }
    if (i != 0) {
        for (int j = i; i < ans->size; i++) {
            ans->data[j - i] = ans->data[j];
        }
        ans->size -= i;
    }
}

void normalize_ln_buffer(ln* ans) {
    assert(ans);
    int changing = false;
    /*if (ans->size < ans->buf_size / 2) {
        ans->buf_size = ans->buf_size / 2;
        changing = true;
    }*/
    if (!changing && ans->size >= ans->buf_size) {
        ans->buf_size = ans->buf_size * 2;
        changing = true;
    }
    if (changing) {
        int* tmp = realloc(ans->data, sizeof(int) * ans->buf_size);
        assert(tmp);
        ans->data = tmp;
    }
}

void normalize_ln(ln* ans) {
    assert(ans);
    normalize_ln_first_zeors(ans);
    normalize_ln_buffer(ans);
}

ln* copy_ln(ln* src) {
    ln *ans = malloc(sizeof(ln));
    assert(ans);
    ans->data = malloc(sizeof(int) * src->buf_size);
    assert(ans->data);
    ans->size = src->size;
    ans->sign = src->sign;
    for (int i = 0; i < ans->size; i++) {
        ans->data[i] = src->data[i];
    }
    return ans;
}

int lib_ln(ln *left, ln *right) {
    if (left->sign == positive && right->sign == negative)
        return true;
    if (left->sign == negative && right->sign == positive)
        return false;
    if (left->size > right->size)
        return left->sign == positive;
    if (left->size < right->size)
        return left->sign != positive;
    for (int i = 0; i < left->size; i++) {
        if (left->data[i] > right->data[i])
            return left->sign == positive;
        if (left->data[i] < right->data[i])
            return left->sign != positive;
    }
    return negative;
}

int equals_ln(ln *left, ln *right) {
    if (left->sign != right->sign)
        return false;
    if (left->size != right->size)
        return false;
    for (int i = 0; i < left->size; i++) {
        if (left->data[i] != right->data[i])
            return false;
    }
    return true;
}


void print_ln(ln* ans) {
    if (ans->size != 0 && ans->sign == negative) {
        printf("%c", '-');
    }
    for (int i = 0; i < ans->size; i++) {
        printf("%d", ans->data[i]);
    }
}

int libim_ln(ln *left, ln *right) { //ignore minus
    if (left->size > right->size)
        return left->sign == positive;
    if (left->size < right->size)
        return left->sign != positive;
    for (int i = 0; i < left->size; i++) {
        if (left->data[i] > right->data[i])
            return left->sign == positive;
        if (left->data[i] < right->data[i])
            return left->sign != positive;
    }
    return negative;
}

/*ln* minus_ln(ln* left, ln* right) {
    ln* ans;
    int razn;
    if (lib_ln(left, right)) {
        ans = copy_ln(left);
        razn = left->size - right->size; // >= 0
        for (int i = razn; i < left->size; i++) {
            ans->data[i] -= right->data[i - razn];
        }

    }
}*/

ln* plus_ln(ln* left, ln* right) {
    int size_diff = left->size - right->size;
    ln* ans;
    if (size_diff >= 0) {
        ans = copy_ln(left);
    }
    else {
        ans = copy_ln(right);
    }
    //normalize_ln_buffer(ans);
    if (size_diff >= 0) {
        for (int i = size_diff; i < ans->size; i++) {
            ans->data[i] += right->data[i - size_diff];
        }
    }
    else {
        for (int i = -size_diff; i < ans->size; i++) {
            ans->data[i] += left->data[i + size_diff];
        }
    }
    for (int i = ans->size - 1; i > 0; i--) {
        ans->data[i - 1] += ans->data[i] / 10;
        ans->data[i] %= 10;
    }
    if (ans->data[0] > 10) {
        ans->size++;
        normalize_ln_buffer(ans);
        for (int i = ans->size - 1; i > 1; i--) {
            ans->data[i] = ans->data[i - 1];
        }
        ans->data[1] = ans->data[0] % 10;
        ans->data[0] = ans->data[0] / 10;
    }
    return ans;
}

ln* minus_ln(ln* left, ln* right) {
    int size_diff = left->size - right->size;
    ln* ans;
    if (size_diff >= 0) {
        ans = copy_ln(left);
    }
    else {
        ans = copy_ln(right);
    }
    //normalize_ln_buffer(ans);
    if (size_diff >= 0) {
        for (int i = size_diff; i < ans->size; i++) {
            ans->data[i] -= right->data[i - size_diff];
        }
    }
    else {
        for (int i = -size_diff; i < ans->size; i++) {
            ans->data[i] -= left->data[i + size_diff];
        }
    }
    for (int i = ans->size - 1; i > 0; i--) {
        ans->data[i - 1] += ans->data[i] / 10;
        ans->data[i] %= 10;
    }
    if (ans->data[0] > 10) {
        ans->size++;
        normalize_ln_buffer(ans);
        for (int i = ans->size - 1; i > 1; i--) {
            ans->data[i] = ans->data[i - 1];
        }
        ans->data[1] = ans->data[0] % 10;
        ans->data[0] = ans->data[0] / 10;
    }
    return ans;
}
////////LONG NUMBER DECLARATION END//////////////

////////STACKLN DECLARATION BEGIN//////////////
typedef struct stackln
{
    ln* data;
    struct stackln *next;
} stackln;

stackln* create_nodeln(ln *data)
{
    stackln *node = malloc(sizeof(stackln));

    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

void pushln(stackln **head, ln *data)
{
    stackln *node = create_nodeln(data);
    assert(node);
    node->next = *head;
    *head = node;
}

ln* popln(stackln **head)
{
    if (!(*head))
        exit_f();
    stackln *tmp = *head;
    ln* data = (*head)->data;
    *head = (*head)->next;
    free(tmp);
    return data;
}

void kill_stackln(stackln *head)
{
    stackln *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}
////////STACKLN DECLARATION END//////////////

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
        default:
            return -1;
    }
}

void read_infix_make_postfix(char* str_infix, char* str_postfix)
{
    stackchar** operations = malloc(sizeof(stackchar**));
    *operations = NULL;
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
    kill_stackchar(*operations);
    free(operations);
//    if (str_postfix[strlen(str_postfix) - 1] == ' ')
//        str_postfix[strlen(str_postfix) - 1] = '\0';
}

ln* calculate_postfix(char* str)
{
    char char_tmp = str[0];
    int int_tmp;
    int str_pointer = 0;
    ln* a = 0;
    ln* b = 0;
    char *str_number;
    stackln** st = malloc(sizeof(stackchar**));
    *st = NULL;
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
            pushln(st, make_ln(str_number));
            str[str_pointer - 1] = ' ';
            continue;
        }
        a = popln(st);
        b = popln(st);
        switch (char_tmp){
            case '-':
                //pushint(st, b - a);
                break;
            case '+':
                pushln(st, plus_ln(b, a));
                //pushint(st, b + a);
                break;
            case '*':
                //pushint(st, b * a);
                break;
            case '/':
                //pushint(st, b / a);
                break;
        }
    }
    ln* tmp = popln(st);
    kill_stackln(*st);
    free(*st);
    return tmp;
}

size_t read_line(char **str)
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
    size_t str_size = read_line(&str_input);
    if (str_size == -1)
        exit_f();

    char* str_postfix = calloc(sizeof(char), str_size);

    read_infix_make_postfix(str_input, str_postfix);

    //printf("%d\n", calculate_postfix(str_postfix)->data);
    print_ln(calculate_postfix(str_postfix));
    //std::cout << std::endl;

    free(str_input);
    free(str_postfix);
    return 0;
}