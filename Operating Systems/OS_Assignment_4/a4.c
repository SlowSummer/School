#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_REF_STRING_LENGTH 20
#define MAX_PAGE_NUMBER 5

// function to generate a random reference string
void generateReferenceString(int *refString, int length) 
{
    //seed rand with time
    srand(time(NULL));

    for (int i = 0; i < length; i++) 
    {
        refString[i] = (rand() % MAX_PAGE_NUMBER) + 1;
    }
}

// function to print the reference string
void printReferenceString(int *refString, int length) 
{
    printf("Reference String: ");

    for (int i = 0; i < length; i++)
    {
        printf("%d ", refString[i]);
    }
    printf("\n");
}

// function to check if a page is in memory
int isPageInMemory(int *memory, int numFrames, int page) 
{
    for (int i = 0; i < numFrames; i++) 
    {
        if (memory[i] == page) 
        {
            return 1;
        }
    }

    return 0;
}

// function to find the index of the page to be replaced in the Optimal algorithm
int findOptimalIndex(int *memory, int numFrames, int *refString, int length, int currentIndex) 
{
    int farthest = currentIndex;
    int index = -1;

    for (int i = 0; i < numFrames; i++) 
    {
        int j;
        for (j = currentIndex; j < length; j++) 
        {
            if (memory[i] == refString[j]) 
            {
                if (j > farthest) 
                {
                    farthest = j;
                    index = i;
                }

                break;
            }
        }

        if (j == length) 
        {
            return i;
        }
    }

    return (index == -1) ? 0 : index;
}

// function to find the index of the page to be replaced in the LRU algorithm
int findLRUIndex(int *memory, int numFrames, int *lastUsed, int currentIndex) 
{
    int lruIndex = 0;

    for (int i = 1; i < numFrames; i++) 
    {
        if (lastUsed[i] < lastUsed[lruIndex]) 
        {
            lruIndex = i;
        }
    }

    return lruIndex;
}

// optimal page replacement algorithm
int optimalPageReplacement(int *refString, int length, int numFrames) 
{
    int memory[numFrames];

    //populate memory with -1 as unused space
    for (int i = 0; i < numFrames; i++) 
    {
        memory[i] = -1;
    }

    int pageFaults = 0;

    for (int i = 0; i < length; i++) 
    {
        if (!isPageInMemory(memory, numFrames, refString[i])) 
        {
            int replaceIndex = (i < numFrames) ? i : findOptimalIndex(memory, numFrames, refString, length, i);
            memory[replaceIndex] = refString[i];
            pageFaults++;
        }

        printf("Optimal - Memory: ");
        
        //print memory
        for (int j = 0; j < numFrames; j++) 
        {
            printf("%d ", memory[j]);
        }

        printf("\n");
    }

    return pageFaults;
}

// LRU algorithm
int lruPageReplacement(int *refString, int length, int numFrames) 
{
    int memory[numFrames];
    int lastUsed[numFrames];

    //populate memory and lastUsed with -1 as unused space
    for (int i = 0; i < numFrames; i++) 
    {
        memory[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0;

    for (int i = 0; i < length; i++) 
    {
        if (!isPageInMemory(memory, numFrames, refString[i])) 
        {
            int replaceIndex = (i < numFrames) ? i : findLRUIndex(memory, numFrames, lastUsed, i);

            memory[replaceIndex] = refString[i];
            pageFaults++;
        }

        for (int j = 0; j < numFrames; j++) 
        {
            if (memory[j] == refString[i]) 
            {
                lastUsed[j] = i;
            }
        }

        printf("LRU - Memory: ");

        //print memory
        for (int j = 0; j < numFrames; j++) 
        {
            printf("%d ", memory[j]);
        }

        printf("\n");
    }

    return pageFaults;
}

int main()
{
    int refString[MAX_REF_STRING_LENGTH];
    int length = MAX_REF_STRING_LENGTH;
    int numFrames;

    // generate random string
    generateReferenceString(refString, length);
    printReferenceString(refString, length);

    // enter number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // run optimal page replacement and lru algorithms
    int optimalPageFaults = optimalPageReplacement(refString, length, numFrames);
    int lruPageFaults = lruPageReplacement(refString, length, numFrames);

    // print page number of faults 
    printf("Optimal Page Faults: %d\n", optimalPageFaults);
    printf("LRU Page Faults: %d\n", lruPageFaults);

    return 0;
}
