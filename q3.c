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

    char **users = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char temp[100];
        printf("Enter username %d: ", i + 1);
        scanf("%s", temp);

        users[i] = malloc(strlen(temp) + 1);
        strcpy(users[i], temp);
    }

    printf("\nValid Usernames:\n");
    for (int i = 0; i < n; i++) {
        if (!containsDigit(users[i])) {
            printf("%s\n", users[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        free(users[i]);
    }
    free(users);

    return 0;
}
