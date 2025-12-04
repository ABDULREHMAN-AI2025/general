#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int category(char c) {
    if (c >= 'A' && c <= 'Z') return 1;
    if (c >= 'a' && c <= 'z') return 2;
    if (c >= '0' && c <= '9') return 3;
    return 4;
}

int main() {
    int n;
    printf("Enter number of participants: ");
    scanf("%d", &n);
    getchar();

    char **passwords = (char **)malloc(n * sizeof(char *));
    char *pattern = (char *)malloc(100);

    printf("Enter password pattern: ");
    fgets(pattern, 100, stdin);
    pattern[strcspn(pattern, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        passwords[i] = (char *)malloc(100);
        printf("Enter password attempt for participant %d: ", i + 1);
        fgets(passwords[i], 100, stdin);
        passwords[i][strcspn(passwords[i], "\n")] = '\0';
    }

    int maxIndex = 0;
    double maxScore = 0;

    printf("\nPassword Similarity Scores:\n");
    for (int i = 0; i < n; i++) {
        int match = 0;
        int len = strlen(passwords[i]);
        int patternLen = strlen(pattern);
        int compareLen = len < patternLen ? len : patternLen;

        for (int j = 0; j < compareLen; j++) {
            if (category(passwords[i][j]) == category(pattern[j]))
                match++;
        }

        double similarity = ((double)match / patternLen) * 100;
        printf("Participant %d: %s -> %.2f%%\n", i + 1, passwords[i], similarity);

        if (similarity > maxScore) {
            maxScore = similarity;
            maxIndex = i;
        }
    }

    printf("\nPassword with highest similarity: %s -> %.2f%%\n", passwords[maxIndex], maxScore);

    free(pattern);
    for (int i = 0; i < n; i++)
        free(passwords[i]);
    free(passwords);

    return 0;
}
