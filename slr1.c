#include <stdio.h>
#include <string.h>
int state[100];
char symbol[100];
int top = -1;
int action[12][6] = {
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 0, 999},
    {0, -2, 7, 0, -2, -2},
    {0, -4, -4, 0, -4, -4},
    {5, 0, 0, 4, 0, 0},
    {0, -6, -6, 0, -6, -6},
    {5, 0, 0, 4, 0, 0},
    {5, 0, 0, 4, 0, 0},
    {0, 6, 0, 0, 11, 0},
    {0, -1, 7, 0, -1, -1},
    {0, -3, -3, 0, -3, -3},
    {0, -5, -5, 0, -5, -5}};

int gotot[12][3] = {
    {1, 2, 3},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1},
    {8, 2, 3},
    {-1, -1, -1},
    {-1, 9, 3},
    {-1, -1, 10},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1},
    {-1, -1, -1}};

int getcol(char *input)
{
    if (strcmp(input, "id") == 0)
        return 0;
    if (strcmp(input, "+") == 0)
        return 1;
    if (strcmp(input, "*") == 0)
        return 2;
    if (strcmp(input, "(") == 0)
        return 3;
    if (strcmp(input, ")") == 0)
        return 4;
    if (strcmp(input, "$") == 0)
        return 5;
    return -1;
}

int gotocol(char ch)
{
    if (ch == 'E')
        return 0;
    if (ch == 'T')
        return 1;
    if (ch == 'F')
        return 2;
    return -1;
}

void push(char ch, int st)
{
    top++;
    symbol[top] = ch;
    state[top] = st;
}

void pop(int n)
{
    top -= n;
}

void print()
{
    int i;
    printf("Stack: ");
    for (i = 0; i <= top; i++)
        printf("%c%d ", symbol[i], state[i]);
    printf("\n");
}

int main()
{
    char input[100][10];
    int n, i = 0;

    printf("Enter number of tokens: ");
    scanf("%d", &n);

    printf("Enter tokens (id, +, *, (, )):\n");
    for (i = 0; i < n; i++)
        scanf("%9s", input[i]);

    strcpy(input[n], "$");
    i = 0;

    top = -1;
    push('$', 0);

    printf("\n%-20s %-15s %s\n",
           "Stack", "Input", "Action");

    while (1)
    {
        int st = state[top];
        int col = getcol(input[i]);

        if (col == -1)
        {
            printf("Invalid input\n");
            break;
        }

        int act = action[st][col];

        if (act == 999)
        {
            printf("String Accepted\n");
            break;
        }

        if (act > 0)
        {
            printf("Shift %d\n", act);
            push(input[i][0], act);
            i++;
            print();
        }
        else if (act < 0)
        {
            int prod = -act;
            char lhs;
            int len;

            switch (prod)
            {
            case 1:
                lhs = 'E';
                len = 3;
                printf("Reduce E -> E+T\n");
                break;

            case 2:
                lhs = 'E';
                len = 1;
                printf("Reduce E -> T\n");
                break;

            case 3:
                lhs = 'T';
                len = 3;
                printf("Reduce T -> T*F\n");
                break;

            case 4:
                lhs = 'T';
                len = 1;
                printf("Reduce T -> F\n");
                break;

            case 5:
                lhs = 'F';
                len = 3;
                printf("Reduce F -> (E)\n");
                break;

            case 6:
                lhs = 'F';
                len = 1;
                printf("Reduce F -> id\n");
                break;

            default:
                printf("Invalid reduction\n");
                return 0;
            }

            pop(len);

            st = state[top];
            int next = gotot[st][gotocol(lhs)];

            if (next == -1)
            {
                printf("Error\n");
                break;
            }

            push(lhs, next);
            print();
        }
        else
        {
            printf("String Rejected\n");
            break;
        }
    }

    return 0;
}
