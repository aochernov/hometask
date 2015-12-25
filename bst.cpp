#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct leaf
{
    int data;
    leaf *left;
    leaf *right;
};

int addtotree(leaf* root, int val)
{
    if(val < root -> data)
    {
        if(root -> left != NULL)
        {
            addtotree(root -> left, val);
        }
        else
        {
            leaf *l = (leaf*) malloc(sizeof(leaf));
            if(l == NULL)
            {
                return 1;
            }
            l -> right = NULL;
            l -> left = NULL;
            l -> data = val;
            root -> left = l;
        }
    }
    if(val > root -> data)
    {
        if(root -> right != NULL)
        {
            addtotree(root -> right, val);
        }
        else
        {
            leaf *l = (leaf*) malloc(sizeof(leaf));
            if(l == NULL)
            {
                return 1;
            }
            l -> right = NULL;
            l -> left = NULL;
            l -> data = val;
            root -> right = l;
        }
    }
}

int freealltree(leaf *root)
{
    if(root -> left != NULL)
    {
        freealltree(root -> left);
    }
    if(root -> right != NULL)
    {
        freealltree(root -> right);
    }
    free(root);
}

int transferroot(leaf *root, leaf *head)
{
    addtotree(head, root -> data);
    if(root -> left != NULL)
    {
        transferroot(root -> left, head);
    }
    if(root -> right != NULL)
    {
        transferroot(root -> right, head);
    }
}

int removefromtree(leaf* root, int val, leaf* ancestor, char side, leaf* head)
{
    if(val < root -> data)
    {
        removefromtree(root -> left, val, root, 'l', head);
    }
    if(val > root -> data)
    {
        removefromtree(root -> right, val, root, 'r', head);
    }
    if(val == root -> data)
    {
        if(root -> right == NULL && root -> left == NULL)
        {
            free(root);
            if(side == 'l')
            {
                ancestor -> left = NULL;
            }
            if(side == 'r')
            {
                ancestor -> right = NULL;
            }
        }
        else
        {
            if(side == 'l')
            {
                ancestor -> left = NULL;
            }
            if(side == 'r')
            {
                ancestor -> right = NULL;
            }
            if(root -> left != NULL)
            {
                transferroot(root -> left, head);
            }
            if(root -> right != NULL)
            {
                transferroot(root -> right, head);
            }
            freealltree(root);
        }
    }
}

int printtree(leaf *root)
{
    printf(" (%d:", root -> data);
    if(root -> left != NULL)
    {
        printtree(root -> left);
    }
    else
    {
        printf(" NULL,");
    }
    if(root -> right != NULL)
    {
        printtree(root -> right);
    }
    else
    {
        printf(" NULL");
    }
    printf(")");
}

int searchelement(leaf *root, int val)
{
    if(val < root -> data && root -> left != NULL)
    {
        searchelement(root -> left, val);
    }
    if(val > root -> data && root -> right != NULL)
    {
        searchelement(root -> right, val);
    }
    if(val < root -> data && root -> left == NULL)
    {
        printf("Not in tree\n");
    }
    if(val > root -> data && root -> right == NULL)
    {
        printf("Not in tree\n");
    }
    if(val == root -> data)
    {
        printf("In tree\n");
    }
}

int printmin(leaf *root)
{
    if(root -> left != NULL)
    {
        printmin(root -> left);
    }
    printf("%d ", root -> data);
    if(root -> right != NULL)
    {
        printmin(root -> right);
    }
}

int printmax(leaf *root)
{
    if(root -> right != NULL)
    {
        printmax(root -> right);
    }
    printf("%d ", root -> data);
    if(root -> left != NULL)
    {
        printmax(root -> left);
    }
}

int main()
{
    leaf* root = NULL;
    root = new leaf;
    char input = ' ';
    int number;
    printf("Please enter root value: ");
    scanf("%d", &(root -> data));
    printf("There is the list of commands:\na <number> - add an element to the tree\nr <number> - remove the element from the tree\ns <number> - search the element in the tree\np - print tree in format (a: b, c)\nm - list elements from min to max\nM - list elements from Max to min\nq - quit the programm\n");
    while(input != 'q')
    {
        scanf("%c", &input);
        if(input == 'a')
        {
            scanf("%d", &number);
            addtotree(root, number);
        }
        if(input == 'r')
        {
            scanf("%d", &number);
            removefromtree(root, number, root, 'c', root);
        }
        if(input == 'p')
        {
            printtree(root);
            printf("\n");
        }
        if(input == 's')
        {
            scanf("%d", &number);
            searchelement(root, number);
        }
        if(input == 'm')
        {
            printmin(root);
            printf("\n");
        }
        if(input == 'M')
        {
            printmax(root);
            printf("\n");
        }
    }
    freealltree(root);
}
