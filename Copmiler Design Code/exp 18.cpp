#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input;
int i = 0;
char lasthandle[6], stack[50];
char handles[][5] = {")E(", "E*E", "E+E", "i", "E^E"};
int top = 0, l;

char prec[9][9] = {
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    {'<', '<', '<', '<', '<', '<', '<', '>', 'e'},
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    {'<', '<', '<', '<', '<', '<', '<', '<', '>'}
};

int getindex(char c) {
    switch(c) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case 'i': return 5;
        case '(': return 6;
        case ')': return 7;
        case '$': return 8;
    }
    return 8;
}

void shift() {
    stack[++top] = input[i++];
    stack[top + 1] = '\0';
}

int reduce() {
    int j, len, found, t;

    for(j = 0; j < 5; j++) {
        len = strlen(handles[j]);

        if(top + 1 >= len &&
           stack[top] == handles[j][0]) {

            found = 1;

            for(t = 0; t < len; t++) {
                if(stack[top-t] != handles[j][t]) {
                    found = 0;
                    break;
                }
            }

            if(found) {
                stack[top-t+1] = 'E';
                top = top-t+1;
                strcpy(lasthandle, handles[j]);
                stack[top+1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

void dispstack() {
    int j;
    for(j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

void dispinput() {
    int j;
    for(j = i; j < l; j++)
        printf("%c", input[j]);
}

int main() {
    input = malloc(50);
    printf("Enter the string:\n");
    scanf("%49s", input);

    input = strcat(input, "$");
    l = strlen(input);
    strcpy(stack, "$");

    printf("\nSTACK\tINPUT\tACTION");

    while(i < l-1) {
        shift();

        printf("\n");
        dispstack();
        printf("\t");
        dispinput();
        printf("\tShift");

        if(prec[getindex(stack[top])]
              [getindex(input[i])] == '>') {

            while(reduce()) {
                printf("\n");
                dispstack();
                printf("\t");
                dispinput();
                printf("\tReduced: E->%s", lasthandle);
            }
        }
    }

    if(reduce()) {
        while(reduce());
    }

    if(strcmp(stack, "$E") == 0)
        printf("\nAccepted");
    else
        printf("\nNot Accepted");

    free(input);
    return 0;
}