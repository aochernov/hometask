#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct node
{
    int data;
    node* next;
};

int insertafter (node* prev, int val)
{
    while (prev -> next != 0)
    {
        prev = prev -> next;
    }
    node* n = (node*) malloc(sizeof(node));
    if(n == NULL)
    {
        return 1;
    }
    if (n != 0)
    {
        n -> data = val;
        n -> next = NULL;
        prev -> next = n;
    }
}

int removefirst(node* head, int val)
{
    if (head -> data != val)
    {
        if (head -> next == NULL)
        {
            return 0;
        }
        while((head -> next) -> data != val)
        {
            head = head -> next;
        }
        node* n = head -> next;
        n -> next = (head -> next) -> next;
        free(head -> next);
        head -> next = n -> next;
    }
    else
    {
        if(head -> next == NULL || (head -> next) -> next == NULL)
        {
            return 0;
        }
        node* n = head -> next;
        n -> next = (head -> next) -> next;
        head -> data = (head -> next) -> data;
        free(head -> next)
        head -> next = (n -> next) -> next;
    }
}

int print(const node *head)
{
    while(head)
    {
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf("\n");
}

int clean(node *head)
{
    while (head)
    {
        node* tmp = head -> next;
        free(head);
        head = tmp;
    }
}

int cycle(node *head)
{
    node *n1, *n2, *n;
    n1 = n2 = head;
    do
    {
        n1 = n1 -> next;
        n2 = (n2 -> next) -> next;
        n = n2 -> next;
        if (n -> next == NULL)
        {
                break;
        }
    }
    while (n1 != n2 && n2 -> next != NULL && (n2 -> next) -> next != NULL);
    if (n1 == n2)
    {
        printf ("Cycle\n");
    }
    else
    {
        printf ("No cycle\n");
    }
}

int main()
{
    node* head = NULL;
    head = new node;
    printf("Please enter the first element of the list: ");
    scanf("%d", &(head -> data));
    char input = '0';
    int number;
    printf("There is the list of commands:\na <number> - add an element at the end of the list\nr <number> - remove the first matching element from the list\np - print all elements of the list\nq - quit the programm\nс - check, if there's cycle in list\n");
    while (input != 'q')
    {
        scanf("%c", &input);
        if (input == 'p')
        {
            print(head);
        }
        if (input == 'a')
        {
            scanf("%d", &number);
            insertafter(head, number);
        }
        if (input == 'r')
        {
            scanf("%d", &number);
            removefirst(head, number);
        }
        if (input == 'c')
        {
            cycle(head);
        }
    }
    clean(head);
    return 0;
}
