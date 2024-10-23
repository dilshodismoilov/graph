#ifndef CALCULATE_H
#define CALCULATE_H

#include <math.h>

#include "stack.h"
double calculate(char *rev_polish[], int n, int *invalid_operation);
int is_op(const char *s);
int is_binary(const char *s);
int invalid_tan_arg(double a);
#endif
