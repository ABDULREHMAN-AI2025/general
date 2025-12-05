#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int containsDigit(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') return 1;
    }
    return 0;
}

int main() {
    int n;
    printf("Enter number of usernames: ");
    scanf("%d", &n);

    char **ptr = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        ptr[i] = malloc(100);  // reserve fixed space for each username
        printf("Enter username %d: ", i + 1);
        scanf("%s", ptr[i]);
        ptr[i] = realloc(ptr[i], strlen(ptr[i]) + 1); // shrink to actual size
    }

    printf("\nValid Usernames:\n");
    for (int i = 0; i < n; i++) {
        if (!containsDigit(ptr[i])) {
            printf("%s\n", ptr[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        free(ptr[i]);
    }
    free(ptr);

    return 0;
}
