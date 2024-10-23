#include <math.h>

#include "calculate.h"
#include "parsing.h"
#include "revpolish.h"
#include "stack.h"
#define HEIGHT 25
#define WIDTH 70
#define PI 3.14159265359

void populate(int a[HEIGHT][WIDTH], const char *s);
void display(const int a[HEIGHT][WIDTH]);
void init_graph(int a[HEIGHT][WIDTH]);
int input(char **s, FILE *stream);
void replace_x(char *s, double x_val);
int main()
{
    char *input_string = NULL;

    if (input(&input_string, stdin))
    {
        int graph[HEIGHT][WIDTH];
        init_graph(graph);
        populate(graph, input_string);
        display(graph);
    }
    else
    {
        printf("n/a");
        // free(input_string);
    }
    free(input_string);
    return 0;
}

void replace_x(char *s, double x_val)
{
    char x_val_string[50];
    snprintf(x_val_string, 50, "%0.6f", x_val);

    char res[256];
    int k = 0;
    for (int i = 0; s[i] != 0; ++i)
    {
        if (s[i] == 'x')
        {
            int j = 0;
            for (j = 0; x_val_string[j] != 0; ++j)
            {
                res[k + j] = x_val_string[j];
            }
            k += j;
        }
        else
        {
            res[k] = s[i];
            ++k;
        }
    }
    res[k] = 0;

    strcpy(s, res);
}

int input(char **s, FILE *stream)
{
    int res = 1;
    char line[256];
    char *ptr;
    fgets(line, 256, stream);
    ptr = strchr(line, '\n');
    if (ptr)
        *ptr = '\0';
    if (strlen(line) + 1 < 256)
    {
        ptr = realloc(*s, 256);
        if (ptr == NULL)
            res = 0;
        else
        {
            *s = ptr;
            strcpy(*s, line);
        }
    }
    return res;
}

void display(const int a[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (j != 0)
                printf(" ");
            if (a[i][j] == 1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

void populate(int a[HEIGHT][WIDTH], const char *s)
{
    double x = 0; // [0..4pi]
    double step = 4 * PI / WIDTH;

    while (x < 4 * PI)
    {
        int n;

        char temp[256];
        strcpy(temp, s);
        replace_x(temp, x);

        char *tokens[MAX_TOKENS];
        parse_string(temp, tokens, &n);
        // int temp_n = n;
        char **rev = reverse_polish(tokens, &n);
        // for(int i=0; i<n; ++i) {
        //     free(tokens[i]);
        // }

        int invalid_op = 0;
        double y = calculate(rev, n, &invalid_op);
        for (int i = 0; i < n; ++i)
        {
            free(tokens[i]);
        }
        for (int i = 0; i < n; ++i)
        {
            free(rev[i]);
        }
        free(rev);

        if (invalid_op == 0)
        {
            int ym = (int)round(12 - y / (2.0 / 25));
            int xm = (int)round(x / step);
            if (ym >= 0 && ym <= 24 && xm >= 0 && xm <= 79)
                a[ym][xm] = 1;
        }
        x += step;
    }
}

void init_graph(int a[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            a[i][j] = 0;
        }
    }
}
