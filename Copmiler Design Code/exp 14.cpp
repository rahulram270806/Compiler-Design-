#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1;

void reduce() {
    if (stack[top] == 'a' || stack[top] == 'b') {
        stack[top] = 'E';
        stack[top + 1] = '\0';
        printf("Reduce: E -> a/b\n");
    }

    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top] == 'E' &&
        (stack[top - 1] == '+' ||
         stack[top - 1] == '*' ||
         stack[top - 1] == '/')) {

        stack[top - 2] = 'E';
        top -= 2;
        stack[top + 1] = '\0';
        printf("Reduce: E -> E op E\n");
    }
}

int main() {
    int i;

    printf("SHIFT REDUCE PARSER\n");
    printf("Enter the input symbol: ");
    scanf("%49s", input);

    printf("\nStack\tInput\tAction\n");

    for (i = 0; input[i] != '\0'; i++) {
        stack[++top] = input[i];
        stack[top + 1] = '\0';

        printf("%s\t%s\tShift %c\n",
               stack, input + i + 1, input[i]);

        reduce();
    }

    if (top == 0 && stack[0] == 'E')
        printf("\nACCEPTED\n");
    else
        printf("\nREJECTED\n");

    return 0;
}