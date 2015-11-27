#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int my_strlen(char *s)
{
    int i = 0;
    while(s[i] != '\0')
    {
        i++;
    }
    return(i);
}

int my_strcmp(char *s1, char *s2)
{
    int comp = 0, i = 0;
    while(s1[i] != s2[i])
    {
        comp = s1[i] - s2[i];
        i++;
    }
    return(comp);
}

int my_strcpy(char *s1, char *s2)
{
    int i;
    for(i = 0; i < my_strlen(s1); i++)
    {
        if(s2[i] == '\0')
        {
            break;
        }
        s1[i] = s2[i];
    }
}

int my_strctt(char *s1, char *s2)
{
    int i, l = my_strlen(s1);
    for(i = 0; i < my_strlen(s2) + 1; i++)
    {
        s1[i + l] = s2[i];
    }
}

struct node
{
    int count;
    char symbol;
    node* next;
};

int addtolist(node* prev, char s)
{
    node* n = NULL;
    n = new node;
    n -> symbol = s;
    n -> count = 1;
    n -> next = NULL;
    prev -> next = n;
}

int countelements(node *head, char el)
{
    while(head -> next != NULL && head -> symbol != el)
        {
            head = head -> next;
        }
        if(head -> symbol != el)
        {
            addtolist(head, el);
        }
        if(head -> symbol == el)
        {
            head -> count = head -> count + 1;
        }
}

int listelements(char *s)
{
    node* head = NULL;
    head = new node;
    head -> count = 1;
    head -> symbol = s[0];
    int i;
    for(i = 1; i < my_strlen(s); i++)
    {
        countelements(head, s[i]);
    }
    while(head)
    {
        printf("%c: %d\n", head -> symbol, head -> count);
        head = head -> next;
    }
}

struct node1
{
    int count;
    char symbol[10];
    node1* next;
};

int addtoliststring(node1* prev, char *s)
{
    node1* n = NULL;
    n = new node1;
    int i;
    for(i = 0; i <= 10; i++)
    {
        (n -> symbol)[i] = s[i];
    }
    n -> count = 1;
    n -> next = NULL;
    prev -> next = n;
}

int countstrings(node1 *head, char *el)
{
    while(head -> next != NULL && my_strcmp(head -> symbol, el) != 0)
        {
            head = head -> next;
        }
        if(my_strcmp(head -> symbol, el) != 0)
        {
            addtoliststring(head, el);
        }
        if(my_strcmp(head -> symbol, el) == 0)
        {
            head -> count = head -> count + 1;
        }
}

int liststrings(void)
{
    char s[10];
    int N, i;
    printf("Please enter the number of strings: ");
    scanf("%d", &N);
    gets(s);
    node1* head = NULL;
    head = new node1;
    head -> count = 1;
    for(i = 0; i <= 10; i++)
    {
        (head -> symbol)[i] = s[i];
    }
    for(i = 0; i < N; i++)
    {
        gets(s);
        countstrings(head, s);
    }
    head = head -> next;
    while(head)
    {
        printf("%s: %d\n", head -> symbol, head -> count);
        head = head -> next;
    }
}

int pairedestrings(void)
{
    char s[10];
    int N, i, j;
    printf("Please enter the number of strings: ");
    scanf("%d", &N);
    char result[10] = "";
    for(i = 0; i <= N; i++)
    {
        gets(s);
        for(j = 0; j <= my_strlen(s); j++)
        {
            result[j] = result[j] ^ s[j];
        }
    }
    puts(result);
}

using namespace std;

int main()
{
    liststrings();
    return 0;
}
