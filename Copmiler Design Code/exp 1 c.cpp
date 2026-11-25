#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    int i, ic=0, cc=0, oc=0, j;
    char b[30], operators[30], identifiers[30], constants[30];

    printf("Enter the string: ");
    scanf("%[^\n]", b);

    for(i=0; i<strlen(b); i++)
    {
        if(isspace(b[i]))
            continue;

        else if(isalpha(b[i]))
            identifiers[ic++] = b[i];

        else if(isdigit(b[i]))
        {
            int m = b[i]-'0';

            while(isdigit(b[i+1]))
                m = m*10 + (b[++i]-'0');

            constants[cc++] = m;
        }
        else if(b[i]=='+' || b[i]=='-' ||
                b[i]=='*' || b[i]=='=')
            operators[oc++] = b[i];
    }

    printf("Identifiers: ");
    for(j=0; j<ic; j++)
        printf("%c ", identifiers[j]);

    printf("\nConstants: ");
    for(j=0; j<cc; j++)
        printf("%d ", constants[j]);

    printf("\nOperators: ");
    for(j=0; j<oc; j++)
        printf("%c ", operators[j]);

    return 0;
}