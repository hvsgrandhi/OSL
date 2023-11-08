#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    key_t key = ftok("/tmp", 'S'); // Generate a unique key for the shared memory segment
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a shared memory segment or open an existing one
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the server's address space
    char *shm = shmat(shmid, NULL, 0);
    if (shm == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Write a message to the shared memory
    char message[] = "Hello from the server!";
    strncpy(shm, message, SHM_SIZE);

    printf("Message sent to shared memory: %s\n", message);

    // Detach the shared memory segment
    shmdt(shm);

    return 0;
}
