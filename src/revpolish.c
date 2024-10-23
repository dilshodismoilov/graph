#include "revpolish.h"

#include "stack.h"

int countBrackets(char **array, int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(array[i], "(") == 0 || strcmp(array[i], ")") == 0) {
            count += 1;
        }
    }
    return count;
}

int precedence(const char *op) {
    int result = 0;

    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) {
        result = 1;
    } else if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) {
        result = 2;
    } else if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "tan") == 0 ||
               strcmp(op, "ctg") == 0 || strcmp(op, "sqrt") == 0 || strcmp(op, "ln") == 0) {
        result = 3;
    }
    return result;
}

int is_operator(const char ch[]) {
    return (strcmp(ch, "+") == 0 || strcmp(ch, "-") == 0 || strcmp(ch, "*") == 0 || strcmp(ch, "/") == 0 ||
            strcmp(ch, "sin") == 0 || strcmp(ch, "cos") == 0 || strcmp(ch, "tan") == 0 ||
            strcmp(ch, "ctg") == 0 || strcmp(ch, "sqrt") == 0 || strcmp(ch, "ln") == 0);
}

char **reverse_polish(char **array, int *n) {
    struct stack *stack = init("(");

    int count_brackets = countBrackets(array, *n);

    int j = 0;
    char **result;
    result = malloc((*n - count_brackets) * sizeof(char *));
    for (int i = 0; i < (*n - count_brackets); i++) result[i] = malloc(50 * sizeof(char));

    for (int i = 0; i < *n; i++) {
        if (strcmp(array[i], "(") == 0) {
            push(array[i], stack);
        } else if (strcmp(array[i], ")") == 0) {
            while (strcmp(peek(stack).val, "(") != 0) {
                strncpy(result[j], pop(stack).val, 50 - 1);
                result[j][50 - 1] = '\0';
                j += 1;
            }

            pop(stack);

        } else if (is_operator(array[i])) {
            while (!is_empty(stack) && strcmp(peek(stack).val, "(") != 0 &&
                   precedence(array[i]) <= precedence(peek(stack).val)) {
                strncpy(result[j], pop(stack).val, 50 - 1);
                result[j][50 - 1] = '\0';
                j += 1;
            }
            push(array[i], stack);
        } else {
            strncpy(result[j], array[i], 50 - 1);
            result[j][50 - 1] = '\0';
            j += 1;
        }
        // free(array);
    }

    // while (!is_empty(stack)) {
    //     strcpy(result[j], pop(stack).val);
    //     j += 1;
    // }

    destroy(stack);
    // for (int i = 0; i < *n; i++) {
    //      free(array[i]);
    //
    // }
    // free(array);
    // array = NULL;
    *n = j;
    return result;
}
