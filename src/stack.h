#ifndef STACK_H
#define STACK_H
#include <stdlib.h>
#include <string.h>
struct node {
    struct node *next;
    char val[50];
};

struct stack {
    struct node *top;
};

struct stack *init(const char *v);
void push(const char *v, struct stack *s);
struct node pop(struct stack *s);
void destroy(struct stack *s);
int is_empty(const struct stack *s);
struct node peek(const struct stack *s);

#endif
