#include <stdio.h>

int main() {
    int processCount, currentProcess, totalProcesses, time, remainingProcesses, flag = 0, timeQuantum;
    int waitingTime = 0, turnaroundTime = 0, arrivalTime[10], burstTime[10], remainingTime[10];

    // Input the total number of processes
    printf("Enter the total number of processes: ");
    scanf("%d", &totalProcesses);

    // Check for valid input range
    if (totalProcesses <= 0 || totalProcesses > 10) {
        printf("Invalid number of processes. Please enter a value between 1 and 10.\n");
        return 1;
    }

    remainingProcesses = totalProcesses;

    // Input arrival time and burst time for each process
    for (processCount = 0; processCount < totalProcesses; processCount++) {
        printf("Enter Arrival Time and Burst Time for Process %d:\n", processCount + 1);
        scanf("%d", &arrivalTime[processCount]);
        scanf("%d", &burstTime[processCount]);

        // Check for valid arrival time and burst time
        if (arrivalTime[processCount] < 0 || burstTime[processCount] <= 0) {
            printf("Invalid arrival time or burst time for Process %d. Please enter non-negative arrival time and positive burst time.\n", processCount + 1);
            return 1;
        }

        remainingTime[processCount] = burstTime[processCount];
    }

    // Input the time quantum
    printf("Enter the Time Quantum: ");
    scanf("%d", &timeQuantum);

    // Check for valid time quantum
    if (timeQuantum <= 0) {
        printf("Invalid time quantum. Please enter a positive value for the time quantum.\n");
        return 1;
    }

    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");

    for (time = 0, processCount = 0; remainingProcesses != 0;) {
        if (remainingTime[processCount] <= timeQuantum && remainingTime[processCount] > 0) {
            time += remainingTime[processCount];
            remainingTime[processCount] = 0;
            flag = 1;
        } else if (remainingTime[processCount] > 0) {
            remainingTime[processCount] -= timeQuantum;
            time += timeQuantum;
        }

        if (remainingTime[processCount] == 0 && flag == 1) {
            remainingProcesses--;
            printf("P[%d]\t|\t%d\t|\t%d\n", processCount + 1, time - arrivalTime[processCount], time - arrivalTime[processCount] - burstTime[processCount]);
            waitingTime += time - arrivalTime[processCount] - burstTime[processCount];
            turnaroundTime += time - arrivalTime[processCount];
            flag = 0;
        }

        if (processCount == totalProcesses - 1)
            processCount = 0;
        else if (arrivalTime[processCount + 1] <= time)
            processCount++;
        else
            processCount = 0;
    }

    // Calculate and display average waiting time and average turnaround time
    printf("\nAverage Waiting Time= %.2f\n", (float)waitingTime / totalProcesses);
    printf("Average Turnaround Time = %.2f\n", (float)turnaroundTime / totalProcesses);

    return 0;
}

// //output
// 7comp69@comp69:~$ gcc rr.c
// comp69@comp69:~$ ./a.out
// Enter Total Process:	 4
// Enter Arrival Time and Burst Time for Process 1:
// 0
// 5
// Enter Arrival Time and Burst Time for Process 2:
// 1
// 4
// Enter Arrival Time and Burst Time for Process 3:
// 2
// 2
// Enter Arrival Time and Burst Time for Process 4:
// 3
// 1
// Enter Time Quantum:	2

// Process	|Turnaround Time|Waiting Time

// P[3]	|	4	|	2
// P[4]	|	4	|	3
// P[2]	|	10	|	6
// P[1]	|	12	|	7

// Average Waiting Time= 4.50
// Average Turnaround Time = 7.50
