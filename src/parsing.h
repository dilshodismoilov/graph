#ifndef SRC_PARCER_H_
#define SRC_PARCER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TOKENS 200
#define MAX_TOKEN_LENGTH 50

void parse_string(const char *math_string, char *tokens[], int *len);
char *my_strdup(const char *s);
int is_digit(char c);
int is_alpha(char c);
int is_function(const char *token);

#endif
