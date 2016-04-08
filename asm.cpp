#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INST_NUMB 10000
#define MEM_SIZE 262144
#define BAD_INSTR -1
#define RET_INSTR 0
#define LD_INSTR 1
#define ST_INSTR 2
#define LDC_INSTR 3
#define ADD_INSTR 4
#define SUB_INSTR 5
#define CMP_INSTR 6
#define JMP_INSTR 7
#define BR_INSTR 8
#define LABEL_LENGTH 6
#define COMMAND_LENGTH 100

using namespace std;
bool error = false, run = true;
int j, currentinstruction = 0, sp = -1;

struct instruction
{
    int type;
    union
    {
        int number;
        size_t address;
        char label[LABEL_LENGTH];
    }
    arg;
};

struct node
{
    int number;
    char label[LABEL_LENGTH];
    node* next;
};

int add_to_label_list (node *prev, int val, char mark[LABEL_LENGTH])
{
    while (prev -> next != 0)
    {
        if (strcmp (prev -> label, mark) == 0)
        {
            run = false;
            error = true;
            printf ("Error. Label \"%s\" is already used.", mark);
        }
        prev = prev -> next;
    }
    node *n = (node*) malloc (sizeof (node));
    if (n == NULL)
    {
        error = true;
        run = false;
        return 1;
    }
    if(n != 0)
    {
        n -> number = val;
        strcpy (n -> label, mark);
        n -> next = NULL;
        prev -> next = n;
    }
}

int getprogrammnumber (node *head, char instr_label[LABEL_LENGTH])
{
    if (strcmp (instr_label, head -> label) == 0)
    {
        return head -> number;
    }
    else
    {
        if (head -> next != NULL)
        {
            getprogrammnumber (head -> next, instr_label);
        }
        else
        {
            return -1;
        }
    }
}

int load_programm (FILE *instr_file, node *head, instruction *instr)
{
    char command[COMMAND_LENGTH];
    int number;
    while (!feof (instr_file))
    {
        fscanf(instr_file, "%s", &command);
        int q = 1;
        while (command[q] != '\0')
        {
            if (command[q] == ';')
            {
                command[q] = 0;
                char comment[COMMAND_LENGTH];
                fgets(comment, COMMAND_LENGTH, instr_file);
                break;
            }
            if (command[q] == ':')
            {
                if (command[q + 1] == 0)
                {
                    command[q] = 0;
                    if (strlen (command) < LABEL_LENGTH)
                    {
                        add_to_label_list (head, j, command);
                        fscanf(instr_file, "%s", &command);
                    }
                    else
                    {
                        error = true;
                        run = false;
                        printf("Wrong label \"%s\"\n", command);
                    }
                }
                else
                {
                    int p = 0;
                    char labelname[LABEL_LENGTH];
                    while (command[p] != '\0')
                    {
                        if (p < q)
                        {
                            labelname[p] = command[p];
                        }
                        if (p == q)
                        {
                            labelname[p] = 0;
                        }
                        command[p] = command[q + p + 1];
                        if (command[p] == 0)
                        {
                            break;
                        }
                        p++;
                    }
                    add_to_label_list (head, j, labelname);
                }
                break;
            }
            q++;
        }
        if (strcmp (command, "ldc") == 0)
        {
            instr[j].type = LDC_INSTR;
            fscanf (instr_file, "%d", &number);
            instr[j].arg.number = number;
            j++;
        }
        else if (strcmp (command, "ld") == 0)
        {
            instr[j].type = LD_INSTR;
            fscanf (instr_file, "%d", &number);
            instr[j].arg.address = number;
            j++;
        }
        else if (strcmp (command, "st") == 0)
        {
            instr[j].type = ST_INSTR;
            fscanf(instr_file, "%d", &number);
            instr[j].arg.address = number;
            j++;
        }
        else if (strcmp (command, "add") == 0)
        {
            instr[j].type = ADD_INSTR;
            j++;
        }
        else if (strcmp (command, "sub") == 0)
        {
            instr[j].type = SUB_INSTR;
            j++;
        }
        else if (strcmp (command, "cmp") == 0)
        {
            instr[j].type = CMP_INSTR;
            j++;
        }
        else if (strcmp (command, "jmp") == 0)
        {
            instr[j].type = JMP_INSTR;
            fscanf (instr_file, "%s", &command);
            int q = 0;
            while (command[q] != '\0')
            {
                if (command[q] == ';')
                {
                    command[q] = 0;
                    char comment[COMMAND_LENGTH];
                    fgets(comment, COMMAND_LENGTH, instr_file);
                    break;
                }
                q++;
            }
            if (strlen (command) < LABEL_LENGTH && strlen (command) != 0)
            {
                strcpy (instr[j].arg.label, command);
                j++;
            }
            else
            {
                error = true;
                run = false;
                printf("Wrong label \"%s\"\n", command);
            }
            strcpy (instr[j].arg.label, command);
            j++;
        }
        else if (strcmp(command, "br") == 0)
        {
            instr[j].type = BR_INSTR;
            fscanf(instr_file, "%s", &command);
            int q = 0;
            while (command[q] != '\0')
            {
                if (command[q] == ';')
                {
                    command[q] = 0;
                    char comment[COMMAND_LENGTH];
                    fgets(comment, COMMAND_LENGTH, instr_file);
                    break;
                }
                q++;
            }
            if (strlen (command) < LABEL_LENGTH && strlen (command) != 0)
            {
                strcpy (instr[j].arg.label, command);
                j++;
            }
            else
            {
                error = true;
                run = false;
                printf ("Wrong label \"%s\"\n", command);
            }
        }
        else if (strcmp (command, "ret") == 0)
        {
            instr[j].type = RET_INSTR;
            j++;
        }
        else if (command[0] == ';')
        {
            fgets (command, 100, instr_file);
        }
        else
        {
            bool is_label = false;
            int q = 0;
            while (command[q] != '\0')
            {

                q++;
            }
            if (is_label == false)
            {
                run = false;
                error = true;
                printf ("Unknown command \"%s\"\n", command);
            }
        }
        if (j == INST_NUMB)
        {
            printf ("Error. Too many commands.\n");
            break;
        }
    }
}

