#include <stdio.h>

typedef struct gift
{
    char name[10];
    char type;
    int price;
    int quantity;

} gift;
int main()
{
    int n, i;

    printf("Enter no of  gifts \n ");
    scanf("%d", &n);

    gift g[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter name \n ");
        scanf("%s", g[i].name);

        printf("Enter type \n ");
        scanf(" %c", &g[i].type);

        printf("Enter price: ");
        scanf("%d", &g[i].price);

        printf("Enter quantity: ");
        scanf("%d", &g[i].quantity);
    }

    int expansiveGift = 0;
    int giftQuantity;

    for (int i = 0; i < n; i++)
    {
        if (g[i].price > expansiveGift)
        {
            expansiveGift = g[i].price;
        }
        if (g[i].quantity > giftQuantity)
        {
            giftQuantity = g[i].quantity;
        }
    }

    printf("The maximum quantity of gift is %d \n ",giftQuantity);
    printf("The most expensive gift is %d \n ",expansiveGift);
    
    

    printf("  \n ");
    

    



    return 0;
}