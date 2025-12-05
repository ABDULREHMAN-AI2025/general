#include <stdio.h>

typedef struct item
{
    char name[10];
    char categroy;
    int quantity;
} item;

int main()
{
    int n;
    printf("Enter number of itemss \n ");
    scanf("%d", &n);

    item items[n];
    item *ptr = items;

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter item %d name: ", i + 1);
        scanf("%s", ptr[i].name);

        printf("Enter category: ");
        scanf("%s", ptr[i].categroy);

        printf("Enter quantity: ");
        scanf("%d", &ptr[i].quantity);
    }
    char searchCategory[20];
    int minQty;

    printf("\nEnter category to filter: ");
    scanf("%s", searchCategory);

    printf("Enter minimum quantity to filter: ");
    scanf("%d", &minQty);

    printf("\nItems matching filter:\n");

    item *p = items; // pointer navigation starts
    for (int i = 0; i < n; i++)
    {
        if (p->quantity >= minQty && strcmp(p->category, searchCategory) == 0)
        {
            printf("Name: %s, Category: %s, Quantity: %d\n", p->name, p->category, p->quantity);
        }
        p++; // move pointer to next item
    }

    

    return 0;
}