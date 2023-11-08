#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to sort an array of integers (bubble sort in this example)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main() {
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    printf("Enter the integers to be sorted:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    pid_t child_pid = fork();

    if (child_pid == 0) {
        // Child process
        // Delay to demonstrate the orphan state
        sleep(2);
        printf("Child process ID: %d\n", getpid());
        printf("Sorting in child process...\n");
        bubbleSort(arr, n);
        printf("Child process sorted the integers.\n");
    } else if (child_pid > 0) {
        // Parent process
        // Delay to demonstrate the zombie state
        sleep(4);
        printf("Parent process ID: %d\n", getpid());
        printf("Parent process waiting for the child...\n");
        wait(NULL); // Wait for the child process to complete
        insertionSort(arr,n);
        printf("Parent process sorted the integers.\n");

        // Display the sorted integers
        printf("Sorted integers: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    }

    free(arr);
    return 0;
}
