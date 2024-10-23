#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "revpolish.h"
#include "stack.h"

void print_result(char **result, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s ", result[i]);
    }
    printf("\n");
}
void test_reverse_polish() {
    int n = 17;

    char *expression1[] = {"1", "+", "2",   "*", "sqrt", "(", "sin", "(", "1",
                           ")", "+", "cos", "(", "1",    ")", ")",   ")"};
    char **result1 = reverse_polish(expression1, &n);
    print_result(result1, n);  // Expected: 3 4 2 * +

    for (int i = 0; i < n; i++) {
        free(result1[i]);
    }
    free(result1);
}

int main() {
    test_reverse_polish();
    return 0;
}
