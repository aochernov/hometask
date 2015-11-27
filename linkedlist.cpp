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
    while(prev -> next != 0)
    {
        prev = prev -> next;
    }
    node *n = (node*) malloc(sizeof(node));
    if(n != 0)
    {
        n -> data = val;
        n -> next = NULL;
        prev -> next = n;
    }
}

int removefirst(node* head, int val)
{
    if(head -> data != val)
    {
        while((head -> next) -> data != val)
        {
            head = head -> next;
        }
        head -> next = (head -> next) -> next;
    }
    else
    {
        head -> data = (head -> next) -> data;
        head -> next = (head -> next) -> next;
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

int quit(node *head)
{
    while(head)
    {
        node* tmp = head -> next;
        free(head);
        head = tmp;
    }
}

int main()
{
    node* head = NULL;
    head = new node;
    char input = '0';
    int number=228;
    printf("There is the list of commands:\na <number> - add an element at the end of the list\nr <number> - remove the first matching element from the list\np - print all elements of the list\nq - quit the programm\n");
    while(input != 'q')
    {
        scanf("%c", &input);
        if(input == 'p')
        {
            print(head);
        }
        if(input == 'a')
        {
            scanf("%d", &number);
            insertafter(head, number);
        }
        if(input == 'r')
        {
            scanf("%d", &number);
            removefirst(head, number);
        }
    }
    quit(head);
    return 0;
}
