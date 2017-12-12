#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct my_struct {
    struct list_head list;
    int value;
};

void lst_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

#define lst_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); \
            pos = pos->next)

#define lst_entry(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define lst_for_each_safe(pos, n, head) \
    for (pos = (head)->next, n = pos->next; pos != (head); \
        pos = n, n = pos->next)


int main(int argc, char **argv)
{
    struct my_struct *tmp;
    struct my_struct myList;
    struct list_head *pos, *q;
    INIT_LIST_HEAD(&myList.list);

    for(unsigned int i = 3; i != 0; --i){
        tmp = (struct my_struct*)malloc(sizeof(struct my_struct));
        printf("Enter value:");
        scanf("%d", &(tmp->value));
        tmp->value = i + 1;
        lst_add(&(tmp->list), &(tmp->list), &(tmp->list).next);
    }
    printf("\n");

    printf ("traversing the list using list_for_each()\n");
    lst_for_each(pos, &myList.list){
        tmp = lst_entry(pos, struct my_struct, list);
        printf("Value = %d\n", tmp->value);
    }
    printf("\n");
    printf ("deleting the list using list_for_each_safe()\n");

    lst_for_each_safe(pos, q, &myList.list){
        tmp = lst_entry(pos, struct my_struct, list);
        printf("freeing item value = %d\n", tmp->value);
        list_del(pos);
        free(tmp);
    }
    return 0;
}

