#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    int info;
    float value;
    struct Node* next;
    struct Node* prev;
} Node;

struct Node* init() {
    struct Node* first;
    struct Node* last;

    first = (struct Node*)malloc(sizeof(struct Node));
    last = (struct Node*)malloc(sizeof(struct Node));

    first->next = last;
    first->prev = last;
    first->info = 1;

    last->next = first;
    last->prev = first;
    last->info = 1;

    return (first);
}

struct Node* list_add(Node* lst, float number)
{
    // One way 
    //struct Node* temp, * p, *e;
    //temp = (struct Node*)malloc(sizeof(Node));
    //p = lst->next;
    //lst->next = temp;
    //temp->next = p;
    //temp->value = number;
    //temp->prev = lst;
    //e = temp->next;
    //e->prev = temp;
    //return(temp);

    // Second way
    struct Node* temp, * p;
    temp = (struct Node*)malloc(sizeof(Node));
    p = lst->next; 
    lst->next = temp; 
    temp->value = number; 
    temp->next = p; 
    temp->prev = lst; 
    if (p != NULL)
        p->prev = temp;
    return(temp);
}

void listprint(Node* lst)
{
    struct Node* p;
    p = lst;
    do {
        p = p->next;
        printf_s("%f\n", p->value);
    } while (p->next->info != 1);
}

void operation(Node* lst) {
    float sum = 0;
    struct Node* first, *last;
    first = lst->next;
    last = lst->prev->prev;

    while (first->info != 1) {
        sum += first->value * last->value;
        first = first->next;
        last = last->prev;
    }
    printf_s("Sum is: %f", sum);
    return (sum);
}

int main() {
    int length;
    printf_s("Please write length: ");
    scanf_s("%d", &length);
    struct  Node* My_list = init();
    int count = -1;
    while (count < length - 1) {
        float num;
        printf_s("Write num: ");
        scanf_s("%f", &num);
        count++;
        list_add(My_list, num);
    }
    listprint(My_list);
    operation(My_list);
    return 1;
};
