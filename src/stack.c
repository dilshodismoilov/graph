#include "stack.h"

struct stack *init(const char *v) {
    struct node *x = malloc(sizeof(struct node));
    strcpy(x->val, v);
    x->next = NULL;
    struct stack *s = malloc(sizeof(struct stack));
    s->top = x;
    return s;
}

void push(const char *v, struct stack *s) {
    struct node *x = malloc(sizeof(struct node));
    strcpy(x->val, v);
    x->next = NULL;

    if (s->top == NULL) {
        s->top = x;
    } else {
        struct node *t = s->top;
        s->top = x;
        x->next = t;
    }
}

struct node pop(struct stack *s) {
    struct node *x = s->top;
    struct node res;
    res.next = NULL;
    if (x != NULL) {
        s->top = x->next;
        res = *x;
        free(x);
    }
    return res;
}

struct node peek(const struct stack *s) {
    struct node *x = s->top;
    struct node res;
    res.next = NULL;
    if (x != NULL) {
        res = *x;
    }
    return res;
}

void destroy(struct stack *s) {
    struct node *cur = s->top;
    struct node *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(s);
}

int is_empty(const struct stack *s) { return s->top == NULL; }
