#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PAGES 100
#define MAX_FRAMES 10

int pages[MAX_PAGES];   // Page reference sequence
int frames[MAX_FRAMES]; // Page frames
int page_faults = 0;

int page_count;  // Number of pages
int frame_count; // Frame size

// Initialize frames with -1 (invalid page)
void initializeFrames()
{
    for (int i = 0; i < frame_count; i++)
    {
        frames[i] = -1;
    }
}

// Display the current state of frames
void displayFrames()
{
    for (int i = 0; i < frame_count; i++)
    {
        if (frames[i] == -1)
        {
            printf("[ ] ");
        }
        else
        {
            printf("[%d] ", frames[i]);
        }
    }
    printf("\n");
}

// Check if a page is already in the frames
bool pageExistsInFrames(int page)
{
    for (int i = 0; i < frame_count; i++)
    {
        if (frames[i] == page)
        {
            return true;
        }
    }
    return false;
}

// First-Come, First-Served (FCFS) Page Replacement Algorithm
void fcfs()
{
    initializeFrames();

    int frame_index = 0;
    for (int i = 0; i < page_count; i++)
    {
        int page = pages[i];
        if (!pageExistsInFrames(page))
        {
            frames[frame_index] = page;
            page_faults++;
            frame_index = (frame_index + 1) % frame_count;
        }
        displayFrames();
    }
}

// Least Recently Used (LRU) Page Replacement Algorithm
void lru()
{
    initializeFrames();

    int frame_index = 0;
    int reference_count = 0;
    int least_recently_used[MAX_FRAMES];

    for (int i = 0; i < frame_count; i++)
    {
        least_recently_used[i] = reference_count++;
    }

    for (int i = 0; i < page_count; i++)
    {
        int page = pages[i];
        if (!pageExistsInFrames(page))
        {
            int lru_frame_index = 0;
            for (int j = 1; j < frame_count; j++)
            {
                if (least_recently_used[j] < least_recently_used[lru_frame_index])
                {
                    lru_frame_index = j;
                }
            }
            frames[lru_frame_index] = page;
            least_recently_used[lru_frame_index] = reference_count++;
            page_faults++;
        }
        else
        {
            for (int j = 0; j < frame_count; j++)
            {
                if (frames[j] == page)
                {
                    least_recently_used[j] = reference_count++;
                    break;
                }
            }
        }
        displayFrames();
    }
}

// Optimal Page Replacement Algorithm
void optimal()
{
    initializeFrames();

    for (int i = 0; i < page_count; i++)
    {
        int page = pages[i];
        if (!pageExistsInFrames(page))
        {
            int replace_index = -1;
            for (int j = 0; j < frame_count; j++)
            {
                if (frames[j] == -1)
                {
                    replace_index = j;
                    break;
                }
                for (int k = i + 1; k < page_count; k++)
                {
                    if (pages[k] == frames[j])
                    {
                        if (k > replace_index)
                        {
                            replace_index = k;
                        }
                        break;
                    }
                }
            }
            if (replace_index == -1)
            {
                replace_index = 0;
            }
            frames[replace_index] = page;
            page_faults++;
        }
        displayFrames();
    }
}

int main()
{
    printf("Enter the number of pages: ");
    scanf("%d", &page_count);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < page_count; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter the frame size (maximum %d): ", MAX_FRAMES);
    scanf("%d", &frame_count);

    if (frame_count > MAX_FRAMES)
    {
        printf("Frame size exceeds the maximum allowed.\n");
        return 1;
    }
    int choice;
    while(true){
        page_faults = 0;
        printf("\nPage Replacement Algorithms:\n");
        printf("1. First-Come, First-Served (FCFS)\n");
        printf("2. Least Recently Used (LRU)\n");
        printf("3. Optimal\n");
        printf("4. Exit\n");
        printf("Enter your choice (1/2/3/4): ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                fcfs();
                break;
            case 2:
                lru();
                break;
            case 3:
                optimal();
                break;
            case 4:
                printf("Exiting...\n\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

        if(choice == 4) break;
        printf("Total page faults: %d\n", page_faults);
    }

    return 0;
}
