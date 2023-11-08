#include <stdio.h>

// Structure to store process information
struct Process {
    int waitingTime;    // WT: Waiting Time
    int arrivalTime;    // AT: Arrival Time
    int burstTime;      // BT: Burst Time
    int turnaroundTime; // TAT: Turnaround Time
};

struct Process processes[10];

int main() {
    int i;
    int n, burstTimeCopy[10];
    int count = 0, time = 0, shortestProcess;
    float totalWaitingTime = 0, totalTurnaroundTime = 0, avgWaitingTime, avgTurnaroundTime;

    // Input the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    printf("Enter the arrival time and burst time for each process:\n");
    printf("ArrivalTime BurstTime\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        burstTimeCopy[i] = processes[i].burstTime; // Make a copy of burst time
    }

    processes[9].burstTime = 9999;

    for (time = 0; count != n; time++) {
        shortestProcess = 9;

        // Find the process with the shortest remaining burst time
        for (i = 0; i < n; i++) {
            if (processes[i].burstTime < processes[shortestProcess].burstTime && (processes[i].arrivalTime <= time && processes[i].burstTime > 0)) {
                shortestProcess = i;
            }
        }

        processes[shortestProcess].burstTime--;

        if (processes[shortestProcess].burstTime == 0) {
            count++;

            // Calculate turnaround time and waiting time
            processes[shortestProcess].turnaroundTime = time - processes[shortestProcess].arrivalTime + 1;
            processes[shortestProcess].waitingTime = processes[shortestProcess].turnaroundTime - burstTimeCopy[shortestProcess];

            // Update total times
            totalTurnaroundTime += processes[shortestProcess].turnaroundTime;
            totalWaitingTime += processes[shortestProcess].waitingTime;
        }
    }

    // Calculate average times
    avgTurnaroundTime = totalTurnaroundTime / n;
    avgWaitingTime = totalWaitingTime / n;

    // Display the process details and average times
    printf("Process    BurstTime    WaitingTime    TurnaroundTime\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, burstTimeCopy[i], processes[i].waitingTime, processes[i].turnaroundTime);
    }
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
}


// output
// comp55@comp55:~/Desktop/os$ gcc sjf.c
// comp55@comp55:~/Desktop/os$ ./a.out
// Enter the number of the process
// 4
// Enter the arrival time and burst time of the process
// AT WT
// 0 18
// 1 4
// 2 7
// 3 2
// Id     BT      WT      TAT
// 1	18	13	31
// 2	4	0	4
// 3	7	5	12
// 4	2	2	4
// Avg waiting time of the process is 5.000000
// Avg turn around time of the process 12.750000
