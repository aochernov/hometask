#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#define MAX_LENGTH 20
#define module 50
#define constant 0

struct node
{
    char word[MAX_LENGTH];
    int count;
    node *next;
};

struct cell
{
    int key;
    node *element;
    cell *next;
};

void createtable(cell *head, int number)
{
    if(number == 0)
    {
        return 0;
    }
    else
    {
        node* first = (node *)malloc(sizeof(node));
        if(first == NULL)
        {
             return 1;
        }
        first -> next = NULL;
        first -> count = 0;
        strcpy(first -> word, "\0");
        cell* newcell = (cell *)malloc(sizeof(cell));
        if(newcell == NULL)
        {
             return 1;
        }
        newcell -> key = module - number;
        newcell -> element = first;
        newcell -> next = NULL;
        head -> next = newcell;
        number--;
        createtable(newcell, number);
    }
}

void addtolist(node *head, char *string)
{
    if(strcmp(head -> word, "\0") == 0)
    {
        strcpy(head -> word, string);
        head -> count = 1;
    }
    if(strcmp(head -> word, string) == 0)
    {
        head -> count = head -> count + 1;
    }
    else
    {
        if(head -> next == NULL)
        {
            node* newnode = (node *)malloc(sizeof(node));
            if(newnode == NULL)
            {
                 return 1;
            }
            newnode -> next = NULL;
            newnode -> count = 1;
            strcpy(newnode -> word, string);
            head -> next = newnode;
        }
        else
        {
            addtolist(head -> next, string);
        }
    }
}

void deletelist(node *head)
{
    if(head -> next == NULL)
    {
        free(head);
    }
    else
    {
        deletelist(head -> next);
        free(head);
    }
}

void deletetable(cell *head)
{
    deletelist(head -> element);
    if(head -> next == NULL)
    {
        free(head);
    }
    else
    {
        deletetable(head -> next);
        free(head);
    }
}

int goodhash(char *input)
{
    int length, i;
    unsigned int hash = 0;
    length = strlen(input);
    for(i = 0; i < length; i++)
    {
        hash = hash + (input[i] * pow(constant, i));
    }
    hash = hash % module;
    return(hash);
}

int gethashsum(char *input)
{
    int length, hash = 0, i;
    length = strlen(input);
    for(i = 0; i < length; i++)
    {
        hash = hash + input[i];
    }
    hash = hash % module;
    return(hash);
}

void printlist(node *head)
{
    while(head != NULL)
    {
        printf("%s: %d\n", head -> word, head -> count);
        head = head -> next;
    }
}

void printtable(cell *head)
{
    if((head -> element) -> count !=0)
    {
        printlist(head -> element);
    }
    if(head -> next != NULL)
    {
        printtable(head -> next);
    }
}

void statistics(cell *head)
{
    int *counter = (int *)malloc(module * sizeof(int));
    if(counter == NULL)
        {
             return 1;
        }
    int i;
    for(i = 0; i < module; i++)
    {
        if(strcmp((head -> element) -> word, "\0") == 0)
        {
            counter[i] = 0;
        }
        else
        {
            counter[i] = 1;
            if((head -> element) -> next != NULL)
            {
                node *tmp = (node *)malloc(sizeof(node));
                if(tmp == NULL)
                {
                     return 1;
                }
                tmp = head -> element;
                do
                {
                    counter[i]++;
                    tmp = tmp -> next;
                }
                while(tmp -> next != NULL);
                free(tmp);
            }
        }
        if(head -> next != NULL)
        {
            head = head -> next;
        }
    }
    int nonzero = 0, numberofelements = 0, minlength = 0x7FFFFFFF, maxlength = 0, arithmeticmean;
    for(i = 0; i < module; i++)
    {
        if(counter[i] != 0)
        {
            nonzero++;
        }
        numberofelements = numberofelements + counter[i];
        if(counter[i] > maxlength)
        {
            maxlength = counter[i];
        }
        if(counter[i] < minlength && counter[i] != 0)
        {
            minlength = counter[i];
        }
    }
    if(nonzero != 0)
    {
        arithmeticmean = numberofelements / nonzero;
    }
    else
    {
        arithmeticmean = 0;
    }
    if(minlength == 0x7FFFFFFF)
    {
        minlength = 0;
    }
    printf("Number of elements in table: %d\nNumber of non empty cells: %d\nMax length of chain: %d\nMin length of chain: %d\nAverage length of chain: %d\n", numberofelements, nonzero, maxlength, minlength, arithmeticmean);
    free(counter);
}

