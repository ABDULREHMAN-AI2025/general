#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void nextLineRemover(char feedback[])
{
    for (int i = 0; feedback[i] != '\0'; i++)
    {
        if (feedback[i] == '\n')
        {
            feedback[i] = '\0';
            break;
        }
    }
}

int main()
{
    int n;
    printf("Enter no of feedback entries: ");
    scanf("%d", &n);
    getchar();

    char **ptr = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
        ptr[i] = (char *)malloc(50);

    int longestIndex = 0;

    for (int i = 0; i < n; i++)
    {
        printf("Enter your feedback: ");
        fgets(ptr[i], 50, stdin);

        nextLineRemover(ptr[i]);

        int count = 0;
        for (int j = 0; ptr[i][j] != '\0'; j++)
            count++;

        if (count > strlen(ptr[longestIndex]))
            longestIndex = i;
    }

    printf("\nAll feedbacks:\n");
    for (int i = 0; i < n; i++)
        printf("%s\n", ptr[i]);

    printf("\nThe longest feedback is: %s\n", ptr[longestIndex]);

    for (int i = 0; i < n; i++)
        free(ptr[i]);
    free(ptr);

    return 0;
}