int run_programm (instruction *instr, node *head, int *stack, int *memory)
{
    int number;
    while (run == true && error == false)
    {
        switch (instr[currentinstruction].type)
        {
            case LD_INSTR:
                sp++;
                stack[sp] = memory[instr[currentinstruction].arg.address];
                currentinstruction++;
                break;
            case ST_INSTR:
                if (sp == -1)
                {
                    printf ("Error. No number in stack.\n");
                    error = true;
                    run = false;
                }
                else
                {
                    memory[instr[currentinstruction].arg.address] = stack[sp];
                    sp--;
                }
                currentinstruction++;
                break;
            case LDC_INSTR:
                sp++;
                stack[sp] = instr[currentinstruction].arg.number;
                currentinstruction++;
                break;
            case ADD_INSTR:
                if (sp == 0)
                {
                    printf("Error. Only one number in stack.\n");
                    run = false;
                    error = true;
                }
                else
                {
                    stack[sp - 1] = stack[sp] + stack[sp - 1];
                    sp--;
                }
                currentinstruction++;
                break;
            case SUB_INSTR:
                if (sp == 0)
                {
                    printf("Error. Only one number in stack.\n");
                    run = false;
                    error = true;
                }
                else
                {
                    stack[sp - 1] = stack[sp] - stack[sp - 1];
                    sp--;
                }
                currentinstruction++;
                break;
            case CMP_INSTR:
                if (sp == 0)
                {
                    printf("Error. Only one number in stack.\n");
                    run = false;
                    error = true;
                }
                else
                {
                    if (stack[sp] > stack[sp - 1])
                    {
                        stack[sp - 1] = 1;
                    }
                    else if (stack[sp] < stack[sp - 1])
                    {
                        stack[sp - 1] = -1;
                    }
                    else
                    {
                        stack[sp - 1] = 0;
                    }
                    sp--;
                }
                currentinstruction++;
                break;
            case JMP_INSTR:
                number = getprogrammnumber (head, instr[currentinstruction].arg.label);
                if (number == -1)
                {
                    printf ("Error. Label \"%s\" does not exist.\n", instr[currentinstruction].arg.label);
                    run = false;
                    error = true;
                }
                else
                {
                    currentinstruction = number;
                }
                break;
            case BR_INSTR:
                if (stack[sp] != 0)
                {
                    number = getprogrammnumber (head, instr[currentinstruction].arg.label);
                    if (number == -1)
                    {
                        printf ("Error. Label \"%s\" does not exist.\n", instr[currentinstruction].arg.label);
                        run = false;
                        error = true;
                    }
                    else
                    {
                        currentinstruction = number;
                    }
                }
                else
                {
                    currentinstruction++;
                }
                break;
            case RET_INSTR:
                run = false;
                break;
            case BAD_INSTR:
                printf ("Error. Incorrect instruction in line %d.\n", currentinstruction);
                run = false;
                error = true;
                break;
        }
    }
}

int main()
{
    int *memory, *stack;
    memory = (int*) malloc (MEM_SIZE * sizeof (int));
    if (memory == NULL)
    {
        printf("Error. Noth enough memory for creating memory of virtual machine.\n");
        error = true;
        run = false;
        return 1;
    }
    stack = (int*) malloc (MEM_SIZE * sizeof (int));
    if (stack == NULL)
    {
        printf("Error. Noth enough memory for creating stack of virtual machine.\n");
        error = true;
        run = false;
        return 1;
    }
    instruction instr[INST_NUMB];
    int i;
    for (i = 0; i < INST_NUMB; i++)
    {
        instr[i].type = BAD_INSTR;
        instr[i].arg.address = -1;
    }
    char command[COMMAND_LENGTH], input;
    node* head = NULL;
    head = new node;
    head -> next = NULL;
    head -> number = -1;
    strcpy(head -> label, " ");
    FILE *instr_file = fopen ("instructions.txt", "r");
    if (instr_file == NULL)
    {
        printf("Error. Wrong file.\n");
        error = true;
        run = false;
        return 1;
    }
    else
    {
        load_programm (instr_file, head, instr);
        fclose (instr_file);
    }
    if (j == INST_NUMB - 1 && instr[INST_NUMB].type != 0)
    {
        error = true;
        run = false;
        printf("Error. The programm has no correct finish.\n");
    }
    run_programm (instr, head, stack, memory);
    if (run == false && error == false)
    {
        if (sp != -1)
            {
                printf ("Programm successfully executed. Result is %d.\n", stack[sp]);
            }
        else
            {
                printf ("Programm successfully executed. No numbers in stack.\n");
            }
    }
    free (memory);
    free (stack);
}