void readfile(char *filename, cell *table, char hashtype)
{
    char input[MAX_LENGTH];
    FILE *fo;
    fo = fopen(filename, "r");
    while(!feof(fo))
    {
        fscanf(fo, "%s", &input);
        int length, i;
        length = strlen(input);
        for(i = 0; i < length; i++)
        {
            input[i] = tolower(input[i]);
        }
        while(!(input[length - 1] <= 'z' && input[length - 1] >= 'a'))
        {
            input[length - 1] = '\0';
            length--;
        }
        while(!(input[0] <= 'z' && input[0] >= 'a'))
        {
            for(i = 0; i < length; i++)
            {
                input[i] = input[i+1];
            }
        }
        int hash;
        if(hashtype == 's')
        {
            hash = gethashsum(input);
        }
        if(hashtype == 'c')
        {
            hash = constant;
        }
        if(hashtype == 'g')
        {
            hash = goodhash(input);
        }
        addtolist(table[hash] -> element, input);
    }
    fclose(fo);
}

using namespace std;

int main()
{
    float time;
    clock_t start_time, finish_time;
    char filename[MAX_LENGTH];
    gets(filename);
    node* first2 = (node *)malloc(sizeof(node));
    if(first2 == NULL)
        {
             return 1;
        }
    first2 -> next = NULL;
    first2 -> count = 0;
    strcpy(first2 -> word, "\0");
    cell* table2 = (cell *)malloc(module * sizeof(cell));
    if(table2 == NULL)
        {
             return 1;
        }
    table2 -> key = 0;
    table2 -> element = first2;
    table2 -> next = NULL;
    start_time = clock();
    readfile(filename, table2, 'c');
    finish_time = clock();
    time = finish_time - start_time;
    printf("Hash function: constant\n");
    statistics(table2);
    printf("Time of execution: %f\n\n", time/CLOCKS_PER_SEC);
    deletetable(table2);
    node* first3 = (node *)malloc(sizeof(node));
    if(first3 == NULL)
        {
             return 1;
        }
    first3 -> next = NULL;
    first3 -> count = 0;
    strcpy(first3 -> word, "\0");
    cell* table3 = (cell *)malloc(module * sizeof(cell));
    if(table3 == NULL)
        {
             return 1;
        }
    table3 -> key = 0;
    table3 -> element = first3;
    table3 -> next = NULL;
    createtable(table3, module - 1);
    start_time = clock();
    readfile(filename, table3, 'g');
    finish_time = clock();
    time = finish_time - start_time;
    printf("Hash function: good\n");
    statistics(table3);
    printf("Time of execution: %f\n\n", time/CLOCKS_PER_SEC);
    deletetable(table3);
    node* first1 = (node *)malloc(sizeof(node));
    if(first1 == NULL)
        {
             return 1;
        }
    first1 -> next = NULL;
    first1 -> count = 0;
    strcpy(first1 -> word, "\0");
    cell* table1 = (cell *)malloc(module * sizeof(cell));
    if(table1 == NULL)
        {
             return 1;
        }
    table1 -> key = 0;
    table1 -> element = first1;
    table1 -> next = NULL;
    createtable(table1, module - 1);
    start_time = clock();
    readfile(filename, table1, 's');
    finish_time = clock();
    time = finish_time - start_time;
    printf("Hash function: sum\n");
    statistics(table1);
    printf("Time of execution: %f\n\n", time/CLOCKS_PER_SEC);
    deletetable(table1);
    return 0;
}
