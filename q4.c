#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter number of movie categories: ");
    scanf("%d", &n);

    int *ratings = (int *)malloc(n * sizeof(int));
    if (ratings == NULL)
        return 1;

    for (int i = 0; i < n; i++) {
        printf("Enter rating count for category %d: ", i + 1);
        scanf("%d", &ratings[i]);
    }

    int total = 0, highestIndex = 0;
    for (int i = 0; i < n; i++) {
        total += ratings[i];
        if (ratings[i] > ratings[highestIndex])
            highestIndex = i;
    }

    float average = (float)total / n;
    printf("\nTotal ratings: %d\n", total);
    printf("Average ratings per category: %.2f\n", average);
    printf("Category with highest rating: %d (Ratings = %d)\n", highestIndex + 1, ratings[highestIndex]);

    int updateIndex, newValue;
    printf("\nEnter category number to update: ");
    scanf("%d", &updateIndex);

    if (updateIndex >= 1 && updateIndex <= n) {
        printf("Enter new rating count: ");
        scanf("%d", &newValue);
        ratings[updateIndex - 1] = newValue;
    }

    total = 0;
    highestIndex = 0;
    for (int i = 0; i < n; i++) {
        total += ratings[i];
        if (ratings[i] > ratings[highestIndex])
            highestIndex = i;
    }

    average = (float)total / n;
    printf("\nUpdated Total ratings: %d\n", total);
    printf("Updated Average ratings per category: %.2f\n", average);
    printf("Updated Category with highest rating: %d (Ratings = %d)\n", highestIndex + 1, ratings[highestIndex]);

    free(ratings);
    return 0;
}
