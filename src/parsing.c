#include "parsing.h"

char *my_strdup(const char *s) {
    char *dup = malloc(strlen(s) + 1);  // +1 для нуль-терминатора
    if (dup) {
        strcpy(dup, s);
    }
    return dup;
}

//функция проверки пробелов
int is_space(char c) { return c == ' ' || c == '\t' || c == '\n'; }

//является ли символ цифрой
int is_digit(char c) { return (c >= '0' && c <= '9'); }

//является ли символ буквой
int is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

//является ли токен функцией
int is_function(const char *token) {
    const char *functions[] = {"sin", "cos", "tan", "ln", "sqrt", "ctg"};
    for (unsigned int i = 0; i < sizeof(functions) / sizeof(functions[0]); i++) {
        if (strcmp(token, functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void parse_string(const char *math_string, char *tokens[], int *len) {
    // char *token = strtok(math_string, " ");
    // *len = 0;
    int token_count = 0;
    char current_num[MAX_TOKEN_LENGTH] = "";
    char current_func[MAX_TOKEN_LENGTH] = "";
    unsigned int i = 0;

    while (math_string[i] != '\0') {
        char ch = math_string[i];

        //если символ это цифра или точка, накапливаем число
        if (is_digit(ch) || ch == '.') {
            strncat(current_num, &ch, 1);
        }
        //если символ буква
        else if (is_alpha(ch)) {
            strncat(current_func, &ch, 1);
            if (ch == 'x') {
                tokens[token_count++] = my_strdup(current_func);
                current_func[0] = '\0';
            }
            if (is_function(current_func) && math_string[i + 1] == '(') {
                tokens[token_count++] = my_strdup(current_func);
                current_func[0] = '\0';  // Сброс
            }
        }
        //если это оператор или скобка
        else {
            //накопленное число добавляем в массив
            if (strlen(current_num) > 0) {
                tokens[token_count++] = my_strdup(current_num);
                current_num[0] = '\0';
            }
            //добавляем оператор скобку или минус
            if (ch == '-' && (i == 0 || math_string[i - 1] == '(' || is_space(math_string[i - 1]))) {
                strncat(current_num, &ch, 1);
            } else if (ch != ' ' && ch != '\n') {
                if (ch == '(') {
                    tokens[token_count++] = my_strdup("(");

                } else if (ch == ')') {
                    tokens[token_count++] = my_strdup(")");

                } else {
                    const char op[2] = {ch, '\0'};
                    tokens[token_count++] = my_strdup(op);
                }
            }
        }
        i++;
    }

    //добавляем последнее число или функцию
    if (strlen(current_num) > 0) {
        tokens[token_count++] = my_strdup(current_num);
    }
    if (strlen(current_func) > 0) {
        tokens[token_count++] = my_strdup(current_func);
    }

    tokens[token_count] = ")";
    *len = token_count + 1;
}
