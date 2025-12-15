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
void deleteCD(cds **c, int *count); // Renamed function for clarity
void search(cds **c, int *count);
void update(cds **c, int *count);

int main()
{

    cds *c = NULL;
    int count = 0;

    // First attempt to add data
    addNew(&c, &count);
    
    // Attempt to delete a record
    deleteCD(&c, &count); 
    
    // Second attempt to add data
    if (count >= 0) // Changed to >= 0, as you can add even if empty
    {
        addNew(&c, &count);
    }
    
    // Attempt to search for data
    search(&c, &count);
    
    // Attempt to update data
    update(&c, &count);


    // Free memory before exiting
    if (c != NULL)
    {
        free(c);
        c = NULL;
    }

    return 0;
}

void addNew(cds **collectionPtr, int *currentCount)
{
    int numAdd;
    printf("Enter No of CDS to add: \n ");
    if (scanf("%d", &numAdd) != 1 || numAdd <= 0) {
        printf("Invalid number entered or nothing to add.\n");
        return;
    }
    
    clear_buffer(); // Clear buffer after scanf for numAdd

    int oldCount = *currentCount;
    int newCount = oldCount + numAdd;

    // The logic below is mostly correct for growing the array:
    cds *temp = (cds *)realloc(*collectionPtr, newCount * sizeof(cds));
    
    if (temp == NULL)
    {
        printf("Memory Doesnot Allocated \n ");
        exit(1);
    }

    *collectionPtr = temp; // CRITICAL: Update the main pointer in main()
    
    // Loop over only the newly added slots
    for (int i = oldCount; i < newCount; i++)
    {
        printf("\n--- CD #%d (Index %d) ---\n", i + 1, i);
        
        printf("Enter ID: ");
        scanf("%d", &(*collectionPtr)[i].ID);
        clear_buffer();
        
        printf("Enter title: ");
        fgets((*collectionPtr)[i].title, sizeof((*collectionPtr)[i].title), stdin);
        (*collectionPtr)[i].title[strcspn((*collectionPtr)[i].title, "\n")] = '\0';

        printf("Enter Artist Name: ");
        fgets((*collectionPtr)[i].artistName, sizeof((*collectionPtr)[i].artistName), stdin);
        (*collectionPtr)[i].artistName[strcspn((*collectionPtr)[i].artistName, "\n")] = '\0';

        printf("Enter no of Tracks \n ");
        scanf("%d",&(*collectionPtr)[i].numberOfTracks);
        clear_buffer();

        printf("Enter genre of the track \n");
        fgets((*collectionPtr)[i].genres, sizeof((*collectionPtr)[i].genres), stdin);
        (*collectionPtr)[i].genres[strcspn((*collectionPtr)[i].genres, "\n")] = '\0';
    }
    
    *currentCount = newCount; // Update the count in main()
    printf("CDs have Been added. Total: %d\n", *currentCount);
}

void deleteCD(cds **c, int *count) // Renamed for clarity
{
    if (*count == 0) {
        printf("Collection is empty. Nothing to delete.\n");
        return;
    }

    int id;
    // CRITICAL FIX B: Initialize to -1 (not found)
    int foundIndex = -1; 
    
    printf("Enter id you want to delete \n ");
    // CRITICAL FIX A: Added & for scanf
    scanf("%d", &id); 
    clear_buffer();
    
    for (int i = 0; i < *count; i++)
    {
        if ((*c)[i].ID == id)
        {
            foundIndex = i;
            break;
        }
    }

    // CRITICAL FIX C: Check for not found
    if (foundIndex == -1)
    {
        printf("Id not found!! \n ");
        return;
    }
    
    // Shifting loop is correct
    for (int i = foundIndex; i < *count - 1; i++)
    {
        (*c)[i] = (*c)[i + 1];
    }
    
    // CRITICAL FIX D: Correct decrement operation
    (*count)--; 

    int newCount = *count;

    if (newCount > 0)
    {
        cds *temp = (cds *)realloc(*c, newCount * sizeof(cds));
        if (temp != NULL)
        {
            // CRITICAL FIX E: Correctly update the main pointer
            *c = temp; 
        }
        // If realloc fails (temp == NULL), we keep the old pointer (*c) 
        // to prevent data loss, even though the block isn't shrunk.
    } else {
        // If the array is empty, free the memory entirely
        free(*c);
        *c = NULL;
    }

    printf("CD has Been Deleted !! Total: %d\n", *count);
}

void search(cds**c,int *count){
    if (*count == 0) {
        printf("Collection is empty. Nothing to search.\n");
        return;
    }
    clear_buffer(); // Ensure buffer is clean before fgets
    
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
        // CRITICAL FIX F: Use strcmp for string comparison
        if (strcmp((*c)[i].title, title) == 0 && strcmp((*c)[i].artistName, artistName) == 0)
        {
            printf("\n--- CD Found ---\n");
            printf("ID: %d \n ",(*c)[i].ID);
            printf("No of Tracks: %d \n ",(*c)[i].numberOfTracks);
            printf("Genres: %s \n ",(*c)[i].genres);
            found = 1;
        }
    }

    if (!found) {
        printf("No CD matched the search criteria.\n");
    }
}

void update(cds**c,int *count){
    if (*count == 0) {
        printf("Collection is empty. Nothing to update.\n");
        return;
    }
    
    int id;
    int foundIndex = -1;
    
    printf("Enter id you want to update \n ");
    // CRITICAL FIX H: Added & for scanf
    scanf("%d", &id); 
    clear_buffer();

    // 1. Search for the CD
    for (int i = 0; i < *count; i++) {
        if ((*c)[i].ID == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Error: ID %d not found for update.\n", id);
        return;
    }

    // 2. Modify the data (in place)
    printf("\n--- Updating CD (ID: %d) ---\n", id);
    
    // Example: Update Title
    printf("Enter NEW Title: ");
    fgets((*c)[foundIndex].title, sizeof((*c)[foundIndex].title), stdin);
    (*c)[foundIndex].title[strcspn((*c)[foundIndex].title, "\n")] = '\0';
    
    // Example: Update Number of Tracks
    printf("Enter NEW Number of Tracks: ");
    scanf("%d", &(*c)[foundIndex].numberOfTracks);
    clear_buffer();

    printf("CD ID %d updated successfully.\n", id);
}