#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, TotalStock = 0, lowestIndex = 0;

    printf("Enter the number of book categories: ");
    scanf("%d", &n);

    int *ptr = (int *)malloc(n * sizeof(int));

    if (ptr == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter stock quantity for category %d: ", i + 1);
        scanf("%d", &ptr[i]);
        TotalStock += ptr[i];
        if (ptr[i] < ptr[lowestIndex]) {
            lowestIndex = i;
        }
    }

    float average = (float)TotalStock / n;

    printf("\nTotal Stock = %d\n", TotalStock);
    printf("Average Stock = %.2f\n", average);
    printf("Category with Lowest Stock is %d (Stock = %d)\n",
           lowestIndex + 1, ptr[lowestIndex]);

    int index, newValue;
    printf("\nEnter the category number you want to update: ");
    scanf("%d", &index);

    if (index >= 1 && index <= n) {
        printf("Enter new stock value: ");
        scanf("%d", &newValue);
        ptr[index - 1] = newValue;
        printf("Stock updated!\n");
    } else {
        printf("Invalid category!\n");
    }

    free(ptr);
    return 0;
}
