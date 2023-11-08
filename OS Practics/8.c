#include <stdio.h>
#include <stdlib.h>
int SSTF();
int SCAN();
int CLOOK();
int main()
{
    int ch, YN = 1, i, l, f;
    char F[10], s[25];
    for (i = 0; i < f; i++)
    {
        F[i] = -1;
    }
    do
    {
        // system("clear");
        printf("\n\n\t*********** MENU ***********");
        printf("\n\n\t1:SSTF\n\n\t2:SCAN\n\n\t3:CLOOK\n\n\t4:EXIT");
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            for (i = 0; i < f; i++)
            {
                F[i] = -1;
            }
            SSTF();
            break;
        case 2:
            for (i = 0; i < f; i++)
            {
                F[i] = -1;
            }
            SCAN();
            break;
        case 3:
            for (i = 0; i < f; i++)
            {
                F[i] = -1;
            }
            CLOOK();
            break;
        case 4:
            exit(0);
        }
        printf("\n\n\tDo u want to continue IF YES PRESS 1\n\n\tIF NO PRESS 0: ");
        scanf("%d", &YN);
    } while (YN == 1);
    return (0);
}
// SSTF Algorithm
int SSTF()
{
    int requestQueue[100];  // Array to store the disk requests
    int i, numRequests, totalHeadMovement = 0, initialHead, requestCount = 0;

    // Prompt the user to enter the number of requests
    printf("Enter the number of requests: ");
    scanf("%d", &numRequests);

    // Prompt the user to enter the request sequence
    printf("Enter the request sequence:\n");
    for (i = 0; i < numRequests; i++)
    {
        scanf("%d", &requestQueue[i]);
    }

    // Prompt the user to enter the initial head position
    printf("Enter initial head position: ");
    scanf("%d", &initialHead);

    while (requestCount != numRequests)
    {
        int minSeekDistance = 1000;  // Initialize with a large value
        int minSeekIndex;

        // Find the request with the minimum seek distance from the current head position
        for (i = 0; i < numRequests; i++)
        {
            int seekDistance = abs(requestQueue[i] - initialHead);

            if (seekDistance < minSeekDistance)
            {
                minSeekDistance = seekDistance;
                minSeekIndex = i;
            }
        }

        // Update the total head movement and current head position
        totalHeadMovement += minSeekDistance;
        initialHead = requestQueue[minSeekIndex];

        // Mark the selected request as serviced (set it to 1000, for example)
        requestQueue[minSeekIndex] = 1000;

        // Increment the request count
        requestCount++;
    }

    // Display the total head movement
    printf("Total head movement is %d\n", totalHeadMovement);

    return 0;
}

// SCAN Algorithm
int SCAN()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head position\n");
    scanf("%d", &initial);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    int index;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMoment = TotalHeadMoment + abs(size - RQ[i - 1] - 1);
        initial = size - 1;
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        TotalHeadMoment = TotalHeadMoment + abs(RQ[i + 1] - 0);
        initial = 0;
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    printf("Total head movement is %d", TotalHeadMoment);
    return 0;
}
// C-LOOK Algorithm
int CLOOK()
{
    int RQ[100], i, j, n, TotalHeadMoment = 0, initial, size, move;
    printf("Enter the number of Requests\n");
    scanf("%d", &n);
    printf("Enter the Requests sequence\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &RQ[i]);
    }
    printf("Enter initial head position\n");
    scanf("%d", &initial);
    printf("Enter total disk size\n");
    scanf("%d", &size);
    printf("Enter the head movement direction for high 1 and for low 0\n");
    scanf("%d", &move);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (RQ[j] > RQ[j + 1])
            {
                int temp;
                temp = RQ[j];
                RQ[j] = RQ[j + 1];
                RQ[j + 1] = temp;
            }
        }
    }
    int index;
    for (i = 0; i < n; i++)
    {
        if (initial < RQ[i])
        {
            index = i;
            break;
        }
    }
    if (move == 1)
    {
        for (i = index; i < n; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = 0; i < index; i++)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    else
    {
        for (i = index - 1; i >= 0; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
        for (i = n - 1; i >= index; i--)
        {
            TotalHeadMoment = TotalHeadMoment + abs(RQ[i] - initial);
            initial = RQ[i];
        }
    }
    printf("Total head movement is %d", TotalHeadMoment);
    return 0;
}
// Output:
// *********** MENU ***********
// 1:SSTF
// 2:SCAN
// 3:CLOOK
// 4:EXIT
// Enter your choice: 1
// Enter the number of Requests
// 50 8
// Enter the Requests sequence
// 176
// 79
// 34
// 60
// 92
// 1
// 41
// 114
// Enter initial head position
// 50
// Total head movement is 333
// Do u want to continue IF YES PRESS 1
// IF NO PRESS 0: 1
// *********** MENU ***********
// 1:SSTF
// 2:SCAN
// 3:CLOOK
// 4:EXIT
// Enter your choice: 2
// Enter the number of Requests
// 8
// Enter the Requests sequence
// 176
// 79
// 34
// 60
// 92
// 1
// 41
// 114
// Enter initial head position
// 50
// Enter total disk size
// 200
// Enter the head movement direction for high 1 and for low 0
// 1
// Total head movement is 347
// Do u want to continue IF YES PRESS 1
// IF NO PRESS 0: 1
// *********** MENU ***********
// 1:SSTF
// 2:SCAN
// 3:CLOOK
// 4:EXIT
// Enter your choice: 3
// Enter the number of Requests
// 8
// Enter the Requests sequence
// 178 6
// 79
// 34
// 60
// 92
// 1
// 41
// 114
// Enter initial head position
// 50
// Enter total disk size
// 200
// Enter the head movement direction for high 1 and for low 0
// 1
// Total head movement is 341
// Do u want to continue IF YES PRESS 1
// IF NO PRESS 0: 0