#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 10

int module = 1;

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
        node* first = NULL;
        first = new node;
        first -> next = NULL;
        first -> count = 0;
        strcpy(first -> word, "\0");
        cell* newcell = (cell *)malloc(sizeof(cell));
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

void addtotable(cell *head, int key, char *string)
{
    for(int i = 0; i < key; i++)
    {
        head = head -> next;
    }
    addtolist(head -> element, string);
}

void printlist(node *head)
{
    printf("%s, ", head -> word);
    if(head -> next != NULL)
    {
        printlist(head -> next);
    }
}

void printtable(cell *head)
{
    printf("%d: ", head -> key);
    printlist(head -> element);
    printf("\n");
    if(head -> next != NULL)
    {
        printtable(head -> next);
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

void findelements(cell *head, int key)
{
    if(head -> key == key)
    {
        if(strcmp((head -> element) -> word, "\0") == 0)
        {
            printf("No element with this hash");
        }
        else
        {
            printlist(head -> element);
        }
    }
    else
    {
        findelements(head -> next, key);
    }
}

void removefromlist(node *ancestor, node *descendant, char *string)
{
    if(strcmp(descendant -> word, string) == 0)
    {
        ancestor -> next = descendant -> next;
        free(descendant);
    }
    else
    {
        removefromlist(descendant, descendant -> next, string);
    }
}

void removefromtable(cell *head, int key, char *string)
{
    if(key == head -> key)
    {
        if(strcmp((head -> element) -> word, string) == 0)
        {
            if((head -> element) -> next == NULL)
            {
                strcpy((head -> element) -> word, "\0");
                (head -> element) -> count = 0;
            }
            else
            {
                node *tmp;
                tmp -> next = (head -> element) -> next;
                free(head -> element);
                head -> element = tmp -> next;
                free(tmp);
            }
        }
        else
        {
            removefromlist(head -> element, (head -> element) -> next, string);
        }
    }
    else
    {
        removefromtable(head -> next, key, string);
    }
}

void statistics(cell *head)
{
    int *counter = (int *)malloc(module * sizeof(int));
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
        head = head -> next;
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

using namespace std;

int main()
{
    node* first = (node *)malloc(sizeof(node));
    first -> next = NULL;
    first -> count = 0;
    strcpy(first -> word, "\0");
    cell* table = (cell *)malloc(sizeof(cell));
    table -> key = 0;
    table -> element = first;
    table -> next = NULL;
    char input;
    int number, i;
    printf("There is the list of commands:\nc <number> - create new table\na <string> - add new word to table\nf <number> - find element by it's hash\nr <string> - remove the word from the table\np - print the table\nd - delete the table\ns - print the statistics\nt <file name> - number of words in text fil\nq - quit the programm\n");
    while(input != 'q')
    {
        scanf("%c", &input);
        if(input == 'c')
        {
            scanf("%d", &number);
            module = number;
            createtable(table, number - 1);
        }
        if(input == 'a')
        {
            char input[MAX_LENGTH], space;
            scanf("%c", &space);
            gets(input);
            int length, hash = 0;
            length = strlen(input);
            for(i = 0; i < length; i++)
            {
                hash = hash + input[i];
            }
            hash = hash % module;
            addtotable(table, hash, input);
        }
        if(input == 'r')
        {
            char input[MAX_LENGTH], space;
            scanf("%c", &space);
            gets(input);
            int length, hash = 0;
            length = strlen(input);
            for(i = 0; i < length; i++)
            {
                hash = hash + input[i];
            }
            hash = hash % module;
            removefromtable(table, hash, input);
        }
        if(input == 'p')
        {
            printtable(table);
        }
        if(input == 'd')
        {
            module = 1;
            deletetable(table -> next);
            table -> next = NULL;
            if((table -> element) -> next != NULL)
            {
                deletelist((table -> element) -> next);
            }
            (table -> element) -> next = NULL;
            strcpy((table -> element) -> word, "\0");
            (table -> element) -> count = 0;
        }
        if(input == 'f')
        {
            scanf("%d", &number);
            findelements(table, number);
            printf("\n");
        }
        if(input == 's')
        {
            statistics(table);
        }
    }
    deletetable(table);
    return 0;
}
