#include <stdio.h>
#include <ctype.h>

int main()
{
    char a[10];
    int flag = 1, i = 1;

    printf("Enter an identifier: ");
    scanf("%9s", a);

    if (!isalpha(a[0]))
        flag = 0;

    while (a[i] != '\0')
    {
        if (!isdigit(a[i]) && !isalpha(a[i]))
        {
            flag = 0;
            break;
        }
        i++;
    }

    if (flag == 1)
        printf("Valid identifier");
    else
        printf("Not a valid identifier");

    return 0;
}