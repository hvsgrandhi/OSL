#include <stdio.h>

int n; // Number of processes
int m; // Number of resources

int max[10][10];       // Maximum resources needed by each process
int allocation[10][10]; // Resources currently allocated to each process
int need[10][10];      // Resources needed by each process
int available[10];     // Available resources

void input() {
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the resources currently allocated to each process:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
}

int checkSafety() {
    int finish[10] = {0};
    int work[10];
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int safeSeq[10];
    int count = 0;
    int flag;

    while (count < n) {
        flag = 0;
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            return 0; // Unsafe state
        }
    }

    printf("Safe sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d", safeSeq[i]);
        if (i < n - 1) {
            printf(" -> ");
        }
    }
    printf("\n");

    return 1; // Safe state
}

int requestResources(int pid, int request[]) {
    for (int i = 0; i < m; i++) {
        if (request[i] > need[pid][i] || request[i] > available[i]) {
            return 0; // Request exceeds maximum need or available resources
        }
    }

    for (int i = 0; i < m; i++) {
        available[i] -= request[i];
        allocation[pid][i] += request[i];
        need[pid][i] -= request[i];
    }

    if (checkSafety()) {
        return 1; // Request granted and system is still in a safe state
    } else {
        // Rollback the changes
        for (int i = 0; i < m; i++) {
            available[i] += request[i];
            allocation[pid][i] -= request[i];
            need[pid][i] += request[i];
        }
        return -1; // Request denied as it would lead to an unsafe state
    }
}

int main() {
    input();

    if (checkSafety()) {
        printf("System is in a safe state initially.\n");
    } else {
        printf("System is in an unsafe state initially. Aborting...\n");
        return 1;
    }

    int pid, request[10];
    printf("Enter the process ID for resource request: ");
    scanf("%d", &pid);
    printf("Enter the resource request for process %d: ", pid);
    for (int i = 0; i < m; i++) {
        scanf("%d", &request[i]);
    }

    int result = requestResources(pid, request);

    if (result == 1) {
        printf("Resource request granted.\n");
    } else if (result == -1) {
        printf("Resource request denied due to potential unsafe state.\n");
    } else {
        printf("Resource request denied. It exceeds maximum need or available resources.\n");
    }

    return 0;
}