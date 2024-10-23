#include "calculate.h"

#include <stdio.h>
#define PI 3.14159265358979323846
double calculate(char* rev_polish[], int n, int* invalid_operation) {
    struct stack* s = NULL;
    double res = 0;
    for (int i = 0; i < n && *invalid_operation == 0; ++i) {
        if (is_op(rev_polish[i]) != 1) {
            if (s == NULL)
                s = init(rev_polish[i]);
            else
                push(rev_polish[i], s);
        } else {
            if (is_binary(rev_polish[i])) {
                double a, b;
                sscanf(pop(s).val, "%lf", &a);
                sscanf(pop(s).val, "%lf", &b);
                if (strcmp(rev_polish[i], "+") == 0)
                    res = b + a;
                else if (strcmp(rev_polish[i], "-") == 0)
                    res = b - a;
                else if (strcmp(rev_polish[i], "*") == 0)
                    res = b * a;
                else if (strcmp(rev_polish[i], "/") == 0) {
                    if (a == 0)
                        *invalid_operation = 1;
                    else
                        res = b / a;
                }
            } else {
                double a;
                sscanf(pop(s).val, "%lf", &a);
                if (strcmp(rev_polish[i], "cos") == 0)
                    res = cos(a);
                else if (strcmp(rev_polish[i], "sin") == 0)
                    res = sin(a);
                else if (strcmp(rev_polish[i], "tan") == 0) {
                    if (fabs(a - PI / 2) < 1e-6)
                        *invalid_operation = 1;
                    else
                        res = tan(a);
                } else if (strcmp(rev_polish[i], "ctg") == 0) {
                    if (invalid_tan_arg(a))
                        *invalid_operation = 1;
                    else
                        res = 1.0 / tan(a);
                } else if (strcmp(rev_polish[i], "sqrt") == 0) {
                    if (a < 0)
                        *invalid_operation = 1;
                    else
                        res = sqrt(a);
                }
            }
            char sres[50];
            snprintf(sres, 50, "%0.2f", res);
            push(sres, s);
        }
        //	free(rev_polish[i]);
    }
    if (s != NULL) destroy(s);
    // free(rev_polish);
    return res;
}

int is_op(const char* s) {
    int res = 0;
    if (is_binary(s) || strcmp(s, "cos") == 0 || strcmp(s, "sin") == 0 || strcmp(s, "tan") == 0 ||
        strcmp(s, "ctg") == 0 || strcmp(s, "sqrt") == 0 || strcmp(s, "ln") == 0)
        res = 1;
    return res;
}

int is_binary(const char* s) {
    int res = 0;
    if (strcmp(s, "+") == 0 || strcmp(s, "-") == 0 || strcmp(s, "*") == 0 || strcmp(s, "/") == 0) res = 1;
    return res;
}
int invalid_tan_arg(double a) {
    int res = 0;
    while (a < 0) {
        a += PI;
    }
    while (a > PI) {
        a -= PI;
    }
    if (fabs(a - PI / 2) < 1e-2) res = 1;
    return res;
}
