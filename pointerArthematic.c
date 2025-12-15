#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

typedef struct
{
    int ID;
    char title[100];
    char artistName[20];
    int numberOfTracks;
    char genres[50];
} cds;

void addNew(cds **c, int *count);
void deleteCD(cds **c, int *count); 
void search(cds **c, int *count);
void update(cds **c, int *count);

int main()
{

    cds *c = NULL;
    int count = 0;

    addNew(&c, &count);
    
    deleteCD(&c, &count); 
    
    if (count >= 0) 
    {
        addNew(&c, &count);
    }
    
    search(&c, &count); 
    update(&c, &count); 

    if (c != NULL)
    {
        free(c);
        c = NULL;
    }

    return 0;
}

// =======================================================
// === 1. addNew FUNCTION (MODIFIED) =====================
// =======================================================

void addNew(cds **collectionPtr, int *currentCount)
{
    int numAdd;
    printf("Enter No of CDS to add: \n ");
    if (scanf("%d", &numAdd) != 1 || numAdd <= 0) {
        printf("Invalid number entered or nothing to add.\n");
        return;
    }
    
    clear_buffer(); 

    int oldCount = *currentCount;
    int newCount = oldCount + numAdd;

    cds *temp = (cds *)realloc(*collectionPtr, newCount * sizeof(cds));
    
    if (temp == NULL)
    {
        printf("Memory Doesnot Allocated \n ");
        exit(1);
    }

    *collectionPtr = temp; 
    
    // Loop over only the newly added slots
    for (int i = oldCount; i < newCount; i++)
    {
        // Access: (*(*collectionPtr + i)).member
        
        printf("\n--- CD #%d (Index %d) ---\n", i + 1, i);
        
        // Accessing ID
        printf("Enter ID: ");
        scanf("%d", &(*(*collectionPtr + i)).ID);
        clear_buffer();
        
        // Accessing title
        printf("Enter title: ");
        fgets((*(*collectionPtr + i)).title, sizeof((*(*collectionPtr + i)).title), stdin);
        (*(*collectionPtr + i)).title[strcspn((*(*collectionPtr + i)).title, "\n")] = '\0';

        // Accessing artistName
        printf("Enter Artist Name: ");
        fgets((*(*collectionPtr + i)).artistName, sizeof((*(*collectionPtr + i)).artistName), stdin);
        (*(*collectionPtr + i)).artistName[strcspn((*(*collectionPtr + i)).artistName, "\n")] = '\0';

        // Accessing numberOfTracks
        printf("Enter no of Tracks \n ");
        scanf("%d",&(*(*collectionPtr + i)).numberOfTracks);
        clear_buffer();

        // Accessing genres
        printf("Enter genre of the track \n");
        fgets((*(*collectionPtr + i)).genres, sizeof((*(*collectionPtr + i)).genres), stdin);
        (*(*collectionPtr + i)).genres[strcspn((*(*collectionPtr + i)).genres, "\n")] = '\0';
    }
    
    *currentCount = newCount; 
    printf("CDs have Been added. Total: %d\n", *currentCount);
}

// =======================================================
// === 2. deleteCD FUNCTION (MODIFIED) ====================
// =======================================================

void deleteCD(cds **c, int *count)
{
    if (*count == 0) {
        printf("Collection is empty. Nothing to delete.\n");
        return;
    }

    int id;
    int foundIndex = -1; 
    
    printf("Enter id you want to delete \n ");
    scanf("%d", &id); 
    clear_buffer();
    
    // Search loop: Change (*c)[i].ID --> (*(*c + i)).ID
    for (int i = 0; i < *count; i++)
    {
        if ((*(*c + i)).ID == id)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        printf("Id not found!! \n ");
        return;
    }
    
    // Shifting loop: Uses explicit pointer arithmetic for assignment
    for (int i = foundIndex; i < *count - 1; i++)
    {
        // Assignment: *( *c + i ) = *( *c + (i + 1) )
        *(*c + i) = *(*c + (i + 1));
    }
    
    
    (*count)--; 

    int newCount = *count;

    if (newCount > 0)
    {
        cds *temp = (cds *)realloc(*c, newCount * sizeof(cds));
        if (temp != NULL)
        {
            *c = temp; 
        }
    } else {
        free(*c);
        *c = NULL;
    }

    printf("CD has Been Deleted !! Total: %d\n", *count);
}

// =======================================================
// === 3. search FUNCTION (MODIFIED) =====================
// =======================================================

void search(cds**c,int *count){
    if (*count == 0) {
        printf("Collection is empty. Nothing to search.\n");
        return;
    }
    clear_buffer(); 
    
    char title[100];
    char artistName[20];
    int found = 0;

    printf("Enter title to search\n ");
    fgets(title,sizeof(title),stdin);
    title[strcspn(title,"\n")]='\0';

    printf("Enter Artist Name to search\n ");
    fgets(artistName,sizeof(artistName),stdin);
    artistName[strcspn(artistName,"\n")]='\0';
    
    for (int i = 0; i < *count; i++)
    {
        // Accessing title and artistName using pointer arithmetic
        if (strcmp((*(*c + i)).title, title) == 0 && strcmp((*(*c + i)).artistName, artistName) == 0)
        {
            printf("\n--- CD Found ---\n");
            
            // Printing members using pointer arithmetic
            printf("ID: %d \n ",(*(*c + i)).ID);
            printf("No of Tracks: %d \n ",(*(*c + i)).numberOfTracks);
            printf("Genres: %s \n ",(*(*c + i)).genres);
            found = 1;
        }
    }

    if (!found) {
        printf("No CD matched the search criteria.\n");
    }
}

// =======================================================
// === 4. update FUNCTION (MODIFIED) =====================
// =======================================================

void update(cds**c,int *count){
    if (*count == 0) {
        printf("Collection is empty. Nothing to update.\n");
        return;
    }
    
    int id;
    int foundIndex = -1;
    
    printf("Enter id you want to update \n ");
    scanf("%d", &id); 
    clear_buffer();

    // 1. Search for the CD: Change (*c)[i].ID --> (*(*c + i)).ID
    for (int i = 0; i < *count; i++) {
        if ((*(*c + i)).ID == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Error: ID %d not found for update.\n", id);
        return;
    }

    // 2. Modify the data (in place) using the foundIndex and pointer arithmetic
    
    printf("\n--- Updating CD (ID: %d) ---\n", id);
    
    // Update Title
    printf("Enter NEW Title: ");
    fgets((*(*c + foundIndex)).title, sizeof((*(*c + foundIndex)).title), stdin);
    (*(*c + foundIndex)).title[strcspn((*(*c + foundIndex)).title, "\n")] = '\0';
    
    // Update Number of Tracks
    printf("Enter NEW Number of Tracks: ");
    scanf("%d", &(*(*c + foundIndex)).numberOfTracks);
    clear_buffer();

    printf("CD ID %d updated successfully.\n", id);
}